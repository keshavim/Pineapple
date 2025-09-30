#include <pineapple.h>






// Example custom layer that inherits from Layer
class TestLayer : public pap::Layer {
public:
    TestLayer()  {
        Layer("testlayer");
    }

    void OnRender() override {
    }

    void OnUpdate(float ts) override {
    }
};


// Example application class
//might try to remove this step
class SandboxApp : public pap::Application {
public:
    SandboxApp() {
        // Demonstrate template function for pushing layer instances
        PushLayer<TestLayer>();

        PAP_PRINT("SandboxApp created and initalized!\n");

        // ODBCConfig cfg {
        //     "MariaDBTest",          // DSN
        //     "MariaDB",              // Driver
        //     "/usr/lib/libmaodbc.so",// Driver path
        //     "localhost",            // Server
        //     "test",                 // Database
        //     "root",                 // User
        //     "jeoYfU*17g#!$B",                 // Password
        //     3306                    // Port
        // };

        // ODBCManager manager(cfg);

        // manager.create_driver_ini_if_missing();
        // manager.create_dsn_if_missing();

        // if (!manager.connect()) {
        //     std::cerr << "Failed to connect.\n";
        //     exit(1);
        // }

        // auto dbs = manager.list_databases();
        // std::cout << "Databases found:\n";
        // for (auto& db : dbs) {
        //     std::cout << " - " << db << "\n";
        // }

    }
};

std::unique_ptr<pap::Application> pap::CreateApplication(){
    return std::make_unique<SandboxApp>();
}
