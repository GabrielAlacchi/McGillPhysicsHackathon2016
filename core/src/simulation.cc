
#include "simulation.hpp"
#include "node-nbody.hpp"

using namespace vecmath;
using namespace std;
using namespace v8;

Simulation::Simulation(long double timestep, std::size_t n) 
	: _timestep(timestep),
	  _buffer(n)
{
	_bodies.reserve(n);
}

void Simulation::addBody(vec3 position, vec3 velocity, long double mass) {
	
	lock_guard<mutex> lock(_mu);	
	
	//_buffer.resize(_buffer.getSize() + 1);
	_bodies.emplace_back();
	
	//km/s to AU/day
	constexpr long double conversionFactor = 1.0 / 1731.45684;
	velocity = conversionFactor * velocity;
	
	_bodies.back().init(position, velocity, 
		mass);

    _buffer.resize(_bodies.size());
}

void Simulation::tick() {
	
    for (size_t i = 0; i < _bodies.size(); ++i) {
		Body& body = _bodies[i];
		body.tick(_bodies, i, _timestep, _buffer);
	}
	
}

void Simulation::renderFramesAsyncBegin(uv_work_t *req) {
    
    // get the pointer to the Work struct passed into the uv_work_t
    NodeBindings::Work *render_work = static_cast<NodeBindings::Work*>(req->data);
    
    Simulation *simulation = render_work->simulation;
    FrameBuffer &buffer = simulation->_buffer;

    //Vector of frames
    render_work->frames.reserve(simulation->_bodies.size() * render_work->numberOfFrames);
    for (size_t i = 0; i < render_work->numberOfFrames; ++i) {
        //Lock the mutex to avoid adding bodies while mid frame calculation  
        std::lock_guard<std::mutex> lock(simulation->_mu);
        render_work->simulation->tick();
        
        const BodyData *bufferRaw = buffer.data();

        const size_t size = buffer.getSize();
        for (size_t t = 0; t < size; ++t) {
            render_work->frames.push_back({
               bufferRaw[t], // BodyData body; in FrameData struct definition
               t == size - 1 // bool lastInFrame; in FrameData struct definition
            });
        }

    }

}

void Simulation::renderFramesAsyncEnd(uv_work_t *req, int status) {

    NodeBindings::Work *render_work = static_cast<NodeBindings::Work*>(req->data);
   
    Isolate* isolate = Isolate::GetCurrent();
    
    HandleScope handleScope(isolate);

    Handle<Array> jsFrames = Array::New(isolate, render_work->numberOfFrames);
    
    size_t frameIndex = 0;
    size_t subArrayIndex = 0;
    for (int i = 0; i < render_work->numberOfFrames; ++i) {
        Handle<Array> bodies = Array::New(isolate);
        do {
            
            using namespace NodeBindings::detail;

            const BodyData& body = render_work->frames[frameIndex].body;
            Handle<Object> obj = Object::New(isolate);
            obj->Set(newString(isolate, "x"), Number::New(isolate, body.pos.x));
            obj->Set(newString(isolate, "y"), Number::New(isolate, body.pos.y));
            obj->Set(newString(isolate, "z"), Number::New(isolate, body.pos.z));
            obj->Set(newString(isolate, "mass"), Number::New(isolate, body.mass));
            obj->Set(newString(isolate, "kinetic"), Number::New(isolate, body.kinetic));
            obj->Set(newString(isolate, "ang_x"), Number::New(isolate, body.angularMomentum.x));
            obj->Set(newString(isolate, "ang_y"), Number::New(isolate, body.angularMomentum.y));
            obj->Set(newString(isolate, "ang_z"), Number::New(isolate, body.angularMomentum.z));
            
            bodies->Set(subArrayIndex++, obj);

        } while (render_work->frames[frameIndex++].lastInFrame);

        jsFrames->Set(i, bodies);

        subArrayIndex = 0;

    }
    
    Local<Value> argv[1] = { jsFrames };

    Local<Function>::New(isolate, render_work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, argv);

    render_work->callback.Reset();

    delete render_work;

}

//Called by Nbody class from javascript
//Queues up the work of rendering (numberOfFrames) to be done async
void Simulation::renderFramesAsync(int numberOfFrames, Handle<Function> callback, Isolate* isolate) {
    NodeBindings::Work *render_work = new NodeBindings::Work;
    
    //Pass the work object to the uv_work_t
    render_work->request.data = render_work;

    render_work->numberOfFrames = numberOfFrames;

    //Pass a reference to the instance of simulation
    render_work->simulation = this;

    //Cast the handle<function> to a persistent
    render_work->callback.Reset(isolate, callback);

    uv_queue_work(uv_default_loop(), &(render_work->request), 
                  Simulation::renderFramesAsyncBegin,
                  Simulation::renderFramesAsyncEnd);

}


