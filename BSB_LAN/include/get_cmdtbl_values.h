
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
#ifdef DEVELOPER_DEBUG
  printFmtToDebug(PSTR("prognr: %.1f, startindex: %d\r\n"), prognr, startFromTableLine);
#endif
  do{
    startFromTableLine++;
    if(cmdtblsize <= startFromTableLine) {
#ifdef DEVELOPER_DEBUG
      printFmtToDebug(PSTR("nextprognr: -1\r\n"));
#endif
      return -1;
    }
    nextprognr = get_cmdtbl_line(startFromTableLine);
#ifdef DEVELOPER_DEBUG
    printFmtToDebug(PSTR("nextindex: %d\r\n"), startFromTableLine);
#endif
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
#ifdef DEVELOPER_DEBUG
  printFmtToDebug(PSTR("nextprognr: %.1f\r\n"), nextprognr);
#endif
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
  int cat_min = 0;
  int cat_max = 0;
  for (uint cat=0;cat<CAT_UNKNOWN;cat++) {
    cat_min = ENUM_CAT_NR[cat*2];
    cat_max = ENUM_CAT_NR[cat*2+1];
    if (cat*2+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
      if (cat_max > ENUM_CAT_NR[cat*2+2]) {
        cat_max = ENUM_CAT_NR[cat*2+2]-1;
      }
    }
    if (cmdtbl[i].line >= cat_min && cmdtbl[i].line <= cat_max) {
      return cat;
    }
  }
  return 0;
//  return cmdtbl[i].category;
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
