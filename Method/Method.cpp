#include "Method.h"

Method::Method() {}

void Method::attachCallback(const Functor0 & callback) {
  callback_ = callback;
}

void Method::attachCallbackIntArg(const Functor1<int> & callback) {
  callbackIntArg_ = callback;
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

