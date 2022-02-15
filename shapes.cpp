#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
#include "shapes.h"
#include "shader.h"
#include "transform.h"

rect::rect(const float &rectWidth, const float &rectHeight, const int &windowWidth, const int &windowHeight, const glm::vec4 &color){
	float tempWidth = rectWidth/windowWidth;
	float tempHeight = rectHeight/windowHeight;
	mRectHeight = tempHeight;
	mRectWidth = tempWidth;
	x1 = -1.0f * tempWidth;
	y1 = -1.0f * tempHeight;
	x2 = tempWidth;
	y2 = tempHeight;
	vertices[0].setPos(glm::vec3(x1, y1, 0.0f));
	vertices[1].setPos(glm::vec3(x2, y1, 0.0f));
	vertices[2].setPos(glm::vec3(x1, y2, 0.0f));
	vertices[3].setPos(glm::vec3(x2, y2, 0.0f));
	for(unsigned int i = 0; i < 4; i++){
        vertices[i].getColor()->x = color.x;
        vertices[i].getColor()->y = color.y;
        vertices[i].getColor()->z = color.z;
        vertices[i].getColor()->w = color.w;
	}
	meshRect.push_back(new mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indicies, sizeof(indicies)/sizeof(indicies[0])));
	shaderRect.push_back(new shader("./basicShader"));
}

void rect::transformRectPos(const glm::vec3 &pos){
    transformRect.getPos()->x = pos.x;
	transformRect.getPos()->y = pos.y;
	transformRect.getPos()->z = pos.z;
}

void rect::transformRectRot(const glm::vec3 &rot){
    transformRect.getRot()->x = rot.x;
	transformRect.getRot()->y = rot.y;
	transformRect.getRot()->z = rot.z;
}

void rect::transformRectScale(const glm::vec3 &scale){
    transformRect.getScale()->x = scale.x;
	transformRect.getScale()->y = scale.y;
	transformRect.getScale()->z = scale.z;
}

float rect::getUniformWidth(){
	return x2+x2;
}

float rect::getUniformHeight(){
	return y2+y2;
}

void rect::changeRectColor(const glm::vec4 &color){
    for(int i = 0; i < 4; i++){
        vertices[i].getColor()->x = color.x;
        vertices[i].getColor()->y = color.y;
        vertices[i].getColor()->z = color.z;
        vertices[i].getColor()->w = color.w;
    }
    meshRect[0]->updateColor(vertices, sizeof(vertices) / sizeof(vertices[0]));
}

void rect::changeRectCoords(std::vector<glm::vec3> &coords){
    for(int i = 0; i < (int)coords.size(); i++){
        vertices[i].getPos()->x = coords[i].x;
        vertices[i].getPos()->y = coords[i].y;
        vertices[i].getPos()->z = coords[i].z;
    }
    meshRect[0]->updateVertexPoints(vertices, sizeof(vertices) / sizeof(vertices[0]));
}

void rect::drawRect(){
	shaderRect[0]->bind();
	shaderRect[0]->update(transformRect);
	meshRect[0]->draw();
}
