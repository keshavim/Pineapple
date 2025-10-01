#pragma once

#include "application.h"
namespace pap {
    extern std::unique_ptr<Application> CreateApplication();
}
// Define the CreateApplication function required by the engine


int main() {
    // Create and run the application
    auto app = pap::CreateApplication();
    app->Run();
    return 0;
}
