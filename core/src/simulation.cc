
#include "simulation.hpp"

using namespace vecmath;

Simulation::Simulation(long double timestep, std::size_t n) 
	: _timestep(timestep),
	  _buffer(n, timestep)
{
	_bodies.reserve(n);
}

void Simulation::addBody(vec3 position, vec3 velocity, long double mass) {
	
	std::lock_guard<std::mutex> lock(mu);	
	
	//_buffer.resize(_buffer.getSize() + 1);
	_bodies.emplace_back();
	
	//km/s to AU/day
	constexpr long double conversionFactor = 1.0 / 1731.45684;
	velocity = conversionFactor * velocity;
	
	_bodies.back().init(position, velocity, 
		mass);
}

void Simulation::tick() {
	
	std::lock_guard<std::mutex> lock(mu);

	for (std::size_t i = 0; i < _bodies.size(); ++i) {
		Body& body = _bodies[i];
		body.tick(_bodies, i, _timestep, _buffer);
	}

	_buffer.sendFrame();
	
}
