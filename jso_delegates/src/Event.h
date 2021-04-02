#pragma once
#include <vector>

namespace jso {
  using namespace std;
  class Event
  {
    typedef void* InstancePointer;
    typedef void (*InternalFunction)(InstancePointer, int);
    typedef std::pair<InstancePointer, InternalFunction> Callback;

    template<void (*Function)(int)>
    static void FunctionCallback(InstancePointer, int ARG0)
    {
      return (Function)(ARG0);
    }

    template<class C, void (C::* Function)(int)>
    static void ClassMethodCallback(InstancePointer instance, int ARG0)
    {
      return (static_cast<C*>(instance)->*Function)(ARG0);
    }

  public:
    Event();
    ~Event();
    template<void (*Function)(int)>
    void addListener()
    {
      _callback.first = nullptr;
      _callback.second = &FunctionCallback<Function>;
    }
    template<class C, void (C::* Function)(int)>
    void addListener(C* instance)
    {
      _callback.first = instance;
      _callback.second = &ClassMethodCallback<C, Function>;
    }
    void broadcast(int ARG0) const;

  private:
    Callback _callback;
  };
}
