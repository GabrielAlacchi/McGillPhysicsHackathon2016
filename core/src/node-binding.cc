
// node-binding.cc
#include <node.h>
#include "node-nbody.hpp"

namespace NodeBindings {

    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports) {
          Nbody::Init(exports);
    }

    NODE_MODULE(node_nbody, InitAll)

}  // namespace demo

