#include "Method.h"

Method::Method() {}

void Method::attachCallback(const Functor0 & callback) {
  callback_ = callback;
}

void Method::attachCallbackIntArg(const Functor1<int> & callback) {
  callbackIntArg_ = callback;
}

void Method::attachCallback2IntArg(const Functor2<int, int> & callback) {
  callback2IntArg_ = callback;
}

void Method::callback() {
  if (callback_) {
    callback_();
  }
}

void Method::callbackIntArg(int val) {
  if (callbackIntArg_) {
    callbackIntArg_(val);
  }
}

void Method::callback2IntArg(int val1, int val2) {
  if (callback2IntArg_) {
    callback2IntArg_(val1, val2);
  }
}

