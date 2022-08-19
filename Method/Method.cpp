/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
#include "Method.h"

Method::Method() {}

void Method::attachCallback(const Functor0 & callback) {
  callback_ = callback;
}

void Method::attachCallbackCharArg(const Functor1<char> & callback) {
  callbackCharArg_ = callback;
}

void Method::attachCallbackIntArg(const Functor1<int> & callback) {
  callbackIntArg_ = callback;
}

void Method::attachCallback2IntArg(const Functor2<int, int> & callback) {
  callback2IntArg_ = callback;
}

void Method::attachCallback3IntArg(const Functor3<int, int, int> & callback) {
  callback3IntArg_ = callback;
}

void Method::attachCallbackFloatArg(const Functor1<float> & callback) {
  callbackFloatArg_ = callback;
}

void Method::attachCallbackIntStringArg(const Functor2<int, String> & callback) {
  callbackIntStringArg_ = callback;
}

void Method::attachCallbackIntStringBoolArg(const Functor3<int, String, bool> & callback) {
  callbackIntStringBoolArg_ = callback;
}

void Method::callback() {
  if (callback_) {
    callback_();
  }
}

void Method::callbackCharArg(char val) {
  if (callbackCharArg_) {
    callbackCharArg_(val);
  }
}

void Method::callbackFloatArg(float val) {
  if (callbackFloatArg_) {
    callbackFloatArg_(val);
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

void Method::callback3IntArg(int val1, int val2, int val3) {
  if (callback3IntArg_) {
    callback3IntArg_(val1, val2, val3);
  }
}

void Method::callbackIntStringArg(int val1, String val2) {
  if (callbackIntStringArg_) {
    callbackIntStringArg_(val1, val2);
  }
}

void Method::callbackIntStringBoolArg(int val1, String val2, bool val3) {
  if (callbackIntStringBoolArg_) {
    callbackIntStringBoolArg_(val1, val2, val3);
  }
}
