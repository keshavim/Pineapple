#include "ShaderProgram.h"
#include "Renderer.h"
#include "backends/OpenGL/OpenGLShaderProgram.h"
#include "core/core.h"


namespace pap {
    ShaderProgram* ShaderProgram::Create(const std::filesystem::path& vertexPath,
                                     const std::filesystem::path& fragmentPath)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::None:
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLShaderProgram(vertexPath, fragmentPath);
        // case RendererAPI::Vulkan:
        //     return new VulkanShaderProgram(vertexPath, fragmentPath);
    }
    return nullptr;
}





}
