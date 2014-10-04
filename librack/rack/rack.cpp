#include "rack/rack.hpp"

using namespace rack;

Rack::~Rack()
{
  for(auto m : chain) {
    delete m;
  }
}

void Rack::use(Middleware *m)
{
  chain.push_back(m);
}

Response *Rack::execute(Request *req) 
{
  Response *res = new Response(200, (void *)"");

  return execute(req, res, 0);
}
  

Response *Rack::execute(Request *req, Response *res, int pos)
{
  if(chain.size() == 0) {
    return res;
  }

  Middleware *current = chain.at(pos);

  if(pos + 1 == chain.size())  {
    res = current->call(req, [&res, this]() -> Response * { return res; });
  } else {
    res = current->call(req, [&req, &res, &pos, this]() -> Response * {
      return execute(req, res, pos + 1);
    });
  }

  return res;
}
