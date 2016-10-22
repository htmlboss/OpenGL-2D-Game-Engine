#include "ErrorSuite.h"

namespace Engine {

	void fatalError(const std::string& errorString) {

		std::cout << errorString << std::endl;

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorString.c_str(), NULL);

		system("pause");
		SDL_Quit();
		exit(1);
	}

	bool CompileShaderStatus(GLuint shader) {

		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(shader);

			std::printf("%s\n", &errorLog[0]);
			return false;
		}

		return true;
	}
}