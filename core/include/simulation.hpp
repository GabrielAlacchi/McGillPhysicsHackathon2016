
#ifndef SIMULATION_H_INCLUDE
#define SIMULATION_H_INCLUDE

#include "body.hpp"
#include <vector>
#include <mutex>
#include <node.h>
#include <uv.h>
#include <v8.h>


class Simulation {
	std::vector<Body> _bodies;
	long double _timestep;
	FrameBuffer _buffer;
	std::mutex _mu;	

    //The functions should be static so they can be passed as function pointers to libuv
    //Without having to use std::bind

    static void renderFramesAsyncBegin(uv_work_t *req);
    static void renderFramesAsyncEnd(uv_work_t *req, int status);

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

    void renderFramesAsync(int numberOfFrames, v8::Handle<v8::Function> callback, v8::Isolate* isolate);

};

#endif
