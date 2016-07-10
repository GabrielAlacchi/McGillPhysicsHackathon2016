
#ifndef SIMULATION_H_INCLUDE
#define SIMULATION_H_INCLUDE

#include "body.hpp"
#include <vector>
#include <mutex>

class Simulation {
	std::vector<Body> _bodies;
	long double _timestep;
	FrameBuffer _buffer;
	std::mutex mu;	
public:
	
	inline long double getTimestep() const 
	{ return _timestep; }
	
	inline std::size_t getSize() const 
	{ return _bodies.size(); }

	inline const Body& getBody(std::size_t index) const 
	{ return _bodies[index]; }

	Simulation(long double timestep, std::size_t n);
	void addBody(vec3 position, vec3 velocity, long double mass);
	void tick();
		
};

#endif
