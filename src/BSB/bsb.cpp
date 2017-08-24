#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "bsb.h"

#define DEBUG_LL 0

// Constructor
BSB::BSB(uint8_t rx, uint8_t tx, uint8_t addr) {
  serial = new BSBSoftwareSerial(rx, tx, true);

  serial->begin(4800);
  serial->listen();
  myAddr=addr;
}

// Dumps a message to Serial
void BSB::print(byte* msg) {
  //if (msg[0] != 0xDC) return;
  byte len = msg[3];
  //if (len > 30) return;
  byte data = 0;

  for (; len > 0; len--) {
    data = msg[msg[3]-len];
    if (data < 16) Serial.print("0");
    Serial.print(data, HEX);
    Serial.print(" ");
  }
  Serial.println();
}

// Dumps a message to Serial
void BSB::printLPB(byte* msg) {
  //if (msg[0] != 0x78) return;
  signed char len = msg[1];
  //if (len > 30) return;
  byte data = 0;

  for (; len >= 0; len--) {
    data = msg[msg[1]-len];
    if (data < 16) Serial.print("0");
    Serial.print(data, HEX);
    Serial.print(" ");
  }
  Serial.println();
}


// Receives a message and stores it to buffer
void BSB::Monitor(byte* msg) {
  unsigned long int ts;
  byte read;
  byte i=0;
    
  if (serial->available() > 0) {
    // get timestamp
    ts=millis();
    // output
    Serial.print(ts);
    Serial.print(" ");
    while (serial->available() > 0) {
      
      // Read serial data...
      read = serial->read() ^ 0xFF;

      msg[i] = read;
      i++;

      // output
      if(read<16){  
        Serial.print("0");
      }
      Serial.print(read, HEX);
      Serial.print(" ");
      // if no inout available -> wait
      if (serial->available() == 0) {
        unsigned long timeout = millis() + 3;// > ((11/4800)*1000);
        while (millis() < timeout) {
          delayMicroseconds(15);
        }
      }
      // if still no input available telegramm has finished
      if (serial->available() == 0) break;
    }
    Serial.println();
  }
}

// —————— LPB-Bus functions ——————

bool BSB::GetMessageLPB(byte* msg) {
  byte i=0,timeout;
  byte read;

  while (serial->available() > 0) {
    // Read serial data...
    read = serial->read() ^ 0xFF;

#if DEBUG_LL
    Serial.println();    
    if(read<16){  
      Serial.print("0");
    }
    Serial.print(read, HEX);
    Serial.print(" ");
#endif    
    
    // ... until SOF detected (= 0x78 for LPB)
    if (read == 0x78) {
      // Restore otherwise dropped SOF indicator
      msg[i++] = read;

      // Delay for more data
      delay(1);

      // read the rest of the message
      while (serial->available() > 0) {
        read = serial->read() ^ 0xFF;
        msg[i++] = read;
#if DEBUG_LL
        if(read<16){  
          Serial.print("0");
        }
        Serial.print(read, HEX);
        Serial.print(" ");
#endif
        // Break if message seems to be completely received (i==msg.length)
        if (i > 1){
          if ( msg[1] > 32 ) // check for maximum message length
            break;
          if (i > msg[1])
            break;
        }
        // Delay until we got next byte
        if (serial->available() == 0) {
          timeout = 30;
          while ((timeout > 0) && (serial->available() == 0)){
            delayMicroseconds(15);
            timeout--;
          }
        }

        // Break if next byte signals next message (0x23 ^ 0xFF == 0xDC)
        // if((serial->peek() == 0x23)) break;
        // DO NOT break because some messages contain a 0xDC 
      }

      // We should have read the message completly. Now check and return
      if (i == msg[1]+1) {
        // Seems to have received all data
        if (CRC_LPB(msg, i) == (uint16_t)(msg[i-1]*256+msg[i])) return true;
        else return false;
      }
      else {
        // Length error
        return false;
      }
    }
  }

  // We got no data so:
  return false;
}

// Generates checksum from message
// (255 - (Telegrammlänge ohne PS - 1)) * 256 + Telegrammlänge ohne PS - 1 + Summe aller Telegrammbytes
uint16_t BSB::CRC_LPB (byte* buffer, uint8_t length) {
  uint16_t crc = 0;
  uint8_t i;

  crc = (257-length)*256+length-2;

  for (i = 0; i < length-1; i++) {
    crc = crc+buffer[i];
  }

  return crc;
}

// Low-Level sending of message to bus
inline bool BSB::_sendLPB(byte* msg) {
// Nun - Ein Teilnehmer will senden :
  byte i;
  byte data;
  byte len = msg[1];
  msg[0] = 0x78;
  msg[2] = 0x00;
  msg[3] = myAddr;

  {
    uint16_t crc = CRC_LPB (msg, len);
    msg[len-1] = (crc >> 8);
    msg[len] = (crc & 0xFF);
  }
#if DEBUG_LL  
  print(msg);
#endif  
  /*
Er wartet 10/4800 Sek ab, lauscht und schaut ob der Bus in dieser Zeit
von jemand anderem benutzt wird. Sprich ob der Bus in dieser Zeit mal
auf 0 runtergezogen wurde. Wenn ja - mit den warten neu anfangen.
*/
  unsigned long timeoutabort = millis() + 1000;
retry:
  {
    if(millis() > timeoutabort){
      return false;
    }
    unsigned long timeout = millis() + 3;//((1/480)*1000);
    while (millis() < timeout) {
      if ( serial->rx_pin_read()) // inverse logic
      {
        goto retry;
      }
    }
  }
  //Serial.println("bus free");

/*
Wenn nicht wird das erste Bit gesendet. ( Startbit )

Jedes gesendete Bit wird ( wegen Bus ) ja sofort auf der Empfangsleitung
wieder ankommen. Man schaut nach, ob das gesendetet Bit mit dem
empfangenen Bit übereinstimmt.
Wenn ich eine "0" sende - also den Bus auf High lasse, dann will ich
sehen, dass der Bus weiterhin auf High ist. Sollte ein anderer
Teilnehmer in dieser Zeit eine "1" senden - also den Bus herunterziehen,
dann höre ich sofort auf mit dem Senden und fange oben wieder an.
Danach folgen nach gleichem Muster die folgenden Bits, Bit 7..0, Parity
und Stop Bit.
*/

  cli();
  for (i=0; i < msg[1]; i++) {
    data = msg[i] ^ 0xFF;
    if (serial->write(data) != 1) {
      // Collision
      sei();
      goto retry;
    }
  }
  sei();
  return true;
}

bool BSB::SendLPB(uint8_t type, uint32_t cmd, byte* rx_msg, byte* tx_msg, byte* param, byte param_len, bool wait_for_reply) {
  byte i;

  // first two bytes are swapped
  byte A2 = (cmd & 0xff000000) >> 24;
  byte A1 = (cmd & 0x00ff0000) >> 16;
  byte A3 = (cmd & 0x0000ff00) >> 8;
  byte A4 = (cmd & 0x000000ff);
  
  tx_msg[1] = param_len + 14;
  tx_msg[4] = 0xC0;	// some kind of sending/receiving flag?
  tx_msg[5] = 0x02;	// yet unknown
  tx_msg[6] = 0x00;	// yet unknown
  tx_msg[7] = 0x14;	// yet unknown
  tx_msg[8] = type;
  // Adress
  tx_msg[9] = A1;
  tx_msg[10] = A2;
  tx_msg[11] = A3;
  tx_msg[12] = A4;

  // Value
  for (i=0; i < param_len; i++)
    tx_msg[13+i] = param[i];
  
  if(!_sendLPB(tx_msg)) return false;

  if(!wait_for_reply) return true;

  i=15;

  unsigned long timeout = millis() + 1000;
  while ((i > 0) && (millis() < timeout)) {
    if (GetMessage(rx_msg)) {
      i--;
      if ((rx_msg[2] == myAddr) && (rx_msg[9] == A2) && (rx_msg[10] == A1) && (rx_msg[11] == A3) && (rx_msg[12] == A4)) {
        return true;
      }
    }
    else {
      delayMicroseconds(205);
    }
  }
  return false;
}

// —————— BSB-Bus functions ——————


bool BSB::GetMessage(byte* msg) {
  byte i=0,timeout;
  byte read;

  while (serial->available() > 0) {
    // Read serial data...
    read = serial->read() ^ 0xFF;

#if DEBUG_LL
    Serialln();    
    if(read<16){  
      Serial.print("0");
    }
    Serial.print(read, HEX);
    Serial.print(" ");
#endif    
    
    // ... until SOF detected (= 0xDC)
    if (read == 0xDC || read == 0xDE) {
      // Restore otherwise dropped SOF indicator
      msg[i++] = read;

      // Delay for more data
      delay(1);

      // read the rest of the message
      while (serial->available() > 0) {
        read = serial->read() ^ 0xFF;
        msg[i++] = read;
#if DEBUG_LL
        if(read<16){  
          Serial.print("0");
        }
        Serial.print(read, HEX);
        Serial.print(" ");
#endif
        // Break if message seems to be completely received (i==msg.length)
        if (i > 3){
          if ( msg[3] > 32 ) // check for maximum message length
            break;
          if (i >= msg[3])
            break;
        }
        // Delay until we got next byte
        if (serial->available() == 0) {
          timeout = 30;
          while ((timeout > 0) && (serial->available() == 0)){
            delayMicroseconds(15);
            timeout--;
          }
        }

        // Break if next byte signals next message (0x23 ^ 0xFF == 0xDC)
        // if((serial->peek() == 0x23)) break;
        // DO NOT break because some messages contain a 0xDC 
      }

      // We should have read the message completly. Now check and return
      if (i == msg[3]) {
        // Seems to have received all data
        if (CRC(msg, i) == 0) return true;
        else return false;
      }
      else {
        // Length error
        return false;
      }
    }
  }

  // We got no data so:
  return false;
}

// Generates CCITT XMODEM CRC from message
uint16_t BSB::CRC (byte* buffer, uint8_t length) {
  uint16_t crc = 0, i;

  for (i = 0; i < length; i++) {
    crc = _crc_xmodem_update(crc, buffer[i]);
  }

  // Complete message returns 0x00
  // Message w/o last 2 bytes (CRC) returns last 2 bytes (CRC)
  return crc;
}

// Low-Level sending of message to bus
inline bool BSB::_send(byte* msg) {
// Nun - Ein Teilnehmer will senden :
  byte i;
  byte data;
  byte len = msg[3];
  msg[0] = 0xDC;
  msg[1] = myAddr | 0x80;
  msg[2] = 0x00;

  {
    uint16_t crc = CRC (msg, len -2);
    msg[len -2] = (crc >> 8);
    msg[len -1] = (crc & 0xFF);
  }
#if DEBUG_LL  
  print(msg);
#endif  
  /*
Er wartet 10/4800 Sek ab, lauscht und schaut ob der Bus in dieser Zeit
von jemand anderem benutzt wird. Sprich ob der Bus in dieser Zeit mal
auf 0 runtergezogen wurde. Wenn ja - mit den warten neu anfangen.
*/
  unsigned long timeoutabort = millis() + 1000;
retry:
  {
    if(millis() > timeoutabort){
      return false;
    }
    unsigned long timeout = millis() + 3;//((1/480)*1000);
    while (millis() < timeout) {
      if ( serial->rx_pin_read()) // inverse logic
      {
        goto retry;
      }
    }
  }
  //Serial.println("bus free");

/*
Wenn nicht wird das erste Bit gesendet. ( Startbit )

Jedes gesendete Bit wird ( wegen Bus ) ja sofort auf der Empfangsleitung
wieder ankommen. Man schaut nach, ob das gesendetet Bit mit dem
empfangenen Bit übereinstimmt.
Wenn ich eine "0" sende - also den Bus auf High lasse, dann will ich
sehen, dass der Bus weiterhin auf High ist. Sollte ein anderer
Teilnehmer in dieser Zeit eine "1" senden - also den Bus herunterziehen,
dann höre ich sofort auf mit dem Senden und fange oben wieder an.
Danach folgen nach gleichem Muster die folgenden Bits, Bit 7..0, Parity
und Stop Bit.
*/

  cli();
  for (i=0; i < msg[3]; i++) {
    data = msg[i] ^ 0xFF;
    if (serial->write(data) != 1) {
      // Collision
      sei();
      goto retry;
    }
  }
  sei();
  return true;
}

bool BSB::Send(uint8_t type, uint32_t cmd, byte* rx_msg, byte* tx_msg, byte* param, byte param_len, bool wait_for_reply) {
  byte i;

  // first two bytes are swapped
  byte A2 = (cmd & 0xff000000) >> 24;
  byte A1 = (cmd & 0x00ff0000) >> 16;
  byte A3 = (cmd & 0x0000ff00) >> 8;
  byte A4 = (cmd & 0x000000ff);
  
  tx_msg[3] = param_len + 11;
  tx_msg[4] = type;
  // Adress
  tx_msg[5] = A1;
  tx_msg[6] = A2;
  tx_msg[7] = A3;
  tx_msg[8] = A4;

  // Value
  for (i=0; i < param_len; i++)
    tx_msg[9+i] = param[i];
  
  if(!_send(tx_msg)) return false;

  if(!wait_for_reply) return true;

  i=15;

  unsigned long timeout = millis() + 1000;
  while ((i > 0) && (millis() < timeout)) {
    if (GetMessage(rx_msg)) {
      i--;
      if ((rx_msg[2] == myAddr) && (rx_msg[5] == A2) && (rx_msg[6] == A1) && (rx_msg[7] == A3) && (rx_msg[8] == A4)) {
        return true;
      }
    }
    else {
      delayMicroseconds(205);
    }
  }
  return false;
}
