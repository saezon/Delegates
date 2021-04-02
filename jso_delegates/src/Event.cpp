#include "Event.h"

#include <iostream>

jso::Event::Event()
  : _callback(nullptr, nullptr)
{
}

jso::Event::~Event()
{
}

void jso::Event::broadcast(int ARG0) const
{
  if (_callback.second != nullptr)
    return _callback.second(_callback.first, ARG0);
}