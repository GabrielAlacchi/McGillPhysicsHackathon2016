
#include "body.hpp"

const vec3& Body::getPosition() const {
	return _position;
}

Body::Body() 
{}

void Body::init(vec3 position, vec3 velocity) {
	this->_position = position;
	this->_velocity = velocity;
}


