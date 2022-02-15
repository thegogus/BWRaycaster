#ifndef SHAPES_H
#define SHAPES_H
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
#include "transform.h"
#include "shader.h"

class rect{
	public:
		rect(const float &rectWidth, const float &rectHeight, const int &windowWidth, const int &windowHeight, const glm::vec4 &color);
		void drawRect();
		float getUniformWidth();
		float getUniformHeight();
		void transformRectPos(const glm::vec3 &pos);
		void transformRectRot(const glm::vec3 &rot);
		void transformRectScale(const glm::vec3 &scale);
		void changeRectCoords(std::vector<glm::vec3> &coords);
		void changeRectColor(const glm::vec4 &color);
	private:
		vertex vertices[4] = {  vertex(glm::vec3(-0.1f, -0.1f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                                vertex(glm::vec3(-0.1f, 0.1f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                                vertex(glm::vec3(0.1f, -0.1f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                                vertex(glm::vec3(0.1f, 0.1f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) };

		unsigned int indicies[6] = {0, 1, 2, 1, 2, 3};
		glm::vec3 mRectPos;
		float mRectWidth;
		float mRectHeight;
		float x1, y1, x2, y2;
		transform transformRect;
		std::vector<mesh*> meshRect;
		std::vector<shader*> shaderRect;
		int counter;
};

#endif //SHAPES_H
