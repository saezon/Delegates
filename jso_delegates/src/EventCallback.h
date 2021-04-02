#pragma once

namespace jso {
  class IEventCallback {
  public:
    virtual void operator()() = 0;
    virtual ~IEventCallback();
    virtual bool operator== (IEventCallback* other) = 0;
  };

  template<typename T>
    class EventCallback : public IEventCallback {
    public:
      EventCallback(T* instance, void(T::*function)())
      : _instance(instance), _function(function) {}
      virtual bool operator== (IEventCallback* other) override {
        EventCallback* otherEventCallback = dynamic_cast<EventCallback>(otherEventCallback);
        if (otherEventCallback == nullptr)
          return false;
        return (_function == otherEventCallback->_function) &&
          (_instance = otherEventCallback->_instance);
      }

      virtual void operator() () override {
        (_instance->*_function)();
      }
    private:
      void (T::*_function)();
      T* _instance;

  };
}