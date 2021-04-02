# Delegates

This is a single header library for an **event system** or **delegates** taking inspiration in *Epic's Unreal Engine 4* delegate system. 

You can just import it to your project and use with without dependencies, defines or anything.
> The file is in _**jso_delegates/src/Events.h**_

## Use
### 1. Include the file 
```c++
#include "Events.h"
```
### 2. Declare a delegate type with the parameter number and type you want
```c++
DECLARE_DELEGATE_NO_PARAM(FNoParamDelegate);
DECLARE_DELEGATE_ONE_PARAM(FOneParamDelegate, TYPE);
DECLARE_DELEGATE_TWO_PARAM(FTwoParamDelegate, TYPE1, TYPE2);
```
> Right now events up to 2 parameters are supported, the number will be increasing over time, so stay tuned!
### 3. Instantiate a delegate
`FOneParamDelegate delegate;`
### 4. Add listeners to delegate
```c++
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
  FOneParam delegate;
  Foo foo;
  delegate.addListener<Foo, &Foo::callback>(&foo);
  delegate.addListener<&Callback>();
 }
```
### 5. Broadcast the event
```c++
delegate.broadcast(0);
```
### 6. Output
```
0
Callback: 0
```
### 7. Remove bindings
*1. Remove all bindings of the event*
```c++
delegate.removeAll();
```
> Specific remove will be added in the future

## Planned features or improvements
* Add events with more parameters
* Add remove binding option for an specific listener instead of having to delete them all
* Add remove binding of all listeners of a given instance
* Improve the performance of the events by getting rid of the vector holding all the listeners

### Bibliography
* [GameProgrammingPatterns](https://gameprogrammingpatterns.com/)
* [Giang Tong - CPP event delegate](https://tongtunggiang.com/2017/cpp-event-delegate/)
* [Molecular Musings - Generic, type-safe delegates and events in C++](https://tongtunggiang.com/2017/cpp-event-delegate/)
