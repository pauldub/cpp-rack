#include "hobbit/base.hpp"

using namespace hobbit;

Base::Base() 
{
  mRoutes = r3_tree_create(10);
  if(mRoutes == nullptr) {
    throw std::bad_alloc();
  }
}

Base::~Base() 
{
  if(mRoutes) {
    r3_tree_free(mRoutes);
  }
}

node *Base::routes() 
{
  return mRoutes;
}

rack::Rack Base::stack() 
{
  return mStack;
}

void Base::use(rack::Middleware *m) 
{
  mStack.use(m);
}

void Base::match(const char *path, route_handler handler) 
{
  r3_tree_insert_path(mRoutes, path, (void *)handler);
}

rack::Response *Base::call(rack::Request *req, rack::NextMiddleware next)
{
  rack::Response *res = next();

  try {
    compile_routes();

    route_handler handler = this->eval_route(req);

    return handler(req, res);
  } catch(exception &e) {
    printf("error: %s\n", e.what());
  }

  return res;
}

void Base::compile_routes()
{
  char *errstr = nullptr;
  int err = r3_tree_compile(mRoutes, &errstr);
  if(err != 0) {
    throw std::runtime_error(errstr);
    free(errstr);
  }

}

route_handler Base::eval_route(rack::Request *req)
{
  node *match = r3_tree_match(mRoutes, "/foo", NULL);
  if(match == nullptr) {
    return nullptr;
  }

  route_handler handler = (route_handler)match->data;
  if(handler == nullptr) {
    throw std::runtime_error("Invalid route handler");
  }

  return handler;
}
