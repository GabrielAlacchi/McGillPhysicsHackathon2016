
#ifndef FRAME_BUFFER_H_INCLUDE
#define FRAME_BUFFER_H_INCLUDE

#include "math.hpp"
#include <vector>
#include <string>

using namespace vecmath;

struct BodyData {
	vec3 pos;
	long double mass;
	long double kinetic;
	long double potential;
	vec3 angularMomentum;
};

class FrameBuffer {
	std::vector<BodyData> _frame;
public:
	FrameBuffer(std::size_t n);
	void resize(std::size_t n);
	std::size_t getSize() const { return _frame.size(); }
	void setNthBody(std::size_t n, vec3 pos, long double mass, long double kinetic, long double potential, vec3 angular);

    const BodyData* data() const;
};

#endif
