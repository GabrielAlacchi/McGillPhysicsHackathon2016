
#include "framebuffer.hpp"
#include <unistd.h>
#include <fstream>

using namespace vecmath;

FrameBuffer::FrameBuffer(std::size_t n) {
	_frame.resize(n);
}

void FrameBuffer::resize(std::size_t n) {
	_frame.resize(n);
}

void FrameBuffer::setNthBody(std::size_t n, vec3 pos, long double mass, long double kinetic, long double potential, vec3 angular) {
	BodyData& data = _frame.at(n);
	data.pos = pos;
	data.mass = mass;
	data.kinetic = kinetic;
	data.potential = potential;
	data.angularMomentum = angular;
}

//Wraps around the vector API
const BodyData *FrameBuffer::data() const {
    return _frame.data();
}
