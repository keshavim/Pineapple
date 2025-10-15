#pragma once
#include "Buffer.h"
#include <memory>



namespace pap
{


enum class ShaderDataType : uint32_t
{
    Float = 0,   // float
    Vec2,        // vec2
    Vec3,        // vec3
    Vec4,        // vec4

    Int,         // int
    IVec2,       // ivec2
    IVec3,       // ivec3
    IVec4,       // ivec4

    Bool         // bool
};
struct VertexBufferElement
{
    uint32_t Count;       // number of components
    ShaderDataType Type;        // GL_FLOAT, GL_INT, etc.
    bool Normalized;
    size_t Offset;        // offset in bytes
};

struct VertexBufferLayout
{
    std::vector<VertexBufferElement> Elements;
    uint32_t Stride = 0;

    void Push(uint32_t count, ShaderDataType type, bool normalized);
};


// ================= Abstract VertexArray =================
class VertexArray
{
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    // Pass by reference since VAO doesn't own the buffer
    virtual void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) = 0;

    // Accept a raw pointer for optional / nullable index buffer
    virtual void SetIndexBuffer(const IndexBuffer* ib) = 0;

    virtual IndexBuffer* GetIndexBuffer() const = 0;

    static VertexArray* Create(); // Factory returns raw ptr; caller owns
};


} // namespace pap
