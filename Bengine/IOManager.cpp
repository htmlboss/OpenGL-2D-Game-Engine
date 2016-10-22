#include "IOManager.h"

namespace Engine {

	bool IOManager::ReadFileToBuffer(const std::string& filePath, std::vector<char>& buffer) {

		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to end of file
		file.seekg(0, std::ios::end);
		//get file size
		long int fileSize = file.tellg();
		//Return to beginning of file
		file.seekg(0, std::ios::beg);
		//ignore file headers
		fileSize -= file.tellg();


		buffer.resize(fileSize);
		file.read(&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}