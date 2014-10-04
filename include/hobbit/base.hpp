#ifndef __H_HOBBIT_BASE
#define __H_HOBBIT_BASE

extern "C" {
  #define bool unsigned char
  #include <r3/r3.h>
  #undef bool
}

#include <new>
#include <exception>

#include <rack/rack.hpp>

namespace hobbit {
  typedef rack::Response *(*route_handler)(rack::Request *, rack::Response *);

  class Base : public rack::Middleware {
    node *mRoutes;
    rack::Rack mStack;

    public:

      Base(); 
      ~Base();

      node *routes();
      rack::Rack stack();

      void use(rack::Middleware *m);

      void match(const char *path, route_handler handler);
      // void get(const char *path, route_handler handler);
      // void post(const char *path, route_handler handler);
      // void put(const char *path, route_handler handler);
      // void delete(const char *path, route_handler handler);

      rack::Response *call(rack::Request *req, rack::NextMiddleware next);

    private:
      void compile_routes();
      route_handler eval_route(rack::Request *req);
  };
}

#endif
