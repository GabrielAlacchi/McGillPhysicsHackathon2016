
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
	std::string unloadJSON();
	int _counter = 0;
	char _curlBuffer[1000];
	void appendToFile(std::string json, bool start);
	long double _timestep;
public:
	FrameBuffer(std::size_t n, long double timestep);
	void resize(std::size_t n);
	void setNthBody(std::size_t n, vec3 pos, long double mass, long double kinetic, long double potential, vec3 angular);
	void sendFrame();
};

#endif
