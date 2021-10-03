#pragma once

#include <string>

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "Texture.h"
#include "../Maths/Maths.h"

namespace Apex{

    struct VertexPCU;

	struct Mesh
    {
        VertexBufferLayout m_Layout;
        VertexArrayObject* m_VAO;
        VertexBuffer* m_VBO;
        IndexBuffer* m_IBO;
        Texture* m_Texture;

        explicit Mesh(const Vec2& position, Vec2 meshDim, Vec3 color, const std::string& path);
        explicit Mesh(std::vector<VertexPCU> vertices);
        explicit Mesh(const Vec2& position, Vec2 meshDim);
        ~Mesh();
    };

}