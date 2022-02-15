#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class vertex{
	public:
		vertex(const glm::vec3 &pos, const glm::vec4 &color);
		void setPos(const glm::vec3 &pos);
		glm::vec3 *getPos();
		glm::vec4 *getColor();
	private:
		glm::vec3 pos;
		glm::vec4 color;
};

class mesh{
	public:
		void draw();
		mesh(vertex* vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndicies);
		~mesh();
		void updateVertexPoints(vertex* vertices, unsigned int numVertices);
		void updateColor(vertex* vertices, unsigned int numVertices);
	private:
		enum{
			POSITION_VB,
			COLOR_VB,
			INDEX_VB,
			NUM_BUFFERS
		};
		GLuint mVertexArrayObject;
		GLuint mVertexArrayBuffers[NUM_BUFFERS];
		unsigned int mDrawCount;
};

#endif //MESH_H
