#ifndef __H_RACK_RACK
#define __H_RACK_RACK

#include "rack/middleware.hpp"

namespace rack {
  class Rack {
      Chain chain;

    public:
      ~Rack();

      void use(Middleware *m);
      Response *execute(Request *req); 

    private:
      Response *execute(Request *req, Response *res, int pos);
  };
}

#endif

