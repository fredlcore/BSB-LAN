/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printBIT(byte *msg,byte data_len) {
  int len = 0;
  if (data_len == 2 || data_len == 3) {
    if (msg[bus->getPl_start()]==0 || data_len == 3) {
      for (int i=7;i>=0;i--) {
        len += sprintf(decodedTelegram.value+len,"%d",msg[bus->getPl_start()+1+data_len-2] >> i & 1);
      }
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printFmtToDebug("BIT len error len!=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printCustomBIT(byte *msg,byte idx) {
  int len = 0;
  for (int i=7;i>=0;i--) {
    len += sprintf(decodedTelegram.value+len,"%d",msg[bus->getPl_start()+idx] >> i & 1);
  }
  printToDebug(decodedTelegram.value);
}


/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printBYTE(byte *msg,byte data_len) {
//  uint8_t pps_offset = (msg[0] == 0x17 && pps_write != 1 && bus->getBusType() == BUS_PPS);

  if (data_len == 2 || bus->getBusType() == BUS_PPS) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS) {
//      sprintf(decodedTelegram.value,"%d",msg[bus->getPl_start()+1+pps_offset]);
      sprintf(decodedTelegram.value,"%d",msg[bus->getPl_start()+1]);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug("BYTE len error len!=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printWORD(byte *msg,byte data_len, float divisor) {
  long lval;
  if (data_len == 3) {
    if (msg[bus->getPl_start()]==0) {
      lval=((long(msg[bus->getPl_start()+1])<<8)+long(msg[bus->getPl_start()+2])) / divisor;
      sprintf(decodedTelegram.value,"%ld",lval);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug("WORD len error len!=3: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printSINT(byte *msg,byte data_len, float multiplier) {
  int16_t lval;
  if (data_len == 3) {
    if (msg[bus->getPl_start()]==0) {
      lval=(((int16_t)(msg[bus->getPl_start()+1])<<8) + (int16_t)(msg[bus->getPl_start()+2])) * multiplier;
      sprintf(decodedTelegram.value,"%d",lval);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug("WORD len error len!=3: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
 void printDWORD(byte *msg, byte data_len, float divider) {
   long lval;
   if (data_len == 5) {
     if (msg[bus->getPl_start()]==0) {
       lval=((long(msg[bus->getPl_start()+1])<<24)+(long(msg[bus->getPl_start()+2])<<16)+(long(msg[bus->getPl_start()+3])<<8)+long(msg[bus->getPl_start()+4]))/divider;
       sprintf(decodedTelegram.value,"%ld",lval);
     } else {
       undefinedValueToBuffer(decodedTelegram.value);
     }
     printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
   } else {
     printFmtToDebug("DWORD len error len!=5: ");
     prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
     decodedTelegram.error = 256;
   }
 }

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
int _printFIXPOINT(char *p, float dval, int precision) {
  int a,b,i;
  int len = 0;
  if (dval<0) {
    p[len++] = '-';
    dval*=-1.0;
  }
  float rval=10.0;
  for (i=0;i<precision;i++) rval*=10.0;
  dval+=5.0/rval; //rounding
  a=(int)(dval);
  if (precision==0) {
    len+=sprintf(p+len,"%d",a);
  } else {
    rval/=10.0;
    b=(int)(dval*rval - a*rval);
    char formatstr[8]="%d.%01d";
    formatstr[5]='0'+precision;
    len+=sprintf(p+len,formatstr,a,b);
  }
  return len;
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT(byte *msg,byte data_len,float divider,int precision) {
  float dval;
//  int8_t pps_offset = (((pps_write == 1 && msg[0] != 0x00) || (pps_write != 1 && msg[0] != 0x17 && msg[0] != 0x00)) && bus->getBusType() == BUS_PPS);
  int8_t pps_offset = (bus->getBusType() == BUS_PPS);

  if (data_len == 3 || data_len == 5) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS || (decodedTelegram.flags & FL_SPECIAL_INF)) {
      if (data_len == 3) {
        if (decodedTelegram.flags & FL_SPECIAL_INF) {
          dval=float((int16_t)(msg[bus->getPl_start()] << 8) + (int16_t)msg[bus->getPl_start()+1]) / divider;
        } else {
          dval=float((int16_t)(msg[bus->getPl_start()+1-pps_offset] << 8) + (int16_t)msg[bus->getPl_start()+2-pps_offset]) / divider;
        }
      } else {
        dval=float((int16_t)(msg[bus->getPl_start()+3-pps_offset] << 8) + (int16_t)msg[bus->getPl_start()+4-pps_offset]) / divider;
      }
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug("FIXPOINT len !=3: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_DWORD(byte *msg,byte data_len,float divider,int precision) {
  float dval;

  if (data_len == 5) {
    if (msg[bus->getPl_start()]==0) {
      dval=float((long(msg[bus->getPl_start()+1])<<24)+(long(msg[bus->getPl_start()+2])<<16)+(long(msg[bus->getPl_start()+3])<<8)+long(msg[bus->getPl_start()+4])) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug("FIXPOINT_DWORD len !=5: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_BYTE(byte *msg,byte data_len,float divider,int precision) {
  float dval;

  if (data_len == 2 || (data_len == 3 && (my_dev_fam == 107 || my_dev_fam == 123 || my_dev_fam == 163))) {
    if (msg[bus->getPl_start()]==0) {
      dval=float((signed char)msg[bus->getPl_start()+1+(data_len==3)]) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug("FIXPOINT_BYTE len !=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_BYTE_US(byte *msg,byte data_len,float divider,int precision) {
  float dval;

  if (data_len == 2) {
    if (msg[bus->getPl_start()]==0) {
      dval=float(msg[bus->getPl_start()+1]) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug("FIXPOINT_BYTE_US len !=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printENUM(uint_farptr_t enumstr,uint16_t enumstr_len,uint16_t search_val, int print_val) {
  uint16_t val = 0;
  decodedTelegram.enumdescaddr = 0;
  if (enumstr!=0) {
    uint16_t c=0;
    while (c<enumstr_len) {
      if ((byte)(pgm_read_byte_far(enumstr+c+2))==' ') {
        val=uint16_t((pgm_read_byte_far(enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(enumstr+c+1));
        c++;
      } else if ((byte)(pgm_read_byte_far(enumstr+c+1))==' ') {
        val=uint16_t(pgm_read_byte_far(enumstr+c));
      }
      //skip leading space
      c+=2;
      if (val==search_val) {
       // enum value found
       break;
      }
      while (pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if (c<enumstr_len) {
      decodedTelegram.enumdescaddr = enumstr+c;
      sprintf(decodedTelegram.value, "%d", val);
      if (print_val) {
        printFmtToDebug("%s - ", decodedTelegram.value);
      }
      printToDebug(decodedTelegram.enumdescaddr);
    } else {
      sprintf(decodedTelegram.value, "%d", search_val);
      printToDebug(decodedTelegram.value);
      decodedTelegram.error = 258;
    }
  }
}

void printKat(uint8_t cat, int print_val, boolean debug_output) {
  const char* enumstr = ENUM_CAT;
  const uint16_t enumstr_len = sizeof(ENUM_CAT);
  uint8_t val = 0;
  decodedTelegram.enumdescaddr = 0;
  decodedTelegram.error = 0;
  uint8_t cat_dev_fam = 0;
  uint8_t cat_dev_var = 0;
  if (enumstr!=0) {
    uint16_t c=0;
    while (c<enumstr_len) {
      if (*(enumstr+c+3)==' ') {
        cat_dev_fam = *(enumstr+c+1);
        cat_dev_var = *(enumstr+c+2);
        val=*(enumstr+c);
        c+=2;
      } else if (*(enumstr+c+1)==' ') {
        val=*(enumstr+c);
        cat_dev_fam = my_dev_fam;
        cat_dev_var = my_dev_var;
      }
      //skip leading space
      c+=2;
      if (val==cat) {
       // enum value found
       break;
      }
      while (*(enumstr+c)!=0) c++;
      c++;
    }
    if (c<enumstr_len) {
      decodedTelegram.enumdescaddr = enumstr+c;
      sprintf(decodedTelegram.value, "%d", val);
      if (print_val && debug_output == true) {
        printFmtToDebug("%s - ", decodedTelegram.value);
      }
      if (debug_output == true) printToDebug(decodedTelegram.enumdescaddr);
      if (cat_dev_fam != my_dev_fam || cat_dev_var != my_dev_var) {
        if (debug_output == true) printToDebug(" (invalid category for destination device)");
        decodedTelegram.error = 263;
      }
    } else {
      sprintf(decodedTelegram.value, "%d", cat);
      if (debug_output == true) printToDebug(decodedTelegram.value);
      decodedTelegram.error = 258;
    }
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printCHOICE(byte *msg, byte data_len, uint_farptr_t enumstr, uint16_t enumstr_len) {
  if (data_len == 2 || bus->getBusType() == BUS_PPS) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS) {
      uint16_t search_val = msg[bus->getPl_start()+1] & 1;  // store either 0 or 1 (not 255)
      printENUM(enumstr,enumstr_len,search_val,1);
      sprintf(decodedTelegram.value,"%d",search_val);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
      printToDebug(decodedTelegram.value);
    }
    } else {
    printToDebug("CHOICE len !=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printCustomENUM(uint_farptr_t enumstr,uint16_t enumstr_len,uint16_t search_val, int print_val) {
  uint8_t val = 0;
  decodedTelegram.enumdescaddr = 0;
  if (enumstr!=0) {
    uint16_t c=0;
    while (c<enumstr_len) {
      val=pgm_read_byte_far(enumstr+c+1);
      //skip leading space
      c+=3;
      if (val==search_val) {
       // enum value found
       break;
      }
      while (pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if (c<enumstr_len) {
      decodedTelegram.enumdescaddr = enumstr+c;
      sprintf(decodedTelegram.value, "%d", val);
      if (print_val) {
        printFmtToDebug("%s - ", decodedTelegram.value);
      }
      printToDebug(decodedTelegram.enumdescaddr);
    } else {
      sprintf(decodedTelegram.value, "%d", search_val);
      printToDebug(decodedTelegram.value);
      decodedTelegram.error = 258;
    }
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printDateTime(byte *msg,byte data_len, uint8_t telegram_type) {
  if (data_len == 9) {
    if (msg[bus->getPl_start()]==0) {
      switch(telegram_type){
        case VT_DATETIME:
          sprintf(decodedTelegram.value,"%02d.%02d.%d %02d:%02d:%02d",msg[bus->getPl_start()+3],msg[bus->getPl_start()+2],msg[bus->getPl_start()+1]+1900,msg[bus->getPl_start()+5],msg[bus->getPl_start()+6],msg[bus->getPl_start()+7]);
          break;
        case VT_YEAR:
          sprintf(decodedTelegram.value,"%d",msg[bus->getPl_start()+1]+1900);
          break;
        case VT_DAYMONTH:
        case VT_VACATIONPROG:
          sprintf(decodedTelegram.value,"%02d.%02d.",msg[bus->getPl_start()+3],msg[bus->getPl_start()+2]);
          break;
        case VT_TIME:
          sprintf(decodedTelegram.value,"%02d:%02d:%02d",msg[bus->getPl_start()+5],msg[bus->getPl_start()+6],msg[bus->getPl_start()+7]);
        break;
      }
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(" VT_DATETIME len !=9: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printDate(byte *msg,byte data_len) {

  if (data_len == 9) {
    if (msg[bus->getPl_start()]==0) {
      sprintf(decodedTelegram.value,"%02d.%02d.",msg[bus->getPl_start()+3],msg[bus->getPl_start()+2]);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(" VT_DATE len !=9: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printTimeProg(byte *msg, byte data_len) {
  int len = 0;

  if (bus->getBusType() == BUS_PPS) {
    for (int i = 1; i > -5; i=i-2) {
      if (msg[bus->getPl_start()+i] <= 0x90) {
        len+=sprintf(decodedTelegram.value+len,"%02d:%02d-%02d:%02d ", msg[bus->getPl_start()+i] / 6, (msg[bus->getPl_start()+i] % 6) * 10, msg[bus->getPl_start()+i-1] / 6, (msg[bus->getPl_start()+i-1] % 6) * 10);
      } else {
        strcpy(decodedTelegram.value+len,"##:##-##:## ");
        len += 12;
      }
    }
    decodedTelegram.value[len-1] = 0;
    printToDebug(decodedTelegram.value);
  } else if (data_len == 12) {
    for (byte i = 0; i < 3; i++) {
      byte k = bus->getPl_start() + i * 4;
      if (msg[k]<24) {
        len+=sprintf(decodedTelegram.value+len,"%02d:%02d-%02d:%02d ",msg[k],msg[k + 1],msg[k + 2],msg[k + 3]);
      } else {
//        len += strlen(strcpy(decodedTelegram.value+len,"--:-- - --:--"));
        strcpy(decodedTelegram.value+len,"##:##-##:## ");
        len += 12;
      }
    }
    decodedTelegram.value[len-1] = 0;       // overwrite trailing whitespace
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(" VT_TIMEPROG len !=12: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printTime(byte *msg,byte data_len) {

  if (data_len == 3) {
    if (bus->getBusType() == BUS_PPS) {
      sprintf(decodedTelegram.value,"%02d:%02d",msg[bus->getPl_start()+1] / 6, (msg[bus->getPl_start()+1] % 6) * 10);
      printFmtToDebug("%02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d", msg[bus->getPl_start()+1] / 6, (msg[bus->getPl_start()+1] % 6) * 10, msg[bus->getPl_start()] / 6, (msg[bus->getPl_start()] % 6) * 10, msg[bus->getPl_start()-1] / 6, (msg[bus->getPl_start()-1] % 6) * 10, msg[bus->getPl_start()-2] / 6, (msg[bus->getPl_start()-2] % 6) * 10, msg[bus->getPl_start()-3] / 6, (msg[bus->getPl_start()-3] % 6) * 10, msg[bus->getPl_start()-4] / 6, (msg[bus->getPl_start()-4] % 6) * 10);
    } else {
      if (msg[bus->getPl_start()]==0) {
        sprintf(decodedTelegram.value,"%02d:%02d",msg[bus->getPl_start()+1],msg[bus->getPl_start()+2]);
      } else {
        strcpy(decodedTelegram.value,"--:--");
      }
      printToDebug(decodedTelegram.value);
    }
  } else {
    printToDebug("VT_HOUR_MINUTES len !=3: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *   byte * msg
 *   byte len
 *  Parameters passed back:
 *   byte *msg    unchanged
 *  Function value returned:
 *   none
 *  Global resources used:
 * *************************************************************** */
void printLPBAddr(byte *msg,byte data_len) {

  if (data_len == 2) {
    if (msg[bus->getPl_start()]==0) {   // payload Int8 value
      sprintf(decodedTelegram.value,"%02d.%02d",msg[bus->getPl_start()+1]>>4,(msg[bus->getPl_start()+1] & 0x0F)+1);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(" VT_LPBADDR len !=2: ");
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
  }
}

//Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr
void loadCategoryDescAddr() {
  printKat(decodedTelegram.cat, 0);
  decodedTelegram.catdescaddr = decodedTelegram.enumdescaddr;
  decodedTelegram.enumdescaddr = 0;
  decodedTelegram.value[0] = 0; //VERY IMPORTANT: reset result before decoding, in other case in case of error value from printENUM will be showed as correct value.
}

/** *****************************************************************
 *  Function:  printTelegram()
 *  Does:      Send the decoded telegram content to the hardware
 *             serial interface.
 *  Pass parameters:
 *   char* msg    the BS bus telegram
 *  Parameters passed back:
 *   char * pvalstr
 *  Function value returned:
 *   char*
 *  Global resources used:
 *   Serial    hardware serial interface to a PC
 *   outBuf[]
 *   decodedTelegram   error status, r/o flag
 *
 *
 *  NOTE: If you need pvalstr, you can call printTelegram() as
 *  printTelegram(msg, query_line);
 *  build_pvalstr(0);
 *  or, if You do not want every time decode pvalstr, you can use
 *  values from decodedTelegram structure after printTelegram() calling
 * *************************************************************** */
void printTelegram(byte* msg, float query_line) {
  resetDecodedTelegram();
/*
#if !DEBUG
  // suppress DE telegrams
  if (msg[0]==0xDE) return;

  // suppress QUERY telegrams
  if (msg[4]==TYPE_QUR) return;
#endif
*/

  uint8_t bus_type = bus->getBusType();
  uint8_t save_setmode = msg[bus->getPl_start()];
  uint8_t msg_source_addr = 0;
  uint8_t msg_dest_addr = 0;

  if (bus_type != BUS_PPS) {
    decodedTelegram.msg_type = msg[4+bus->offset];
    if (decodedTelegram.msg_type == TYPE_ANS) {
      decodedTelegram.enable_byte = msg[9+bus->offset];
    } else {
      decodedTelegram.enable_byte = 0;      // check if necessary to set enable_byte for sending SET telegram (logical values inverted, 01 = enable, 00 = disable)
    }
    msg_source_addr = msg[1+(bus_type*2)];
    msg_dest_addr = msg[2];
    // source
    SerialPrintAddr(msg_source_addr); // source address
    printToDebug("->");
    SerialPrintAddr(msg_dest_addr); // destination address
    printToDebug(" ");
    // msg[3] contains the message length, not handled here
    SerialPrintType(decodedTelegram.msg_type); // message type, human readable
    printFmtToDebug(" ");

    if (decodedTelegram.msg_type == TYPE_SET) {   // temporarily 
      msg[bus->getPl_start()]=0;
    }
  } else {
    if (!monitor) {
      if (msg[0] < 0xF0) {
        switch (msg[0] & 0x0F) {
          case 0x0D: printToDebug("PPS INF "); break;   // 0x1D
          case 0x0E: printToDebug("PPS REQ "); break;   // 0x1E
          case 0x07: printToDebug("PPS RTS "); break;   // 0x17
          default: break;
        }
      } else {
        switch (msg[0]) {
          case 0xF8:
          case 0xFB:
          case 0xFD:
          case 0xFE: printToDebug("PPS ANS "); break;
          default: break;
        }
      }
    }
  }

  uint32_t cmd = 0;
  //  uint8_t pps_cmd = msg[1 + (msg[0] == 0x17 && pps_write != 1)];
  uint8_t pps_cmd = msg[1];
  switch (bus_type) {
    case BUS_PPS:
      cmd = 0x2D000000 + ((uint16_t)query_line) - 15000;    // PPS commands start at parameter no. 15000
      cmd = cmd + (pps_cmd * 0x10000);
      break;
    default:
      if ((msg[4+bus->offset] & 0x0F)==TYPE_QUR || (msg[4+bus->offset] & 0x0F)==TYPE_SET) { //QUERY and SET: First two bytes of CommandID are in reversed order
        cmd=(uint32_t)msg[6+bus->offset]<<24 | (uint32_t)msg[5+bus->offset]<<16 | (uint32_t)msg[7+bus->offset] << 8 | (uint32_t)msg[8+bus->offset];
      } else {
        cmd=(uint32_t)msg[5+bus->offset]<<24 | (uint32_t)msg[6+bus->offset]<<16 | (uint32_t)msg[7+bus->offset] << 8 | (uint32_t)msg[8+bus->offset];
      }
      break;
  }
  // search for the command code in cmdtbl
  int i=0;        // begin with line 0
  int save_i=0;
  bool known=0;
  uint8_t score = 0;
  uint32_t c = 0;     // command code
  if (query_line != -1) {
    while (1) {
      i = findLine(query_line);
      c = cmdtbl[i].cmd;
      uint16_t dev_flags = cmdtbl[i].flags;
      if (((dev_flags & FL_NOSWAP_QUR) || (msg[4+bus->offset] & 0x0F) == TYPE_INF)) {  // if the QUR telegram is modified (in the sense that the first two bytes are not swapped), then the ANS telegram is also affected in the same way (i.e. the first two bytes are swapped here)
        c=((c & 0xFF000000) >> 8) | ((c & 0x00FF0000) << 8) | (c & 0x0000FFFF);
      }
      if (i != -1) {
        if ((c & 0xFF00FFFF) == (cmd & 0xFF00FFFF)) {
          save_i = i;
          known = true;
          break;
        }
        i++;
      } else {
        known = false;
        break;
      }
    }

  } else {
    int line = 0, match_line = 0;
    c=cmdtbl[i].cmd;
    line = cmdtbl[i].line;
    while (c!=CMD_END) {
      if ((c & 0xFF00FFFF) == (cmd & 0xFF00FFFF) || (bus_type == BUS_PPS && ((c & 0x00FF0000) >> 16 == pps_cmd))) {
        uint16_t dev_flags = cmdtbl[i].flags;
        uint8_t dev_fam = cmdtbl[i].dev_fam;
        uint8_t dev_var = cmdtbl[i].dev_var;
        match_line = cmdtbl[i].line;
        // Scoring system to find a command ID in the table:
        // 1 point: command ID is DEV_ALL (255, 255), but command ID is FL_NO_CMD (no longer in active use since version 3.0)
        // 2 points: command ID is DEV_ALL, and is not FL_NO_CMD
        // 3 points: command ID matches own device family, not device variant, but is FL_NO_CMD
        // 4 points: command ID matches own device family, and is not FL_NO_CMD
        // 5 points: command ID machtes own device family and variant, but is FL_NO_CMD
        // 6 points: command ID matches own device family and variant. Most exact match, abort further search.
        if ((dev_fam == my_dev_fam || dev_fam == 255) && (dev_var == my_dev_var || dev_var == 255)) {
          if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
            if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
              known = false;
              score = 5;
            } else {
              known = true;
              save_i = i;
              score = 6;
              break;
            }
          }
          if (dev_fam!=my_dev_fam) {
            if ((dev_flags & FL_NO_CMD) == FL_NO_CMD && score < 1) {
              known = false;
              score = 1;
            } else if (score < 2) {
              known = true;
              save_i = i;
              score = 2;
            }
          }
          if (dev_fam==my_dev_fam) {
            if ((dev_flags & FL_NO_CMD) == FL_NO_CMD && score < 3) {
              known = false;
              score = 3;
            } else if (score < 4) {
              known = true;
              save_i = i;
              score = 4;
            }
          }
        } else {          // Command ID found in other device family's entry. Store this as a last resort.
          score = 0;
          if (known != true) {
            known = true;
            save_i = i;
          }
        }
      }

      i++;
      line = cmdtbl[i].line;
      c=cmdtbl[i].cmd;
      if (line > match_line && known == false) {
        score = 0;
      }
    }
  }
  if (!known || (bus_type == BUS_PPS && (msg[0] & 0x0F) == 0x07)) { // no hex code match or PPS RTS telegram type (0x17)
    // Entry in command table is "UNKNOWN" (0x00000000)
    if (bus_type != BUS_PPS) {
      printToDebug("     ");
      if (decodedTelegram.msg_type < 0x12 || decodedTelegram.msg_type > 0x20) {
        printFmtToDebug("%08lX ", cmd);             // print what we have got
      }
    }
  } else {
    i = save_i;
    // Entry in command table is a documented command code
    decodedTelegram.prognr=cmdtbl[i].line;

    printFmtToDebug("%4.1f ",decodedTelegram.prognr);

    // print category
    loadPrognrElementsFromTable(query_line, i);
    loadCategoryDescAddr(); //Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr

    printToDebug(" - ");
    // print menue text
    printToDebug(decodedTelegram.prognrdescaddr);
    printToDebug(": ");
  }

  // decode parameter
  int data_len=0;
  switch (bus_type) {
    case BUS_BSB:
    if (decodedTelegram.msg_type < 0x12 || decodedTelegram.msg_type > 0x20) {
      data_len=msg[bus->getLen_idx()]-11;     // get packet length, then subtract
    } else {
      data_len=msg[bus->getLen_idx()]-7;      // for yet unknow telegram types 0x12 to 0x15
    }
    break;
    case BUS_LPB:
    if (decodedTelegram.msg_type < 0x12 || decodedTelegram.msg_type > 0x20) {
      data_len=msg[bus->getLen_idx()]-14;     // get packet length, then subtract
    } else {
      data_len=msg[bus->getLen_idx()]-7;      // for yet unknow telegram types 0x12 to 0x15
    }
    break;
    case BUS_PPS:
    if ((msg[0] & 0x0F) != 0x07 && (msg[0] & 0x0F) != 0x0E) {   // PPS telegram types 0x17 and 0x1E do not contain payload
      data_len = 3;
    } else {
      data_len = 0; // Do not try to decode request telegrams coming from the heataer (0x17 and 0x1E)
    }
    break;
  }
  if (data_len < 0) {
    printFmtToDebug("len ERROR %d", msg[bus->getLen_idx()]);
  } else {
    if (data_len > 0) {
      if (known) {
        if (decodedTelegram.msg_type==TYPE_ERR) {
//          outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[9]); For truncated error message LPB bus systems
//          if ((msg[9]==0x07 && bus_type==0) || (msg[9]==0x05 && bus_type==1)) {
          decodedTelegram.error = msg[bus->getPl_start()]; //0x07 - parameter not supported
          printFmtToDebug("error %d", decodedTelegram.error);
        } else {
          switch (decodedTelegram.type) {
            case VT_BIT: // u8
              printBIT(msg,data_len);
              break;
            case VT_LITER: // u8 Liter
            case VT_POWER_SHORT: // u8 Watt
            case VT_POWER_SHORT_N: // u8 Watt
            case VT_MONTHS: // u8 Monate
            case VT_MONTHS_N: // u8 Monate
            case VT_DAYS: // u8 Tage
            case VT_GRADIENT_SHORT: //u8 min
            case VT_HOURS_SHORT: // u8 h
            case VT_HOURS_SHORT_N: // u8 h
            case VT_MINUTES_SHORT: //u8 min
            case VT_MINUTES_SHORT_N: //u8 min
            case VT_SECONDS_SHORT: //u8 s
            case VT_SECONDS_SHORT_N: //u8 s
            case VT_PERCENT: // u8 %
            case VT_PERCENT_NN: // u8 %
            case VT_PERCENT1: // u8 %
            case VT_BYTE: // u8
            case VT_BYTE_N: // u8
//            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 //FUJITSU
              printBYTE(msg,data_len);
              break;
            case VT_MONTHS_WORD: // u16 Monate
            case VT_DAYS_WORD: // u16 Tage
            case VT_HOURS_WORD: // u16 h
            case VT_HOURS_WORD_N: // u16 h
            case VT_MINUTES_WORD: //u16 min
            case VT_MINUTES_WORD_N: //u16 min
            case VT_MINUTES_WORD10: //u16 min
            case VT_MSECONDS_WORD: //s16 ms
            case VT_MSECONDS_WORD_N: //s16 ms
            case VT_SECONDS_WORD: //u16 s
            case VT_SECONDS_WORD_N: //u16 s
            case VT_GRADIENT: // u16
//            case VT_INTEGRAL: // u16
            case VT_UINT: //  u16
            case VT_UINT_N: //  u16
              printWORD(msg,data_len,decodedTelegram.operand);
              break;
            case VT_MINUTES: // u32 min
            case VT_HOURS: // u32 h
            case VT_HOURS_N: // u32 h
            case VT_SECONDS_DWORD: //u32? s
            case VT_TEMP_DWORD: // u32 / 10.0 kW
            case VT_ENERGY: // u32 / 1.0 kWh
            case VT_ENERGY_N: // u32 / 1.0 kWh
            case VT_ENERGY10: // u32 / 10.0 kWh
            case VT_ENERGY10_N: // u32 / 10.0 kWh
            case VT_ENERGY_MWH: //u32 / 1 MW
            case VT_ENERGY_MWH_N: //u32 / 1 MW
            case VT_POWER: // u32 / 10.0 kW
            case VT_POWER100: //u32 / 100 kW
            case VT_CUBICMETER: //  u32 / 10
            case VT_CUBICMETER_N: //  u32 / 10
            case VT_UINT100:  // u32 / 100
            case VT_DWORD: // s32
            case VT_DWORD_N: // s32
            case VT_DWORD10:
              printDWORD(msg,data_len,decodedTelegram.operand);
              break;
            case VT_SINT: //  s16
            case VT_SINT_NN: //  s16
              printSINT(msg,data_len,decodedTelegram.operand);
              break;
            case VT_SECONDS_SHORT2: // s8 / 2 (signed)
            case VT_SECONDS_SHORT2_N: // s8 / 2 (signed)
            case VT_SECONDS_SHORT4: // s8 / 4 (signed)
            case VT_SECONDS_SHORT5: // s8 / 5 (signed)
            case VT_TEMP_SHORT64: // s8 / 64 (signed)
            case VT_TEMP_SHORT5: // s8 / 2 (signed)
            case VT_TEMP_SHORT5_N: // s8 / 2 (signed)
            case VT_TEMP_SHORT: // s8 (signed)
            case VT_TEMP_PER_MIN: // s8
            case VT_VOLTAGE: // u8
            case VT_VOLTAGE_N: // u8
              printFIXPOINT_BYTE(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_BYTE5_N: // u8 / 5.0
            case VT_BYTE10: // u8 / 10.0
            case VT_BYTE10_N: // u8 / 10.0
            case VT_LPM_SHORT: // u8 / 0.1 l/min
            case VT_PRESSURE: // u8 / 10.0 bar
            case VT_PRESSURE_NN: // u8 / 10.0 bar
            case VT_PRESSURE50: // u8 / 50.0 bar
            case VT_PERCENT5: // u8 %
            case VT_TEMP_SHORT5_US: // u8 / 2 (unsigned)
            case VT_TEMP_SHORT_US: //u8 (unsigned)
            case VT_TEMP_SHORT_US_N: //u8 (unsigned)
              printFIXPOINT_BYTE_US(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_TEMP: // s16 / 64.0 - Wert als Temperatur interpretiert (RAW / 64)
            case VT_TEMP_N: // s16 / 64.0 - Wert als Temperatur interpretiert (RAW / 64)
            case VT_SECONDS_WORD2: // u16  - Wert als Temperatur interpretiert (RAW / 5)
            case VT_SECONDS_WORD2_N: // u16  - Wert als Temperatur interpretiert (RAW / 5)
            case VT_SECONDS_WORD4: // u16  - Wert als Temperatur interpretiert (RAW / 4)
            case VT_SECONDS_WORD4_N: // u16  - Wert als Temperatur interpretiert (RAW / 4)
            case VT_SECONDS_WORD5: // u16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_SECONDS_WORD5_N: // u16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_SECONDS_WORD16: //u16 s
            case VT_TEMP_WORD: // s16  - Wert als Temperatur interpretiert (RAW)
            case VT_TEMP_WORD5_US: // s16  - Wert als Temperatur interpretiert (RAW / 2)
//            case VT_TEMP_WORD60: //  u16 / 60
            case VT_VOLTAGE_WORD: //unsigned?
            case VT_VOLTAGE_WORD1: //unsigned
            case VT_CELMIN: // u16 / °Cmin
            case VT_CELMIN_N: // u16 / °Cmin
            case VT_LITERPERHOUR: // u16 / l/h
            case VT_LITERPERHOUR_N: // u16 / l/h
            case VT_LITERPERHOUR100: // u16 / l/h
            case VT_LITERPERHOUR100_N: // u16 / l/h
            case VT_LITERPERMIN: // u16 / 0.1 l/min
            case VT_LITERPERMIN_N: // u16 / 0.1 l/min
            case VT_PRESSURE_WORD: // u16 / 10.0 bar
            case VT_PRESSURE_WORD_NN: // u16 / 10.0 bar
            case VT_PRESSURE_1000: // u16 / 1000.0 bar
            case VT_POWER_W: // u16 / 1.0 W
            case VT_POWER_W_N: // u16 / 1.0 W
            case VT_POWER_WORD: // u16 / 10.0 kW
            case VT_POWER_WORD_N: // u16 / 10.0 kW
            case VT_POWER_WORD100: // u16 / 100.0 kW
            case VT_ENERGY_WORD: // u16 / 10.0 kWh
            case VT_ENERGY_WORD_N: // u16 / 10.0 kWh
            case VT_SPF: // u16 / 100
            case VT_ENERGY_CONTENT: // u16 / 10.0 kWh/m³
            case VT_CURRENT: // u16 / 100 uA
            case VT_CURRENT1000:
            case VT_PROPVAL: // u16 / 16
            case VT_SPEED: // u16
            case VT_SPEED2: // u16
            case VT_SPEED2_N: // s16
            case VT_FREQ: // u16
            case VT_FREQ10: // s16
            case VT_FP1: // s16 / 10.0 Wert als Festkommazahl mit 1/10 Schritten interpretiert (RAW / 10)
            case VT_FP02: // u16 / 50.0 - Wert als Festkommazahl mit 2/100 Schritten interpretiert (RAW / 50)
            case VT_METER:
            case VT_PERCENT_WORD1: // u16 %
            case VT_PERCENT_WORD: // u16 / 2 %
            case VT_PERCENT_100: // u16 / 100 %
            case VT_SINT1000: // s16 / 1000
            case VT_UINT100_WORD:  // u16 / 100
            case VT_UINT100_WORD_N:  // u16 / 100
            case VT_UINT2_N: //  u16 / 5
            case VT_UINT5: //  u16 * 5
            case VT_UINT10: //  u16 / 10
            case VT_AMP:
              printFIXPOINT(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_BINARY_ENUM:
            case VT_ONOFF:
            case VT_YESNO:
            case VT_CLOSEDOPEN:
            case VT_VOLTAGEONOFF:
              printCHOICE(msg,data_len, decodedTelegram.enumstr, decodedTelegram.enumstr_len);
              break;
            case VT_LPBADDR: //decoding unklar 00 f0 -> 15.01
              printLPBAddr(msg,data_len);
              break;
            case VT_HOUR_MINUTES: // u8:u8
            case VT_HOUR_MINUTES_N: // u8:u8
              printTime(msg,data_len);
              break;
            case VT_YEAR:
            case VT_TIME:
            case VT_DAYMONTH:
            case VT_VACATIONPROG:
            case VT_DATETIME: // special
              printDateTime(msg,data_len, decodedTelegram.type);
              break;
            case VT_TIMEPROG:
              printTimeProg(msg,data_len);
              break;
/*
//VT_WEEKDAY is ENUM
// ENUM_WEEKDAY used in one program 1642 as enum
//VT_WEEKDAY defined as DT_WDAY but DT_WDAY nowhere used
            case VT_WEEKDAY: // enum
              if (data_len == 2) {
                if (msg[bus->getPl_start()]==0) {
                  int len=sizeof(ENUM_WEEKDAY);
                  printENUM(ENUM_WEEKDAY,len,msg[bus->getPl_start()+1],0);
                } else {
                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(" VT_WEEKDAY !=2: ");
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
*/
            case VT_WEEKDAY:
            case VT_ENUM: // enum
              if (data_len == 2 || data_len == 3) {
                if ((msg[bus->getPl_start()]==0 && data_len==2) || (msg[bus->getPl_start()]==0 && data_len==3) || (bus_type == BUS_PPS)) {
                  if (decodedTelegram.enumstr!=0) {
                    if (data_len == 2 || bus_type == BUS_PPS) {
                      printENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,msg[bus->getPl_start()+1],1);
                    } else if (data_len == 3) {                            // Fujitsu: data_len == 3
                      long lval;
                      lval=(long(msg[bus->getPl_start()+1])<<8)+long(msg[bus->getPl_start()+2]);
                      printENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,lval,1);
                    }
                  } else {
                    decodedTelegram.error = 259;
                    printToDebug(printError(decodedTelegram.error));
                    SerialPrintData(msg);
                  }
                } else {
                  strcpy(decodedTelegram.value, "65535");
                  decodedTelegram.enumdescaddr = STR_DISABLED;
//                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(" VT_ENUM len !=2 && len != 3: ");
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_CUSTOM_ENUM: // custom enum - extract information from a telegram that contains more than one kind of information/data. First byte of the ENUM is the index to the payload where the data is located. This will then be used as data to be displayed/evaluated.
            {
              if (decodedTelegram.enumstr!=0) {
                uint8_t idx = pgm_read_byte_far(decodedTelegram.enumstr+0);
                printCustomENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,msg[bus->getPl_start()+idx],1);
              } else {
                decodedTelegram.error = 259;
                printToDebug(printError(decodedTelegram.error));
                SerialPrintData(msg);
              }
              break;
            }
            case VT_CUSTOM_BYTE: // custom byte
            {
              if (decodedTelegram.enumstr!=0) {
                uint8_t idx = pgm_read_byte_far(decodedTelegram.enumstr+0);
                uint8_t len = pgm_read_byte_far(decodedTelegram.enumstr+1);
                uint32_t val = 0;
                for (int x=0; x<len; x++) {
                  val = val + ((uint32_t)msg[bus->getPl_start()+idx+x] << (8*(len-1-x)));
                }
                sprintf(decodedTelegram.value,"%lu",val);
                printToDebug(decodedTelegram.value);
              } else {
                decodedTelegram.error = 259;
                printToDebug(printError(decodedTelegram.error));
                SerialPrintData(msg);
              }
              break;
            }
            case VT_CUSTOM_BIT: // u8
            {
              uint8_t bit_index = (byte)pgm_read_byte_far(decodedTelegram.enumstr);
              printCustomBIT(msg,bit_index);
              break;
            }
            case VT_STRING: // string
              if (data_len > 0) {
                if (msg[bus->getPl_start()]!=0) {
                  msg[bus->getPl_start() + data_len]='\0'; // write terminating zero
                  printToDebug((char*)&msg[bus->getPl_start()]);
                  strcpy(decodedTelegram.value,(char*)&msg[bus->getPl_start()]);
                  remove_char(decodedTelegram.value, '\'');
                } else {
                  strcpy(decodedTelegram.value,"-");
                }
                 printToDebug(decodedTelegram.value);
              } else {
                printToDebug(" VT_STRING len == 0: ");
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_PPS_TIME: // PPS: Time and day of week
            {
              sprintf(decodedTelegram.value, "%02d:%02d:%02d", hour(), minute(), second());
              printToDebug(decodedTelegram.value);
              break;
            }
            case VT_ERRORCODE: //  u16 or u8 (via OCI420)
              if (data_len == 3 || data_len == 2) {
                if (msg[bus->getPl_start()]==0) {
                  long lval;
                  if (data_len == 3) {
                    lval=(long(msg[bus->getPl_start()+1])<<8)+long(msg[bus->getPl_start()+2]);
                  } else {
                    lval=long(msg[bus->getPl_start()+1]);
                  }
                  printENUM(decodedTelegram.enumstr, decodedTelegram.enumstr_len,lval,1);
                } else {
                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(" VT_ERRORCODE len == 0: ");
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_UNKNOWN:
            default:
              prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
              if (decodedTelegram.telegramDump)
                strcpy(decodedTelegram.value, decodedTelegram.telegramDump);
              decodedTelegram.error = 260;
              break;
          }
        }
      } else {
        if (bus_type != BUS_PPS) {
          SerialPrintData(msg);
        }
//        writelnToDebug();
//        SerialPrintRAW(msg,msg[len_idx]+bus_type);
        decodedTelegram.error = 257;
      }
    }
  }
  msg[bus->getPl_start()] = save_setmode;
  if (bus_type != BUS_PPS || (bus_type == BUS_PPS && !monitor)) {
    writelnToDebug();
  }
  if (verbose) {
    if (bus_type != BUS_PPS) {
      SerialPrintRAW(msg,msg[bus->getLen_idx()]+bus_type);
    } else {
      SerialPrintRAW(msg, 9);
    }
    writelnToDebug();
  }
  if ((decodedTelegram.msg_type == TYPE_SET || decodedTelegram.msg_type == TYPE_INF) && decodedTelegram.prognr > -1 && msg_source_addr != bus->getBusAddr()) {   // restore enable/disable SET byte and log to MQTT if sender is not us
    parameter param;
    param.number = decodedTelegram.prognr;
    if (msg_dest_addr != bus->getBusDest() && decodedTelegram.msg_type != TYPE_INF) {
      param.dest_addr = msg_dest_addr;
    } else {
      param.dest_addr = -1;
    }
    if ((LoggingMode & CF_LOGMODE_MQTT) && decodedTelegram.error == 0) {
      mqtt_sendtoBroker(param);
    }
  }
}
