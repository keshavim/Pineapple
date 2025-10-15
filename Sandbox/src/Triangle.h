#pragma once

#include "pineapple.h"
#include "renderer/VertexArray.h"
#include "temp_shader_functions.h"

class TriangleLayer : public pap::Layer
{
public:
    TriangleLayer()
    {
        // Create shaders
        m_Shader = render::CreateGraphicsShader("shaders/Vertex.glsl", "shaders/Fragment.glsl");

        // Create geometry
        struct Vertex
        {
            float Position[2];
            float TexCoord[2];
        };

        Vertex vertices[] = {
            {{-1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
            {{3.0f, -1.0f},  {2.0f, 0.0f}}, // Bottom-right
            {{-1.0f,  3.0f}, {0.0f, 2.0f}}  // Top-left
        };

        // Create VAO
        m_VertexArray.reset(pap::VertexArray::Create());

        // Create VBO
        m_VertexBuffer.reset(pap::VertexBuffer::Create((float*)vertices, sizeof(vertices)));

        // Describe layout
        pap::VertexBufferLayout layout;
        layout.Push(2, pap::ShaderDataType::Float, false); // Position
        layout.Push(2, pap::ShaderDataType::Float, false); // TexCoord

        // Attach buffer to VAO with layout
        m_VertexArray->AddVertexBuffer(*m_VertexBuffer, layout);
    }

    ~TriangleLayer() override
    {
        m_VertexArray.reset();   // cleans up VAO via its destructor
        m_VertexBuffer.reset();  // cleans up VBO
        glDeleteProgram(m_Shader);
    }

    void onRender() override
    {
        glUseProgram(m_Shader);

        // Uniforms
        glUniform1f(0, pap::Application::GetTime());

        auto [x, y] = pap::Application::GetFramebufferSize();
        glUniform2f(1, x, y);
        glViewport(0, 0, static_cast<GLsizei>(x), static_cast<GLsizei>(y));

        // Render
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_VertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    std::shared_ptr<pap::VertexArray> m_VertexArray;
    std::shared_ptr<pap::VertexBuffer> m_VertexBuffer;

    GLuint m_Shader = 0;
};
