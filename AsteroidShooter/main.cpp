#ifdef _DEBUG
#include "vld.h"
#endif

#include "includes\AsteroidShooter.h"

#include <iostream>

int main(int argc, char** argv) {

	AsteroidShooter shooter;

	try {
		shooter.Run();
	}
	catch (...) {
		std::cerr << "Unhandled exception occured.\n";
		system("pause");
		return -1;
	}

	return 0;
}