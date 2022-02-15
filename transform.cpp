#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "./transform.h"


transform::transform(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scale){
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
}

glm::vec3 *transform::getScale(){
	return &scale;
}

glm::vec3 *transform::getPos(){
	return &pos;
}

glm::vec3 *transform::getRot(){
	return &rot;
}

void transform::setPos(const glm::vec3& pos){
	this->pos = pos;
}

void transform::setRot(const glm::vec3& rot){
	this->rot = rot;
}

void transform::setScale(const glm::vec3& scale){
	this->scale = scale;
}

glm::mat4 transform::getModel() const{
	glm::mat4 posMatrix = glm::translate(pos);
	glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}
