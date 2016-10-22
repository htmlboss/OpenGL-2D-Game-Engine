
#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <GL/glew.h>
#include "ErrorSuite.h"

#include <string>
#include <vector>
#include <fstream>


namespace Engine {
	class GLSLProgram {
	public:
		GLSLProgram();
		~GLSLProgram();

		GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

		void linkShaders();

		void addAttribute(const char* attributeName);

		GLint getUniformLocation(const std::string& UniformName);

		void use(GLuint programID);
		void unuse();
	private:

		int _numAttributes;

		void compileShader(const std::string& filePath, GLuint id);

		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};
}

#endif