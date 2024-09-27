#pragma once

#include <algorithm>
#include "console.h"
#include "math.h"
#include "vertex.h"
#include "light.h"

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    void begin();
    void draw(Vertex *vertices, int *indices, int indiciesCount);
    void render();

    void createProjectionMatrix(float fov, float near, float far);
    void createViewMatrix(float camX, float camY, float camZ);

private:
    wchar_t background = ' ', fill = 0x2588;
    int width, height;

    wchar_t *screen;
    wchar_t **backBuffer;

    fMat viewMatrix = fMat::identity(4);
    fMat projectionMatrix = fMat::identity(4);

    void set(iVec2 pos);
    void line(iVec2 start, iVec2 end);
    void line(fVec3 start, fVec3 end);
    void tri(Vertex *vertices, int *indices);

    bool edgeFunction(const iVec2 &a, const iVec2 &b, const iVec2 &c);
    iVec2 worldToScreen(const fVec3 &worldPos);
};