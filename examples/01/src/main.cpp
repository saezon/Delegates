#include <iostream>
#include <Events.h>
using namespace std;

void Callback_f(float value)
{
  cout << "Callback: " << value << endl;
}

void NoCallback()
{
  cout << "HAHAHA" << endl;
}
DECLARE_DELEGATE_ONE_PARAM(FOneParam, int);
DECLARE_DELEGATE_THREE_PARAM(FThreeParam, int, bool, char*);

void TwoParam(float value, bool b)
{
  if (b)
    cout << "Function " << value * 100.0f << endl;
  else
    cout << "Function " << value * 1000.0f << endl;
}

void Callback(int value)
{
  cout << "Callback: " << value << endl;
}

void CallbackThree(int i, bool b, char* string)
{
  cout << "Callback: " << i << " bool: " << b << " string: " << string << endl;
}

class Foo
{
public:
  void callback(int value)
  {
    cout << value << endl;
  }
};

int main() {
  FOneParam delegate(2);
  FThreeParam threeparam;
  Foo foo;
  delegate.addListener<Foo, &Foo::callback>(&foo);
  delegate.addListener<&Callback>();
  threeparam.addListener<&CallbackThree>();
  //event.removeAll();
  for (auto i = 0; i < 10; i++)
  {
    delegate.broadcast(i);
  }
  threeparam.broadcast(20, false, "Hello World");
  system("pause");
  return 0;
}