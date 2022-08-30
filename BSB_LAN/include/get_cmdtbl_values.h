
inline uint32_t get_cmdtbl_cmd(int i) {
//  c=pgm_read_dword(&cmdtbl[i].cmd);  // command code
  return cmdtbl[i].cmd;
}

inline float get_cmdtbl_line(int i) {
//  l=pgm_read_word(&cmdtbl[i].line);  // ProgNr
  return cmdtbl[i].line;
}

float get_next_prognr(float currentProgNR, int startFromTableLine){
  if(startFromTableLine < 0) {
#if defined(__SAM3X8E__)
    double intpart;
#else
    float intpart;
#endif
    modf(currentProgNR, &intpart);
    return intpart + 1;
  }
  int cmdtblsize = sizeof(cmdtbl)/sizeof(cmdtbl[0]);
  float prognr = get_cmdtbl_line(startFromTableLine);
  float nextprognr = -1;
//  printFmtToDebug(PSTR("prognr: %.1f, startindex: %d\r\n"), prognr, startFromTableLine);
  do{
    startFromTableLine++;
    if(cmdtblsize == startFromTableLine) {
//      printFmtToDebug(PSTR("nextprognr: -1\r\n"));
      return -1;
    }
    nextprognr = get_cmdtbl_line(startFromTableLine);
//    printFmtToDebug(PSTR("nextindex: %d\r\n"), startFromTableLine);
  } while (prognr == nextprognr);
  if(currentProgNR >= BSP_INTERNAL && currentProgNR < BSP_END) {
    float prognrDiff = currentProgNR - prognr;
#if defined(__SAM3X8E__)
    double intpart1, intpart2;
#else
    float intpart1, intpart2;
#endif
    modf(prognr, &intpart1);
    modf(nextprognr, &intpart2);
    if(intpart1 == intpart2) {
      nextprognr += prognrDiff;
    } else {
      if(recognizeVirtualFunctionGroup(currentProgNR + 1)){
#if defined(__SAM3X8E__)
          double intpart;
#else
          float intpart;
#endif
        modf(currentProgNR, &intpart);
        nextprognr = intpart + 1;
      }
    }
  }
//  printFmtToDebug(PSTR("nextprognr: %.1f\r\n"), nextprognr);
  return nextprognr;
}

inline uint_farptr_t get_cmdtbl_desc(int i) {
  return cmdtbl[i].desc;
}

inline uint_farptr_t get_cmdtbl_enumstr(int i) {
  return cmdtbl[i].enumstr;
}

inline uint16_t get_cmdtbl_enumstr_len(int i) {
  return cmdtbl[i].enumstr_len;
}


inline uint8_t get_cmdtbl_category(int i) {
  return cmdtbl[i].category;
}

inline uint8_t get_cmdtbl_type(int i) {
  return cmdtbl[i].type;
}

inline uint8_t get_cmdtbl_dev_fam(int i) {
  return cmdtbl[i].dev_fam;
}

inline uint8_t get_cmdtbl_dev_var(int i) {
  return cmdtbl[i].dev_var;
}

inline uint8_t get_cmdtbl_flags(int i) {
  return cmdtbl[i].flags;
}
