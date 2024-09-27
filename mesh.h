#include "vertex.h"
#include "primitives.h"
#include "math.h"

class Mesh
{
public:
    Mesh(Vertex *vertices, int *indices, int indicesCount, int verticesCount) : vertices(vertices), indices(indices), verticesCount(verticesCount), indicesCount(indicesCount), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}
    Mesh(Vertex *vertices, int *indices, int indicesCount, int verticesCount, fVec3 position, fVec3 rotation, fVec3 scale)
        : vertices(vertices), indices(indices), verticesCount(verticesCount), indicesCount(indicesCount), position(position), rotation(rotation), scale(scale) {}

    inline void setPosition(fVec3 position)
    {
        this->position = position;
        for (int i = 0; i < verticesCount; ++i)
        {
            vertices[i].position += position;
        }
    }
    inline void setRotation(fVec3 rotation)
    {
        this->rotation = rotation;
        for (int i = 0; i < verticesCount; ++i)
        {
            vertices[i].position = vertices[i].position.rotateX(rotation.x);
            vertices[i].position = vertices[i].position.rotateY(rotation.y);
            vertices[i].position = vertices[i].position.rotateZ(rotation.z);

            vertices[i].normals = vertices[i].normals.rotateX(rotation.x);
            vertices[i].normals = vertices[i].normals.rotateY(rotation.y);
            vertices[i].normals = vertices[i].normals.rotateZ(rotation.z);
        }
    }
    inline void setScale(fVec3 scale)
    {
        this->scale = scale;
        for (int i = 0; i < verticesCount; ++i)
        {
            vertices[i].position *= scale;
        }
    }

    inline fVec3 getPosition() const
    {
        return position;
    }
    inline fVec3 getRotation() const
    {
        return rotation;
    }
    inline fVec3 getScale() const
    {
        return scale;
    }

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

    virtual ~Mesh()
    {
        delete[] vertices;
        delete[] indices;
    }

private:
    fVec3 position, rotation, scale;

    Vertex *vertices = nullptr;
    int *indices = nullptr;
    int verticesCount = 0, indicesCount = 0;
};