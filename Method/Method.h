#ifndef _METHOD_H_
#define _METHOD_H_
#include <Functor.h>

class Method
{
  public:
    Method();
    void attachCallback(const Functor0 & callback);
    void attachCallbackIntArg(const Functor1<int> & callback);
    void callback();
    void callbackIntArg(int val);

  protected:
    Functor0 callback_;
    Functor1<int> callbackIntArg_;
};

#endif