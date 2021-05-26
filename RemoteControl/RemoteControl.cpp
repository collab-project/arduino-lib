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
  int led_pin
) {
  _receivePin = recv_pin;
  _ledPin = led_pin;
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
    //printSummary();

    // enable receiving of the next value
    IrReceiver.resume();

    // check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      _cmdReceiveCallback.callbackIntArg(IrReceiver.decodedIRData.command);

      Serial.print(millis());
      Serial.print(" - Received IR flag: ");
      Serial.println(IrReceiver.decodedIRData.flags);
      if (IrReceiver.decodedIRData.flags == IRDATA_FLAGS_IS_REPEAT) {
        Serial.println("REPEAT");
      }
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
  Serial.println();
}
