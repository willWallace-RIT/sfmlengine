#pragma once
#include <cstdlib>
#include <ctime>
// https://stackoverflow.com/questions/686353/random-float-number-generation
struct randFloat {
	float randF() {
		return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	}
	float randRange(float max) {
		
		
		return static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / max));
	}
	float randRange(float min, float max) {
		
		return min + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

};
struct randInt {
	int randRange(int max) {
		
		return static_cast <int> (std::rand() / (RAND_MAX / (float)max));
	}
	int randRange(int min, int max) {
		
		
		 return min + static_cast <int> (std::rand() / (RAND_MAX / (float)(max - min)));
	}
};
