#pragma once

#include "vertex.h"
#include "primitives.h"
#include "math.h"

class Mesh
{
public:
    // Constructors
    Mesh(Vertex *vertices, int *indices, int indicesCount, int verticesCount) : vertices(vertices), indices(indices), verticesCount(verticesCount), indicesCount(indicesCount), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}
    Mesh(Vertex *vertices, int *indices, int indicesCount, int verticesCount, fVec3 position, fVec3 rotation, fVec3 scale)
        : vertices(vertices), indices(indices), verticesCount(verticesCount), indicesCount(indicesCount), position(position), rotation(rotation), scale(scale) {}

    // Setters
    inline void setPosition(fVec3 position)
    {
        this->position = position;
        for (int i = 0; i < verticesCount; ++i)
        {
            vertices[i].position += position;
        }
    }
    inline void setRotation(fVec3 angles)
    {
        this->rotation += angles;
        for (int i = 0; i < verticesCount; ++i)
        {
            // Rotate the vertex position and normals around the center of the mesh
            vertices[i].position = vertices[i].position.rotate(position, angles);
            vertices[i].normals = vertices[i].normals.rotate(position, angles);
        }
    }
    inline void setRotation(fVec3 origin, fVec3 angles)
    {
        this->rotation += angles;
        for (int i = 0; i < verticesCount; ++i)
        {
            // Rotate the vertex position and normals around user-defined origin
            vertices[i].position = vertices[i].position.rotate(origin, angles);
            vertices[i].normals = vertices[i].normals.rotate(origin, angles);
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

    // Getters
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