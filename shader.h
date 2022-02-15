#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <string>
#include "transform.h"

class shader{
	public:
		static GLuint createShader(const std::string &text, GLenum shaderType);
		static std::string loadShader(const std::string &fileName);
		static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);    
		void bind();
		void update(const transform &transform);
		shader(const std::string& fileName);
		~shader();
	private:
		enum{
			TRANSFORM_U,

			NUM_UNIFORMS
		};
		static const unsigned int NUM_SHADERS = 2;
		GLuint mGlProgram;
		GLuint mGlShaders[NUM_SHADERS];
		GLuint mGlUniforms[NUM_UNIFORMS];
};

#endif //SHADER_H
