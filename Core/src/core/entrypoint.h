#pragma once

#include "application.h"

namespace pap
{
extern void CreateApplication();
}
// Define the CreateApplication function required by the engine

int main()
{

    // Create and run the application
    pap::Application::Init();
    pap::CreateApplication();
    pap::Application::Run();
    pap::Application::Shutdown();
    return 0;
}
