#include <iostream>
#include <vector>

#include <rack/rack.hpp>
#include <hobbit/base.hpp>

using namespace std;
using namespace rack;

class Controller : public hobbit::Base {
  typedef hobbit::Base super;

  public:
    Controller() {
      super();

      match("/foo", [](Request *req, Response *res) {
        printf("Matched!\n");

        res->body = (void *)"i got the route";

        return res;
      });

      match("/bar", [](Request *req, Response *res) {
          printf("Got the bar\n");

          res->body = (void *)"Got the bar";

          return res;
      });
    };
};

class NotFound : public Middleware {
  public:
    rack::Response *call(rack::Request *req, rack::NextMiddleware next) {
      Response *res = next();

      res->status = 404;

      return res;
    };
};

#include <algorithm>
#include <string>

class Uppercaser : public Middleware {
  public:
    rack::Response *call(rack::Request *req, rack::NextMiddleware next) {
      Response *res = next();
      cout << (char *)res->body << endl;

      string s = (char *)res->body;

      transform(s.begin(), s.end(), s.begin(), ::toupper);

      res->body = (void *)s.c_str();

      return res;
    };
};

int main(int argc, char *argv[])
{
  printf("starting\n");

  Rack app;

  app.use(new Uppercaser);
  app.use(new NotFound);
  app.use(new Controller);
  
  // Middleware m1, m2, m3;
  // app.use(&m1);
  // app.use(&m2);
  // app.use(&m3);

  Request request(200, Headers(), (void *)"foo");

  // result is allocated on the heap.
  Response *result = app.execute(&request);

  printf("done: %d %s\n", result->status, result->body);

  delete result;

  return 0;
}
