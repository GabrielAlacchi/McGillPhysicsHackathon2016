
#include "body.hpp"

using namespace vecmath;

void Body::addToAccel(const Body& body) {
	const vec3& bodyPosition = body.getPosition();
	const vec3& displacement = 
		_position - bodyPosition;
	const vec3& outwardsUnit = 
		vecmath::normalize(displacement);
	
	long double numerator = 
		-G * body.getMass();	
	long double displacementScalar = vecmath::magnitude(displacement);
	
	long double denominator = std::pow(displacementScalar, 2);
	
	long double magnitude = numerator / denominator;
	_acceleration = _acceleration 
				+ magnitude * outwardsUnit; 	

	_potential += magnitude * _mass * displacementScalar;

}

Body::Body() 
{
	_acceleration = vecmath::zeroVec;
}

void Body::init(vec3 position, vec3 velocity, long double mass) {
	this->_position = position;
	this->_velocity = velocity;
	this->_mass = mass;
}

void Body::tick(const std::vector<Body>& bodies, std::size_t myIndex, long double timeStep, FrameBuffer& buffer) {
	
	//Initialize the deltaV and deltaPos with the last frame's acceleration and velocity
	vec3 deltaV = timeStep * 
		_acceleration;
	vec3 deltaPos = timeStep * _velocity + 0.5 * timeStep * timeStep * _acceleration;

	_acceleration = vecmath::zeroVec;
	_potential = 0.0;
	std::size_t size = bodies.size();
	for (std::size_t i = 0; i < size; ++i) {
		if (i != myIndex) {
			const Body& body = bodies[i];
			addToAccel(body);			
		}
	}

	long double kinetic = 0.5 * _mass * vecmath::sqMagnitude(_velocity);
	vec3 angularMomentum = vecmath::cross(_position, _mass * _velocity);

	buffer.setNthBody(myIndex, _position, _mass, kinetic, _potential, angularMomentum);

	//After calculating the new acceleration change the velocity and position of the object, this is the end result of the frame	

	_position = _position + deltaPos;
	_velocity = _velocity + deltaV;

}

