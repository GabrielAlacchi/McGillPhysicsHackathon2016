
#ifndef NODE_NBODY___H_INCLUDE
#define NODE_NBODY___H_INCLUDE

#include <node.h>
#include <node_object_wrap.h>
#include "simulation.hpp"
#include "framebuffer.hpp"

namespace NodeBindings {

    namespace detail {

        inline v8::Local<v8::String> newString(v8::Isolate* isolate, const char* str) {
            return v8::String::NewFromUtf8(isolate, str);
        }
        
    }

    //Necessary unit of data to generate JSON object from frames
    struct FrameData {
        BodyData body;
        bool lastInFrame;
    };

    struct Work {
        
        //uv integration
        uv_work_t request; //libuv event loop
        v8::Persistent<v8::Function> callback; //javascript callback

        //Number of frames to render
        int numberOfFrames;
        Simulation *simulation;

        std::vector<FrameData> frames;

    };

    class Nbody : public node::ObjectWrap {
         public:
            static void Init(v8::Local<v8::Object> exports);

         private:
            explicit Nbody(long double timestep);
            ~Nbody();
            
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddBody(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RenderFrames(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Persistent<v8::Function> constructor;
            
            Simulation _sim;

    };

}  // namespace demo

#endif
