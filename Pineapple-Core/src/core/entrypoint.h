#pragma once

#include "application.h"
namespace pap {
    extern void InitApplication();
}
// Define the CreateApplication function required by the engine


int main() {
    // Create and run the application
    pap::Application app;
    pap::InitApplication();
    app.Run();
    return 0;
}
