/*  Copyright (c) 2020-2021, Collab
 *  All rights reserved
*/
#ifndef _METHOD_H_
#define _METHOD_H_
#include <Arduino.h>
#include <Functor.h>

class Method
{
  public:
    Method();
    void attachCallback(const Functor0 & callback);
    void attachCallbackCharArg(const Functor1<char> & callback);
    void attachCallbackIntArg(const Functor1<int> & callback);
    void attachCallback2IntArg(const Functor2<int, int> & callback);
    void attachCallback3IntArg(const Functor3<int, int, int> & callback);
    void attachCallbackFloatArg(const Functor1<float> & callback);
    void attachCallbackIntStringArg(const Functor2<int, String> & callback);
    void attachCallbackIntStringBoolArg(const Functor3<int, String, bool> & callback);
    void callback();
    void callbackCharArg(char val);
    void callbackIntArg(int val);
    void callback2IntArg(int val1, int val2);
    void callback3IntArg(int val1, int val2, int val3);
    void callbackIntStringArg(int val1, String val2);
    void callbackIntStringBoolArg(int val1, String val2, bool val3);
    void callbackFloatArg(float val);

  protected:
    Functor0 callback_;
    Functor1<char> callbackCharArg_;
    Functor1<int> callbackIntArg_;
    Functor1<float> callbackFloatArg_;
    Functor2<int, int> callback2IntArg_;
    Functor3<int, int, int> callback3IntArg_;
    Functor2<int, String> callbackIntStringArg_;
    Functor3<int, String, bool> callbackIntStringBoolArg_;
};

#endif