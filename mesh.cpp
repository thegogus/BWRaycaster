#include <glm/glm.hpp>
#include <cstdio>
#include <vector>
#include "mesh.h"

vertex::vertex(const glm::vec3 &pos, const glm::vec4 &color){
	this->pos = pos;
	this->color = color;
}

void vertex::setPos(const glm::vec3 &pos){
	this->pos = pos;
}

glm::vec3 *vertex::getPos(){
    return &pos;
}

glm::vec4 *vertex::getColor(){
    return &color;
}

mesh::mesh(vertex* vertices, unsigned int numVertices, unsigned int *indicies, unsigned int numIndicies){

	mDrawCount = numIndicies;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec4> colors;

	positions.reserve(numVertices);
    colors.reserve(numVertices);

    for(unsigned int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].getPos());
        colors.push_back(*vertices[i].getColor());
    }

	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[COLOR_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(colors[0]), &colors[0], GL_STREAM_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(indicies[0]), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

mesh::~mesh(){
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void mesh::updateVertexPoints(vertex* vertices, unsigned int numVertices){
    std::vector<glm::vec3> positions;
    positions.reserve(numVertices);
    for(unsigned int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].getPos());
    }

    glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(positions[0]), &positions[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void mesh::updateColor(vertex* vertices, unsigned int numVertices){
    std::vector<glm::vec4> colors;
    colors.reserve(numVertices);
    for(unsigned int i = 0; i < numVertices; i++){
        colors.push_back(*vertices[i].getColor());
    }
    glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[COLOR_VB]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(colors[0]), &colors[0]);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void mesh::draw(){
	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, mDrawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
