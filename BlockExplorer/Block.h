#pragma once

#include <cmath>
#include <vector>
#include <SDL.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define SCREEN_X 400
#define SCREEN_Y 300

float cameraDistance = 20;
float scale = 2;
float cameraAngle = 0;

using namespace std;

class Block {
private:
    vector<vector<float>> cubeVertices = {
        {1.0f, 1.0f, 1.0f},     // TR F
        {1.0f, -1.0f, 1.0f},    // BR F
        {-1.0f, -1.0f, 1.0f},   // BL F
        {-1.0f, 1.0f, 1.0f},    // TL F
        {1.0f, 1.0f, -1.0f},    // TR B
        {1.0f, -1.0f, -1.0f},   // BR B
        {-1.0f, -1.0f, -1.0f},  // BL B
        {-1.0f, 1.0f, -1.0f}    // TL B
    };

    vector<int> CURXYPOS = {0, 0};

public:
    bool renderPointsToCamera(SDL_Renderer* renderer);
    bool renderPointsAboveFacingCameraPoints(SDL_Renderer* renderer);
    bool rotateY(SDL_Renderer * renderer, float angle);
};


bool Block::renderPointsToCamera(SDL_Renderer* renderer) {
    // Project and draw the rotated and scaled cube
    for (const auto& vertex : cubeVertices) {
        float x = vertex[0] * scale;
        float y = vertex[1] * scale;
        float z = vertex[2] * scale;

        int screenX = SCREEN_X + static_cast<int>(cameraDistance * x);
        int screenY = SCREEN_Y + static_cast<int>(cameraDistance * y);

        SDL_RenderDrawPoint(renderer, static_cast<int>(screenX), static_cast<int>(screenY));
    }

    return true;
}

bool Block::rotateY(SDL_Renderer* renderer, float angle) {
    vector<vector<float>> rotatedVerticies = {};
    for (const auto& vertex : cubeVertices) {
        float newX = vertex[0] * cos(angle) - vertex[2] * sin(angle);
        float newZ = vertex[0] * sin(angle) + vertex[2] * cos(angle);

        rotatedVerticies.push_back({newX, vertex[1], newZ});
    }
    cubeVertices = rotatedVerticies;
    return true;
}
