/*
  Base64 decode example

  Decodes the text "QmFzZTY0RGVjb2RlRXhhbXBsZQA=" to "Base64DecodeExample"

  Created 04 May 2016
  by Arturo Guadalupi

  This example code is in the public domain.

*/

#include <Base64.h>

void setup()
{
  // start serial port at 115200 bps:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB only
  }

  // encoding
  char inputString[] = "QmFzZTY0RGVjb2RlRXhhbXBsZQA=";
  int inputStringLength = strlen(inputString);

  Serial.print("Input string is:\t");
  Serial.println(inputString);

  Serial.println();

  int decodedLength = Base64.decodedLength(inputString, inputStringLength);
  char decodedString[decodedLength];
  Base64.decode(decodedString, inputString, inputStringLength);
  Serial.print("Decoded string is:\t");
  Serial.println(decodedString);
}


void loop() {

}

