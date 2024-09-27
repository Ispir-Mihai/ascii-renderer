#include "renderer.h"
#include <iostream>

Renderer::Renderer(int width, int height)
    : width(width), height(height)
{
    // Allocate rows
    backBuffer = new wchar_t *[width];

    // Allocate columns
    for (int x = 0; x < width; ++x)
        backBuffer[x] = new wchar_t[height];

    // Fill with background char
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            backBuffer[x][y] = background;

    // Allocate screen buffer
    screen = new wchar_t[width * 2 * height + height + 1]();

    // Disable buffering, hide cursor and clear the console
    Console::disableBuffering();
    Console::hideCursor();
    Console::clear();
}

Renderer::~Renderer()
{
    // Free memory
    for (int i = 0; i < width; ++i)
        delete[] backBuffer[i];

    delete[] backBuffer;
    delete[] screen;
}

void Renderer::begin()
{
    // Clear the back buffer
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (backBuffer[x][y] != background)
                backBuffer[x][y] = background;

    // Clear the screen
    Console::clear();
}
void Renderer::draw(Vertex *vertices, int *indices, int indiciesCount)
{
    // Iterate over all triangles (each triangle has 3 indices)
    for (int i = 0; i < indiciesCount / 3; ++i)
    {
        // Indices of the current triangle
        int triIndices[3] = {
            indices[i * 3],
            indices[i * 3 + 1],
            indices[i * 3 + 2]};

        // Draw the triangle
        tri(vertices, triIndices);
    }
}
void Renderer::render()
{
    // Draw the back buffer to the screen buffer
    int screenIndex = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Draw the character twice for more accurate aspect ratio
            screen[screenIndex++] = backBuffer[x][y];
            screen[screenIndex++] = backBuffer[x][y];
        }
        screen[screenIndex++] = L'\n';
    }
    screen[screenIndex] = L'\0';

    Console::fastwrite(screen);
}

void Renderer::set(iVec2 pos)
{
    // Check if the position is out of bounds
    if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
        return;

    // Check if the character is different
    if (backBuffer[pos.x][pos.y] == fill)
        return;

    // Set the character
    backBuffer[pos.x][pos.y] = fill;
}
void Renderer::line(iVec2 start, iVec2 end)
{
    // Bresenham's line algorithm
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);

    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;

    int err = dx - dy;

    iVec2 current = start;
    while (current != end)
    {
        set(current);

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            current.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            current.y += sy;
        }
    }
}
void Renderer::line(fVec3 start, fVec3 end)
{
    // Line in world space
    iVec2 screenStart = worldToScreen(start);
    iVec2 screenEnd = worldToScreen(end);

    line(screenStart, screenEnd);
}
void Renderer::tri(Vertex *vertices, int *indices)
{
    iVec2 v0 = worldToScreen(vertices[indices[0]].position);
    iVec2 v1 = worldToScreen(vertices[indices[1]].position);
    iVec2 v2 = worldToScreen(vertices[indices[2]].position);

    // Check if the triangle is backfacing
    float area = (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
    if (area <= 0)
        return; // Early exit if the triangle is backfacing

    // Fill the triangle
    int minX = std::min({v0.x, v1.x, v2.x});
    int maxX = std::max({v0.x, v1.x, v2.x});
    int minY = std::min({v0.y, v1.y, v2.y});
    int maxY = std::max({v0.y, v1.y, v2.y});

    // Iterate over all pixels inside the bounding box
    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            // Check if the point (x, y) is inside the triangle
            if (edgeFunction(v0, v1, {x, y}) &&
                edgeFunction(v1, v2, {x, y}) &&
                edgeFunction(v2, v0, {x, y}))
            {
                // Barycentric coordinates
                float alpha = ((v1.y - v2.y) * (x - v2.x) + (v2.x - v1.x) * (y - v2.y)) /
                              ((v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y));
                float beta = ((v2.y - v0.y) * (x - v2.x) + (v0.x - v2.x) * (y - v2.y)) /
                             ((v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y));
                float gamma = 1.0f - alpha - beta;

                // Interpolating Z values using barycentric coordinates
                float z = alpha * vertices[indices[0]].position.z +
                          beta * vertices[indices[1]].position.z +
                          gamma * vertices[indices[2]].position.z;

                // Interpolating normals using barycentric coordinates
                fVec3 normal = (vertices[indices[0]].normals * alpha +
                                vertices[indices[1]].normals * beta +
                                vertices[indices[2]].normals * gamma)
                                   .normalize();

                // Calculate the light direction
                fVec3 lightDir = fVec3(0, 0, 1);

                // Calculate the light intensity based on the interpolated normal
                float intensity = Light::calculateLightIntensity(lightDir, normal);

                // Set the pixel color based on the intensity
                fill = Light::getShade(intensity);
                set({x, y}); // Pass the calculated shade to the set function
            }
        }
    }
}

void Renderer::createProjectionMatrix(float fov, float near, float far)
{
    // Create a perspective projection matrix
    float scale = 1.f / tan(fov * .5f);

    projectionMatrix[0][0] = scale / (width / height);
    projectionMatrix[1][1] = scale;
    projectionMatrix[2][2] = (far + near) / (near - far);
    projectionMatrix[2][3] = (2 * far * near) / (near - far);
    projectionMatrix[3][2] = -1;
    projectionMatrix[3][3] = 0;
}
void Renderer::createViewMatrix(float camX, float camY, float camZ)
{
    // Create a view matrix
    viewMatrix[0][0] = 1;
    viewMatrix[0][1] = 0;
    viewMatrix[0][2] = 0;
    viewMatrix[0][3] = -camX;
    viewMatrix[1][0] = 0;
    viewMatrix[1][1] = 1;
    viewMatrix[1][2] = 0;
    viewMatrix[1][3] = -camY;
    viewMatrix[2][0] = 0;
    viewMatrix[2][1] = 0;
    viewMatrix[2][2] = 1;
    viewMatrix[2][3] = -camZ;
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    viewMatrix[3][3] = 1;
}

bool Renderer::edgeFunction(const iVec2 &a, const iVec2 &b, const iVec2 &c)
{
    // Edge function
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) >= 0;
}
iVec2 Renderer::worldToScreen(const fVec3 &worldPos)
{
    // Convert world space to screen space
    fMat worldPosMat(4, 1);

    worldPosMat[0][0] = worldPos.x;
    worldPosMat[1][0] = worldPos.y;
    worldPosMat[2][0] = worldPos.z;
    worldPosMat[3][0] = 1.f;

    fMat clipPosMat = projectionMatrix * viewMatrix * worldPosMat;

    if (clipPosMat[3][0] == 0)
        return iVec2();

    clipPosMat[0][0] /= clipPosMat[3][0];
    clipPosMat[1][0] /= clipPosMat[3][0];
    clipPosMat[2][0] /= clipPosMat[3][0];

    if (clipPosMat[2][0] < 0.f || clipPosMat[2][0] > 1.f)
        return iVec2();

    iVec2 screenPos;

    screenPos.x = (clipPosMat[0][0] + 1.f) * .5f * width;
    screenPos.y = (1.f - clipPosMat[1][0]) * .5f * height;

    return screenPos;
}