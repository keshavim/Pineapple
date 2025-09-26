#include <pineapple.h>
#include <iostream>

// Example custom layer that inherits from Layer
class TestLayer : public Pineapple::Layer {
public:
    TestLayer(const std::string& name = "TestLayer") : Layer(name) {}

    void OnAttach() override {
        std::cout << "TestLayer (" << GetName() << ") attached!" << std::endl;
    }

    void OnDetach() override {
        std::cout << "TestLayer (" << GetName() << ") detached!" << std::endl;
    }

    void OnUpdate() override {
        std::cout << "TestLayer (" << GetName() << ") updating..." << std::endl;
    }
};

// Another example layer
class RenderLayer : public Pineapple::Layer {
public:
    RenderLayer() : Layer("RenderLayer") {}

    void OnAttach() override {
        std::cout << "RenderLayer attached!" << std::endl;
    }

    void OnDetach() override {
        std::cout << "RenderLayer detached!" << std::endl;
    }

    void OnUpdate() override {
        std::cout << "RenderLayer rendering frame..." << std::endl;
    }
};

// Example application class
class SandboxApp : public Pineapple::Application {
public:
    SandboxApp() {
        std::cout << "SandboxApp created!" << std::endl;

        // Demonstrate template function for pushing layer instances
        PushLayer<TestLayer>("CustomTestLayer");
        PushLayer<RenderLayer>();
        PushLayer<TestLayer>("AnotherTestLayer");
    }

    void Init() override {
        std::cout << "SandboxApp initializing..." << std::endl;
        Pineapple::Application::Init(); // Call base class Init
    }

    void Update() override {
        // Call base class Update to update all layers
        Pineapple::Application::Update();
    }
};

// Define the CreateApplication function required by the engine
Pineapple::Application* Pineapple::CreateApplication() {
    return new SandboxApp();
}

int main() {
    std::cout << "=== Pineapple Application Demo ===" << std::endl;

    // Create and run the application
    auto app = Pineapple::CreateApplication();
    app->Run();
    delete app;

    std::cout << "=== Demo Complete ===" << std::endl;
    return 0;
}
