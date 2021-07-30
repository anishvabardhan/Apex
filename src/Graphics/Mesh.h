#pragma once

#include <string>

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Texture.h"
#include "../Maths/Maths.h"

namespace Apex{

	class Mesh
    {
        VertexArray* m_VAO;
        IndexBuffer* m_IBO;
        Texture* m_Texture;
    public:
        explicit Mesh(const Vec2& position, Vec2 meshDim, const std::string& path);
        explicit Mesh(const Vec2& position, Vec2 meshDim);
        ~Mesh();

        inline VertexArray* GetVAO() const { return m_VAO; }
        inline IndexBuffer* GetIBO() const { return m_IBO; }
        inline Texture* GetTexture() const { return m_Texture; }
    };

}