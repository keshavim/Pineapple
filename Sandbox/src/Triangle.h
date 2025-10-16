#pragma once

#include "pineapple.h"
#include "renderer/ShaderProgram.h"
#include "renderer/VertexArray.h"

class TriangleLayer : public pap::Layer
{
public:
    TriangleLayer()
    {
        // Create shaders
        m_Shader.reset(pap::ShaderProgram::Create(PAP_RELATIVE_PATH("shaders/Vertex.glsl"),
                                                  PAP_RELATIVE_PATH("shaders/Fragment.glsl")));

        // Create geometry
        struct Vertex
        {
            float Position[2];
            float TexCoord[2];
        };

        Vertex vertices[] = {
            {{-1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
            {{3.0f, -1.0f}, {2.0f, 0.0f}},  // Bottom-right
            {{-1.0f, 3.0f}, {0.0f, 2.0f}}   // Top-left
        };

        // Create VAO
        m_VertexArray.reset(pap::VertexArray::Create());

        // Create VBO
        m_VertexBuffer.reset(pap::VertexBuffer::Create((float *)vertices, sizeof(vertices)));

        // Describe layout
        pap::VertexBufferLayout layout;
        layout.Push(2, pap::ShaderDataType::Float, false); // Position
        layout.Push(2, pap::ShaderDataType::Float, false); // TexCoord

        // Attach buffer to VAO with layout
        m_VertexArray->AddVertexBuffer(*m_VertexBuffer, layout);
    }

    ~TriangleLayer() override
    {
        m_VertexArray.reset(); // cleans up VAO via its destructor
        m_VertexBuffer.reset();
        m_Shader.reset();
    }

    void onRender() override
    {
        m_Shader->Bind();

        // Uniforms
        m_Shader->SetUniform1f("iTime", pap::Application::GetTime());

        auto [x, y] = pap::Application::GetFramebufferSize();
        m_Shader->SetUniform2f("iResolution", x, y);
        glViewport(0, 0, static_cast<GLsizei>(x), static_cast<GLsizei>(y));

        // Render
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_VertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    std::shared_ptr<pap::VertexArray> m_VertexArray;
    std::shared_ptr<pap::VertexBuffer> m_VertexBuffer;

    std::shared_ptr<pap::ShaderProgram> m_Shader;
};
