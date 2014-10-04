#ifndef __H_RACK_RESPONSE
#define __H_RACK_RESPONSE

#include "rack/headers.hpp"

using namespace std;

namespace rack {
  class Response {
    public:
      int status;
      Headers headers;
      void *body;

      Response(int s, Headers h, void *b) {
        this->status = s;
        this->headers = h;
        this->body = b;
      }

      Response(int status, void *body) : Response(status, Headers(), body) {};
  };
}

#endif

