#include "renderer.h"
#include "primitives.h"
#include "mesh.h"
#include "light.h"

int main()
{
    Renderer renderer(50, 50);

    Light light = {{0, 0, 2}, 1.0f};

    renderer.createProjectionMatrix(45.f, .01f, 1000.f);
    renderer.createViewMatrix(0.f, 0.f, 5.f);

    Cube cubePrimitive;
    Mesh cubeMesh(cubePrimitive.getVertices(), cubePrimitive.getIndices(), cubePrimitive.getIndicesCount(), cubePrimitive.getVerticesCount());

    cubeMesh.setPosition({0, 0, 0});
    cubeMesh.setScale({1, .8, .6});

    for (;;)
    {
        renderer.begin();

        cubeMesh.setRotation({.15, .25, .35});
        renderer.draw(cubeMesh.getVertices(), cubeMesh.getIndices(), cubeMesh.getIndicesCount());

        renderer.render();
    }

    return 0;
}