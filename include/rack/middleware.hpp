#ifndef __H_RACK_MIDDLEWARE
#define __H_RACK_MIDDLEWARE

#include <iostream>
#include <functional>
#include <vector>

#include "rack/request.hpp" 
#include "rack/response.hpp" 

namespace rack {
  using NextMiddleware = std::function<Response *()>;

  class Middleware {
    public:
      virtual Response *call(Request *req, NextMiddleware next) = 0;
  };

  typedef vector<Middleware *> Chain;
}

#endif
