
#include "simulation.hpp"

int main(int argc, char **argv) {
	
	Simulation sim(1.0, 2);
	
	vec3 pos1, vel1;
	vec3 pos2, vel2;

	pos1 = {0.0, 0.0, 0.0};
	vel1 = {0.0, 0.0, 0.0};
	pos2 = {1.0, 0.0, 0.0};
	vel2 = {0.0, 1.0, 0.0};
	
	sim.addBody(pos1, vel1, 1e6);
	sim.addBody(pos2, vel2, 1.0);
	
	for (int i = 0; i < 61; ++i) {
		sim.tick();
	}
	
	return 0;
}
