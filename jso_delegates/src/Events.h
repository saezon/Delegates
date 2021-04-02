#pragma once

#include <vector>

namespace jso {
  using namespace std;
  using InstancePointer = void*;
#define EVENT_REMOVE_ALL_IMPLEMENTATION(callbacks) callbacks.clear();
#define EVENT_ADD_LISTENER_FUNCTION_IMPLEMENTATION(callbacks, function) \
   for (const auto& callback : _callbacks) { \
     if (callback->first == nullptr && callback->second == &FunctionCallback<Function>)\
       return; }\
   auto ptr = std::make_unique<Callback>(nullptr, &FunctionCallback<Function>); \
   _callbacks.push_back(move(ptr));
#define EVENT_ADD_LISTENER_CLASS_METHOD_IMPLEMENTATION(callbacks, method) \
  for (const auto& callback : _callbacks) { \
    if (callback->first == instance && \
      callback->second == &ClassMethodCallback<C, Function>) \
      return;} \
  auto ptr = make_unique<Callback>(instance, &ClassMethodCallback<C, Function>); \
  _callbacks.push_back(move(ptr));
#define EVENT_BROADCAST_IMPLEMENTATION(callbacks, ...) \
  for (const auto& callback : callbacks) \
  callback->second(callback->first, __VA_ARGS__);

  //! NO PARAM
  template<typename T>
  class Event
  {
    typedef void (*InternalFunction)(InstancePointer);
    using Callback = std::pair<InstancePointer, InternalFunction>;
    template<void (*Function)()>
    static void FunctionCallback(InstancePointer)
    {
      return (Function)();
    }

    template<class C, void (C::* Function)()>
    static void ClassMethodCallback(InstancePointer instance)
    {
      return (static_cast<C*>(instance)->*Function)();
    }

  public:
    Event()
    {
    }
    ~Event() {}
    template<void (*Function)()>
    void addListener()
    {
      EVENT_ADD_LISTENER_FUNCTION_IMPLEMENTATION(_callbacks, &FunctionCallback<Function>);
    }
    template<class C, void (C::* Function)()>
    void addListener(C* instance)
    {
      EVENT_ADD_LISTENER_CLASS_METHOD_IMPLEMENTATION(_callbacks, &ClassMethodCallback<C, Function>);
    }
    void broadcast() const
    {
      EVENT_BROADCAST_IMPLEMENTATION(_callbacks);
    }
    void removeAll()
    {
      EVENT_REMOVE_ALL_IMPLEMENTATION(_callbacks);
    }

  private:
    using CallbackArray = vector<unique_ptr<Callback>>;
    CallbackArray _callbacks;
  };

  //! ONE PARAM
  template<typename R, typename ARG0>
  class Event<R(ARG0)>
  {
    typedef void (*InternalFunction)(InstancePointer, ARG0);
    using Callback = std::pair<InstancePointer, InternalFunction>;
    template<void (*Function)(ARG0)>
    static void FunctionCallback(InstancePointer, ARG0 arg0)
    {
      return (Function)(arg0);
    }

    template<class C, void (C::* Function)(ARG0)>
    static void ClassMethodCallback(InstancePointer instance, ARG0 arg0)
    {
      return (static_cast<C*>(instance)->*Function)(arg0);
    }

  public:
    Event() {}
    ~Event() {}
    template<void (*Function)(ARG0)>
    void addListener()
    {
      EVENT_ADD_LISTENER_FUNCTION_IMPLEMENTATION(_callbacks, &FunctionCallback<Function>);
    }
    template<class C, void (C::* Function)(ARG0)>
    void addListener(C* instance)
    {
      EVENT_ADD_LISTENER_CLASS_METHOD_IMPLEMENTATION(_callbacks, &ClassMethodCallback<C, Function>);
    }
    void broadcast(ARG0 arg0) const
    {
      EVENT_BROADCAST_IMPLEMENTATION(_callbacks, arg0);
    }
    void removeAll()
    {
      EVENT_REMOVE_ALL_IMPLEMENTATION(_callbacks);
    }

  private:
    using CallbackArray = vector<unique_ptr<Callback>>;
    CallbackArray _callbacks;
  };

  //! TWO PARAM
  template<typename R, typename ARG0, typename ARG1>
  class Event<R(ARG0, ARG1)>
  {
    typedef void (*InternalFunction)(InstancePointer, ARG0, ARG1);
    using Callback = std::pair<InstancePointer, InternalFunction>;
    template<void (*Function)(ARG0, ARG1)>
    static void FunctionCallback(InstancePointer, ARG0 arg0, ARG1 arg1)
    {
      return (Function)(arg0, arg1);
    }

    template<class C, void (C::* Function)(ARG0, ARG1)>
    static void ClassMethodCallback(InstancePointer instance, ARG0 arg0, ARG1 arg1)
    {
      return (static_cast<C*>(instance)->*Function)(arg0, arg1);
    }

  public:
    Event() {}
    ~Event() {}
    template<void (*Function)(ARG0, ARG1)>
    void addListener()
    {
      EVENT_ADD_LISTENER_FUNCTION_IMPLEMENTATION(_callbacks, &FunctionCallback<Function>);
    }
    template<class C, void (C::* Function)(ARG0, ARG1)>
    void addListener(C* instance)
    {
      EVENT_ADD_LISTENER_CLASS_METHOD_IMPLEMENTATION(_callbacks, &ClassMethodCallback<C, Function>);
    }
    void broadcast(ARG0 arg0, ARG1 arg1) const
    {
      EVENT_BROADCAST_IMPLEMENTATION(_callbacks, arg0, arg1);
    }
    void removeAll()
    {
      EVENT_REMOVE_ALL_IMPLEMENTATION(_callbacks);
    }

  private:
    using CallbackArray = vector<unique_ptr<Callback>>;
    CallbackArray _callbacks;
  };
}

#define DECLARE_DELEGATE_NO_PARAM(name) using name = jso::Event<void>
#define DECLARE_DELEGATE_ONE_PARAM(name, type) using name = jso::Event<void(type)>
#define DECLARE_DELEGATE_TWO_PARAM(name, type1, type2) using name = jso::Event<void(type1, type2)>
