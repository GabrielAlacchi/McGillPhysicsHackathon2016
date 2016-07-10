
#include "simulation.hpp"

using namespace vecmath;

Simulation::Simulation(long double timestep, std::size_t n) 
	: _timestep(timestep),
	  _buffer(n)
{
	_bodies.reserve(n);
}

void Simulation::addBody(vec3 position, vec3 velocity, long double mass) {
	_bodies.emplace_back();
	_bodies.back().init(position, velocity, 
		mass);
}

void Simulation::tick() {
	
	for (std::size_t i = 0; i < _bodies.size(); ++i) {
		Body& body = _bodies[i];
		body.tick(_bodies, i, _timestep, _buffer);
	}

	//TODO: Add code to upload this frame
	_buffer.sendFrame();
	
}
