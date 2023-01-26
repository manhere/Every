#include "Arduino.h"
#include "Every.h"

Every::Every(unsigned long interval, char* unit) {
  _interval = interval;
  _previousTime = micros();
  _paused = false;
  _repeat = true;
  _callback = NULL;
  if (unit == "microseconds") {
    _interval *= 1;
  }
  if (unit == "milliseconds") {
    _interval *= 1000;
  }
  if (unit == "seconds") {
    _interval *= 1000000;
  }
  if (unit == "minutes") {
    _interval *= 1000000*60;
  }
}

bool Every::trigger() {
  if (_triggered) {
    _triggered = false;
    if(!_repeat) _paused = true;
    if(_callback != NULL) _callback();
    return true;
  }
  return false;
}

void Every::update() {
  if(_paused) return;
  unsigned long currentTime = micros();
  if (currentTime < _previousTime) {
    _previousTime = currentTime;
  }
  else if (currentTime - _previousTime >= _interval) {
    _previousTime = currentTime;
    _triggered = true;
  }
}

unsigned long Every::remaining(char* unit) {
  unsigned long currentTime = micros();
  if(_paused) return 0;
  if (_previousTime > currentTime) {
    return 0;
  }
  else if (_previousTime + _interval > currentTime) {
    unsigned long remainingTime = _previousTime + _interval - currentTime;
    if (unit == "microseconds") {
      return remainingTime;
    }
    if (unit == "milliseconds") {
      return remainingTime / 1000;
    }
    if (unit == "seconds") {
      return remainingTime / 1000000;
    }
    if (unit == "minutes") {
      return remainingTime / (1000000 * 60);
    }
  }
  else {
    return 0;
  }
}


void Every::setInterval(float interval,char* unit) {
  _interval = interval;
  if (unit == "microseconds") {
    _interval *= 1;
  }
  if (unit == "milliseconds") {
    _interval *= 1000;
  }
  if (unit == "seconds") {
    _interval *= 1000000;
  }
  if (unit == "minutes") {
    _interval *= 1000000*60;
  }
}

unsigned long  Every::getInterval(char* unit) {
  unsigned long interval = _interval;	
  if (unit == "microseconds") {
    return interval /= 1;
  }
  if (unit == "milliseconds") {
    return interval /= 1000;
  }
  if (unit == "seconds") {
    return interval /= 1000000;
  }
  if (unit == "minutes") {
    return interval /= 1000000*60;
  }
  
}

void Every::setRepeat(bool repeat) {
  _repeat = repeat;
}

void Every::setCallback(void (*callback)()) {
  _callback = callback;
}
