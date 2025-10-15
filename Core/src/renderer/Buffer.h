#pragma once
#include <cstdint>
#include <vector>


namespace pap {


class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void SetData(const void* data, size_t size) = 0;
    virtual void BindToVAO(uint32_t vao, uint32_t bindingIndex, uint32_t stride) = 0;
    virtual uint32_t GetID() = 0;

    static VertexBuffer* Create(float *vertices, uint32_t size);
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual uint32_t GetCount() const = 0;

    static IndexBuffer* Create(uint32_t *indices, uint32_t size);

};
}
