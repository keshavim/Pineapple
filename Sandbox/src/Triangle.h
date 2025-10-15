

#pragma once

#include "pineapple.h"
#include "temp_shader_functions.h"

class TriangleLayer : public pap::Layer
{
public:
    TriangleLayer()
    {
        // Create shaders
        m_Shader = render::CreateGraphicsShader("shaders/Vertex.glsl", "shaders/Fragment.glsl");

        // Create geometry
        glCreateVertexArrays(1, &m_VertexArray);
        struct Vertex
        {
            float Position[2];
            float TexCoord[2];
        };

        // Define vertices
        Vertex vertices[] = {
            {{-1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
            {{3.0f, -1.0f}, {2.0f, 0.0f}},  // Bottom-right
            {{-1.0f, 3.0f}, {0.0f, 2.0f}}   // Top-left
        };

        m_VertexBuffer.reset(pap::VertexBuffer::Create((float *)vertices, sizeof(vertices)));
        m_VertexBuffer->BindToVAO(m_VertexArray, 0, sizeof(Vertex));

        // Enable attributes
        glEnableVertexArrayAttrib(m_VertexArray, 0); // position
        glEnableVertexArrayAttrib(m_VertexArray, 1); // uv

        // Format: location, size, type, normalized, relative offset
        glVertexArrayAttribFormat(m_VertexArray,
                                  0,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  static_cast<GLuint>(offsetof(Vertex, Position)));
        glVertexArrayAttribFormat(m_VertexArray,
                                  1,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  static_cast<GLuint>(offsetof(Vertex, TexCoord)));

        // Link attribute locations to binding index 0
        glVertexArrayAttribBinding(m_VertexArray, 0, 0);
        glVertexArrayAttribBinding(m_VertexArray, 1, 0);
    }

    ~TriangleLayer() override
    {
        glDeleteVertexArrays(1, &m_VertexArray);
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
        glBindVertexArray(m_VertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLuint m_VertexArray = 0;
    std::unique_ptr<pap::VertexBuffer> m_VertexBuffer;

    GLuint m_Shader = 0;
};
