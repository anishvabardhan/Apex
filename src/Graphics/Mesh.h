#pragma once

#include <string>

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "../Maths/Maths.h"
#include "../Maths/AABB2.h"

namespace Apex {

    struct VertexPCU;

    struct Mesh
    {
        VertexArrayObject* m_VAO;
        VertexBuffer* m_VBO;
        IndexBuffer* m_IBO;

        Mesh(std::vector<VertexPCU> vertices, const unsigned int* indices, VertexBufferLayout layout);
        ~Mesh();
    };


}