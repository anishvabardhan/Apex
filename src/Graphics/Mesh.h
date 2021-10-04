#pragma once

#include <string>

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "../Maths/Maths.h"

namespace Apex{

    struct VertexPCU;

	struct Mesh
    {
        VertexArrayObject* m_VAO;
        VertexBuffer* m_VBO;
        IndexBuffer* m_IBO;

        explicit Mesh(std::vector<VertexPCU> vertices, VertexBufferLayout layout);
        ~Mesh();
    };

}