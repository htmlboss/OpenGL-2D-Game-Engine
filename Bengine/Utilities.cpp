#include "includes\Utilities.h"
namespace Engine {

	int rangeRandomNum(int min, int max) {

		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_int_distribution<int> distr(min, max);

		return distr(generator);
	}
}