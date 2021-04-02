#include <iostream>
#include <CommonDefs.h>
#include <Events.h>
using namespace std;

void Callback(int value)
{
  cout << "Callback: " << value << endl;
}

void Callback_f(float value)
{
  cout << "Callback: " << value << endl;
}

void NoCallback()
{
  cout << "HAHAHA" << endl;
}

void TwoParam(float value, bool b)
{
  if (b)
    cout << "Function " << value * 100.0f << endl;
  else
    cout << "Function " << value * 1000.0f << endl;
}

class Foo
{
public:
  void init(int value)
  {
    cout << value << endl;
  }
  void FloatPrint(float value)
  {
    cout << value << endl;
  }
  void NoParam()
  {
    cout << "Member hjahaha" << endl;
  }

  void TwoParam(float value, bool b)
  {
    if (b)
      cout << value * 100.0f << endl;
    else
      cout << value * 1000.0f << endl;
  }
};

DECLARE_DELEGATE_NO_PARAM(FNoParam);
DECLARE_DELEGATE_ONE_PARAM(FOneParam_int, int);
DECLARE_DELEGATE_ONE_PARAM(FOneParam_float, float);
DECLARE_DELEGATE_TWO_PARAM(FTwoParam, float, bool);

int main() {
  FOneParam_int event;
  FOneParam_float event_float;
  FNoParam noparam;
  FTwoParam twoparam;
  Foo foo;
  event.addListener<Foo, &Foo::init>(&foo);
  event.addListener<&Callback>();
  event_float.addListener<Foo, &Foo::FloatPrint>(&foo);
  noparam.addListener<Foo, &Foo::NoParam>(&foo);
  twoparam.addListener<&TwoParam>();
  twoparam.addListener<Foo, &Foo::TwoParam>(&foo);
  jso::print("Hello world from jso library");
  //event.removeAll();
  for (auto i = 0; i < 10; i++)
  {
    //noparam.broadcast();
    //event.broadcast(i);
    //event_float.broadcast(i * 2.0f);
    twoparam.broadcast(i, rand() % 2);
  }
  system("pause");
  return 0;
}