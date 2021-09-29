#pragma once

#include <string>

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "Texture.h"
#include "../Maths/Maths.h"
#include "VertexPCU.h"

namespace Apex{

	class Mesh
    {
        VertexArrayObject* m_VAO;
        IndexBuffer* m_IBO;
        Texture* m_Texture;
    public:
        explicit Mesh(const Vec2& position, Vec2 meshDim, Vec3 color, const std::string& path);
        explicit Mesh(std::vector<VertexPCU> vertices);
        explicit Mesh(const Vec2& position, Vec2 meshDim);
        ~Mesh();

        inline VertexArrayObject* GetVAO() const { return m_VAO; }
        inline IndexBuffer* GetIBO() const { return m_IBO; }
        inline Texture* GetTexture() const { return m_Texture; }
    };

}