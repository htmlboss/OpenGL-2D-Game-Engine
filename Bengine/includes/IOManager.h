#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <vector>
#include <string>
#include <fstream>

#include "ErrorSuite.h"

namespace Engine {
	class IOManager {

	public:
		static bool ReadFileToBuffer(const std::string& filePath, std::vector<char>& buffer);
	};
}

#endif // !IOMANAGER_H