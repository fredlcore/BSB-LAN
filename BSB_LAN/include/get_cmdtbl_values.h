
uint32_t get_cmdtbl_cmd(int i) {
  uint32_t c = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//  c=pgm_read_dword(&cmdtbl[i].cmd);  // command code
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl1[0].cmd) + i * sizeof(cmdtbl1[0]));
#else
    c = cmdtbl1[i].cmd;
#endif
} else if (i < entries2) {
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl2[0].cmd) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    c = cmdtbl2[i-entries1].cmd;
#endif
  } else {
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl3[0].cmd) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    c = cmdtbl3[i-entries2].cmd;
#endif
  }
  return c;
}

float get_cmdtbl_line(int i) {
  float l = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//  l=pgm_read_word(&cmdtbl[i].line);  // ProgNr
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].line) + i * sizeof(cmdtbl1[0]));
#else
    l = cmdtbl1[i].line;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].line) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    l = cmdtbl2[i-entries1].line;
#endif
  } else {
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].line) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    l = cmdtbl3[i-entries2].line;
#endif
  }
  return l;
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
  int cmdtblsize = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) + sizeof(cmdtbl2)/sizeof(cmdtbl2[0]) + sizeof(cmdtbl3)/sizeof(cmdtbl3[0]);
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

uint_farptr_t get_cmdtbl_desc(int i) {
  uint_farptr_t desc = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].desc) + i * sizeof(cmdtbl1[0]));
#else
    desc = cmdtbl1[i].desc;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].desc) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    desc = cmdtbl2[i-entries1].desc;
#endif
  } else {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].desc) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    desc = cmdtbl3[i-entries2].desc;
#endif
  }
  return desc;
}

uint_farptr_t get_cmdtbl_enumstr(int i) {
  uint_farptr_t enumstr = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr) + i * sizeof(cmdtbl1[0]));
#else
    enumstr = cmdtbl1[i].enumstr;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    enumstr = cmdtbl2[i-entries1].enumstr;
#endif
  } else {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].enumstr) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    enumstr = cmdtbl3[i-entries2].enumstr;
#endif
  }
  return enumstr;
}

uint16_t get_cmdtbl_enumstr_len(int i) {
  uint16_t enumstr_len = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr_len) + i * sizeof(cmdtbl1[0]));
#else
    enumstr_len = cmdtbl1[i].enumstr_len;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr_len) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    enumstr_len = cmdtbl2[i-entries1].enumstr_len;
#endif
  } else {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].enumstr_len) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    enumstr_len = cmdtbl3[i-entries2].enumstr_len;
#endif
  }
  return enumstr_len;
}


uint8_t get_cmdtbl_category(int i) {
  uint8_t cat = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//   cat=pgm_read_byte(&cmdtbl[i].category);
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].category) + i * sizeof(cmdtbl1[0]));
#else
    cat = cmdtbl1[i].category;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].category) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    cat = cmdtbl2[i-entries1].category;
#endif
  } else {
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].category) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    cat = cmdtbl3[i-entries2].category;
#endif
  }
  return cat;
}

uint8_t get_cmdtbl_type(int i) {
  uint8_t type = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].type) + i * sizeof(cmdtbl1[0]));
#else
    type = cmdtbl1[i].type;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].type) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    type = cmdtbl2[i-entries1].type;
#endif
  } else {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].type) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    type = cmdtbl3[i-entries2].type;
#endif
  }
  return type;
}

uint8_t get_cmdtbl_dev_fam(int i) {
  uint8_t dev_fam = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_fam) + i * sizeof(cmdtbl1[0]));
#else
    dev_fam = cmdtbl1[i].dev_fam;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_fam) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    dev_fam = cmdtbl2[i-entries1].dev_fam;
#endif
  } else {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].dev_fam) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    dev_fam = cmdtbl3[i-entries2].dev_fam;
#endif
  }
  return dev_fam;
}

uint8_t get_cmdtbl_dev_var(int i) {
  uint8_t dev_var = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_var) + i * sizeof(cmdtbl1[0]));
#else
    dev_var = cmdtbl1[i].dev_var;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_var) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    dev_var = cmdtbl2[i-entries1].dev_var;
#endif
  } else {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].dev_var) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    dev_var = cmdtbl3[i-entries2].dev_var;
#endif
  }
  return dev_var;
}

uint8_t get_cmdtbl_flags(int i) {
  uint8_t flags = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].flags) + i * sizeof(cmdtbl1[0]));
#else
    flags = cmdtbl1[i].flags;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].flags) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    flags = cmdtbl2[i-entries1].flags;
#endif
  } else {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].flags) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    flags = cmdtbl3[i-entries2].flags;
#endif
  }
  return flags;
}
