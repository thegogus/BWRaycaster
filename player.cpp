#include <vector>
#include <glm/glm.hpp>
#include "player.h"
#define PI 3.14159265359

player::player(const glm::vec3 &playerPos, const unsigned int &screenWidth, const unsigned int &screenHeight, const glm::vec4 &color){
    mPlayerPos = playerPos;
    mPlayerRect.reserve(1);
    mPlayerRect.push_back(new rect(10, 10, screenWidth, screenHeight, color));
    mPlayerRect[0]->transformRectPos(mPlayerPos);
    mPlayerView.reserve(1);
    mPlayerView.push_back(new rect(2, 16, screenWidth, screenHeight, color));
    mPlayerView[0]->transformRectPos(glm::vec3(mPlayerPos.x, mPlayerPos.y+mPlayerRect[0]->getUniformHeight(), 0.0f));
}

void player::drawPlayer(){
    mPlayerRect[0]->drawRect();
}

void player::changePlayerPosition(const glm::vec3 &pos){
    mPlayerPos.x = pos.x;
    mPlayerPos.y = pos.y;
    mPlayerPos.z = pos.z;
    mPlayerRect[0]->transformRectPos(pos);
}

void player::changePlayerRotation(const glm::vec3 &rot, const float &angle){
    mPlayerRect[0]->transformRectRot(rot);
}
