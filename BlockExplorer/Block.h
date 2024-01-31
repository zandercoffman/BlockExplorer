#pragma once
#include <cmath>

using namespace std;

class Block() {
    private:
        static vector<vector<float>> cubeVertices[8][3] = {
            {1.0f, 1.0f, 1.0f},     // TR F
            {1.0f, -1.0f, 1.0f},    // BR F
            {-1.0f, -1.0f, 1.0f},   // BL F
            {-1.0f, 1.0f, 1.0f},    // TL F
            {1.0f, 1.0f, -1.0f},    // TR B
            {1.0f, -1.0f, -1.0f},   // BR B
            {-1.0f, -1.0f, -1.0f},  // BL B
            {-1.0f, 1.0f, -1.0f}    // TL B
        };

    public:
        static const vector<vector<float>>& Block::getVerticies() const {
            return cubeVertices;
        }

        void rotateY(float angle);
};

void Block::rotateY(float angle) {
    for (const auto& vertex : Block::getVerticies()) {
        double x = vertex[0] * cos(angle) - vertex[2] * sin(angle);
        double z = vertex[0] * sin(angle) + vertex[2] * cos(angle);

        vertex[0] = x;
        vertex[2] = z;
    }
}
