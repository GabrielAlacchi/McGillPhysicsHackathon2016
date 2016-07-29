
// node-binding.cc
#include <node.h>
#include "node_nbody.hpp"

namespace NodeBindings {

    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports) {
          Nbody::Init(exports);
    }

    NODE_MODULE(nbody-darkmagic, InitAll)

}  // namespace demo

