#pragma once

#include <string>

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Texture.h"
#include "../Maths/Maths.h"
#include "../Maths/AABB2.h"

namespace Apex{

	class Mesh
    {
        VertexArray* m_VAO;
        VertexBuffer* m_VBO;
        IndexBuffer* m_IBO;
        Texture* m_Texture;
    public:
        explicit Mesh(const Vec2& position, Vec2 meshDim, Vec3 color, const std::string& path);
        explicit Mesh(const Vec2& position, const Vec2& meshDim, const Vec4& color, const AABB2& uvPos);
        explicit Mesh(const Vec2& position, Vec2 meshDim);
        explicit Mesh(const AABB2& position, AABB2 uvPos);
        ~Mesh();

        inline VertexArray* GetVAO() const { return m_VAO; }
        inline IndexBuffer* GetIBO() const { return m_IBO; }
        inline Texture* GetTexture() const { return m_Texture; }
    };

}