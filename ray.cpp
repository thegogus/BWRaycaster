#include <glm/glm.hpp>
#include "ray.h"
#include "shapes.h"

ray::ray(){
    mRectRay.reserve(1);
    mRectRay.push_back(new rect(1, 512, 512, 512, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    mRayCoords.reserve(4);
    for(unsigned int i = 0; i < 4; i++){
        mRayCoords[i] = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    mRayUniformSize = mRectRay[0]->getUniformWidth();
}

void ray::changeRayPosition(std::vector<glm::vec3> &coords){
    mRayCoords = coords;
    mRectRay[0]->changeRectCoords(mRayCoords);
}

void ray::changeRayColor(const glm::vec4 &color){
    mRectRay[0]->changeRectColor(color);
}

void ray::transformRayPos(const glm::vec3 &pos){
    mRectRay[0]->transformRectPos(pos);
}

void ray::transformRayRot(const glm::vec3 &rot){
    mRectRay[0]->transformRectRot(rot);
}

void ray::transformRayScale(const glm::vec3 &scale){
    mRectRay[0]->transformRectScale(scale);
}

void ray::drawRay(){
    mRectRay[0]->drawRect();
}

float *ray::getRayAngle(){
    return &mRayAngle;
}

float ray::getUniformRaySize(){
    return mRayUniformSize;
}

std::vector<glm::vec3> *ray::getRayCoords(){
    return &mRayCoords;
}
