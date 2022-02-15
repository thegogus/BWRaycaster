#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>

class transform{
	public:
		transform(const glm::vec3 &pos = glm::vec3(0, 0, 0), const glm::vec3 &rot = glm::vec3(0, 0, 0), const glm::vec3 &scale = glm::vec3(1.0, 1.0, 1.0));
		glm::mat4 getModel();
		glm::vec3 *getPos();
		glm::vec3 *getRot();
		glm::vec3 *getScale();
		void setPos(const glm::vec3& pos);
		void setRot(const glm::vec3& rot);
		void setScale(const glm::vec3& scale);
		glm::mat4 getModel() const;
	private:
		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale;
};

#endif //TRANSFORM_H
