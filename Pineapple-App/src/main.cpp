#include <pineapple.h>
// Example custom layer that inherits from Layer
class TestLayer : public pap::Layer {
public:
    TestLayer()  {
        Layer("testlayer");
    }

    void OnRender() override {
        PAP_PRINT("TestLayer ({}) detached!\n", GetName());
    }

    void OnUpdate(float ts) override {
        PAP_PRINT("TestLayer ({}) updating...\n", GetName());
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

    }
};

std::unique_ptr<pap::Application> pap::CreateApplication(){
    return std::make_unique<SandboxApp>();
}
