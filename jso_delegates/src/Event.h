#pragma once
#include <EventCallback.h>
#include <vector>

namespace jso {
  using namespace std;
  class Event
  {
  public:
    Event();
    ~Event();

    void addListener(IEventCallback* action);
    void removeListener(IEventCallback* action);
    void fire();

  private:
    typedef vector<IEventCallback*> CallbackArray;
    CallbackArray _actions;
  };
}
