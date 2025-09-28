#include <pineapple.h>
// Example custom layer that inherits from Layer
class TestLayer : public pap::Layer {
public:
    TestLayer(const std::string& name = "TestLayer") : Layer(name) {}

    void OnAttach() override {
        PAP_INFO("TestLayer ({}) attached!\n", GetName());
    }

    void OnDetach() override {
        PAP_PRINT("TestLayer ({}) detached!\n", GetName());
    }

    void OnUpdate() override {
        PAP_PRINT("TestLayer ({}) updating...\n", GetName());
    }
};


// Example application class
class SandboxApp : public pap::Application {
public:
    SandboxApp() {


        // Demonstrate template function for pushing layer instances
        PushLayer<TestLayer>("CustomTestLayer");

        PAP_PRINT("SandboxApp created and initalized!\n");

    }
};

std::unique_ptr<pap::Application> pap::CreateApplication(){
    return std::make_unique<SandboxApp>();
}
