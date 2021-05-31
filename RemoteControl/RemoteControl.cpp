/*
* Copyright (c) 2021 Collab
* All rights reserved
*/
/*
  RemoteControl.cpp - Remote control.
*/

#include "RemoteControl.h"

RemoteControl::RemoteControl(
  int recv_pin,
  Method cmd_recv_cb,
  bool led_feedback,
  int led_pin,
  bool debug
) {
  _receivePin = recv_pin;
  _ledPin = led_pin;
  _debug = debug;
  _ledFeedback = led_feedback;
  _cmdReceiveCallback = cmd_recv_cb;
}

void RemoteControl::begin() {
  // start the receiver
  if (_ledFeedback == false) {
    IrReceiver.begin(_receivePin, _ledFeedback);
  } else {
    IrReceiver.begin(_receivePin, _ledFeedback, _ledPin);
  }
}

/*
* Check if received data is available and if yes, try to decode it.
* Decoded result is in the IrReceiver.decodedIRData structure.
*/
void RemoteControl::loop() {
  if (IrReceiver.decode()) {
    // enable for verbose logging
    if (_debug) {
      printSummary();
    }

    // enable receiving of the next value
    IrReceiver.resume();

    // check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      int repeat = 0;
      // check for repeat
      if (IrReceiver.decodedIRData.flags & (IRDATA_FLAGS_IS_AUTO_REPEAT | IRDATA_FLAGS_IS_REPEAT)) {
          if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_AUTO_REPEAT) {
            // XXX: not sure what auto repeat is supposed to do
          }
          repeat = 1;
      }
      // notify listeners
      _cmdReceiveCallback.callback2IntArg(IrReceiver.decodedIRData.command, repeat);
    }
  }
}

void RemoteControl::printSummary() {
  // print a short summary of received data
  IrReceiver.printIRResultShort(&Serial);

  if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // unknown protocol, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
  }
}
