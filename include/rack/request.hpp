#ifndef __H_RACK_REQUEST
#define __H_RACK_REQUEST

#include "rack/headers.hpp"

using namespace std;

namespace rack {
  class Request {
    public:
      int status;
      Headers headers;
      void *body;

      Request(int s, Headers h, void *b) {
        this->status = s;
        this->headers = h;
        this->body = b;
      }
  };
}

#endif

