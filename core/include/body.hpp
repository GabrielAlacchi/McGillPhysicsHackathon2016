
#ifndef BODY_H_INCLUDE_GUARD
#define BODY_H_INCLUDE_GUARD

#include "math.hpp"
#include <vector>
#include "framebuffer.hpp"

constexpr long double G = 8.89e-10;

using namespace vecmath;

class Body {
	vec3 _position;
	vec3 _velocity;
	vec3 _acceleration;
	long double _mass;
	long double _potential;
	void addToAccel(const Body& body);
public:
	const vec3& getPosition() const 
	{ return _position; }
	
	long double getMass() const 
	{ return _mass; }
	
	Body();

	void init(vec3 position, vec3 velocity, 
		long double mass);
	void tick(const std::vector<Body>& bodies, std::size_t myIndex, long double timeStep, FrameBuffer& buffer);
			
};

#endif
