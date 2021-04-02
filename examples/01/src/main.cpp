#include <iostream>
#include <CommonDefs.h>
#include <Event.h>
using namespace std;

void Callback(int value)
{
  cout << "Callback: " << value << endl;
}

class Foo
{
public:
  void init(int value)
  {
    cout << value << endl;
  }
};

int main() {
  jso::Event event;
  Foo foo;
  event.addListener<Foo, &Foo::init>(&foo);
  jso::print("Hello world from jso library");
  for (auto i = 0; i < 10; i++)
    event.broadcast(i);
  system("pause");
  return 0;
}