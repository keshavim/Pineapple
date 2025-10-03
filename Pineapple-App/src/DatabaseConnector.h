#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <nanodbc/nanodbc.h>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "db_result.h"

/// Database connector that runs queries on a background thread.
class DatabaseConnector
{
public:
    DatabaseConnector();
    ~DatabaseConnector();

    /// Connect asynchronously to the database.
    void connect(const std::string &dsn, const std::string &user, const std::string &pass, long timeout = 0);

    /// Disconnect from the database.
    void disconnect();

    /// Execute a raw SQL string on the background thread and get the result synchronously.
    DBResult executeRawSQL(const std::string &sql);

private:
    using Task = std::function<void()>;

    void enqueueTask(Task task);
    void runWorker();

    std::optional<nanodbc::connection> connection_;
    std::thread workerThread_;
    std::mutex queueMutex_;
    std::condition_variable cv_;
    std::queue<Task> taskQueue_;
    bool stopThread_;

    std::atomic<bool> stop_flag_{false};
};
