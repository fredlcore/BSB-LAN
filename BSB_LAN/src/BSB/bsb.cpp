#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#if defined(ESP32)
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "soc/uart_reg.h"
#endif

#include "bsb.h"

//#define DEBUG_LL 1

// Constructor
BSB::BSB(uint8_t rx, uint8_t tx, uint8_t addr, uint8_t d_addr) {
  bus_type = 0;
  len_idx = 3;
  myAddr=addr;
  destAddr=d_addr;
  rx_pin=rx;
  tx_pin=tx;

  serial = &Serial1;
#if !defined(ESP32)
  if (rx == 19) {	// 19 = RX pin of Serial1 USART module
    pinMode(53, OUTPUT);    // provide voltage
    digitalWrite(53, 1);
    pinMode(24, OUTPUT);    // provide 3V3 volt also via pin 24 for V2 versions of PCB board when used on the Due. Cut the 5V pin, short the 5V hole to pin 24 (via pin 22) to get necessary 3V3 voltage.
    digitalWrite(24, 1);
  }
#endif
}

void BSB::enableInterface() {
#if defined(ESP32)
  Serial1.begin(4800, SERIAL_8O1, rx_pin, tx_pin);
  Serial1.setRxFIFOFull(1);
  Serial1.setRxTimeout(1);
/*
  uart_intr_config_t uart_intr;
  uart_intr.intr_enable_mask = UART_RXFIFO_FULL_INT_ENA_M
                          | UART_RXFIFO_TOUT_INT_ENA_M
                          | UART_FRM_ERR_INT_ENA_M;
  uart_intr.rxfifo_full_thresh = 1; //UART_FULL_THRESH_DEFAULT,  //120 default!! aghh! need receive 120 chars before we see them
  uart_intr.rx_timeout_thresh = 2; // ,  //10 works well for my short messages I need send/receive
  uart_intr.txfifo_empty_intr_thresh = 10; //UART_EMPTY_THRESH_DEFAULT
  uart_intr_config(UART_NUM_1, &uart_intr);
*/
#else
  Serial1.begin(4800, SERIAL_8O1);
#endif    
}

void BSB::disableInterface() {
  Serial1.flush();
  Serial1.end();
}


uint8_t BSB::setBusType(uint8_t bus_type_val, uint16_t addr, uint16_t d_addr) {
  bus_type = bus_type_val;
  switch (bus_type) {
    case 0:
      len_idx = 3;
      offset = 0;
      pl_start = 9;
      break;
    case 1:
      len_idx = 1;
      offset = 4;
      pl_start = 13;
      break;
    case 2:
      len_idx = 8;
      pl_start = 6;
      break;
    default: len_idx = 3; pl_start = 9; offset = 0; break;
  }
  if (addr<=0xff) {
    myAddr = addr & 0xFF;
  }
  if (d_addr<=0xff) {
    destAddr = d_addr & 0xFF;
  }
/*
  Serial.print(F("My address: "));
  Serial.println(myAddr);
  Serial.print(F("Destination address: "));
  Serial.println(destAddr);
*/
  return bus_type;
}

uint8_t BSB::getBusType() {
  return bus_type;
}

uint8_t BSB::getBusAddr() {
  return myAddr;
}

uint8_t BSB::getBusDest() {
  return destAddr;
}

uint8_t BSB::getLen_idx() {
/*
  if (bus_type == BUS_PPS) {
    return len_idx +1;  // different only for BUS_PPS
  }
*/
  return len_idx;
}

uint8_t BSB::getPl_start() {
  return pl_start;
}


// Dumps a message to Serial
void BSB::print(byte* msg) {
  if (bus_type != 2) {
    byte len = msg[len_idx];
    if (len > 32) return;
    byte data = 0;

    for (int i=0; i<len+bus_type; i++) {	// msg length counts from zero with LPB (bus_type 1) and from 1 with BSB (bus_type 0)
      data = msg[i];
      if (data < 16) Serial.print("0");
      Serial.print(data, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

// Receives a message and stores it to buffer
boolean BSB::Monitor(byte* msg) {
  unsigned long int ts;
  byte i=0;
    
  if (serial->available() > 0) {
    // get timestamp
    ts=millis();
    // output
    Serial.print(ts);
    Serial.print(" ");
    while (serial->available() > 0) {
      // Read serial data...
      msg[i] = readByte();;

      // output
      if(msg[i]<16){  
        Serial.print("0");
      }
      Serial.print(msg[i], HEX);
      Serial.print(" ");
      i++;
      // if no inout available -> wait
      if (serial->available() == 0) {
        delay(3)    ;// > ((11/4800)*1000);   // Interestingly, here the timeout is already set to 3ms... (see GetMessage() below)
      }
      // if still no input available telegramm has finished
      if (serial->available() == 0 || i > 32) break;
    }
    Serial.println();
    return true;
  }
  return false;
}

bool BSB::GetMessage(byte* msg) {
  byte i=0;
  uint8_t read;

  while (serial->available() > 0) {
    // Read serial data...
    read = readByte();
/*
#if DEBUG_LL
    Serial.println();    
    if(read<16){  
      Serial.print("0");
    }
    Serial.print(read, HEX);
    Serial.print(" ");
#endif    
*/    
    // ... until SOF detected (= 0xDC, 0xDE bei BSB bzw. 0x78 bei LPB)
    if ((bus_type == BUS_BSB && (read == 0xDC || read == 0xDE)) || (bus_type == BUS_LPB && read == 0x78) || (bus_type == BUS_PPS && ((read & 0x0F) == 0x07 || (read & 0x0F) == 0x0D || (read & 0x0F) == 0x0E || read == 0xF8  || read == 0xFB || read == 0xFD || read == 0xFE))) {    // PPS telegram types 0x17, 0x1D, 0x1E, 0xF8, 0xFB, 0x$FD and 0xFE
      // Restore otherwise dropped SOF indicator
      msg[i++] = read;
      if (bus_type == BUS_PPS && (msg[0] & 0x0F) == 0x07) {   // First byte received is PPS RTS telegram (0x17)?
/*
        // make sure we're not in the middle of an ongoing telegram
        unsigned long wait_timer = millis();
        while (millis()-wait_timer <= 4) {    // wait up to 4ms for a new byte to be reported by HardwareSerial
          if (serial->available() > 0) {
            break;
          }
          delay(1);
        }
*/
        if (serial->available() == 0) {
          return true;  // No more bytes incoming? PPS-Bus request byte 0x17 just contains one byte, so return
        }
      }

//      	uint8_t PPS_write_enabled = myAddr;
//      	if (PPS_write_enabled == 1) {
//          return true; // PPS-Bus request byte 0x17 just contains one byte, so return
//      	} else {
//      	  len_idx = 9;
//	      }

      // Delay for more data
      if (serial->available() == 0) {
        delay(4);   // I wonder why HardwareSerial needs longer than SoftwareSerial until a character is ready to be processed. Also, why 3ms are fine for the Mega, but at least 4ms are necessary on the Due
      }
      // read the rest of the message
      while (serial->available() > 0) {
        read = readByte();
        msg[i++] = read;
/*
#if DEBUG_LL
        if(read<16){  
          Serial.print("0");
        }
        Serial.print(read, HEX);
        Serial.print(" ");
#endif
*/
        // Break if message seems to be completely received (i==msg.length)
        if (i > len_idx) {
          if (bus_type == BUS_PPS) {
            break;
          }
          if ( msg[len_idx] > 32 ) // check for maximum message length
            break;
          if (i >= msg[len_idx]+bus_type)
            break;
        }
        // Delay until we got next byte
        if (serial->available() == 0) {
          delay(4); // see question/reason above
        }
      }

      // We should have read the message completely. Now check and return

      if (bus_type == BUS_PPS) {
        if (i == len_idx+1) {
	        len_idx = 8;
          return true; // TODO: add CRC check before returning true/false
        }
      } else {

        if (i == msg[len_idx]+bus_type) {		// LPB msg length is one less than BSB
          // Seems to have received all data
          if (bus_type == 1) {
            if (CRC_LPB(msg, i-1)-msg[i-2]*256-msg[i-1] == 0) {
              return true;
            } else {
              Serial.println("CRC error:");
              print (msg);
              return false;
            }
	        } else {
            if (CRC(msg, i) == 0) {
              return true;
            } else {
              Serial.println("CRC error:");
              print (msg);
              return false;
            }
	        }
        } else {
          // Length error
          Serial.println("Length error:");
          print (msg);
          return false;
        }
      }
    }
  }
  // We got no data so:
  return false;
}

// Generates CCITT XMODEM CRC from BSB message
uint16_t BSB::CRC (byte* buffer, uint8_t length) {
  uint16_t crc = 0;

  for (uint8_t i = 0; i < length; i++) {
    crc = _crc_xmodem_update(crc, buffer[i]);
  }

  // Complete message returns 0x00
  // Message w/o last 2 bytes (CRC) returns last 2 bytes (CRC)
  return crc;
}

// Generates checksum from LPB message
// (255 - (Telegrammlänge ohne PS - 1)) * 256 + Telegrammlänge ohne PS - 1 + Summe aller Telegrammbytes
uint16_t BSB::CRC_LPB (byte* buffer, uint8_t length) {
  uint16_t crc = 0;

  crc = (257-length)*256+length-2;

  for (uint8_t i = 0; i < length-1; i++) {
    crc = crc+buffer[i];
  }

  return crc;
}

// Generates CRC for PPS message
uint8_t BSB::CRC_PPS (byte* buffer, uint8_t length) {
  uint8_t crc = 0;
  int sum = 0;

  for (uint8_t i = 0; i < length; i++) {
    sum+=buffer[i];
  }
  sum = sum & 0xFF;
  crc = 0xFF - sum + 1;

  return crc;
}

uint16_t BSB::_crc_xmodem_update (uint16_t crc, uint8_t data) {
  uint8_t i;

  crc = crc ^ ((uint16_t)data << 8);
  for (i=0; i<8; i++) {
    if (crc & 0x8000) {
      crc = (crc << 1) ^ 0x1021;
    } else {
      crc <<= 1;
    }
  }
  return crc;
}

// Low-Level sending of message to bus
inline int8_t BSB::_send(byte* msg) {
// Nun - Ein Teilnehmer will senden :
  byte data, len;
  if (bus_type != 2) {
    len = msg[len_idx];
  } else {
    len = len_idx;
  }
  // switch (bus_type) {
    // case 0:
      // msg[0] = 0xDC;
      // msg[1] = myAddr | 0x80;
      // msg[2] = destAddr;
      // break;
    // case 1:
      // msg[0] = 0x78;
      // msg[2] = destAddr;
      // msg[3] = myAddr;
      // break;
  // }
  {
    if (bus_type == 0) {
      msg[0] = 0xDC;
      msg[1] = myAddr | 0x80;
      msg[2] = destAddr;
      uint16_t crc = CRC (msg, len -2);
      msg[len -2] = (crc >> 8);
      msg[len -1] = (crc & 0xFF);
    }
    if (bus_type == 1) {
      msg[0] = 0x78;
      msg[2] = destAddr;
      msg[3] = myAddr;
      uint16_t crc = CRC_LPB (msg, len);
      msg[len-1] = (crc >> 8);
      msg[len] = (crc & 0xFF);
    }
    if (bus_type == BUS_PPS) {
      uint8_t crc = CRC_PPS (msg, len);
      msg[len] = crc;
    }
  }

#if DEBUG_LL  
  print(msg);
#endif  
  static const unsigned long timeoutabort = 1000;  // one second timeout
  unsigned long start_timer = millis();
  unsigned long waitfree;
  retry:
  waitfree = random(1,20) + 3 + 59; // range 63 .. 82 ms, BSB mimimum delay between telegrams is 59 ms (25 for LPB -> miwi), plus duration of one full (32 bytes) telegram (3 ms), plus random amount of 1-20 ms.
  { // block begins
    if(millis()-start_timer > timeoutabort){  // one second has elapsed
      return BUS_NOTFREE;
    }
    if (bus_type != 2) {
      unsigned long timeout = millis();
      // Probe the bus until the delay calculated above has passed. We want to wait this long even on the first try because we want to make sure the minimum delay between telegrams has passed.
      while (millis()-timeout < waitfree) {
        bool rx_pin = rx_pin_read();
        if (rx_pin) {  // If there is activity on the bus / the bus has been pulled low, we have to try again and wait for 'waitfree' ms. 
#if DEBUG_LL
          Serial.println("Activity on the bus while waiting, retrying...");
#endif
          delay(146); // Wait the duration of 11 bits at 4800 bps times 32 (maximum telegram size) in ms (*1000) times 2 (because we can just keep waiting for an answer telegram) 
          while (serial->available()) {
            char c = readByte();
#if DEBUG_LL
            if (c < 16) Serial.print("0");
            Serial.print(c, HEX);
            Serial.print(" ");
#endif
            c = c;  // prevent compiler warning about unused variable if DEBUG_LL is not active
          }
#if DEBUG_LL
          Serial.println();
#endif
          goto retry;
        } // endif
      } // endwhile
    }
  } // block ends

  //Serial.println("bus free");

/*
Wenn nicht wird das erste Bit gesendet. ( Startbit )

Jedes gesendete Bit wird ( wegen Bus ) ja sofort auf der Empfangsleitung
wieder ankommen. Man schaut nach, ob das gesendete Bit mit dem
empfangenen Bit übereinstimmt.
Wenn ich eine "0" sende - also den Bus auf High lasse, dann will ich
sehen, dass der Bus weiterhin auf High ist. Sollte ein anderer
Teilnehmer in dieser Zeit eine "1" senden - also den Bus herunterziehen,
dann höre ich sofort auf mit dem Senden und fange oben wieder an.
Danach folgen nach gleichem Muster die folgenden Bits, Bit 7..0, Parity
und Stop Bit.
*/

/* 
FH 27.12.2018: Wer auch immer das obige geschrieben hat, es macht bezogen auf
den nachfolgenden Code keinen Sinn: 
1. Es wird hier nicht bitweise gesendet, sondern ein ganzes Byte an
BSBSoftwareSerial::write übergeben. Dort wird dann unabhängig davon, ob der 
Bus frei ist oder nicht, dieses komplette Byte inkl. Start-, Stop- und Parity-
Bits gesendet.
2. BSBSoftwareSerial::write gibt immer 1 zurück, außer wenn _tx_delay == 0 ist.
Diese Variable wird aber nur einmalig bei Aufruf von BSBSoftwareSerial::begin
gesetzt und wäre nur in seltenen Ausnahmefällen == 0.
So wie es jetzt scheint, findet die Kollisionsprüfung beim Senden nicht statt.
*/

/*
FH 23.03.2021: Eine Kollisionsprüfung während des Sendens ist mit HardwareSerial nicht mehr ohne Weiteres möglich.
Nachdem oben schon auf einen freien Bus gewartet wurde, wird nun jedes gesendete Byte, das ja wieder auf der Empfangsleitung
ankommt, auf Gleichheit überprüft. Wenn dies nicht der Fall ist, gab es einen Zwischenfall und das Telegramm wird erneut gesendet.
Da bei HardwareSerial die gesendeten Bytes nichts sofort im Empfangspuffer landen, wird bis zu 50ms gewartet, bis der 
UART buffer gefüllt ist und ein empfangenes Byte meldet.
*/

/*
FH 25.12.2021: Mit Umstieg auf ESP32 SDK 2.0.2 kommen gesendete Daten nicht wieder auf der Empfangsleitung an. Sowohl das flush() als auch die 50ms
sorgen dafür, dass bereits die Antwort-Telegramme als "fremde" Daten und somit als Buskollision gewertet werden, weswegen dieser Teil auskommentiert wurde.
Ob damit weiterhin eine Bus-Kollisionserkennung möglich ist, muss noch geprüft werden.
*/

/*
FH 30.05.2024: Anscheinend kamen die gesendeten Daten auch weiterhin auf der Empfangsleitung an, wurden aber durch den Test 
auf den entsprechenden Empfänger dann gleich wieder verworfen. Als Konsequenz wurde der 50ms RX-Test wieder vom Adruino Due auch auf
die ESP32 ausgeweitet.
*/

  byte loop_len = len;
  if (bus_type != 2) {
    loop_len = len + bus_type - 1; // same msg length difference as above
  }
  for (byte i=0; i <= loop_len; i++) {
    data = msg[i];
    if (bus_type != 2) {
      data = data ^ 0xFF;
    }
    serial->write(data);
#if !defined(ESP32)
    serial->flush();
#endif
    if (bus_type==2 && i==0 && data==0x17) {
      unsigned long timeout = millis();
      while ((millis()-timeout < 200) && serial->available() == 0) {
        delay(1);
      }
      while (serial->available()) {
        char c = readByte();
        c = c;
      }
      return BUS_OK;  // In case we emulate a DC225, we are regularly sending single byte (0x17) messages, so abort loop after first byte.
    }
/*
//    if ((HwSerial == true && rx_pin_read() == false) || (HwSerial == false && rx_pin_read())) {  // Test RX pin (logical 1 is 0 with HardwareSerial and 1 with SoftwareSerial inverted)
    if (rx_pin_read()) {
      // Collision
#if defined(__AVR__)
      if (HwSerial == false) {
        sei();
      }
#endif
      goto retry;
    }
*/
  }
//#if !defined(ESP32)
  serial->flush();
  unsigned long timeout = millis();
  while ((millis()-timeout < 50) && serial->available() == 0) {
    delay(1);
  }
//#endif
//  delay(loop_len*2+10);      // Wait up to 32 characters for the maximum number of bytes in a telegram to show up again on RX after sending it via TX.
  if (serial->available()) {      
    for (uint8_t i=0; i<=loop_len; i++) {
      char readdata = readByte();
      if (msg[i] != readdata) {
#if DEBUG_LL
        Serial.println(readdata, HEX);
#endif
        Serial.println("Collision on the bus, retrying...");
        delay(146);   // Wait the duration of 11 bits at 4800 bps times 32 (maximum telegram size) in ms (*1000) times 2 (because we can just keep waiting for an answer telegram) 
        while (serial->available()) {
          char c = readByte();
#if DEBUG_LL
          if (c < 16) Serial.print("0");
          Serial.print(c, HEX);
#endif
          c = c;  // prevent compiler warning about unused variable if DEBUG_LL is not active
        }
#if DEBUG_LL
        Serial.println();
#endif
        goto retry;
      }
    }
  }
  return BUS_OK;
}

int8_t BSB::Send(uint8_t type, uint32_t cmd, byte* rx_msg, byte* tx_msg, byte* param, byte param_len, bool wait_for_reply) {
  byte i;
  byte length_offset = 0;

  if (bus_type == BUS_PPS) {
    return _send(tx_msg);
  }

  while(serial->available()) {
    readByte();
  }

  // first two bytes are swapped
  byte A2 = (cmd & 0xff000000) >> 24;
  byte A1 = (cmd & 0x00ff0000) >> 16;
  byte A3 = (cmd & 0x0000ff00) >> 8;
  byte A4 = (cmd & 0x000000ff);

  // special treatment of internal query types
  if (type == 0x12) {   // TYPE_IQ1
    A1 = A3;
    A2 = A4;
    length_offset = 2;
  }
  if (type == 0x14) {   // TYPE_IQ2
    A1 = A4;
    length_offset = 3;
  }
  
  if (bus_type == 1) {
    tx_msg[1] = param_len + 14 - length_offset;
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
  } else {
    tx_msg[3] = param_len + 11 - length_offset;
    tx_msg[4] = type;
    // Adress
    tx_msg[5] = A1;
    tx_msg[6] = A2;
    tx_msg[7] = A3;
    tx_msg[8] = A4;
  }

  // Value
  for (i=0; i < param_len; i++) {
    if (bus_type == 1) {
      tx_msg[13+i] = param[i];
    } else {
      tx_msg[9+i] = param[i];
    }
  }
  int8_t return_value = _send(tx_msg);
  if(return_value != BUS_OK) return return_value;
  if(!wait_for_reply) return return_value;

  i=15;

  unsigned long timeout = millis() + 3000;
  while ((i > 0) && (millis() < timeout)) {
    if (GetMessage(rx_msg)) {
#if DEBUG_LL
      Serial.print(F("\r\nDuration until answer received: "));
      Serial.println(3000-(timeout-millis()));
      print(rx_msg);
#endif
      i--;
      byte msg_type = rx_msg[4+offset];
      if (rx_msg[2] == myAddr && ((type == 0x12 && msg_type == 0x13) || (type=0x14 && msg_type == 0x15))) {
        return BUS_OK;
      }
      if (bus_type != 2) {
/* Activate for LPB systems with truncated error messages (no commandID in return telegram) 
	if (rx_msg[2] == myAddr && rx_msg[8]==0x08) {  // TYPE_ERR
	  return false;
	}
*/
        if ((rx_msg[2] == myAddr) && (rx_msg[5+offset] == A2) && (rx_msg[6+offset] == A1) && (rx_msg[7+offset] == A3) && (rx_msg[8+offset] == A4)) {
          return BUS_OK;
	      } else {
#if DEBUG_LL
          Serial.println(F("Message received, but not for us:"));
          print(rx_msg);
#endif
        }
      }
    } else {
      delayMicroseconds(205);
    }
  }
#if DEBUG_LL
  Serial.println(F("No answer for this send telegram:"));
#endif
  print(tx_msg);

  return BUS_NOMATCH;
}

boolean BSB::rx_pin_read() {
  return boolean(* portInputRegister(digitalPinToPort(rx_pin)) & digitalPinToBitMask(rx_pin)) ^ 1;
}

uint8_t BSB::readByte() {
  byte read = serial->read();
  if (bus_type != 2) {
    read = read ^ 0xFF;
  }
  return read;
}