
#ifndef BODY_H_INCLUDE_GUARD
#define BODY_H_INCLUDE_GUARD

#include "math.hpp"

class Body {
	vec3 _position;
	vec3 _velocity;
	vec3 _acceleration;
public:
	const vec3& getPosition() const;

	Body();
	
	void init(vec3 position, vec3 velocity);
	void tick();

}





#endif
