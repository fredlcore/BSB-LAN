/*
  Base64 encode example

  Encodes the text "Base64EncodeExample" to "QmFzZTY0RW5jb2RlRXhhbXBsZQA="

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
  char inputString[] = "Base64EncodeExample";
  int inputStringLength = strlen(inputString);

  Serial.print("Input string is:\t");
  Serial.println(inputString);

  Serial.println();

  int encodedLength = Base64.encodedLength(inputStringLength);
  char encodedString[encodedLength];
  Base64.encode(encodedString, inputString, inputStringLength);
  Serial.print("Encoded string is:\t");
  Serial.println(encodedString);
}


void loop() {

}

