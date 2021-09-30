#pragma once

#include <string>

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "Texture.h"
#include "../Maths/Maths.h"
#include "VertexPCU.h"

namespace Apex{

	struct Mesh
    {
        const void* m_Vertices;
        const unsigned int* m_Indices;
        VertexBufferLayout m_Layout;
        VertexArrayObject* m_VAO;
        VertexBuffer* m_VBO;
        IndexBuffer* m_IBO;
        Texture* m_Texture;

        explicit Mesh(const Vec2& position, Vec2 meshDim, Vec3 color, const std::string& path);
        explicit Mesh(std::vector<VertexPCU> vertices);
        explicit Mesh(const Vec2& position, Vec2 meshDim);
        ~Mesh();

        void CopyToCPU(const void* vertices, const unsigned int* indices);
        void CopyToGPU(const void* vertices, const unsigned int* indices);

        inline VertexArrayObject* GetVAO() const { return m_VAO; }
        inline VertexBuffer* GetVBO() const { return m_VBO; }
        inline IndexBuffer* GetIBO() const { return m_IBO; }
        inline Texture* GetTexture() const { return m_Texture; }
    };

}