
#include "node-nbody.hpp"

namespace NodeBindings {

    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::FunctionTemplate;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::Persistent;
    using v8::String;
    using v8::Value;

    using namespace v8;

    Persistent<Function> Nbody::constructor;

    Nbody::Nbody(long double timestep) : _sim(timestep, 1) {
    }

    Nbody::~Nbody() {
    }

    void Nbody::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "Nbody"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
          // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "addBody", AddBody);
        NODE_SET_PROTOTYPE_METHOD(tpl, "renderFrames", RenderFrames);

        constructor.Reset(isolate, tpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Nbody"),
        tpl->GetFunction());
    }

    void Nbody::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new Nbody(...)`
            long double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
            Nbody* obj = new Nbody(value);
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `Nbody(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            args.GetReturnValue().Set(cons->NewInstance(argc, argv));
        }
    }

    void Nbody::AddBody(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        
        Nbody* nbody = ObjectWrap::Unwrap<Nbody>(args.Holder());
        
        if (!args[0]->IsObject())
            return;

        Handle<Object> object = Handle<Object>::Cast(args[0]);

        using namespace detail;

        vecmath::vec3 position = {
            object->Get(newString(isolate, "x"))->NumberValue(),
            object->Get(newString(isolate, "y"))->NumberValue(),
            object->Get(newString(isolate, "z"))->NumberValue()
        };

        vecmath::vec3 velocity = {      
            object->Get(newString(isolate, "v_x"))->NumberValue(),
            object->Get(newString(isolate, "v_y"))->NumberValue(),
            object->Get(newString(isolate, "v_z"))->NumberValue()
        };
        
        long double mass = object->Get(newString(isolate, "m"))->NumberValue();

        nbody->_sim.addBody(position, velocity, mass);

    }

    void Nbody::RenderFrames(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        Nbody* nbody = ObjectWrap::Unwrap<Nbody>(args.Holder());

        int numberOfFrames = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();
        
        Handle<Function> callback = Handle<Function>::Cast(args[1]);

        nbody->_sim.renderFramesAsync(numberOfFrames, callback, isolate);

    }


}




