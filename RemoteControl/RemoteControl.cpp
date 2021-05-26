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
  int led_pin,
  Method cmd_recv_cb,
  bool led_feedback
) {
  _receivePin = recv_pin;
  _ledPin = led_pin;
  _ledFeedback = led_feedback;
  _cmdReceiveCallback = cmd_recv_cb;
}

void RemoteControl::begin() {
  // start the receiver
  IrReceiver.begin(_receivePin, _ledFeedback, _ledPin);
}

/*
* Check if received data is available and if yes, try to decode it.
* Decoded result is in the IrReceiver.decodedIRData structure.
*/
void RemoteControl::loop() {
  if (IrReceiver.decode()) {
    // enable receiving of the next value
    IrReceiver.resume();

    // check the received data and perform actions according to the received command
    // ignore 0 because it interferes with the MP3 audio player
    if (IrReceiver.decodedIRData.command != 0) {
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
