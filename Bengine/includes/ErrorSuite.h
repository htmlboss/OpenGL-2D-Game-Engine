#ifndef ERRORSUITE_H
#define ERRORSUITE_H

#include <string>
#include <iostream>
#include <vector>
#include <SDL\include\SDL.h>
#include <GL\glew.h>

namespace Engine {
	//Generic Fatal Error
	extern void fatalError(const std::string& errorString);

	//Checks status of shader compilation
	extern bool CompileShaderStatus(GLuint shader);
}

#endif
