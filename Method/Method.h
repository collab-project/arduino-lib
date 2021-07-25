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
    void attachCallbackIntArg(const Functor1<int> & callback);
    void attachCallback2IntArg(const Functor2<int, int> & callback);
    void attachCallbackFloatArg(const Functor1<float> & callback);
    void attachCallbackIntStringArg(const Functor2<int, String> & callback);
    void callback();
    void callbackIntArg(int val);
    void callback2IntArg(int val1, int val2);
    void callbackIntStringArg(int val1, String val2);
    void callbackFloatArg(float val);

  protected:
    Functor0 callback_;
    Functor1<int> callbackIntArg_;
    Functor2<int, int> callback2IntArg_;
    Functor2<int, String> callbackIntStringArg_;

    Functor1<float> callbackFloatArg_;
};

#endif