
#include "simulation.hpp"

Simulation::Simulation(long double timestep, int n) 
	: _timestep(timestep)
{
	_bodies.reserve(n);
}

void Simulation::addBody(vec3 position, vec3 velocity) {
	_bodies.emplace_back();
	_bodies.back().init(position, velocity);
}


