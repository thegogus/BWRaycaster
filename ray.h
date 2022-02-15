#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
#include <vector>
#include "shapes.h"

class ray{
    public:
        ray();
        void changeRayPosition(std::vector<glm::vec3> &coords);
        void changeRayColor(const glm::vec4 &color);
        void transformRayPos(const glm::vec3 &pos);
        void transformRayRot(const glm::vec3 &rot);
        void transformRayScale(const glm::vec3 &scale);
        void drawRay();
        float *getRayAngle();
        std::vector<glm::vec3> *getRayCoords();
        float getUniformRaySize();
    private:
        float mRayAngle;
        float mRayUniformSize;
        std::vector<rect*> mRectRay;
        std::vector<glm::vec3> mRayCoords;
};

#endif // RAY_H
