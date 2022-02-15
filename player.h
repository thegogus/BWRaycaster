#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <glm/glm.hpp>
#include "shapes.h"

class player{
    public:
        player(const glm::vec3 &playerPos, const unsigned int &screenWidth, const unsigned int &screenHeight, const glm::vec4 &color);
        void drawPlayer();
        void changePlayerPosition(const glm::vec3 &pos);
        void changePlayerRotation(const glm::vec3 &rot, const float &angle);
    private:
        std::vector<rect*> mPlayerRect;
        std::vector<rect*> mPlayerView;
        std::vector<glm::vec3> mHatCoord;
        glm::vec3 mPlayerPos;
};
#endif // PLAYER_H
