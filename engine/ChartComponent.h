#pragma once

//#include <iostream>
#include <vector>

namespace ECSEngine {

struct ChartNote {
    float bpm;
    float subdivision;

    // parallel arrays
    std::vector<bool> lane;
    std::vector<bool> hold;
    std::vector<float> holdSubdivision;
    std::vector<float> holdLength;
};

struct ChartComponent {
    std::vector<ChartNote> data;
    SpriteID noteTexID;
    int cur = 0;

    int sleepFrame = 0;
};

}  // namespace ECSEngine
