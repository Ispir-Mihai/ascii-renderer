#pragma once

#include "math.h"

struct Light
{
    static float calculateLightIntensity(const fVec3 &normal, const fVec3 &lightDir)
    {
        float intensity = std::max(0.f, normal.dot(lightDir));
        return intensity;
    }

    static wchar_t getShade(float intensity)
    {
        // Convert the intensity to a shade character
        if (intensity < 0.25f)
            return 0x2591; // Light Shade
        else if (intensity < 0.5f)
            return 0x2592; // Medium Shade
        else if (intensity < 0.75f)
            return 0x2593; // Dark Shade
        else
            return 0x2588; // Full Block
    }
};
