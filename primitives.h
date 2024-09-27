#pragma once

#include "math.h"
#include "vertex.h"

class Primitive
{
public:
    inline Vertex *getVertices()
    {
        return vertices;
    }
    inline int *getIndices()
    {
        return indices;
    }
    inline int getIndicesCount()
    {
        return indicesCount;
    }
    inline int getVerticesCount()
    {
        return verticesCount;
    }

    virtual ~Primitive()
    {
        delete[] vertices;
        delete[] indices;
    }

protected:
    Vertex *vertices = nullptr;
    int *indices = nullptr;
    int verticesCount = 0, indicesCount = 0;
};

class Quad : public Primitive
{
public:
    Quad() : Primitive()
    {
        vertices = new Vertex[4]{
            {{-1, 1, 0}, {0, 0, 1}},
            {{1, 1, 0}, {0, 0, 1}},
            {{1, -1, 0}, {0, 0, 1}},
            {{-1, -1, 0}, {0, 0, 1}}};

        indices = new int[6]{
            0, 1, 2,
            0, 2, 3};

        verticesCount = 4;
        indicesCount = 6;
    }
};

class Cube : public Primitive
{
public:
    Cube() : Primitive()
    {
        vertices = new Vertex[24]{
            // Front face
            {{-1, -1, 1}, {0, 0, 1}}, // 0: Bottom-left-front
            {{1, -1, 1}, {0, 0, 1}},  // 1: Bottom-right-front
            {{1, 1, 1}, {0, 0, 1}},   // 2: Top-right-front
            {{-1, 1, 1}, {0, 0, 1}},  // 3: Top-left-front

            // Back face
            {{-1, -1, -1}, {0, 0, -1}}, // 4: Bottom-left-back
            {{-1, 1, -1}, {0, 0, -1}},  // 5: Top-left-back
            {{1, 1, -1}, {0, 0, -1}},   // 6: Top-right-back
            {{1, -1, -1}, {0, 0, -1}},  // 7: Bottom-right-back

            // Left face
            {{-1, -1, -1}, {-1, 0, 0}}, // 8: Bottom-left-back
            {{-1, -1, 1}, {-1, 0, 0}},  // 9: Bottom-left-front
            {{-1, 1, 1}, {-1, 0, 0}},   // 10: Top-left-front
            {{-1, 1, -1}, {-1, 0, 0}},  // 11: Top-left-back

            // Right face
            {{1, -1, -1}, {1, 0, 0}}, // 12: Bottom-right-back
            {{1, 1, -1}, {1, 0, 0}},  // 13: Top-right-back
            {{1, 1, 1}, {1, 0, 0}},   // 14: Top-right-front
            {{1, -1, 1}, {1, 0, 0}},  // 15: Bottom-right-front

            // Top face
            {{-1, 1, -1}, {0, 1, 0}}, // 16: Top-left-back
            {{1, 1, -1}, {0, 1, 0}},  // 17: Top-right-back
            {{1, 1, 1}, {0, 1, 0}},   // 18: Top-right-front
            {{-1, 1, 1}, {0, 1, 0}},  // 19: Top-left-front

            // Bottom face
            {{-1, -1, -1}, {0, -1, 0}}, // 20: Bottom-left-back
            {{-1, -1, 1}, {0, -1, 0}},  // 21: Bottom-left-front
            {{1, -1, 1}, {0, -1, 0}},   // 22: Bottom-right-front
            {{1, -1, -1}, {0, -1, 0}}   // 23: Bottom-right-back
        };

        indices = new int[36]{
            // Front face (2 triangles)
            0, 2, 1, 0, 3, 2,
            // Back face (2 triangles)
            4, 6, 5, 4, 7, 6,
            // Left face (2 triangles)
            8, 10, 9, 8, 11, 10,
            // Right face (2 triangles)
            12, 14, 13, 12, 15, 14,
            // Top face (2 triangles)
            16, 17, 18, 16, 18, 19,
            // Bottom face (2 triangles)
            20, 21, 22, 20, 22, 23};

        verticesCount = 24;
        indicesCount = 36;
    }
};