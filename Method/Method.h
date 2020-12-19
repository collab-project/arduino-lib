/*  Copyright (c) 2020, Collab
 *  All rights reserved
*/
#ifndef _METHOD_H_
#define _METHOD_H_
#include <Functor.h>

class Method
{
  public:
    Method();
    void attachCallback(const Functor0 & callback);
    void attachCallbackIntArg(const Functor1<int> & callback);
    void attachCallback2IntArg(const Functor2<int, int> & callback);
    void callback();
    void callbackIntArg(int val);
    void callback2IntArg(int val1, int val2);

  protected:
    Functor0 callback_;
    Functor1<int> callbackIntArg_;
    Functor2<int, int> callback2IntArg_;
};

#endif