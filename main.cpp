#include <iostream>
#include <chrono>

#include "renderer.h"
#include "primitives.h"
#include "mesh.h"
#include "light.h"

int main()
{
    Renderer renderer(100, 100);

    renderer.createProjectionMatrix(45.f, .01f, 1000.f);
    renderer.createViewMatrix(0.f, 0.f, 5.f);

    Cube cubePrimitive;
    Mesh cubeMesh(cubePrimitive.getVertices(), cubePrimitive.getIndices(), cubePrimitive.getIndicesCount(), cubePrimitive.getVerticesCount());

    for (;;)
    {
        renderer.begin();

        cubeMesh.setRotation({.25, .25, .25});
        renderer.draw(cubeMesh);

        renderer.render();
    }

    return 0;
}