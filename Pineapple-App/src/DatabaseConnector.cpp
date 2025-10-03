#include "DatabaseConnector.h"
#include <iostream>


DatabaseConnector::DatabaseConnector() : stopThread_(false)
{
    workerThread_ = std::thread(&DatabaseConnector::runWorker, this);
}

DatabaseConnector::~DatabaseConnector()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        stopThread_ = true;
        cv_.notify_all();
    }
    if (workerThread_.joinable())
    {
        workerThread_.join();
    }
}

void DatabaseConnector::connect(const std::string &dsn, const std::string &user, const std::string &pass, long timeout)
{
    enqueueTask([this, dsn, user, pass, timeout]() {
        try
        {
            // Try nanodbc's standard DSN-based connect first
            connection_ = nanodbc::connection(dsn, user, pass, timeout);
            std::cout << "[DB] Connected successfully to DSN: " << dsn << "\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "[DB] Initial connection failed: " << e.what() << "\n";

            // Fallback: try DSN-only connect (some drivers ignore user/pass and get it from odbc.ini)
            try
            {
                connection_ = nanodbc::connection(dsn);
                std::cout << "[DB] Connected using DSN only (likely using odbc.ini credentials).\n";
            }
            catch (const std::exception &e2)
            {
                std::cerr << "[DB] DSN-only connection failed: " << e2.what() << "\n";
            }
        }
    });
}
void DatabaseConnector::disconnect()
{
    // Enqueue the actual disconnect task first
    enqueueTask([this]() {
        if (connection_.has_value())
        {
            if (connection_->connected())
            {
                try
                {
                    connection_->disconnect();
                    std::cout << "[DB] Disconnected successfully.\n";
                }
                catch (const std::exception &e)
                {
                    std::cerr << "[DB] Disconnect error: " << e.what() << "\n";
                }
            }
            connection_.reset();
        }
        else
        {
            std::cout << "[DB] No active connection to disconnect.\n";
        }
    });

    // Signal the worker thread to stop after finishing current tasks
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        stopThread_ = true;
        cv_.notify_all();
    }

    // Join the worker thread here to ensure it actually terminates
    if (workerThread_.joinable())
    {
        workerThread_.join();
        std::cout << "[DB] Worker thread stopped.\n";
    }
}


DBResult DatabaseConnector::executeRawSQL(const std::string &sql)
{
    auto prom = std::make_shared<std::promise<DBResult>>();
    auto fut = prom->get_future();

    enqueueTask([this, sql, prom]() {
        if (!connection_.has_value() || !connection_->connected())
        {
            std::cerr << "[DB] No active connection.\n";
            prom->set_value(DBResult{});
            return;
        }
        try
        {
            nanodbc::result r = nanodbc::execute(*connection_, sql);
            DBResult result(r);
            prom->set_value(std::move(result));
        }
        catch (const std::exception &e)
        {
            std::cerr << "[DB] Query error: " << e.what() << "\n";
            prom->set_value(DBResult{});
        }
    });

    return fut.get();
}


void DatabaseConnector::enqueueTask(Task task)
{
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        taskQueue_.push(std::move(task));
    }
    cv_.notify_one();
}

void DatabaseConnector::runWorker()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        cv_.wait(lock, [this] { return stop_flag_ || !taskQueue_.empty(); });

        if (stop_flag_ && taskQueue_.empty())
        {
            break; // exit loop cleanly
        }

        auto task = std::move(taskQueue_.front());
        taskQueue_.pop();
        lock.unlock();

        try
        {
            task();
        }
        catch (const std::exception &e)
        {
            std::cerr << "[DB] Worker exception: " << e.what() << std::endl;
        }
    }
}
