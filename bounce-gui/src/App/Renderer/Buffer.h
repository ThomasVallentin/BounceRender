//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_BUFFER_H
#define BOUNCE_GUI_BUFFER_H

#include <string>
#include <utility>
#include <vector>

namespace Bounce::Gui {

    enum class ShaderDataType {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3,  Mat4,
        Int,   Int2,   Int3,   Int4,
        Bool,
    };

    static unsigned int ShaderDataTypeSize(const ShaderDataType &type) {
        switch (type) {
            case ShaderDataType::Float:   return 4;
            case ShaderDataType::Float2:  return 4 * 2;
            case ShaderDataType::Float3:  return 4 * 3;
            case ShaderDataType::Float4:  return 4 * 4;
            case ShaderDataType::Mat3:    return 4 * 9;
            case ShaderDataType::Mat4:    return 4 * 16;
            case ShaderDataType::Int:     return 4;
            case ShaderDataType::Int2:    return 4 * 2;
            case ShaderDataType::Int3:    return 4 * 3;
            case ShaderDataType::Int4:    return 4 * 4;
            case ShaderDataType::Bool:    return 1;
            case ShaderDataType::None:    return 0;
        }

        return 0;
    }

    struct BufferElement {
        std::string name;
        ShaderDataType type;
        unsigned int size;
        unsigned int offset;
        bool normalized;

        BufferElement(const ShaderDataType &type,
                      const std::string &name,
                      const bool &normalized=false)
                : name(name),
                  type(type),
                  size(ShaderDataTypeSize(type)),
                  offset(0),
                  normalized(normalized) {}

    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement> &elements)
                : m_elements(elements) {
            unsigned int offset = 0;
            m_stride = 0;
            for (auto &element : m_elements) {
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }

        inline const std::vector<BufferElement> &GetElements() const { return m_elements; }
        inline unsigned int GetStride() const { return m_stride; }


        inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    private:
        std::vector<BufferElement> m_elements;
        unsigned int m_stride;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual BufferLayout GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout &layout) = 0;

        static VertexBuffer* Create(float* vertices, unsigned int size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetCount() const = 0;

        static IndexBuffer* Create(unsigned int* vertices, unsigned int count);
    };

}


#endif //BOUNCE_GUI_BUFFER_H
