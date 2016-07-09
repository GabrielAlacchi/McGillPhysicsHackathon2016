
#ifndef SIMULATION_H_INCLUDE
#define SIMULATION_H_INCLUDE

#include "body.hpp"
#include <vector>

class Simulation {
	std::vector<Body> _bodies;
public:
	
	void addBody(vec3 position, vec3 velocity);

}

#endif
