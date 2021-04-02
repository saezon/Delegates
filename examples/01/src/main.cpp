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
  Foo foo;
  delegate.addListener<Foo, &Foo::callback>(&foo);
  delegate.addListener<&Callback>();
  //event.removeAll();
  for (auto i = 0; i < 10; i++)
  {
    delegate.broadcast(i);
  }
  system("pause");
  return 0;
}