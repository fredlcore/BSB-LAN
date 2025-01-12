#define DEFAULT_DEFS 1

// Menu Categories
typedef enum{
  CAT_DATUMZEIT,
  CAT_HK1,
  CAT_KONFIG,
  CAT_DIAG_VERBRAUCHER,
  CAT_USER_DEFINED,
  CAT_PPS,
  CAT_USERSENSORS,
  CAT_UNKNOWN
}category_t;

/****************************************************/
/* TABLES and STRINGS                               */
/****************************************************/
// Menue Kategorien
const char ENUM_CAT[] = {
"\x00 " ENUM_CAT_00_TEXT "\0"
"\x01 " ENUM_CAT_11_TEXT "\0"
"\x02 " ENUM_CAT_31_TEXT "\0"
"\x03 " ENUM_CAT_3d_TEXT "\0"
"\x04 " ENUM_CAT_40_TEXT "\0"
"\x05 " ENUM_CAT_43_TEXT "\0"
"\x06 " ENUM_CAT_44_TEXT "\0"
"\x07 " ENUM_CAT_45_TEXT
};

const float ENUM_CAT_NR[] = {
  0, 6,
  700, 900,
  5700, 6699,
  8700, 9075,
  10000, 11999,
  15000, 15099,
  20000, 20899 //Virtual category for durations, averages, One Wire, DHT22, MAX! sensors, custom floats and longs
};

 /* Menue Strings */
const char STR0[] = STR0_TEXT;
const char STR1[] = STR1_TEXT;
const char STR2[] = STR2_TEXT;
const char STR3[] = STR3_TEXT;
const char STR5[] = STR5_TEXT;
const char STR6[] = STR6_TEXT;
const char STR20[] = STR20_TEXT;
const char STR21[] = STR21_TEXT;
const char STR22[] = STR22_TEXT;
const char STR23[] = STR23_TEXT;
const char STR25[] = STR25_TEXT;
const char STR26[] = STR26_TEXT;
const char STR27[] = STR27_TEXT;
const char STR28[] = STR28_TEXT;
const char STR29[] = STR29_TEXT;
const char STR30[] = STR30_TEXT;
const char STR31[] = STR31_TEXT;
const char STR40[] = STR40_TEXT;
const char STR42[] = STR42_TEXT;
const char STR42_2[] = STR42_2_TEXT;
const char STR44[] = STR44_TEXT;
const char STR46[] = STR46_TEXT;
const char STR48[] = STR48_TEXT;
const char STR54[] = STR54_TEXT;
const char STR70[] = STR70_TEXT;
const char STR71[] = STR71_TEXT;
const char STR120[] = STR120_TEXT;
const char STR121[] = STR121_TEXT;
const char STR130[] = STR130_TEXT;
const char STR131[] = STR131_TEXT;
const char STR132[] = STR132_TEXT;
const char STR133[] = STR133_TEXT;
const char STR134[] = STR134_TEXT;
const char STR135[] = STR135_TEXT;
const char STR136[] = STR136_TEXT;
const char STR137[] = STR137_TEXT;
const char STR138[] = STR138_TEXT;
const char STR140[] = STR140_TEXT;
const char STR500[] = STR500_TEXT;
const char STR501[] = STR501_TEXT;
const char STR502[] = STR502_TEXT;
const char STR503[] = STR503_TEXT;
const char STR504[] = STR504_TEXT;
const char STR505[] = STR505_TEXT;
const char STR506[] = STR506_TEXT;

const char STR516[] = STR516_TEXT;

#define STR520 STR500
#define STR521 STR501
#define STR522 STR502
#define STR523 STR503
#define STR524 STR504
#define STR525 STR505
#define STR526 STR506
#define STR536 STR516

#define STR540 STR500
#define STR541 STR501
#define STR542 STR502
#define STR543 STR503
#define STR544 STR504
#define STR545 STR505
#define STR546 STR506
#define STR556 STR516

#define STR560 STR500
#define STR561 STR501
#define STR562 STR502
#define STR563 STR503
#define STR564 STR504
#define STR565 STR505
#define STR566 STR506
#define STR576 STR516

#define STR600 STR500
#define STR601 STR501
#define STR602 STR502
#define STR603 STR503
#define STR604 STR504
#define STR605 STR505
#define STR606 STR506
#define STR616 STR516

/* Die Zeilennummern 632-682 entsprechen nicht den Zeilennummern im Bedienteil,
 * sondern wurden künstlich hinzugefügt */
const char STR632[] = STR632_TEXT;
const char STR633[] = STR633_TEXT;
const char STR634[] = STR634_TEXT;
const char STR635[] = STR635_TEXT;
const char STR636[] = STR636_TEXT;
const char STR637[] = STR637_TEXT;
const char STR638[] = STR638_TEXT;
const char STR639[] = STR639_TEXT;
const char STR640[] = STR640_TEXT;
const char STR641[] = STR641_TEXT;
const char STR642[] = STR642_TEXT;
const char STR643[] = STR643_TEXT;
const char STR644[] = STR644_TEXT;
const char STR645[] = STR645_TEXT;
const char STR646[] = STR646_TEXT;
const char STR647[] = STR647_TEXT;
const char STR648[] = STR648_TEXT;

#define STR649 STR632
#define STR650 STR633
#define STR651 STR634
#define STR652 STR635
#define STR653 STR636
#define STR654 STR637
#define STR655 STR638
#define STR656 STR639
#define STR657 STR640
#define STR658 STR641
#define STR659 STR642
#define STR660 STR643
#define STR661 STR644
#define STR662 STR645
#define STR663 STR646
#define STR664 STR647
#define STR665 STR648

#define STR666 STR632
#define STR667 STR633
#define STR668 STR634
#define STR669 STR635
#define STR670 STR636
#define STR671 STR637
#define STR672 STR638
#define STR673 STR639
#define STR674 STR640
#define STR675 STR641
#define STR676 STR642
#define STR677 STR643
#define STR678 STR644
#define STR679 STR645
#define STR680 STR646
#define STR681 STR647
#define STR682 STR648

/*
#define STR641 STR500
#define STR642 STR642
#define STR643 STR643
#define STR648 STR648
#define STR651 STR500
#define STR652 STR642
#define STR653 STR643
#define STR658 STR648
#define STR661 STR500
#define STR662 STR642
#define STR663 STR643
#define STR668 STR648
*/

// Heizkreis 1
const char STR700[] = STR700_TEXT;
const char STR701[] = STR701_TEXT;
#define STR702 STR701
#define STR703 STR702
const char STR704[] = STR704_TEXT;
const char STR705[] = STR705_TEXT;
const char STR706[] = STR706_TEXT;
const char STR707[] = STR707_TEXT;
const char STR709[] = STR709_TEXT;
const char STR710[] = STR710_TEXT;
const char STR711[] = STR711_TEXT;
const char STR712[] = STR712_TEXT;
const char STR714[] = STR714_TEXT;
#define STR716 STR711
const char STR720[] = STR720_TEXT;
const char STR721[] = STR721_TEXT;
const char STR726[] = STR726_TEXT;
const char STR730[] = STR730_TEXT;
const char STR732[] = STR732_TEXT;
const char STR733[] = STR733_TEXT;
const char STR734[] = STR734_TEXT;
const char STR739[] = STR739_TEXT;
const char STR740[] = STR740_TEXT;
const char STR741[] = STR741_TEXT;
const char STR742[] = STR742_TEXT;
const char STR744[] = STR744_TEXT;
const char STR746[] = STR746_TEXT;
const char STR750[] = STR750_TEXT;
const char STR760[] = STR760_TEXT;
const char STR761[] = STR761_TEXT;
const char STR770[] = STR770_TEXT;
const char STR780[] = STR780_TEXT;
const char STR781[] = STR781_TEXT;
const char STR790[] = STR790_TEXT;
const char STR791[] = STR791_TEXT;
const char STR794[] = STR794_TEXT;
const char STR800[] = STR800_TEXT;
const char STR801[] = STR801_TEXT;
const char STR809[] = STR809_TEXT;
const char STR810[] = STR810_TEXT;
const char STR812[] = STR812_TEXT;
const char STR820[] = STR820_TEXT;
const char STR830[] = STR830_TEXT;
const char STR831[] = STR831_TEXT;
const char STR832[] = STR832_TEXT;
const char STR833[] = STR833_TEXT;
const char STR834[] = STR834_TEXT;
const char STR835[] = STR835_TEXT;
const char STR836[] = STR836_TEXT;
const char STR841[] = STR841_TEXT;
const char STR843[] = STR843_TEXT;
const char STR850[] = STR850_TEXT;
const char STR851[] = STR851_TEXT;
const char STR855[] = STR855_TEXT;
const char STR856[] = STR856_TEXT;
const char STR857[] = STR857_TEXT;
const char STR860[] = STR860_TEXT;
const char STR861[] = STR861_TEXT;
const char STR864[] = STR864_TEXT;
const char STR870[] = STR870_TEXT;
const char STR872[] = STR872_TEXT;
const char STR880[] = STR880_TEXT;
const char STR881[] = STR881_TEXT;
const char STR882[] = STR882_TEXT;
const char STR883[] = STR883_TEXT;
const char STR884[] = STR884_TEXT;
const char STR885[] = STR885_TEXT;
const char STR886[] = STR886_TEXT;
const char STR886_2[] = STR886_2_TEXT;
const char STR887[] = STR887_TEXT;
const char STR888[] = STR888_TEXT;
const char STR888_2[] = STR888_2_TEXT;
const char STR889[] = STR889_TEXT;
const char STR890[] = STR890_TEXT;
const char STR890_2[] = STR890_2_TEXT;
const char STR891[] = STR891_TEXT;
const char STR892[] = STR892_TEXT;
const char STR893[] = STR893_TEXT;
const char STR894[] = STR894_TEXT;
const char STR895[] = STR895_TEXT;
const char STR898[] = STR898_TEXT;

// Einstellungen Kühlkreis 1
#define STR900 STR700
#define STR901 STR701
#define STR902 STR710
#define STR903 STR712
const char STR904[] = STR904_TEXT;
#define STR905 STR709
const char STR907[] = STR907_TEXT;
const char STR908[] = STR908_TEXT;
const char STR909[] = STR909_TEXT;
const char STR912[] = STR912_TEXT;
const char STR913[] = STR913_TEXT;
const char STR914[] = STR914_TEXT;
const char STR918[] = STR918_TEXT;
const char STR919[] = STR919_TEXT;
const char STR920[] = STR920_TEXT;
const char STR923[] = STR923_TEXT;
const char STR924[] = STR924_TEXT;
const char STR925[] = STR925_TEXT;
#define STR928 STR750
#define STR932 STR760
const char STR933[] = STR933_TEXT;
const char STR937[] = STR937_TEXT;
#define STR938 STR831
#define STR939 STR832
#define STR940 STR833
#define STR941 STR834
#define STR942 STR835
#define STR943 STR836
const char STR945[] = STR945_TEXT;
const char STR946[] = STR946_TEXT;
const char STR947[] = STR947_TEXT;
const char STR948[] = STR948_TEXT;
const char STR949[] = STR949_TEXT;
const char STR950[] = STR950_TEXT;
#define STR962 STR870
#define STR963 STR872
#define STR969 STR900

// Einstellungen Heizkreis 2
#define STR1000 STR700
#define STR1001 STR701
#define STR1004 STR704
#define STR1005 STR705
#define STR1006 STR706
#define STR1007 STR707
#define STR1010 STR710
#define STR1011 STR711
#define STR1012 STR712
#define STR1014 STR714
#define STR1016 STR711
#define STR1020 STR720
#define STR1021 STR721
#define STR1026 STR726
#define STR1030 STR730
#define STR1032 STR732
#define STR1033 STR733

const char STR1044[] = STR1044_TEXT;
#define STR1040 STR740
#define STR1041 STR741
#define STR1042 STR742
#define STR1046 STR746
#define STR1050 STR750
#define STR1060 STR760
#define STR1061 STR761
#define STR1070 STR770
#define STR1080 STR780
#define STR1081 STR781
#define STR1090 STR790
#define STR1091 STR791
#define STR1094 STR794
#define STR1100 STR800
#define STR1101 STR801
#define STR1109 STR809
#define STR1110 STR810
#define STR1112 STR812
#define STR1120 STR820
#define STR1130 STR830
#define STR1131 STR831
#define STR1132 STR832
#define STR1133 STR833
#define STR1134 STR834
#define STR1135 STR835
#define STR1136 STR836
#define STR1141 STR841
#define STR1143 STR843
#define STR1150 STR850
#define STR1151 STR851
#define STR1155 STR855
#define STR1156 STR856
#define STR1157 STR857
#define STR1160 STR860
#define STR1161 STR861
#define STR1164 STR864
#define STR1170 STR870
#define STR1172 STR872
#define STR1180 STR880
#define STR1181 STR881
#define STR1182 STR882
#define STR1183 STR883
#define STR1185 STR885
#define STR1186 STR886
#define STR1186_2 STR886_2
#define STR1188_2 STR888_2
#define STR1189 STR889
#define STR1190 STR890
#define STR1198 STR898
#define STR1200 STR900

// Heizkreis 3/P
#define STR1300 STR700
#define STR1301 STR701
#define STR1301 STR701
#define STR1304 STR704
#define STR1305 STR705
#define STR1306 STR706
#define STR1307 STR707
#define STR1310 STR710
#define STR1311 STR711
#define STR1312 STR712
#define STR1314 STR714
#define STR1316 STR711
#define STR1320 STR720
#define STR1321 STR721
#define STR1326 STR726
#define STR1330 STR730
#define STR1332 STR732
#define STR1333 STR733
#define STR1340 STR740
#define STR1341 STR741
#define STR1342 STR742
#define STR1344 STR744
#define STR1346 STR746
#define STR1350 STR750
#define STR1360 STR760
#define STR1361 STR761
#define STR1370 STR770
#define STR1380 STR780
#define STR1381 STR781
#define STR1390 STR790
#define STR1391 STR791
#define STR1394 STR794
#define STR1400 STR1100
#define STR1401 STR801
#define STR1409 STR809
#define STR1410 STR810
#define STR1412 STR812
#define STR1420 STR820
#define STR1430 STR830
#define STR1431 STR831
#define STR1432 STR832
#define STR1433 STR833
#define STR1434 STR834
#define STR1435 STR835
#define STR1436 STR836
#define STR1441 STR841
#define STR1443 STR843
#define STR1450 STR1150
#define STR1451 STR1151
#define STR1455 STR1155
#define STR1456 STR1156
#define STR1457 STR1157
#define STR1460 STR860
#define STR1461 STR861
#define STR1464 STR864
#define STR1470 STR870
#define STR1472 STR872
#define STR1480 STR880
#define STR1481 STR881
#define STR1482 STR882
#define STR1483 STR883
#define STR1485 STR885
#define STR1486 STR886
#define STR1486_2 STR886_2
#define STR1488 STR888
#define STR1489 STR889
#define STR1490 STR890
#define STR1498 STR898
#define STR1500 STR900

// Trinkwasser
#define STR1600 STR700_TEXT
const char STR1601[] = STR1601_TEXT;
const char STR1602[] = STR1602_TEXT;
const char STR1603[] = STR1603_TEXT;
const char STR1610[] = STR1610_TEXT;
const char STR1612[] = STR1612_TEXT;
const char STR1614[] = STR1614_TEXT;
const char STR1615[] = STR1615_TEXT;
const char STR1616[] = STR1616_TEXT;
const char STR1620[] = STR1620_TEXT;
const char STR1630[] = STR1630_TEXT;
const char STR1640[] = STR1640_TEXT;
const char STR1641[] = STR1641_TEXT;
const char STR1642[] = STR1642_TEXT;
const char STR1644[] = STR1644_TEXT;
const char STR1645[] = STR1645_TEXT;
const char STR1646[] = STR1646_TEXT;
const char STR1647[] = STR1647_TEXT;
const char STR1648[] = STR1648_TEXT;
const char STR1660[] = STR1660_TEXT;
const char STR1661[] = STR1661_TEXT;
const char STR1663[] = STR1663_TEXT;
const char STR1680[] = STR1680_TEXT;

//Verbraucherkreis 1
const char STR1859[] = STR1859_TEXT;
#define STR1874 STR1630
#define STR1875 STR861
#define STR1878 STR870
#define STR1880 STR963

//Verbraucherkreis 2
#define STR1909 STR1859
#define STR1924 STR1630
#define STR1925 STR1875
#define STR1928 STR1878
#define STR1930 STR963

//Schwimmbadkreis
#define STR1959 STR1859
#define STR1974 STR1630
#define STR1975 STR1875
#define STR1978 STR1878
#define STR1980 STR963

// Hx Pumpe
const char STR2008[] = STR2008_TEXT;
const char STR2010[] = STR2010_TEXT;
const char STR2012[] = STR2012_TEXT;
const char STR2014[] = STR2014_TEXT;
const char STR2015[] = STR2015_TEXT;
const char STR2033[] = STR2033_TEXT;
const char STR2035[] = STR2035_TEXT;
const char STR2037[] = STR2037_TEXT;
const char STR2039[] = STR2039_TEXT;
const char STR2040[] = STR2040_TEXT;
const char STR2044[] = STR2044_TEXT;
const char STR2046[] = STR2046_TEXT;
const char STR2048[] = STR2048_TEXT;
const char STR2050[] = STR2050_TEXT;
const char STR2051[] = STR2051_TEXT;

// Schwimmbad
const char STR2055[] = STR2055_TEXT;
const char STR2056[] = STR2056_TEXT;
const char STR2065[] = STR2065_TEXT;
const char STR2070[] = STR2070_TEXT;
const char STR2080[] = STR2080_TEXT;

// Vorregler/Zubringerpumpe
#define STR2110 STR740
#define STR2111 STR741
const char STR2112[] = STR2112_TEXT;
const char STR2121[] = STR2121_TEXT;
#define STR2130 STR830
#define STR2131 STR831
#define STR2132 STR832
#define STR2133 STR833
#define STR2134 STR834
#define STR2135 STR835
#define STR2136 STR836
const char STR2150[] = ENUM_CAT_20_TEXT;

// Kessel
#define STR2200 STR700
const char STR2201[] = STR2201_TEXT;
const char STR2203[] = STR2203_TEXT;
const char STR2204[] = STR2204_TEXT;
const char STR2205[] = STR2205_TEXT;
const char STR2206[] = STR2206_TEXT;
const char STR2208[] = STR2208_TEXT;
const char STR2210[] = STR2210_TEXT;
const char STR2211[] = STR2211_TEXT;
const char STR2212[] = STR2212_TEXT;
const char STR2213[] = STR2213_TEXT;
const char STR2214[] = STR2214_TEXT;
const char STR2215[] = STR2215_TEXT;
const char STR2217[] = STR2217_TEXT;
const char STR2220[] = STR2220_TEXT;
const char STR2221[] = STR2221_TEXT;
const char STR2222[] = STR2222_TEXT;
const char STR2232[] = STR2232_TEXT;
const char STR2233[] = STR2233_TEXT;
const char STR2234[] = STR2234_TEXT;
const char STR2235[] = STR2235_TEXT;
const char STR2236[] = STR2236_TEXT;
const char STR2237[] = STR2237_TEXT;
const char STR2238[] = STR2238_TEXT;
const char STR2239[] = STR2239_TEXT;
const char STR2240[] = STR2240_TEXT;
const char STR2241[] = STR2241_TEXT;
const char STR2243[] = STR2243_TEXT;
const char STR2245[] = STR2245_TEXT;
const char STR2250[] = STR2250_TEXT;
const char STR2253[] = STR2253_TEXT;
const char STR2260[] = STR2260_TEXT;
const char STR2261[] = STR2261_TEXT;
const char STR2262[] = STR2262_TEXT;
const char STR2263[] = STR2263_TEXT;
const char STR2264[] = STR2264_TEXT;
const char STR2270[] = STR2270_TEXT;
const char STR2271[] = STR2271_TEXT;
const char STR2272[] = STR2272_TEXT;
const char STR2273[] = STR2273_TEXT;
const char STR2274[] = STR2274_TEXT;
const char STR2276[] = STR2276_TEXT;
const char STR2278[] = STR2278_TEXT;
#define STR2282 STR834
#define STR2283 STR835
#define STR2284 STR836
const char STR2285[] = STR2285_TEXT;
const char STR2290[] = STR2290_TEXT;
const char STR2291[] = STR2291_TEXT;
const char STR2292[] = STR2292_TEXT;
const char STR2300[] = STR2300_TEXT;
const char STR2301[] = STR2301_TEXT;
const char STR2305[] = STR2305_TEXT;
const char STR2310[] = STR2310_TEXT;
const char STR2315[] = STR2315_TEXT;
const char STR2316[] = STR2316_TEXT;
const char STR2317[] = STR2317_TEXT;
const char STR2320[] = STR2320_TEXT;
const char STR2321[] = STR2321_TEXT;
#define STR2322 STR882
#define STR2323 STR883
const char STR2324[] = STR2324_TEXT;
const char STR2325[] = STR2325_TEXT;
const char STR2326[] = STR2326_TEXT;
const char STR2327[] = STR2327_TEXT;
#define STR2328 STR886_2
const char STR2329[] = STR2329_TEXT;
const char STR2330[] = STR2330_TEXT;
const char STR2331[] = STR2331_TEXT;
const char STR2334[] = STR2334_TEXT;
const char STR2335[] = STR2335_TEXT;
const char STR2340[] = STR2340_TEXT;
const char STR2370[] = STR2370_TEXT;
const char STR2371[] = STR2371_TEXT;
const char STR2372[] = STR2372_TEXT;
const char STR2373[] = STR2373_TEXT;
const char STR2375[] = STR2375_TEXT;
const char STR2376[] = STR2376_TEXT;
const char STR2377[] = STR2377_TEXT;
const char STR2381[] = STR2381_TEXT;
const char STR2382[] = STR2382_TEXT;
const char STR2440[] = STR2440_TEXT;
const char STR2441[] = STR2441_TEXT;
const char STR2441_2[] = STR2441_2_TEXT;
const char STR2442[] = STR2442_TEXT;
const char STR2442_2[] = STR2442_2_TEXT;
const char STR2442_3[] = STR2442_3_TEXT;
const char STR2443[] = STR2443_TEXT;
const char STR2443_2[] = STR2443_2_TEXT;
const char STR2443_3[] = STR2443_3_TEXT;
const char STR2444[] = STR2444_TEXT;
const char STR2444_2[] = STR2444_2_TEXT;
const char STR2444_3[] = STR2444_3_TEXT;
const char STR2445[] = STR2445_TEXT;
const char STR2445_2[] = STR2445_2_TEXT;
const char STR2446[] = STR2446_TEXT;
const char STR2450[] = STR2450_TEXT;
#define STR2450_2 STR2241
const char STR2451[] = STR2451_TEXT;
#define STR2452 STR2245
const char STR2452_2[] = STR2452_2_TEXT;
const char STR2452_3[] = STR2452_3_TEXT;
const char STR2453[] = STR2453_TEXT;
const char STR2454[] = STR2454_TEXT;
const char STR2455[] = STR2455_TEXT;
const char STR2456[] = STR2456_TEXT;
const char STR2457[] = STR2457_TEXT;
const char STR2458[] = STR2458_TEXT;
const char STR2459[] = STR2459_TEXT;
const char STR2460[] = STR2460_TEXT;
const char STR2461[] = STR2461_TEXT;
const char STR2462[] = STR2462_TEXT;
const char STR2463[] = STR2463_TEXT;
const char STR2464[] = STR2464_TEXT;
const char STR2465[] = STR2465_TEXT;
const char STR2466[] = STR2466_TEXT;
const char STR2467[] = STR2467_TEXT;
const char STR2470[] = STR2470_TEXT;
const char STR2471[] = STR2471_TEXT;
const char STR2472[] = STR2472_TEXT;
const char STR2473[] = STR2473_TEXT;
const char STR2474[] = STR2474_TEXT;
const char STR2476[] = STR2476_TEXT;
const char STR2477[] = STR2477_TEXT;
const char STR2478[] = STR2478_TEXT;
#define STR2479 STR2478
const char STR2480[] = STR2480_TEXT;
const char STR2490[] = STR2490_TEXT;
const char STR2491[] = STR2491_TEXT;
const char STR2492[] = STR2492_TEXT;
const char STR2494[] = STR2494_TEXT;
const char STR2495[] = STR2495_TEXT;
const char STR2496[] = STR2496_TEXT;
const char STR2500[] = STR2500_TEXT;
const char STR2501[] = STR2501_TEXT;
const char STR2502[] = STR2502_TEXT;
const char STR2503[] = STR2503_TEXT;
const char STR2504[] = STR2504_TEXT;
const char STR2505[] = STR2505_TEXT;
const char STR2509[] = STR2509_TEXT;
const char STR2510[] = STR2510_TEXT;
const char STR2511[] = STR2511_TEXT;
const char STR2512[] = STR2512_TEXT;
const char STR2521[] = STR2521_TEXT;
const char STR2522[] = STR2522_TEXT;
const char STR2527[] = STR2527_TEXT;
const char STR2528[] = STR2528_TEXT;
const char STR2531[] = STR2531_TEXT;
const char STR2540[] = STR2540_TEXT;
const char STR2541[] = STR2541_TEXT;
const char STR2542[] = STR2542_TEXT;
const char STR2543[] = STR2543_TEXT;
const char STR2544[] = STR2544_TEXT;
const char STR2545[] = STR2545_TEXT;
const char STR2546[] = STR2546_TEXT;
const char STR2547[] = STR2547_TEXT;
const char STR2550[] = STR2550_TEXT;
const char STR2551[] = STR2551_TEXT;
const char STR2560[] = STR2560_TEXT;
const char STR2630[] = STR2630_TEXT;
const char STR2655[] = STR2655_TEXT;
const char STR2656[] = STR2656_TEXT;
const char STR2657[] = STR2657_TEXT;
const char STR2662[] = STR2662_TEXT;
const char STR2663[] = STR2663_TEXT;
#define STR2670 STR2478
const char STR2672[] = STR2672_TEXT;
const char STR2675[] = STR2675_TEXT;
const char STR2681[] = STR2681_TEXT;
const char STR2682[] = STR2682_TEXT;

//Sitherm Pro
const char STR2700[] = STR2700_TEXT;
const char STR2700_2[] = STR2700_2_TEXT;
const char STR2701[] = STR2701_TEXT;
const char STR2702[] = STR2702_TEXT;
const char STR2702_2[] = STR2702_2_TEXT;
const char STR2703[] = STR2703_TEXT;
const char STR2703_2[] = STR2703_2_TEXT;
const char STR2704[] = STR2704_TEXT;
const char STR2705[] = STR2705_TEXT;
const char STR2705_2[] = STR2705_2_TEXT;
const char STR2706[] = STR2706_TEXT;
const char STR2710[] = STR2710_TEXT;
#define STR2710_2 STR2705
const char STR2711[] = STR2711_TEXT;
const char STR2714[] = STR2714_TEXT;
const char STR2717[] = STR2717_TEXT;
const char STR2718[] = STR2718_TEXT;
const char STR2720[] = STR2720_TEXT;
const char STR2721[] = STR2721_TEXT;
#define STR2726 STR2720
const char STR2727[] = STR2727_TEXT;
const char STR2730[] = STR2730_TEXT;
#define STR2731 STR2702_2
#define STR2732 STR2703_2
const char STR2741[] = STR2741_TEXT;
const char STR2742[] = STR2742_TEXT;
const char STR2743[] = STR2743_TEXT;
const char STR2744[] = STR2744_TEXT;
const char STR2745[] = STR2745_TEXT;
const char STR2746[] = STR2746_TEXT;
const char STR2747[] = STR2747_TEXT;
const char STR2748[] = STR2748_TEXT;
#define STR2749 STR2703
const char STR2750[] = STR2750_TEXT;
const char STR2751[] = STR2751_TEXT;
const char STR2752[] = STR2752_TEXT;
const char STR2753[] = STR2753_TEXT;

// Wärmepumpe
const char STR2776[] = STR2776_TEXT;
const char STR2777[] = STR2777_TEXT;
const char STR2778[] = STR2778_TEXT;
const char STR2779[] = STR2779_TEXT;
const char STR2785[] = STR2785_TEXT;
const char STR2786[] = STR2786_TEXT;
const char STR2787[] = STR2787_TEXT;
const char STR2789[] = STR2789_TEXT;
const char STR2790[] = STR2790_TEXT;
#define STR2792 STR882
#define STR2793 STR883
#define STR2794 STR2324
#define STR2795 STR2325
#define STR2796 STR2326
#define STR2799 STR2329
const char STR2800[] = STR2800_TEXT;
const char STR2801[] = STR2801_TEXT;
const char STR2802[] = STR2802_TEXT;
const char STR2803[] = STR2803_TEXT;
const char STR2804[] = STR2804_TEXT;
const char STR2805[] = STR2805_TEXT;
const char STR2806[] = STR2806_TEXT;
const char STR2807[] = STR2807_TEXT;
const char STR2809[] = STR2809_TEXT;
const char STR2810[] = STR2810_TEXT;
const char STR2811[] = STR2811_TEXT;
const char STR2812[] = STR2812_TEXT;
const char STR2813[] = STR2813_TEXT;
const char STR2814[] = STR2814_TEXT;
const char STR2815[] = STR2815_TEXT;
const char STR2816[] = STR2816_TEXT;
const char STR2817[] = STR2817_TEXT;
const char STR2818[] = STR2818_TEXT;
const char STR2819[] = STR2819_TEXT;
const char STR2820[] = STR2820_TEXT;
const char STR2821[] = STR2821_TEXT;
const char STR2822[] = STR2822_TEXT;
const char STR2823[] = STR2823_TEXT;
const char STR2824[] = STR2824_TEXT;
const char STR2825[] = STR2825_TEXT;
const char STR2826[] = STR2826_TEXT;
const char STR2827[] = STR2827_TEXT;
const char STR2829[] = STR2829_TEXT;
const char STR2830[] = STR2830_TEXT;
const char STR2835[] = STR2835_TEXT;
const char STR2836[] = STR2836_TEXT;
const char STR2837[] = STR2837_TEXT;
const char STR2838[] = STR2838_TEXT;
const char STR2839[] = STR2839_TEXT;
const char STR2840[] = STR2840_TEXT;
const char STR2841[] = STR2841_TEXT;
const char STR2842[] = STR2842_TEXT;
const char STR2843[] = STR2843_TEXT;
const char STR2844[] = STR2844_TEXT;
const char STR2845[] = STR2845_TEXT;
const char STR2846[] = STR2846_TEXT;
const char STR2847[] = STR2847_TEXT;
const char STR2848[] = STR2848_TEXT;
const char STR2849[] = STR2849_TEXT;
const char STR2850[] = STR2850_TEXT;
const char STR2851[] = STR2851_TEXT;
const char STR2852[] = STR2852_TEXT;
const char STR2853[] = STR2853_TEXT;
const char STR2854[] = STR2854_TEXT;
const char STR2860[] = STR2860_TEXT;
const char STR2861[] = STR2861_TEXT;
const char STR2862[] = STR2862_TEXT;
const char STR2863[] = STR2863_TEXT;
const char STR2864[] = STR2864_TEXT;
const char STR2865[] = STR2865_TEXT;
const char STR2867[] = STR2867_TEXT;
#define STR2868 STR2330
const char STR2870[] = STR2870_TEXT;
const char STR2871[] = STR2871_TEXT;
const char STR2873[] = STR2873_TEXT;
const char STR2874[] = STR2874_TEXT;
const char STR2875[] = STR2875_TEXT;
const char STR2878[] = STR2878_TEXT;
const char STR2879[] = STR2879_TEXT;
const char STR2880[] = STR2880_TEXT;
const char STR2881[] = STR2881_TEXT;
const char STR2882[] = STR2882_TEXT;
const char STR2883[] = STR2883_TEXT;
const char STR2884[] = STR2884_TEXT;
const char STR2886[] = STR2886_TEXT;
const char STR2889[] = STR2889_TEXT;
const char STR2893[] = STR2893_TEXT;
const char STR2894[] = STR2894_TEXT;
const char STR2895[] = STR2895_TEXT;
const char STR2896[] = STR2896_TEXT;
const char STR2898[] = STR2898_TEXT;
const char STR2899[] = STR2899_TEXT;
const char STR2900[] = STR2900_TEXT;
const char STR2903[] = STR2903_TEXT;
const char STR2904[] = STR2904_TEXT;
const char STR2908[] = STR2908_TEXT;
#define STR2909 STR2203
const char STR2910[] = STR2910_TEXT;
const char STR2911[] = STR2911_TEXT;
#define STR2912 STR2208
const char STR2916[] = STR2916_TEXT;
const char STR2920[] = STR2920_TEXT;
const char STR2922[] = STR2922_TEXT;
const char STR2923[] = STR2923_TEXT;
const char STR2941[] = STR2941_TEXT;
const char STR2951[] = STR2951_TEXT;
const char STR2952[] = STR2952_TEXT;
const char STR2953[] = STR2953_TEXT;
const char STR2954[] = STR2954_TEXT;
const char STR2963[] = STR2963_TEXT;
const char STR2964[] = STR2964_TEXT;
const char STR2965[] = STR2965_TEXT;
const char STR2966[] = STR2966_TEXT;
const char STR2970[] = STR2970_TEXT;
const char STR3000[] = STR3000_TEXT;
const char STR3002[] = STR3002_TEXT;
const char STR3004[] = STR3004_TEXT;
const char STR3006[] = STR3006_TEXT;
const char STR3007[] = STR3007_TEXT;
const char STR3008[] = STR3008_TEXT;
const char STR3009[] = STR3009_TEXT;
const char STR3010[] = STR3010_TEXT;
const char STR3011[] = STR3011_TEXT;
const char STR3012[] = STR3012_TEXT;
const char STR3014[] = STR3014_TEXT;
const char STR3015[] = STR3015_TEXT;
const char STR3016[] = STR3016_TEXT;
const char STR3017[] = STR3017_TEXT;
const char STR3019[] = STR3019_TEXT;
const char STR3025[] = STR3025_TEXT;
const char STR3026[] = STR3026_TEXT;
const char STR3027[] = STR3027_TEXT;
const char STR3028[] = STR3028_TEXT;
const char STR3029[] = STR3029_TEXT;
const char STR3030[] = STR3030_TEXT;
const char STR3031[] = STR3031_TEXT;
const char STR3032[] = STR3032_TEXT;
const char STR3033[] = STR3033_TEXT;

// Energiezähler (Fujitsu Waterstage)
const char STR3090[] = STR3090_TEXT;
const char STR3092[] = STR3092_TEXT;
const char STR3093[] = STR3093_TEXT;
const char STR3094[] = STR3094_TEXT;
const char STR3095[] = STR3095_TEXT;
const char STR3097[] = STR3097_TEXT;
const char STR3098[] = STR3098_TEXT;
const char STR3100[] = STR3100_TEXT;
const char STR3102[] = STR3102_TEXT;
const char STR3103[] = STR3103_TEXT;
const char STR3104[] = STR3104_TEXT;
const char STR3106[] = STR3106_TEXT;
const char STR3108[] = STR3108_TEXT;
const char STR3109[] = STR3109_TEXT;
const char STR3110[] = STR3110_TEXT;
const char STR3112[] = STR3112_TEXT;
const char STR3113[] = STR3113_TEXT;
const char STR3116[] = STR3116_TEXT;
const char STR3119[] = STR3119_TEXT;
const char STR3121[] = STR3121_TEXT;
const char STR3122[] = STR3122_TEXT;
const char STR3123[] = STR3123_TEXT;
const char STR3124[] = STR3124_TEXT;
const char STR3125[] = STR3125_TEXT;
const char STR3126[] = STR3126_TEXT;
const char STR3128[] = STR3128_TEXT;
const char STR3129[] = STR3129_TEXT;
const char STR3130[] = STR3130_TEXT;
const char STR3131[] = STR3131_TEXT;
const char STR3132[] = STR3132_TEXT;
const char STR3133[] = STR3133_TEXT;
const char STR3135[] = STR3135_TEXT;
const char STR3136[] = STR3136_TEXT;
const char STR3137[] = STR3137_TEXT;
const char STR3138[] = STR3138_TEXT;
const char STR3139[] = STR3139_TEXT;
const char STR3140[] = STR3140_TEXT;
const char STR3142[] = STR3142_TEXT;
const char STR3143[] = STR3143_TEXT;
const char STR3144[] = STR3144_TEXT;
const char STR3145[] = STR3145_TEXT;
const char STR3146[] = STR3146_TEXT;
const char STR3147[] = STR3147_TEXT;
const char STR3149[] = STR3149_TEXT;
const char STR3150[] = STR3150_TEXT;
const char STR3151[] = STR3151_TEXT;
const char STR3152[] = STR3152_TEXT;
const char STR3153[] = STR3153_TEXT;
const char STR3154[] = STR3154_TEXT;
const char STR3156[] = STR3156_TEXT;
const char STR3157[] = STR3157_TEXT;
const char STR3158[] = STR3158_TEXT;
const char STR3159[] = STR3159_TEXT;
const char STR3160[] = STR3160_TEXT;
const char STR3161[] = STR3161_TEXT;
const char STR3163[] = STR3163_TEXT;
const char STR3164[] = STR3164_TEXT;
const char STR3165[] = STR3165_TEXT;
const char STR3166[] = STR3166_TEXT;
const char STR3167[] = STR3167_TEXT;
const char STR3168[] = STR3168_TEXT;
const char STR3170[] = STR3170_TEXT;
const char STR3171[] = STR3171_TEXT;
const char STR3172[] = STR3172_TEXT;
const char STR3173[] = STR3173_TEXT;
const char STR3174[] = STR3174_TEXT;
const char STR3175[] = STR3175_TEXT;
const char STR3177[] = STR3177_TEXT;
const char STR3178[] = STR3178_TEXT;
const char STR3179[] = STR3179_TEXT;
const char STR3180[] = STR3180_TEXT;
const char STR3181[] = STR3181_TEXT;
const char STR3182[] = STR3182_TEXT;
const char STR3184[] = STR3184_TEXT;
const char STR3185[] = STR3185_TEXT;
const char STR3186[] = STR3186_TEXT;
const char STR3187[] = STR3187_TEXT;
const char STR3188[] = STR3188_TEXT;
const char STR3189[] = STR3189_TEXT;
const char STR3190[] = STR3190_TEXT;
const char STR3192[] = STR3192_TEXT;
const char STR3193[] = STR3193_TEXT;
const char STR3195[] = STR3195_TEXT;
const char STR3196[] = STR3196_TEXT;
const char STR3257[] = STR3257_TEXT;
#define STR3260 STR3880
#define STR3261 STR3881
const char STR3264[] = STR3264_TEXT;
const char STR3265[] = STR3265_TEXT;
const char STR3266[] = STR3266_TEXT;
const char STR3267[] = STR3267_TEXT;

// 3500 Kaskade
const char STR3510[] = STR3510_TEXT;
const char STR3511[] = STR3511_TEXT;
const char STR3512[] = STR3512_TEXT;
const char STR3514[] = STR3514_TEXT;
const char STR3516[] = STR3516_TEXT;
const char STR3517[] = STR3517_TEXT;
const char STR3518[] = STR3518_TEXT;
const char STR3522[] = STR3522_TEXT;
const char STR3523[] = STR3523_TEXT;
const char STR3525[] = STR3525_TEXT;
const char STR3535[] = STR3535_TEXT;
const char STR3538[] = STR3538_TEXT;
const char STR3542[] = STR3542_TEXT;
const char STR3543[] = STR3543_TEXT;
const char STR3530[] = STR3530_TEXT;
const char STR3531[] = STR3531_TEXT;
const char STR3532[] = STR3532_TEXT;
const char STR3533[] = STR3533_TEXT;
const char STR3534[] = STR3534_TEXT;
const char STR3540[] = STR3540_TEXT;
const char STR3541[] = STR3541_TEXT;
const char STR3544[] = STR3544_TEXT;
const char STR3550[] = STR3550_TEXT;
#define STR3560 STR2270
#define STR3563 STR2273
#define STR3561 STR2271
#define STR3562 STR2272
#define STR3570 STR834
#define STR3571 STR835
#define STR3572 STR836
const char STR3590[] = STR3590_TEXT;

// 3690 Zusatzerzeuger
const char STR3690[] = STR3690_TEXT;
const char STR3691[] = STR3691_TEXT;
const char STR3692[] = STR3692_TEXT;
#define STR3694 STR2908
#define STR3700 STR2203
#define STR3701 STR2204
const char STR3705[] = STR3705_TEXT;
#define STR3710 STR2210
const char STR3718[] = STR3718_TEXT;
const char STR3719[] = STR3719_TEXT;
const char STR3720[] = STR3720_TEXT;
const char STR3722[] = STR3722_TEXT;
const char STR3723[] = STR3723_TEXT;
const char STR3725[] = STR3725_TEXT;
const char STR3750[] = STR3750_TEXT;
const char STR3755[] = STR3755_TEXT;

// 3800 Solar
const char STR3810[] = STR3810_TEXT;
const char STR3811[] = STR3811_TEXT;
const char STR3812[] = STR3812_TEXT;
const char STR3813[] = STR3813_TEXT;
const char STR3814[] = STR3814_TEXT;
const char STR3815[] = STR3815_TEXT;
const char STR3816[] = STR3816_TEXT;
const char STR3817[] = STR3817_TEXT;
const char STR3818[] = STR3818_TEXT;
const char STR3822[] = STR3822_TEXT;
const char STR3825[] = STR3825_TEXT;
const char STR3826[] = STR3826_TEXT;
const char STR3827[] = STR3827_TEXT;
const char STR3828[] = STR3828_TEXT;
const char STR3830[] = STR3830_TEXT;
const char STR3831[] = STR3831_TEXT;
const char STR3832[] = STR3832_TEXT;
const char STR3833[] = STR3833_TEXT;
const char STR3834[] = STR3834_TEXT;
const char STR3835[] = STR3835_TEXT;
const char STR3840[] = STR3840_TEXT;
const char STR3850[] = STR3850_TEXT;
const char STR3851[] = STR3851_TEXT;
const char STR3860[] = STR3860_TEXT;
const char STR3861[] = STR3861_TEXT;
const char STR3862[] = STR3862_TEXT;
const char STR3865[] = STR3865_TEXT;
const char STR3867[] = STR3867_TEXT;
const char STR3868[] = STR3868_TEXT;
const char STR3869[] = STR3869_TEXT;
#define STR3870 STR882
#define STR3871 STR883
#define STR3872 STR835
#define STR3873 STR836
#define STR3875 STR2327
#define STR3876 STR2328
const char STR3880[] = STR3880_TEXT;
const char STR3881[] = STR3881_TEXT;
const char STR3884[] = STR3884_TEXT;
const char STR3886[] = STR3886_TEXT;
const char STR3887[] = STR3887_TEXT;
const char STR3888[] = STR3888_TEXT;
const char STR3889[] = STR3889_TEXT;
const char STR3891[] = STR3891_TEXT;
const char STR3896[] = STR3896_TEXT;
const char STR3897[] = STR3897_TEXT;

// 4100 Feststoffkessel
const char STR4101[] = STR4101_TEXT;
const char STR4102[] = STR4102_TEXT;
const char STR4103[] = STR4103_TEXT;
#define STR4110 STR2210
#define STR4112 STR2212
#define STR4114 STR2315
#define STR4130 STR3810
#define STR4131 STR3811
const char STR4133[] = STR4133_TEXT;
const char STR4134[] = STR4134_TEXT;
const char STR4135[] = STR4135_TEXT;
const char STR4136[] = STR4136_TEXT;
const char STR4137[] = STR4137_TEXT;
const char STR4138[] = STR4138_TEXT;
#define STR4140 STR2250
const char STR4141[] = STR4141_TEXT;
#define STR4153 STR2270
const char STR4158[] = STR4158_TEXT;
#define STR4163 STR834
#define STR4164 STR835
#define STR4165 STR836
#define STR4170 STR2300
const char STR4180[] = STR4180_TEXT;
const char STR4182[] = STR4182_TEXT;
const char STR4184[] = STR4184_TEXT;
const char STR4190[] = STR4190_TEXT;
const char STR4192[] = STR4192_TEXT;
#define STR4201 STR882
#define STR4202 STR883
#define STR4203 STR2324
#define STR4204 STR2325

// 4700 Pufferspeicher
const char STR4705[] = STR4705_TEXT;
const char STR4708[] = STR4708_TEXT;
const char STR4709[] = STR4709_TEXT;
const char STR4710[] = STR4710_TEXT;
const char STR4711[] = STR4711_TEXT;
const char STR4712[] = STR4712_TEXT;
const char STR4720[] = STR4720_TEXT;
const char STR4721[] = STR4721_TEXT;
const char STR4722[] = STR4722_TEXT;
const char STR4723[] = STR4723_TEXT;
const char STR4724[] = STR4724_TEXT;
const char STR4726[] = STR4726_TEXT;
const char STR4728[] = STR4728_TEXT;
const char STR4735[] = STR4735_TEXT;
const char STR4739[] = STR4739_TEXT;
const char STR4740[] = STR4740_TEXT;
const char STR4743[] = STR4743_TEXT;
const char STR4744[] = STR4744_TEXT;
const char STR4746[] = STR4746_TEXT;
const char STR4749[] = STR4749_TEXT;
const char STR4750[] = STR4750_TEXT;
const char STR4751[] = STR4751_TEXT;
const char STR4755[] = STR4755_TEXT;
const char STR4756[] = STR4756_TEXT;
const char STR4757[] = STR4757_TEXT;
const char STR4760[] = STR4760_TEXT;
const char STR4761[] = STR4761_TEXT;
#define STR4783 STR2080
const char STR4790[] = STR4790_TEXT;
const char STR4791[] = STR4791_TEXT;
const char STR4795[] = STR4795_TEXT;
const char STR4796[] = STR4796_TEXT;
const char STR4800[] = STR4800_TEXT;
#define STR4810 STR2208
const char STR4811[] = STR4811_TEXT;
const char STR4813[] = STR4813_TEXT;
const char STR4830[] = STR4830_TEXT;
const char STR4831[] = STR4831_TEXT;
// 5000 Trinkwasserspeicher
const char STR5007[] = STR5007_TEXT;
const char STR5008[] = STR5008_TEXT;
const char STR5010[] = STR5010_TEXT;
const char STR5011[] = STR5011_TEXT;
const char STR5012[] = STR5012_TEXT;
const char STR5013[] = STR5013_TEXT;
const char STR5016[] = STR5016_TEXT;
const char STR5019[] = STR5019_TEXT;
const char STR5020[] = STR5020_TEXT;
const char STR5021[] = STR5021_TEXT;
const char STR5022[] = STR5022_TEXT;
const char STR5022_2[] = STR5022_2_TEXT;
const char STR5023[] = STR5023_TEXT;
const char STR5024[] = STR5024_TEXT;
const char STR5025[] = STR5025_TEXT;
const char STR5026[] = STR5026_TEXT;
const char STR5027[] = STR5027_TEXT;
const char STR5028[] = STR5028_TEXT;
const char STR5029[] = STR5029_TEXT;
const char STR5030[] = STR5030_TEXT;
const char STR5032[] = STR5032_TEXT;
const char STR5040[] = STR5040_TEXT;
const char STR5041[] = STR5041_TEXT;
const char STR5042[] = STR5042_TEXT;
const char STR5050[] = STR5050_TEXT;
const char STR5051[] = STR5051_TEXT;
const char STR5055[] = STR5055_TEXT;
const char STR5056[] = STR5056_TEXT;
const char STR5057[] = STR5057_TEXT;
const char STR5060[] = STR5060_TEXT;
const char STR5061[] = STR5061_TEXT;
const char STR5062[] = STR5062_TEXT;
const char STR5070[] = STR5070_TEXT;
const char STR5071[] = STR5071_TEXT;
const char STR5085[] = STR5085_TEXT;
const char STR5090[] = STR5090_TEXT;
const char STR5092[] = STR5092_TEXT;
const char STR5093[] = STR5093_TEXT;
const char STR5100[] = STR5100_TEXT;
const char STR5101[] = STR5101_TEXT;
const char STR5102[] = STR5102_TEXT;
#define STR5103 STR2324
#define STR5104 STR2325
#define STR5105 STR2326
#define STR5106 STR2327
#define STR5107 STR886_2
const char STR5108[] = STR5108_TEXT;
const char STR5109[] = STR5109_TEXT;
#define STR5120 STR830
const char STR5122[] = STR5122_TEXT;
const char STR5123[] = STR5123_TEXT;
#define STR5124 STR834
#define STR5125 STR835
#define STR5126 STR836
const char STR5130[] = STR5130_TEXT;
const char STR5131[] = STR5131_TEXT;
const char STR5139[] = STR5139_TEXT;
const char STR5140[] = STR5140_TEXT;
const char STR5141[] = STR5141_TEXT;
const char STR5142[] = STR5142_TEXT;
const char STR5143[] = STR5143_TEXT;
const char STR5144[] = STR5144_TEXT;
const char STR5145[] = STR5145_TEXT;
const char STR5146[] = STR5146_TEXT;
const char STR5148[] = STR5148_TEXT;
const char STR5151[] = STR5151_TEXT;

// 5400 Trinkwasser Durchlauferhitzer
#define STR5400 STR710
const char STR5406[] = STR5406_TEXT;
const char STR5420[] = STR5420_TEXT;
const char STR5429[] = STR5429_TEXT;
const char STR5430[] = STR5430_TEXT;
const char STR5431[] = STR5431_TEXT;
const char STR5432[] = STR5432_TEXT;
const char STR5433[] = STR5433_TEXT;
const char STR5434[] = STR5434_TEXT;
const char STR5435[] = STR5435_TEXT;
#define STR5441 STR2501
#define STR5444 STR2505
const char STR5445[] = STR5445_TEXT;
const char STR5450[] = STR5450_TEXT;
const char STR5451[] = STR5451_TEXT;
const char STR5452[] = STR5452_TEXT;
const char STR5453[] = STR5453_TEXT;
const char STR5454[] = STR5454_TEXT;
const char STR5455[] = STR5455_TEXT;
const char STR5456[] = STR5456_TEXT;
const char STR5460[] = STR5460_TEXT;
const char STR5461[] = STR5461_TEXT;
const char STR5462[] = STR5462_TEXT;
const char STR5464[] = STR5464_TEXT;
const char STR5468[] = STR5468_TEXT;
const char STR5470[] = STR5470_TEXT;
const char STR5471[] = STR5471_TEXT;
const char STR5472[] = STR5472_TEXT;
#define STR5473 STR5472
const char STR5475[] = STR5475_TEXT;
const char STR5476[] = STR5476_TEXT;
const char STR5480[] = STR5480_TEXT;
const char STR5481[] = STR5481_TEXT;
const char STR5482[] = STR5482_TEXT;
const char STR5483[] = STR5483_TEXT;
const char STR5486[] = STR5486_TEXT;
const char STR5487[] = STR5487_TEXT;
const char STR5488[] = STR5488_TEXT;
const char STR5489[] = STR5489_TEXT;
const char STR5490[] = STR5490_TEXT;
const char STR5491[] = STR5491_TEXT;
#define STR5530 STR882
#define STR5531 STR883
const char STR5535[] = STR5535_TEXT;
const char STR5536[] = STR5536_TEXT;
const char STR5537[] = STR5537_TEXT;
#define STR5544 STR834
#define STR5545 STR835
#define STR5546 STR836
#define STR5547 STR2285
const char STR5550[] = STR5550_TEXT;

// Allgemeine Funktionen
const char STR5570[] = STR5570_TEXT;
const char STR5571[] = STR5571_TEXT;
const char STR5572[] = STR5572_TEXT;
const char STR5573[] = STR5573_TEXT;
const char STR5574[] = STR5574_TEXT;
const char STR5575[] = STR5575_TEXT;
const char STR5577[] = STR5577_TEXT;

const char STR5580[] = STR5580_TEXT;
const char STR5581[] = STR5581_TEXT;
const char STR5582[] = STR5582_TEXT;
const char STR5583[] = STR5583_TEXT;
const char STR5584[] = STR5584_TEXT;
const char STR5585[] = STR5585_TEXT;
const char STR5587[] = STR5587_TEXT;

// Konfiguration
const char STR5700[] = STR5700_TEXT;
const char STR5701[] = STR5701_TEXT;
const char STR5710[] = ENUM_CAT_11_TEXT;
const char STR5711[] = ENUM_CAT_12_TEXT;
const char STR5712[] = STR5712_TEXT;
const char STR5715[] = ENUM_CAT_14_TEXT;
const char STR5721[] = STR5721_TEXT;
const char STR5730[] = STR5730_TEXT;
const char STR5730_2[] = STR5730_2_TEXT;
const char STR5731[] = STR5731_TEXT;
const char STR5732[] = STR5732_TEXT;
const char STR5733[] = STR5733_TEXT;
const char STR5734[] = STR5734_TEXT;
const char STR5736[] = STR5736_TEXT;
const char STR5737[] = STR5737_TEXT;
const char STR5738[] = STR5738_TEXT;
// const char STR5737[] = "Wirksinn TWW Umlenkventil";
const char STR5740[] = STR5740_TEXT;
#define STR5760 STR2150
const char STR5761[] = STR5761_TEXT;
#define STR5770 STR3750
const char STR5772[] = STR5772_TEXT;
const char STR5774[] = STR5774_TEXT;
const char STR5775[] = STR5775_TEXT;
const char STR5800[] = STR5800_TEXT;
const char STR5806[] = STR5806_TEXT;
const char STR5807[] = STR5807_TEXT;
const char STR5810[] = STR5810_TEXT;
const char STR5811[] = STR5811_TEXT;
const char STR5813[] = STR5813_TEXT;
const char STR5840[] = STR5840_TEXT;
const char STR5841[] = STR5841_TEXT;
const char STR5870[] = STR5870_TEXT;
const char STR5890[] = STR5890_TEXT;
const char STR5890_2[] = STR5890_2_TEXT;
const char STR5891[] = STR5891_TEXT;
const char STR5891_2[] = STR5891_2_TEXT;
const char STR5892[] = STR5892_TEXT;
const char STR5894[] = STR5894_TEXT;
const char STR5895[] = STR5895_TEXT;
const char STR5896[] = STR5896_TEXT;
const char STR5902[] = STR5902_TEXT;
const char STR5904[] = STR5904_TEXT;
const char STR5908[] = STR5908_TEXT;
const char STR5909[] = STR5909_TEXT;
const char STR5920[] = STR5920_TEXT;
const char STR5921[] = STR5921_TEXT;
const char STR5922[] = STR5922_TEXT;
const char STR5923[] = STR5923_TEXT;
const char STR5924[] = STR5924_TEXT;
const char STR5926[] = STR5926_TEXT;
const char STR5927[] = STR5927_TEXT;
const char STR5928[] = STR5928_TEXT;
const char STR5930[] = STR5930_TEXT;
const char STR5931[] = STR5931_TEXT;
const char STR5932[] = STR5932_TEXT;
const char STR5933[] = STR5933_TEXT;
const char STR5934[] = STR5934_TEXT;
const char STR5941[] = STR5941_TEXT;
const char STR5942[] = STR5942_TEXT;
const char STR5950[] = STR5950_TEXT;
const char STR5951[] = STR5951_TEXT;
const char STR5952[] = STR5952_TEXT;
const char STR5953[] = STR5953_TEXT;
const char STR5954[] = STR5954_TEXT;
const char STR5954_2[] = STR5954_2_TEXT;
const char STR5955[] = STR5955_TEXT;
const char STR5956[] = STR5956_TEXT;
const char STR5956_2[] = STR5956_2_TEXT;
const char STR5957_2[] = STR5957_2_TEXT;
#define STR5957_3 STR5950
const char STR5960_2[] = STR5960_2_TEXT;
const char STR5961_2[] = STR5961_2_TEXT;
const char STR5962_2[] = STR5962_2_TEXT;
const char STR5963_2[] = STR5963_2_TEXT;
const char STR5964_2[] = STR5964_2_TEXT;
const char STR5964_3[] = STR5964_3_TEXT;
const char STR5957[] = STR5957_TEXT;
const char STR5960[] = STR5960_TEXT;
const char STR5961[] = STR5961_TEXT;
const char STR5962[] = STR5962_TEXT;
const char STR5963[] = STR5963_TEXT;
const char STR5964[] = STR5964_TEXT;
const char STR5965[] = STR5965_TEXT;
const char STR5966[] = STR5966_TEXT;
const char STR5966_2[] = STR5966_2_TEXT;
const char STR5970[] = STR5970_TEXT;
const char STR5970_2[] = STR5970_2_TEXT;
const char STR5971[] = STR5971_TEXT;
const char STR5971_2[] = STR5971_2_TEXT;
const char STR5973[] = STR5973_TEXT;
const char STR5973_2[] = STR5973_2_TEXT;
const char STR5974[] = STR5974_TEXT;
const char STR5975[] = STR5975_TEXT;
const char STR5975_2[] = STR5975_2_TEXT;
const char STR5976[] = STR5976_TEXT;
const char STR5976_2[] = STR5976_2_TEXT;
const char STR5977[] = STR5977_TEXT;
const char STR5978[] = STR5978_TEXT;
const char STR5978_2[] = STR5978_2_TEXT;
const char STR5980[] = STR5980_TEXT;
const char STR5981[] = STR5981_TEXT;
const char STR5982[] = STR5982_TEXT;
const char STR5983[] = STR5983_TEXT;
const char STR5984[] = STR5984_TEXT;
const char STR5985[] = STR5985_TEXT;
const char STR5986[] = STR5986_TEXT;
const char STR5987[] = STR5987_TEXT;
const char STR5988[] = STR5988_TEXT;
const char STR5989[] = STR5989_TEXT;
const char STR5990[] = STR5990_TEXT;
const char STR5992[] = STR5992_TEXT;
const char STR6008[] = STR6008_TEXT;
const char STR6009[] = STR6009_TEXT;
const char STR6011[] = STR6011_TEXT;
const char STR6012[] = STR6012_TEXT;
const char STR6014[] = STR6014_TEXT;
const char STR6015[] = STR6015_TEXT;
const char STR6020[] = STR6020_TEXT;
const char STR6021[] = STR6021_TEXT;
const char STR6022[] = STR6022_TEXT;
const char STR6024[] = STR6024_TEXT;
const char STR6026[] = STR6026_TEXT;
const char STR6028[] = STR6028_TEXT;
const char STR6030[] = STR6030_TEXT;
const char STR6031[] = STR6031_TEXT;
const char STR6032[] = STR6032_TEXT;
const char STR6033[] = STR6033_TEXT;
const char STR6034[] = STR6034_TEXT;
const char STR6035[] = STR6035_TEXT;
const char STR6036[] = STR6036_TEXT;
const char STR6037[] = STR6037_TEXT;
const char STR6038[] = STR6038_TEXT;
const char STR6040[] = STR6040_TEXT;
const char STR6041[] = STR6041_TEXT;
const char STR6042[] = STR6042_TEXT;
const char STR6043[] = STR6043_TEXT;
const char STR6044[] = STR6044_TEXT;
const char STR6045[] = STR6045_TEXT;
#define STR6046 STR5960_2
#define STR6047 STR5961_2
#define STR6048 STR5962_2
const char STR6048_2[] = STR6048_2_TEXT;
#define STR6049 STR5963_2
const char STR6049_2[] = STR6049_2_TEXT;
#define STR6050 STR5964_2
const char STR6050_2[] = STR6050_2_TEXT;
const char STR6051[] = STR6051_TEXT;
const char STR6052[] = STR6052_TEXT;
#define STR6052_2 STR5966_TEXT
const char STR6054[] = STR6054_TEXT;
const char STR6055[] = STR6055_TEXT;
const char STR6057[] = STR6057_TEXT;
const char STR6058[] = STR6058_TEXT;
const char STR6059[] = STR6059_TEXT;
const char STR6060[] = STR6060_TEXT;
const char STR6062[] = STR6062_TEXT;
const char STR6063[] = STR6063_TEXT;
const char STR6065[] = STR6065_TEXT;
const char STR6066[] = STR6066_TEXT;
const char STR6067[] = STR6067_TEXT;
const char STR6068[] = STR6068_TEXT;
const char STR6070[] = STR6070_TEXT;
const char STR6071[] = STR6071_TEXT;
const char STR6072[] = STR6072_TEXT;
const char STR6075[] = STR6075_TEXT;
const char STR6078[] = STR6078_TEXT;
const char STR6079[] = STR6079_TEXT;
const char STR6085[] = STR6085_TEXT;
const char STR6086[] = STR6086_TEXT;
const char STR6089[] = STR6089_TEXT;
const char STR6089_2[] = STR6089_2_TEXT;
const char STR6090[] = STR6090_TEXT;
const char STR6090_2[] = STR6090_2_TEXT;
const char STR6091[] = STR6091_TEXT;
const char STR6092[] = STR6092_TEXT;
const char STR6093[] = STR6093_TEXT;
const char STR6097[] = STR6097_TEXT;
const char STR6098[] = STR6098_TEXT;
const char STR6099[] = STR6099_TEXT;
const char STR6100[] = STR6100_TEXT;
const char STR6101[] = STR6101_TEXT;
const char STR6102[] = STR6102_TEXT;
const char STR6107[] = STR6107_TEXT;
const char STR6110[] = STR6110_TEXT;
const char STR6112[] = STR6112_TEXT;
const char STR6116[] = STR6116_TEXT;
const char STR6117[] = STR6117_TEXT;
const char STR6118[] = STR6118_TEXT;
const char STR6120[] = STR6120_TEXT;
const char STR6127[] = STR6127_TEXT;
const char STR6128[] = STR6128_TEXT;
const char STR6129[] = STR6129_TEXT;
#define STR6130 STR2012
const char STR6131[] = STR6131_TEXT;
#define STR6134 STR2037
const char STR6135[] = STR6135_TEXT;
const char STR6136[] = STR6136_TEXT;
const char STR6137[] = STR6137_TEXT;
const char STR6138[] = STR6138_TEXT;
const char STR6140[] = STR6140_TEXT;
const char STR6141[] = STR6141_TEXT;
const char STR6142[] = STR6142_TEXT;
const char STR6143[] = STR6143_TEXT;
const char STR6144[] = STR6144_TEXT;
const char STR6145[] = STR6145_TEXT;
const char STR6146[] = STR6146_TEXT;
const char STR6146_2[] = STR6146_2_TEXT;
const char STR6148[] = STR6148_TEXT;
const char STR6150[] = STR6150_TEXT;
const char STR6151[] = STR6151_TEXT;
const char STR6152[] = STR6152_TEXT;
const char STR6153[] = STR6153_TEXT;
const char STR6180[] = STR6180_TEXT;
const char STR6181[] = STR6181_TEXT;
const char STR6182[] = STR6182_TEXT;
const char STR6183[] = STR6183_TEXT;
const char STR6200[] = STR6200_TEXT;
const char STR6201[] = STR6201_TEXT;
const char STR6204[] = STR6204_TEXT;
const char STR6205[] = STR6205_TEXT;
const char STR6212[] = STR6212_TEXT;
const char STR6213[] = STR6213_TEXT;
const char STR6215[] = STR6215_TEXT;
const char STR6217[] = STR6217_TEXT;
const char STR6220[] = STR6220_TEXT;
const char STR6221[] = STR6221_TEXT;
const char STR6222[] = STR6222_TEXT;
const char STR6223[] = STR6223_TEXT;
const char STR6224[] = STR6224_TEXT;
const char STR6225[] = STR6225_TEXT;
const char STR6226[] = STR6226_TEXT;
const char STR6227[] = STR6227_TEXT;
const char STR6228[] = STR6228_TEXT;
const char STR6229[] = STR6229_TEXT;
const char STR6230[] = STR6230_TEXT;
const char STR6230_2[] = STR6230_2_TEXT;
const char STR6231[] = STR6231_TEXT;
const char STR6232[] = STR6232_TEXT;
const char STR6233[] = STR6233_TEXT;
const char STR6234[] = STR6234_TEXT;
const char STR6235[] = STR6235_TEXT;
const char STR6236[] = STR6236_TEXT;
const char STR6240[] = STR6240_TEXT;
const char STR6240_2[] = STR6240_2_TEXT;
const char STR6241[] = STR6241_TEXT;
const char STR6242[] = STR6242_TEXT;
const char STR6243[] = STR6243_TEXT;
const char STR6244[] = STR6244_TEXT;
const char STR6245[] = STR6245_TEXT;
const char STR6246[] = STR6246_TEXT;
const char STR6247[] = STR6247_TEXT;
const char STR6248[] = STR6248_TEXT;
const char STR6249[] = STR6249_TEXT;
const char STR6250[] = STR6250_TEXT;
const char STR6250_2[] = STR6250_2_TEXT;
const char STR6251[] = STR6251_TEXT;
const char STR6252[] = STR6252_TEXT;
const char STR6253[] = STR6253_TEXT;
const char STR6254[] = STR6254_TEXT;
const char STR6255[] = STR6255_TEXT;
const char STR6256[] = STR6256_TEXT;
const char STR6257[] = STR6257_TEXT;
const char STR6258[] = STR6258_TEXT;
const char STR6259[] = STR6259_TEXT;
const char STR6260[] = STR6260_TEXT;
const char STR6270[] = STR6270_TEXT;
const char STR6270_2[] = STR6270_2_TEXT;
const char STR6271[] = STR6271_TEXT;
const char STR6272[] = STR6272_TEXT;
const char STR6273[] = STR6273_TEXT;
const char STR6280[] = STR6280_TEXT;
const char STR6290[] = STR6290_TEXT;
const char STR6300[] = STR6300_TEXT;
const char STR6300_2[] = STR6300_2_TEXT;
const char STR6310[] = STR6310_TEXT;
const char STR6330[] = STR6330_TEXT;
const char STR6344[] = STR6344_TEXT;
const char STR6345[] = STR6345_TEXT;
const char STR6346[] = STR6346_TEXT;
const char STR6347[] = STR6347_TEXT;
const char STR6348[] = STR6348_TEXT;
const char STR6351[] = STR6351_TEXT;
const char STR6352[] = STR6352_TEXT;
const char STR6355[] = STR6355_TEXT;
const char STR6356[] = STR6356_TEXT;
const char STR6357[] = STR6357_TEXT;
const char STR6359[] = STR6359_TEXT;
const char STR6375[] = STR6375_TEXT;
const char STR6420[] = STR6420_TEXT;
const char STR6421[] = STR6421_TEXT;

const char STR6486[] = STR6486_TEXT;
const char STR6487[] = STR6487_TEXT;
const char STR6488[] = STR6488_TEXT;
const char STR6489[] = STR6489_TEXT;
const char STR6490[] = STR6490_TEXT;
const char STR6491[] = STR6491_TEXT;
const char STR6492[] = STR6492_TEXT;
const char STR6493[] = STR6493_TEXT;
const char STR6494[] = STR6494_TEXT;
const char STR6495[] = STR6495_TEXT;
const char STR6496[] = STR6496_TEXT;
const char STR6497[] = STR6497_TEXT;
const char STR6498[] = STR6498_TEXT;


// LPB-System
const char STR6600[] = STR6600_TEXT;
const char STR6601[] = STR6601_TEXT;
const char STR6604[] = STR6604_TEXT;
const char STR6605[] = STR6605_TEXT;
const char STR6606[] = STR6606_TEXT;
const char STR6610[] = STR6610_TEXT;
const char STR6611[] = STR6611_TEXT;
const char STR6612[] = STR6612_TEXT;
const char STR6620[] = STR6620_TEXT;
const char STR6621[] = STR6621_TEXT;
#define STR6623 STR900
const char STR6624[] = STR6624_TEXT;
const char STR6625[] = STR6625_TEXT;
const char STR6627[] = STR6627_TEXT;
const char STR6630[] = STR6630_TEXT;
const char STR6631[] = STR6631_TEXT;
const char STR6632[] = STR6632_TEXT;
const char STR6640[] = STR6640_TEXT;
const char STR6650[] = STR6650_TEXT;
const char STR6651[] = STR6651_TEXT;
const char STR6652[] = STR6652_TEXT;
const char STR6653[] = STR6653_TEXT;
const char STR6654[] = STR6654_TEXT;
const char STR6699[] = STR6699_TEXT;

// Fehler
const char STR6700[] = STR6700_TEXT;
const char STR6705[] = STR6705_TEXT;
#define STR6704 STR6705
const char STR6706[] = STR6706_TEXT;
const char STR6707[] = STR6707_TEXT;
const char STR6708[] = STR6708_TEXT;
const char STR6710[] = STR6710_TEXT;
const char STR6711[] = STR6711_TEXT;
const char STR6740[] = STR6740_TEXT;
const char STR6741[] = STR6741_TEXT;
const char STR6742[] = STR6742_TEXT;
const char STR6743[] = STR6743_TEXT;
const char STR6745[] = STR6745_TEXT;
const char STR6746[] = STR6746_TEXT;
const char STR6747[] = STR6747_TEXT;

// THISION Fehlerparameter
const char STR6800_2[] = STR6800_2_TEXT;
const char STR6801_2[] = STR6801_2_TEXT;
const char STR6805_2[] = STR6805_2_TEXT;
const char STR6806_2[] = STR6806_2_TEXT;
const char STR6810_2[] = STR6810_2_TEXT;
const char STR6811_2[] = STR6811_2_TEXT;
const char STR6813_2[] = STR6813_2_TEXT;
const char STR6815_2[] = STR6815_2_TEXT;
const char STR6816_2[] = STR6816_2_TEXT;
const char STR6820_2[] = STR6820_2_TEXT;
const char STR6821[] = STR6821_TEXT;
const char STR6823_2[] = STR6823_2_TEXT;
const char STR6825[] = STR6825_TEXT;
const char STR6826[] = STR6826_TEXT;
const char STR6830[] = STR6830_TEXT;
const char STR6831[] = STR6831_TEXT;
const char STR6833_2[] = STR6833_2_TEXT;
const char STR6835[] = STR6835_TEXT;
const char STR6836[] = STR6836_TEXT;
const char STR6840_2[] = STR6840_2_TEXT;
const char STR6843_2[] = STR6843_2_TEXT;
const char STR6845[] = STR6845_TEXT;
const char STR6846[] = STR6846_TEXT;
const char STR6855[] = STR6855_TEXT;
const char STR6856[] = STR6856_TEXT;
const char STR6865[] = STR6865_TEXT;
const char STR6866[] = STR6866_TEXT;
const char STR6875[] = STR6875_TEXT;
const char STR6876[] = STR6876_TEXT;
const char STR6885[] = STR6885_TEXT;
const char STR6886[] = STR6886_TEXT;
const char STR6895[] = STR6895_TEXT;
const char STR6896[] = STR6896_TEXT;
const char STR6905[] = STR6905_TEXT;
const char STR6906[] = STR6906_TEXT;
const char STR6915[] = STR6915_TEXT;
const char STR6916[] = STR6916_TEXT;
const char STR6925[] = STR6925_TEXT;
const char STR6926[] = STR6926_TEXT;
const char STR6935[] = STR6935_TEXT;
const char STR6936[] = STR6936_TEXT;
const char STR6945[] = STR6945_TEXT;
const char STR6946[] = STR6946_TEXT;
const char STR6955[] = STR6955_TEXT;
const char STR6956[] = STR6956_TEXT;
const char STR6965[] = STR6965_TEXT;
const char STR6966[] = STR6966_TEXT;
const char STR6975[] = STR6975_TEXT;
const char STR6976[] = STR6976_TEXT;
const char STR6985[] = STR6985_TEXT;
const char STR6986[] = STR6986_TEXT;
const char STR6995[] = STR6995_TEXT;
const char STR6996[] = STR6996_TEXT;

#define STR6803_2 STR6801_2
#define STR6823 STR6820_2
#define STR6833 STR6830
#define STR6840 STR6808
#define STR6843 STR6840
#define STR6841 STR6809
#define STR6850 STR6810
#define STR6851 STR6811
#define STR6860 STR6812
#define STR6861 STR6813
#define STR6870 STR6814
#define STR6871 STR6815
#define STR6880 STR6816
#define STR6881 STR6817
#define STR6890 STR6818
#define STR6891 STR6819
#define STR6999 STR6820

// übrige Fehlerparameter
const char STR6800[] = STR6800_TEXT;
const char STR6801[] = STR6801_TEXT;
const char STR6802[] = STR6802_TEXT;
const char STR6803[] = STR6803_TEXT;
const char STR6804[] = STR6804_TEXT;
const char STR6805[] = STR6805_TEXT;
const char STR6806[] = STR6806_TEXT;
const char STR6807[] = STR6807_TEXT;
const char STR6808[] = STR6808_TEXT;
const char STR6809[] = STR6809_TEXT;
const char STR6810[] = STR6810_TEXT;
const char STR6811[] = STR6811_TEXT;
const char STR6812[] = STR6812_TEXT;
const char STR6813[] = STR6813_TEXT;
const char STR6814[] = STR6814_TEXT;
const char STR6815[] = STR6815_TEXT;
const char STR6816[] = STR6816_TEXT;
const char STR6817[] = STR6817_TEXT;
const char STR6818[] = STR6818_TEXT;
const char STR6819[] = STR6819_TEXT;
const char STR6900[] = STR6900_TEXT;
const char STR6901[] = STR6901_TEXT;
const char STR6910[] = STR6910_TEXT;
const char STR6911[] = STR6911_TEXT;
const char STR6920[] = STR6920_TEXT;
const char STR6921[] = STR6921_TEXT;
const char STR6930[] = STR6930_TEXT;
const char STR6931[] = STR6931_TEXT;
const char STR6940[] = STR6940_TEXT;
const char STR6941[] = STR6941_TEXT;
const char STR6950[] = STR6950_TEXT;
const char STR6951[] = STR6951_TEXT;
const char STR6960[] = STR6960_TEXT;
const char STR6961[] = STR6961_TEXT;
const char STR6970[] = STR6970_TEXT;
const char STR6971[] = STR6971_TEXT;
const char STR6980[] = STR6980_TEXT;
const char STR6981[] = STR6981_TEXT;
const char STR6990[] = STR6990_TEXT;
const char STR6991[] = STR6991_TEXT;
const char STR6820[] = STR6820_TEXT;

// Wartung / Sonderbetrieb
const char STR7001[] = STR7001_TEXT;
const char STR7007[] = STR7007_TEXT;
const char STR7010[] = STR7010_TEXT;
const char STR7011[] = STR7011_TEXT;
const char STR7012[] = STR7012_TEXT;
const char STR7040[] = STR7040_TEXT;
const char STR7041[] = STR7041_TEXT;
const char STR7042[] = STR7042_TEXT;
const char STR7043[] = STR7043_TEXT;
const char STR7044[] = STR7044_TEXT;
const char STR7045[] = STR7045_TEXT;
const char STR7046[] = STR7046_TEXT;
const char STR7050[] = STR7050_TEXT;
const char STR7051[] = STR7051_TEXT;
const char STR7053[] = STR7053_TEXT;
const char STR7054[] = STR7054_TEXT;
const char STR7056[] = STR7056_TEXT;
const char STR7070[] = STR7070_TEXT;
const char STR7071[] = STR7071_TEXT;
const char STR7072[] = STR7072_TEXT;
const char STR7073[] = STR7073_TEXT;
const char STR7074[] = STR7074_TEXT;
const char STR7075[] = STR7075_TEXT;
const char STR7076[] = STR7076_TEXT;
const char STR7077[] = STR7077_TEXT;
const char STR7078[] = STR7078_TEXT;
const char STR7079[] = STR7079_TEXT;
const char STR7080[] = STR7080_TEXT;
const char STR7081[] = STR7081_TEXT;
const char STR7082[] = STR7082_TEXT;
const char STR7083[] = STR7083_TEXT;
const char STR7090[] = STR7090_TEXT;
const char STR7091[] = STR7091_TEXT;
const char STR7092[] = STR7092_TEXT;
const char STR7093[] = STR7093_TEXT;
const char STR7119[] = STR7119_TEXT;
const char STR7120[] = STR7120_TEXT;
const char STR7130[] = STR7130_TEXT;
const char STR7131[] = STR7131_TEXT;
const char STR7140[] = STR7140_TEXT;
const char STR7141[] = STR7141_TEXT;
const char STR7142[] = STR7142_TEXT;
const char STR7143[] = STR7143_TEXT;
const char STR7145[] = STR7145_TEXT;
const char STR7146[] = STR7146_TEXT;
const char STR7147[] = STR7147_TEXT;
const char STR7150[] = STR7150_TEXT;
const char STR7152[] = STR7152_TEXT;
const char STR7153[] = STR7153_TEXT;
const char STR7160[] = STR7160_TEXT;
const char STR7165[] = STR7165_TEXT;
const char STR7166[] = STR7166_TEXT;
const char STR7167[] = STR7167_TEXT;
const char STR7168[] = STR7168_TEXT;
const char STR7170[] = STR7170_TEXT;
const char STR7181[] = STR7181_TEXT;
const char STR7183[] = STR7183_TEXT;
const char STR7230[] = STR7230_TEXT;
const char STR7231[] = STR7231_TEXT;
const char STR7232[] = STR7232_TEXT;
const char STR7233[] = STR7233_TEXT;
const char STR7236[] = STR7236_TEXT;
const char STR7237[] = STR7237_TEXT;
const char STR7238[] = STR7238_TEXT;
const char STR7239[] = STR7239_TEXT;
const char STR7240[] = STR7240_TEXT;
const char STR7244[] = STR7244_TEXT;
const char STR7250[] = STR7250_TEXT;
const char STR7251[] = STR7251_TEXT;
#define STR7251_2 STR1
const char STR7252[] = STR7252_TEXT;
const char STR7253[] = STR7253_TEXT;

// Konfiguration Erweit'module
#define STR7300 STR6020
#define STR7301 STR6030
#define STR7302 STR6031
#define STR7303 STR6032
#define STR7307 STR6040
#define STR7308 STR6041
const char STR7311[] = STR7311_TEXT;
const char STR7321[] = STR7321_TEXT;
const char STR7322[] = STR7322_TEXT;
const char STR7324[] = STR7324_TEXT;
const char STR7325[] = STR7325_TEXT;
const char STR7326[] = STR7326_TEXT;
const char STR7327[] = STR7327_TEXT;
#define STR7342 STR6024
#define STR7348 STR6240_2
#define STR7349 STR6241
#define STR7350 STR6242
#define STR7355 STR6243
#define STR7356 STR6244
#define STR7357 STR6245
#define STR7375 STR6021
#define STR7376 STR6033
#define STR7377 STR6034
#define STR7378 STR6035
const char STR7386[] = STR7386_TEXT;
const char STR7387[] = STR7387_TEXT;
const char STR7396[] = STR7396_TEXT;
const char STR7397[] = STR7397_TEXT;
const char STR7399[] = STR7399_TEXT;
const char STR7400[] = STR7400_TEXT;
const char STR7401[] = STR7401_TEXT;
const char STR7402[] = STR7402_TEXT;
#define STR7417 STR6026
#define STR7423 STR6246
#define STR7424 STR6247
#define STR7425 STR6248
#define STR7430 STR6249
#define STR7431 STR6250_2
#define STR7432 STR6251
#define STR7450 STR6022
#define STR7451 STR6036
#define STR7452 STR6037
#define STR7453 STR6038
#define STR7457 STR6044
#define STR7458 STR6045
const char STR7471[] = STR7471_TEXT;
const char STR7472[] = STR7472_TEXT;
const char STR7474[] = STR7474_TEXT;
const char STR7475[] = STR7475_TEXT;
const char STR7476[] = STR7476_TEXT;
const char STR7477[] = STR7477_TEXT;
#define STR7492 STR6028
#define STR7498 STR6252
#define STR7499 STR6253
#define STR7500 STR6254
#define STR7505 STR6255
#define STR7506 STR6256
#define STR7507 STR6257

// Ein-/Ausgangstest
const char STR7700[] = STR7700_TEXT;
const char STR7705[] = STR7705_TEXT;
const char STR7705_2[] = STR7705_2_TEXT;
const char STR7708[] = STR7708_TEXT;
const char STR7708_2[] = STR7708_2_TEXT;
const char STR7710[] = STR7710_TEXT;
const char STR7711[] = STR7711_TEXT;
const char STR7711_2[] = STR7711_2_TEXT;
const char STR7712[] = STR7712_TEXT;
const char STR7713[] = STR7713_TEXT;
const char STR7714[] = STR7714_TEXT;
const char STR7716[] = STR7716_TEXT;
const char STR7717[] = STR7717_TEXT;
const char STR7718[] = STR7718_TEXT;
const char STR7719[] = STR7719_TEXT;
const char STR7720[] = STR7720_TEXT;
const char STR7721[] = STR7721_TEXT;
const char STR7722[] = STR7722_TEXT;
const char STR7723[] = STR7723_TEXT;
const char STR7724[] = STR7724_TEXT;
const char STR7725[] = STR7725_TEXT;
const char STR7725_2[] = STR7725_2_TEXT;
const char STR7726[] = STR7726_TEXT;
const char STR7730[] = STR7730_TEXT;
const char STR7732[] = STR7732_TEXT;
const char STR7734[] = STR7734_TEXT;
const char STR7750[] = STR7750_TEXT;
const char STR7760[] = STR7760_TEXT;
const char STR7770[] = STR7770_TEXT;
const char STR7771[] = STR7771_TEXT;
const char STR7772[] = STR7772_TEXT;
const char STR7775[] = STR7775_TEXT;
const char STR7777[] = STR7777_TEXT;
const char STR7780[] = STR7780_TEXT;
const char STR7781[] = STR7781_TEXT;
const char STR7782[] = STR7782_TEXT;
const char STR7783[] = STR7783_TEXT;
const char STR7784[] = STR7784_TEXT;
const char STR7785[] = STR7785_TEXT;
const char STR7785_2[] = STR7785_2_TEXT;
const char STR7786[] = STR7786_TEXT;
const char STR7787[] = STR7787_TEXT;
const char STR7787_2[] = STR7787_2_TEXT;
const char STR7788[] = STR7788_TEXT;
const char STR7789[] = STR7789_TEXT;
const char STR7790[] = STR7790_TEXT;
const char STR7791[] = STR7791_TEXT;
#define STR7804 STR7820
#define STR7805 STR7821
#define STR7806 STR7822
#define STR7807 STR7823
const char STR7809[] = STR7809_TEXT;
const char STR7810[] = STR7810_TEXT;
const char STR7811[] = STR7811_TEXT;
const char STR7812[] = STR7812_TEXT;
const char STR7813[] = STR7813_TEXT;
const char STR7814[] = STR7814_TEXT;
const char STR7815[] = STR7815_TEXT;
const char STR7816[] = STR7816_TEXT;
const char STR7817[] = STR7817_TEXT;
const char STR7820[] = STR7820_TEXT;
const char STR7821[] = STR7821_TEXT;
const char STR7822[] = STR7822_TEXT;
const char STR7823[] = STR7823_TEXT;
const char STR7824[] = STR7824_TEXT;
const char STR7830[] = STR7830_TEXT;
const char STR7831[] = STR7831_TEXT;
const char STR7832[] = STR7832_TEXT;
const char STR7833[] = STR7833_TEXT;
const char STR7834[] = STR7834_TEXT;
const char STR7835[] = STR7835_TEXT;
const char STR7840[] = STR7840_TEXT;
const char STR7841[] = STR7841_TEXT;
const char STR7844[] = STR7844_TEXT;
const char STR7845[] = STR7845_TEXT;
const char STR7846[] = STR7846_TEXT;
const char STR7847[] = STR7847_TEXT;
const char STR7848[] = STR7848_TEXT;
const char STR7849[] = STR7849_TEXT;
const char STR7852[] = STR7852_TEXT;
const char STR7854[] = STR7854_TEXT;
const char STR7855[] = STR7855_TEXT;
const char STR7858[] = STR7858_TEXT;
const char STR7860[] = STR7860_TEXT;
const char STR7862[] = STR7862_TEXT;
const char STR7865[] = STR7865_TEXT;
const char STR7870[] = STR7870_TEXT;
const char STR7872[] = STR7872_TEXT;
const char STR7874[] = STR7874_TEXT;
const char STR7881[] = STR7881_TEXT;
const char STR7884[] = STR7884_TEXT;
const char STR7889[] = STR7889_TEXT;
const char STR7890[] = STR7890_TEXT;
const char STR7891[] = STR7891_TEXT;
const char STR7911[] = STR7911_TEXT;
const char STR7912[] = STR7912_TEXT;
const char STR7913[] = STR7913_TEXT;
const char STR7914[] = STR7914_TEXT;
const char STR7915[] = STR7915_TEXT;
const char STR7916[] = STR7916_TEXT;
const char STR7917[] = STR7917_TEXT;
const char STR7919[] = STR7919_TEXT;
const char STR7945[] = STR7945_TEXT;
const char STR7946[] = STR7946_TEXT;
const char STR7950[] = STR7950_TEXT;
const char STR7951[] = STR7951_TEXT;
const char STR7952[] = STR7952_TEXT;
const char STR7973[] = STR7973_TEXT;
const char STR7974[] = STR7974_TEXT;
const char STR7975[] = STR7975_TEXT;
const char STR7976[] = STR7976_TEXT;
const char STR7977[] = STR7977_TEXT;
const char STR7978[] = STR7978_TEXT;
const char STR7996[] = STR7996_TEXT;
const char STR7999[] = STR7999_TEXT;

// Status
const char STR8000[] = STR8000_TEXT;
const char STR8001[] = STR8001_TEXT;
const char STR8002[] = STR8002_TEXT;
const char STR8003[] = STR8003_TEXT;
const char STR8004[] = STR8004_TEXT;
const char STR8005[] = STR8005_TEXT;
const char STR8006[] = STR8006_TEXT;
const char STR8007[] = STR8007_TEXT;
const char STR8008[] = STR8008_TEXT;
const char STR8009[] = STR8009_TEXT;
const char STR8010[] = STR8010_TEXT;
const char STR8011[] = STR8011_TEXT;
const char STR8022[] = STR8022_TEXT;
const char STR8023[] = STR8023_TEXT;
const char STR8025[] = STR8025_TEXT;
const char STR8050[] = STR8050_TEXT;
const char STR8051[] = STR8051_TEXT;
const char STR8052[] = STR8052_TEXT;
const char STR8053[] = STR8053_TEXT;
const char STR8054[] = STR8054_TEXT;
const char STR8055[] = STR8055_TEXT;
const char STR8056[] = STR8056_TEXT;
const char STR8057[] = STR8057_TEXT;
const char STR8058[] = STR8058_TEXT;
const char STR8059[] = STR8059_TEXT;
const char STR8060[] = STR8060_TEXT;
const char STR8061[] = STR8061_TEXT;
const char STR8062[] = STR8062_TEXT;
const char STR8063[] = STR8063_TEXT;
const char STR8064[] = STR8064_TEXT;
const char STR8065[] = STR8065_TEXT;
const char STR8066[] = STR8066_TEXT;
const char STR8067[] = STR8067_TEXT;
const char STR8068[] = STR8068_TEXT;
#define STR8069 STR8067
#define STR8070 STR6820
const char STR8099[] = STR8099_TEXT;

// Diagnose Kaskade
const char STR8100[] = STR8100_TEXT;
#define STR8101 STR1
const char STR8102[] = STR8102_TEXT;
#define STR8103 STR1
const char STR8104[] = STR8104_TEXT;
#define STR8105 STR1
const char STR8106[] = STR8106_TEXT;
#define STR8107 STR1
const char STR8108[] = STR8108_TEXT;
#define STR8109 STR1
const char STR8110[] = STR8110_TEXT;
#define STR8111 STR1
const char STR8112[] = STR8112_TEXT;
#define STR8113 STR1
const char STR8114[] = STR8114_TEXT;
#define STR8115 STR1
const char STR8116[] = STR8116_TEXT;
#define STR8117 STR1
const char STR8118[] = STR8118_TEXT;
#define STR8119 STR1
const char STR8120[] = STR8120_TEXT;
#define STR8121 STR1
const char STR8122[] = STR8122_TEXT;
#define STR8123 STR1
const char STR8124[] = STR8124_TEXT;
#define STR8125 STR1
const char STR8126[] = STR8126_TEXT;
#define STR8127 STR1
const char STR8128[] = STR8128_TEXT;
#define STR8129 STR1
const char STR8130[] = STR8130_TEXT;
#define STR8131 STR1
const char STR8138[] = STR8138_TEXT;
const char STR8139[] = STR8139_TEXT;
const char STR8140[] = STR8140_TEXT;
const char STR8141[] = STR8141_TEXT;
const char STR8150[] = STR8150_TEXT;
const char STR8151[] = STR8151_TEXT;
const char STR8199[] = STR8199_TEXT;

// 8300 Diagnose Erzeuger
const char STR8300[] = STR8300_TEXT;
const char STR8301[] = STR8301_TEXT;
const char STR8302[] = STR8302_TEXT;
const char STR8303[] = STR8303_TEXT;
const char STR8304[] = STR8304_TEXT;
const char STR8308[] = STR8308_TEXT;
const char STR8309[] = STR8309_TEXT;
const char STR8310[] = STR8310_TEXT;
const char STR8311[] = STR8311_TEXT;
const char STR8312[] = STR8312_TEXT;
#define STR8313 STR3725
const char STR8314[] = STR8314_TEXT;
const char STR8315[] = STR8315_TEXT;
const char STR8316[] = STR8316_TEXT;
const char STR8317[] = STR8317_TEXT;
const char STR8318[] = STR8318_TEXT;
const char STR8319[] = STR8319_TEXT;
const char STR8320[] = STR8320_TEXT;
const char STR8321[] = STR8321_TEXT;
const char STR8321_2[] = STR8321_2_TEXT;
const char STR8323[] = STR8323_TEXT;
const char STR8324[] = STR8324_TEXT;
const char STR8325[] = STR8325_TEXT;
const char STR8325_2[] = STR8325_2_TEXT;
const char STR8326[] = STR8326_TEXT;
const char STR8327[] = STR8327_TEXT;
const char STR8328[] = STR8328_TEXT;
#define STR8329 STR2730
const char STR8330[] = STR8330_TEXT;
const char STR8331[] = STR8331_TEXT;
const char STR8332[] = STR8332_TEXT;
const char STR8333[] = STR8333_TEXT;
const char STR8336[] = STR8336_TEXT;
const char STR8337[] = STR8337_TEXT;
const char STR8338[] = STR8338_TEXT;
const char STR8339[] = STR8339_TEXT;
const char STR8340[] = STR8340_TEXT;
const char STR8366[] = STR8366_TEXT;
const char STR8378[] = STR8378_TEXT;
const char STR8379[] = STR8379_TEXT;
const char STR8380[] = STR8380_TEXT;
const char STR8381[] = STR8381_TEXT;
const char STR8382[] = STR8382_TEXT;
const char STR8383[] = STR8383_TEXT;
const char STR8390[] = STR8390_TEXT;
const char STR8395[] = STR8395_TEXT;
const char STR8396[] = STR8396_TEXT;
const char STR8397[] = STR8397_TEXT;
const char STR8398[] = STR8398_TEXT;
const char STR8400[] = STR8400_TEXT;
const char STR8401[] = STR8401_TEXT;
const char STR8402[] = STR8402_TEXT;
const char STR8403[] = STR8403_TEXT;
const char STR8404[] = STR8404_TEXT;
const char STR8405[] = STR8405_TEXT;
const char STR8406[] = STR8406_TEXT;
const char STR8407[] = STR8407_TEXT;
const char STR8408[] = STR8408_TEXT;
const char STR8410[] = STR8410_TEXT;
const char STR8411[] = STR8411_TEXT;
const char STR8412[] = STR8412_TEXT;
const char STR8413[] = STR8413_TEXT;
const char STR8414[] = STR8414_TEXT;
const char STR8415[] = STR8415_TEXT;
#define STR8416 STR2846
const char STR8417[] = STR8417_TEXT;
const char STR8420[] = STR8420_TEXT;
const char STR8423[] = STR8423_TEXT;
const char STR8424[] = STR8424_TEXT;
const char STR8425[] = STR8425_TEXT;
const char STR8426[] = STR8426_TEXT;
const char STR8427[] = STR8427_TEXT;
const char STR8428[] = STR8428_TEXT;
const char STR8429[] = STR8429_TEXT;
const char STR8430[] = STR8430_TEXT;
const char STR8431[] = STR8431_TEXT;
const char STR8432[] = STR8432_TEXT;
const char STR8434[] = STR8434_TEXT;
const char STR8435[] = STR8435_TEXT;
const char STR8435_1[] = STR8435_1_TEXT;
const char STR8436[] = STR8436_TEXT;
const char STR8436_1[] = STR8436_1_TEXT;
const char STR8437[] = STR8437_TEXT;
const char STR8438[] = STR8438_TEXT;
const char STR8440[] = STR8440_TEXT;
const char STR8441[] = STR8441_TEXT;
const char STR8442[] = STR8442_TEXT;
const char STR8443[] = STR8443_TEXT;
const char STR8444[] = STR8444_TEXT;
const char STR8446[] = STR8446_TEXT;
const char STR8448[] = STR8448_TEXT;
const char STR8449[] = STR8449_TEXT;
const char STR8450[] = STR8450_TEXT;
const char STR8451[] = STR8451_TEXT;
const char STR8452[] = STR8452_TEXT;
const char STR8453[] = STR8453_TEXT;
const char STR8454[] = STR8454_TEXT;
const char STR8455[] = STR8455_TEXT;
const char STR8456[] = STR8456_TEXT;
const char STR8457[] = STR8457_TEXT;
const char STR8458[] = STR8458_TEXT;
const char STR8460[] = STR8460_TEXT;
const char STR8461[] = STR8461_TEXT;
const char STR8462[] = STR8462_TEXT;
const char STR8463[] = STR8463_TEXT;
// Kommt auch noch ein Telegramm 0x593D1779, könnte Verdampfungsdruck E in bar sein oder vertauscht mit dem oben
const char STR8464[] = STR8464_TEXT;
// Kommt auch noch ein Telegramm 0x593D17AC, könnte Überhitzungssollwert E in °C sein oder vertauscht mit dem oben
const char STR8465[] = STR8465_TEXT;
const char STR8466[] = STR8466_TEXT;
const char STR8467[] = STR8467_TEXT;
const char STR8469[] = STR8469_TEXT;
const char STR8470[] = STR8470_TEXT;
const char STR8471[] = STR8471_TEXT;
const char STR8475[] = STR8475_TEXT;
const char STR8477[] = STR8477_TEXT;
const char STR8478[] = STR8478_TEXT;
const char STR8480[] = STR8480_TEXT;
const char STR8481[] = STR8481_TEXT;
const char STR8482[] = STR8482_TEXT;
const char STR8485[] = STR8485_TEXT;
const char STR8487[] = STR8487_TEXT;
const char STR8488[] = STR8488_TEXT;

// Diagnose Erzeuger - Solar
const char STR8499[] = STR8499_TEXT;
const char STR8499_2[] = STR8499_2_TEXT;
const char STR8501[] = STR8501_TEXT;
const char STR8502[] = STR8502_TEXT;
const char STR8505[] = STR8505_TEXT;
const char STR8506[] = STR8506_TEXT;
const char STR8507[] = STR8507_TEXT;
const char STR8508[] = STR8508_TEXT;
const char STR8510[] = STR8510_TEXT;
const char STR8511[] = STR8511_TEXT;
const char STR8512[] = STR8512_TEXT;
const char STR8513[] = STR8513_TEXT;
const char STR8513_2[] = STR8513_2_TEXT;
const char STR8514[] = STR8514_TEXT;
const char STR8515[] = STR8515_TEXT;
const char STR8519[] = STR8519_TEXT;
const char STR8520[] = STR8520_TEXT;
const char STR8521[] = STR8521_TEXT;
const char STR8526[] = STR8526_TEXT;
const char STR8527[] = STR8527_TEXT;
const char STR8530[] = STR8530_TEXT;
const char STR8531[] = STR8531_TEXT;
const char STR8532[] = STR8532_TEXT;
const char STR8543[] = STR8543_TEXT;
const char STR8547[] = STR8547_TEXT;
const char STR8548[] = STR8548_TEXT;
const char STR8549[] = STR8549_TEXT;
const char STR8550[] = STR8550_TEXT;
const char STR8551[] = STR8551_TEXT;
const char STR8552[] = STR8552_TEXT;
const char STR8559[] = STR8559_TEXT;
const char STR8560[] = STR8560_TEXT;
const char STR8568[] = STR8568_TEXT;
const char STR8570[] = STR8570_TEXT;
#define STR8585 STR8319
const char STR8586[] = STR8586_TEXT;

// Diagnose Verbraucher
const char STR8700[] = STR8700_TEXT;
const char STR8701[] = STR8701_TEXT;
const char STR8702[] = STR8702_TEXT;
const char STR8703[] = STR8703_TEXT;
const char STR8704[] = STR8704_TEXT;
const char STR8705[] = STR8705_TEXT;
const char STR8720[] = STR8720_TEXT;
const char STR8721[] = STR8721_TEXT;
const char STR8722[] = STR8722_TEXT;
const char STR8730[] = STR8730_TEXT;
const char STR8731[] = STR8731_TEXT;
const char STR8732[] = STR8732_TEXT;
const char STR8735[] = STR8735_TEXT;
const char STR8739[] = STR8739_TEXT;
const char STR8740[] = STR8740_TEXT;
const char STR8741[] = STR8741_TEXT;
const char STR8742[] = STR8742_TEXT;
const char STR8743[] = STR8743_TEXT;
const char STR8744[] = STR8744_TEXT;
const char STR8749[] = STR8749_TEXT;
const char STR8750[] = STR8750_TEXT;
const char STR8751[] = STR8751_TEXT;
const char STR8752[] = STR8752_TEXT;
const char STR8753[] = STR8753_TEXT;
const char STR8754[] = STR8754_TEXT;
const char STR8756[] = STR8756_TEXT;
const char STR8757[] = STR8757_TEXT;
const char STR8760[] = STR8760_TEXT;
const char STR8761[] = STR8761_TEXT;
const char STR8762[] = STR8762_TEXT;
const char STR8765[] = STR8765_TEXT;
const char STR8770[] = STR8770_TEXT;
const char STR8771[] = STR8771_TEXT;
const char STR8772[] = STR8772_TEXT;
const char STR8773[] = STR8773_TEXT;
const char STR8774[] = STR8774_TEXT;
const char STR8779[] = STR8779_TEXT;
const char STR8790[] = STR8790_TEXT;
const char STR8791[] = STR8791_TEXT;
const char STR8792[] = STR8792_TEXT;
const char STR8795[] = STR8795_TEXT;
const char STR8800[] = STR8800_TEXT;
const char STR8801[] = STR8801_TEXT;
const char STR8802[] = STR8802_TEXT;
const char STR8803[] = STR8803_TEXT;
const char STR8804[] = STR8804_TEXT;
const char STR8809[] = STR8809_TEXT;
const char STR8820[] = STR8820_TEXT;
const char STR8821[] = STR8821_TEXT;
const char STR8823[] = STR8823_TEXT;
const char STR8825[] = STR8825_TEXT;
const char STR8826[] = STR8826_TEXT;
const char STR8827[] = STR8827_TEXT;
const char STR8830[] = STR8830_TEXT;
const char STR8831[] = STR8831_TEXT;
const char STR8832[] = STR8832_TEXT;
const char STR8835[] = STR8835_TEXT;
const char STR8836[] = STR8836_TEXT;
const char STR8837[] = STR8837_TEXT;
const char STR8840[] = STR8840_TEXT;
const char STR8841[] = STR8841_TEXT;
const char STR8842[] = STR8842_TEXT;
const char STR8843[] = STR8843_TEXT;
const char STR8850[] = STR8850_TEXT;
const char STR8851[] = STR8851_TEXT;
const char STR8852[] = STR8852_TEXT;
const char STR8853[] = STR8853_TEXT;
const char STR8860[] = STR8860_TEXT;
const char STR8875[] = STR8875_TEXT;
const char STR8885[] = STR8885_TEXT;
const char STR8895[] = STR8895_TEXT;
const char STR8900[] = STR8900_TEXT;
const char STR8901[] = STR8901_TEXT;
const char STR8930[] = STR8930_TEXT;
const char STR8931[] = STR8931_TEXT;
const char STR8950[] = STR8950_TEXT;
const char STR8951[] = STR8951_TEXT;
const char STR8952[] = STR8952_TEXT;
const char STR8956[] = STR8956_TEXT;
const char STR8957[] = STR8957_TEXT;
const char STR8962[] = STR8962_TEXT;
const char STR8970[] = STR8970_TEXT;
const char STR8980[] = STR8980_TEXT;
const char STR8981[] = STR8981_TEXT;
const char STR8982[] = STR8982_TEXT;
const char STR8983[] = STR8983_TEXT;
const char STR8984[] = STR8984_TEXT;
const char STR8990[] = STR8990_TEXT;
const char STR8991[] = STR8991_TEXT;
const char STR9000[] = STR9000_TEXT;
const char STR9001[] = STR9001_TEXT;
const char STR9004[] = STR9004_TEXT;
const char STR9005[] = STR9005_TEXT;
const char STR9006[] = STR9006_TEXT;
const char STR9009[] = STR9009_TEXT;
const char STR9010[] = STR9010_TEXT;
const char STR9011[] = STR9011_TEXT;
const char STR9012[] = STR9012_TEXT;
const char STR9016[] = STR9016_TEXT;
const char STR9017[] = STR9017_TEXT;
#define STR9031 STR5890
#define STR9032 STR5891
#define STR9033 STR5892
#define STR9034 STR5894
#define STR9035 STR5895
#define STR9036 STR5896
const char STR9037[] = STR9037_TEXT;
const char STR9038[] = STR9038_TEXT;
const char STR9039[] = STR9039_TEXT;
const char STR9040[] = STR9040_TEXT;
const char STR9041[] = STR9041_TEXT;
const char STR9042[] = STR9042_TEXT;
const char STR9043[] = STR9043_TEXT;
#define STR9050 STR6030
#define STR9051 STR6031
#define STR9052 STR6032
#define STR9053 STR6033
#define STR9054 STR6034
#define STR9055 STR6035
#define STR9056 STR6036
#define STR9057 STR6037
#define STR9058 STR6038
const char STR9071[] = STR9071_TEXT;
const char STR9072[] = STR9072_TEXT;
const char STR9073[] = STR9073_TEXT;
const char STR9074[] = STR9074_TEXT;
#define STR9075 STR6375

// Feuerungsautomat
const char STR9500[] = STR9500_TEXT;
const char STR9501[] = STR9501_TEXT;
const char STR9502[] = STR9502_TEXT;
const char STR9504[] = STR9504_TEXT;
const char STR9504_2[] = STR9504_2_TEXT;
const char STR9505[] = STR9505_TEXT;
const char STR9506[] = STR9506_TEXT;
const char STR9510[] = STR9510_TEXT;
const char STR9512[] = STR9512_TEXT;
const char STR9512_2[] = STR9512_2_TEXT;
const char STR9513[] = STR9513_TEXT;
const char STR9514[] = STR9514_TEXT;
const char STR9517[] = STR9517_TEXT;
const char STR9518[] = STR9518_TEXT;
const char STR9519[] = STR9519_TEXT;
const char STR9520[] = STR9520_TEXT;
const char STR9522[] = STR9522_TEXT;
const char STR9523[] = STR9523_TEXT;
const char STR9524[] = STR9524_TEXT;
const char STR9524_2[] = STR9524_2_TEXT;
const char STR9525[] = STR9525_TEXT;
const char STR9526[] = STR9526_TEXT;
const char STR9527[] = STR9527_TEXT;
const char STR9529[] = STR9529_TEXT;
const char STR9529_2[] = STR9529_2_TEXT;
const char STR9530[] = STR9530_TEXT;
const char STR9531[] = STR9531_TEXT;
const char STR9534[] = STR9534_TEXT;
const char STR9540[] = STR9540_TEXT;
const char STR9541[] = STR9541_TEXT;
const char STR9541_2[] = STR9541_2_TEXT;
const char STR9542[] = STR9542_TEXT;
const char STR9544[] = STR9544_TEXT;
const char STR9545[] = STR9545_TEXT;
const char STR9550[] = STR9550_TEXT;
const char STR9551[] = STR9551_TEXT;
const char STR9552[] = STR9552_TEXT;
const char STR9560[] = STR9560_TEXT;
const char STR9563[] = STR9563_TEXT;
const char STR9610[] = STR9610_TEXT;
const char STR9611[] = STR9611_TEXT;
const char STR9612[] = STR9612_TEXT;
const char STR9613[] = STR9613_TEXT;
const char STR9614[] = STR9614_TEXT;
const char STR9615[] = STR9615_TEXT;
const char STR9616[] = STR9616_TEXT;
const char STR9617[] = STR9617_TEXT;
const char STR9618[] = STR9618_TEXT;
const char STR9619[] = STR9619_TEXT;
const char STR9626[] = STR9626_TEXT;
const char STR9627[] = STR9627_TEXT;
const char STR9630[] = STR9630_TEXT;
#define STR9631 STR2325
#define STR9632 STR2326
const char STR9650[] = STR9650_TEXT;
const char STR9651[] = STR9651_TEXT;
const char STR9652[] = STR9652_TEXT;

/* User-defined command numbers */
#define STR10000 STR8740
#define STR10001 STR8770
#define STR10002 STR8800

#define ENUM42_00_TEXT ENUM_CAT_11_TEXT
#define ENUM47_01_TEXT ENUM_CAT_11_TEXT
#define ENUM48_01_TEXT ENUM_CAT_11_TEXT
#define ENUM48_02_TEXT ENUM_CAT_14_TEXT
#define ENUM700_02_TEXT ENUM648_01_TEXT
#define ENUM780_00_TEXT MENU_TEXT_OFF
#define ENUM843_00_TEXT ENUM48_00_TEXT
#define ENUM843_02_TEXT STR2201_TEXT
#define ENUM850_00_TEXT ENUM780_00_TEXT
#define ENUM860_00_TEXT MENU_TEXT_OFF
#define ENUM860_01_TEXT ENUM861_01_TEXT
#define ENUM860_02_TEXT ENUM861_02_TEXT
#define ENUM861_00_TEXT ENUM780_00_TEXT
#define ENUM880_02_TEXT STR2317_TEXT
#define ENUM898_00_TEXT ENUM700_00_TEXT
#define ENUM898_01_TEXT ENUM648_01_TEXT
#define ENUM898_02_TEXT ENUM700_03_TEXT
#define ENUM900_00_TEXT ENUM48_00_TEXT
#define ENUM900_01_TEXT ENUM700_00_TEXT
#define ENUM900_02_TEXT ENUM648_01_TEXT
#define ENUM900_03_TEXT ENUM700_03_TEXT
#define ENUM900_04_TEXT ENUM700_01_TEXT
#define ENUM900_2_00_TEXT ENUM700_00_TEXT
#define ENUM900_2_01_TEXT ENUM648_01_TEXT
#define ENUM900_2_03_TEXT ENUM700_03_TEXT
#define ENUM900_2_04_TEXT ENUM700_01_TEXT
#define ENUM907_01_TEXT ENUM1620_00_TEXT
#define ENUM907_02_TEXT ENUM6136_02_TEXT
#define ENUM907_03_TEXT ENUM_CAT_0c_TEXT
#define ENUM945_01_TEXT ENUM2706_09_TEXT
#define ENUM945_02_TEXT MENU_TEXT_OPEN
#define ENUM945_03_TEXT MENU_TEXT_CLOSE
#define ENUM1000_00_TEXT ENUM700_00_TEXT
#define ENUM1000_01_TEXT ENUM700_01_TEXT
#define ENUM1000_02_TEXT ENUM648_01_TEXT
#define ENUM1000_03_TEXT ENUM700_03_TEXT
#define ENUM1300_00_TEXT ENUM700_00_TEXT
#define ENUM1300_01_TEXT ENUM700_01_TEXT
#define ENUM1300_02_TEXT ENUM648_01_TEXT
#define ENUM1300_03_TEXT ENUM700_03_TEXT
#define ENUM1600_00_TEXT ENUM780_00_TEXT
#define ENUM1600_01_TEXT MENU_TEXT_ON
#define ENUM1601_00_TEXT ENUM48_00_TEXT
#define ENUM1601_02_TEXT ENUM_CAT_2e_TEXT
#define ENUM1620_2_00_TEXT ENUM1620_00_TEXT
#define ENUM1620_2_01_TEXT ENUM1620_01_TEXT
#define ENUM1620_2_04_TEXT ENUM1620_02_TEXT
#define ENUM1630_04_TEXT ENUM780_00_TEXT
#define ENUM1640_00_TEXT ENUM780_00_TEXT
#define ENUM1660_01_TEXT ENUM_CAT_08_TEXT
#define ENUM1660_03_TEXT ENUM1620_02_TEXT
#define ENUM1660_04_TEXT ENUM_CAT_0c_TEXT
#define ENUM1680_00_TEXT ENUM48_00_TEXT
#define ENUM1680_01_TEXT ENUM780_00_TEXT
#define ENUM1680_02_TEXT ENUM1600_01_TEXT
#define ENUM1680_03_TEXT ENUM1600_02_TEXT
#define ENUM2015_01_TEXT ENUM5715_03_TEXT
#define ENUM2015_03_TEXT ENUM3109_03_TEXT
#define ENUM2040_01_TEXT ENUM5715_03_TEXT
#define ENUM2040_02_TEXT ENUM2015_02_TEXT
#define ENUM2040_03_TEXT ENUM3109_03_TEXT
#define ENUM2132_00_TEXT ENUM832_00_TEXT
#define ENUM2132_01_TEXT ENUM832_01_TEXT
#define ENUM2200_01_TEXT ENUM700_01_TEXT
#define ENUM2205_00_TEXT ENUM780_00_TEXT
#define ENUM2205_02_TEXT ENUM1600_01_TEXT
#define ENUM2305_2_01_TEXT ENUM2305_00_TEXT
#define ENUM2305_2_02_TEXT ENUM2305_01_TEXT
#define ENUM2320_00_TEXT ENUM48_00_TEXT
#define ENUM2320_02_TEXT STR8311_TEXT
#define ENUM2320_03_TEXT ENUM880_02_TEXT
#define ENUM2450_00_TEXT ENUM780_00_TEXT
#define ENUM2450_01_TEXT ENUM2305_00_TEXT
#define ENUM2450_03_TEXT ENUM2305_01_TEXT
#define ENUM2500_00_TEXT ENUM2480_00_TEXT
#define ENUM2500_01_TEXT ENUM2480_ff_TEXT
#define ENUM2501_00_TEXT ENUM48_00_TEXT
#define ENUM2740_00_TEXT MENU_TEXT_NO
#define ENUM2706_00_TEXT ENUM2476_ff_TEXT
#define ENUM2706_03_TEXT ENUM2206_01_TEXT
#define ENUM2710_00_TEXT MENU_TEXT_OFF
#define ENUM2726_01_TEXT ENUM2721_01_TEXT
#define ENUM2749_00_TEXT ENUM2740_00_TEXT
#define ENUM2790_00_TEXT ENUM48_00_TEXT
#define ENUM2790_02_TEXT ENUM3009_01_TEXT
#define ENUM2790_03_TEXT STR8425_TEXT
#define ENUM2801_01_TEXT ENUM5040_02_TEXT
#define ENUM2880_01_TEXT ENUM3692_01_TEXT
#define ENUM2880_06_TEXT STR7141_TEXT
#define ENUM2880_07_TEXT STR1640_TEXT
#define ENUM2900_00_TEXT ENUM1630_02_TEXT
#define ENUM2903_01_TEXT STR8398_TEXT
#define ENUM2908_01_TEXT ENUM3694_01_TEXT
#define ENUM2911_00_TEXT ENUM2476_ff_TEXT
#define ENUM2911_01_TEXT ENUM2920_01_TEXT
#define ENUM2920_00_TEXT ENUM2706_00_TEXT
#define ENUM2922_00_TEXT MENU_TEXT_OFF
#define ENUM2923_00_TEXT ENUM1630_02_TEXT
#define ENUM2923_01_TEXT ENUM4137_01_TEXT
#define ENUM2923_02_TEXT ENUM4795_02_TEXT
#define ENUM2923_03_TEXT ENUM4795_03_TEXT
#define ENUM3009_00_TEXT ENUM48_00_TEXT
#define ENUM3009_02_TEXT STR8426_TEXT
#define ENUM3030_00_TEXT MENU_TEXT_OFF
#define ENUM3092_00_TEXT UNIT_KWH_TEXT
#define ENUM3095_00_TEXT ENUM48_00_TEXT
#define ENUM3100_00_TEXT ENUM48_00_TEXT
#define ENUM3100_01_TEXT ENUM3095_01_TEXT
#define ENUM3100_02_TEXT ENUM3095_05_TEXT
#define ENUM3100_03_TEXT ENUM3095_06_TEXT
#define ENUM3100_04_TEXT ENUM3095_07_TEXT
#define ENUM3100_05_TEXT ENUM3095_08_TEXT
#define ENUM3100_06_TEXT ENUM3095_09_TEXT
#define ENUM3100_07_TEXT ENUM3095_0a_TEXT
#define ENUM3100_08_TEXT ENUM3095_0b_TEXT
#define ENUM3100_09_TEXT ENUM3095_0c_TEXT
#define ENUM3100_0a_TEXT ENUM3095_0d_TEXT
#define ENUM3102_00_TEXT ENUM48_00_TEXT
#define ENUM3102_01_TEXT ENUM3092_00_TEXT
#define ENUM3109_00_TEXT ENUM48_00_TEXT
#define ENUM3109_01_TEXT STR3110_TEXT
#define ENUM3109_02_TEXT STR3113_TEXT
#define ENUM3192_00_TEXT ENUM48_00_TEXT
#define ENUM3192_01_TEXT ENUM3109_01_TEXT
#define ENUM3192_02_TEXT ENUM3109_02_TEXT
#define ENUM3192_03_TEXT ENUM3109_03_TEXT
#define ENUM3541_00_TEXT ENUM48_00_TEXT
#define ENUM3692_00_TEXT ENUM2476_ff_TEXT
#define ENUM3725_01_TEXT STR8950_TEXT
#define ENUM3750_01_TEXT ENUM_CAT_2c_TEXT
#define ENUM3750_02_TEXT ENUM_CAT_24_TEXT
#define ENUM3822_00_TEXT ENUM1630_02_TEXT
#define ENUM3822_01_TEXT ENUM_CAT_2e_TEXT
#define ENUM3822_02_TEXT ENUM_CAT_2d_TEXT
#define ENUM3880_01_TEXT ENUM1630_02_TEXT
#define ENUM3887_01_TEXT ENUM1630_02_TEXT
#define ENUM3887_02_TEXT ENUM3092_00_TEXT
#define ENUM4133_03_TEXT ENUM3725_02_TEXT
#define ENUM4133_06_TEXT STR2210_TEXT
#define ENUM4134_00_TEXT ENUM48_00_TEXT
#define ENUM4137_00_TEXT ENUM48_00_TEXT
#define ENUM4720_00_TEXT ENUM48_00_TEXT
#define ENUM4720_01_TEXT ENUM4137_01_TEXT
#define ENUM4720_02_TEXT ENUM4137_03_TEXT
#define ENUM4739_00_TEXT MENU_TEXT_OFF
#define ENUM4739_01_TEXT ENUM861_02_TEXT
#define ENUM4757_00_TEXT ENUM780_00_TEXT
#define ENUM4757_02_TEXT ENUM861_02_TEXT
#define ENUM4795_01_TEXT ENUM4720_01_TEXT
#define ENUM4810_00_TEXT ENUM780_00_TEXT
#define ENUM4810_01_TEXT ENUM861_01_TEXT
#define ENUM4810_02_TEXT ENUM861_02_TEXT
#define ENUM4813_01_TEXT ENUM4720_01_TEXT
#define ENUM5007_02_TEXT ENUM4134_01_TEXT
#define ENUM5007_03_TEXT ENUM4134_02_TEXT
#define ENUM5013_00_TEXT MENU_TEXT_OFF
#define ENUM5016_00_TEXT MENU_TEXT_OFF
#define ENUM5016_01_TEXT ENUM5013_02_TEXT
#define ENUM5016_02_TEXT STR1645_TEXT
#define ENUM5022_01_TEXT ENUM4134_01_TEXT
#define ENUM5040_00_TEXT ENUM780_00_TEXT
#define ENUM5040_01_TEXT ENUM861_02_TEXT
#define ENUM5041_01_TEXT ENUM4134_01_TEXT
#define ENUM5041_02_TEXT ENUM4134_02_TEXT
#define ENUM5057_00_TEXT ENUM780_00_TEXT
#define ENUM5057_01_TEXT ENUM4757_01_TEXT
#define ENUM5057_02_TEXT ENUM861_02_TEXT
#define ENUM5060_01_TEXT ENUM3692_01_TEXT
#define ENUM5060_02_TEXT ENUM4757_01_TEXT
#define ENUM5060_03_TEXT ENUM861_02_TEXT
#define ENUM5060_05_TEXT STR7141_TEXT
#define ENUM5060_06_TEXT STR1640_TEXT
#define ENUM5061_01_TEXT ENUM1620_00_TEXT
#define ENUM5061_02_TEXT ENUM1660_02_TEXT
#define ENUM5061_03_TEXT ENUM1620_02_TEXT
#define ENUM5130_00_TEXT ENUM861_02_TEXT
#define ENUM5131_00_TEXT ENUM4133_01_TEXT
#define ENUM5131_01_TEXT ENUM4133_02_TEXT
#define ENUM5464_00_TEXT ENUM48_00_TEXT
#define ENUM5464_01_TEXT ENUM1620_00_TEXT
#define ENUM5464_02_TEXT ENUM1660_02_TEXT
#define ENUM5464_04_TEXT ENUM_CAT_09_TEXT
#define ENUM5464_05_TEXT ENUM_CAT_0c_TEXT
#define ENUM5475_00_TEXT ENUM6040_03_TEXT
#define ENUM5475_01_TEXT ENUM6272_15_TEXT
#define ENUM5475_02_TEXT ENUM5930_03_TEXT
#define ENUM5491_00_TEXT MENU_TEXT_OFF
#define ENUM5491_01_TEXT ENUM5040_02_TEXT
#define ENUM5550_00_TEXT MENU_TEXT_NO
#define ENUM5550_01_TEXT MENU_TEXT_YES
#define ENUM5711_00_TEXT ENUM780_00_TEXT
#define ENUM5715_00_TEXT ENUM780_00_TEXT
#define ENUM5730_2_01_TEXT ENUM4133_01_TEXT
#define ENUM5734_02_TEXT ENUM_CAT_10_TEXT
#define ENUM5760_01_TEXT ENUM2150_01_TEXT

#define ENUM5573_00_TEXT ENUM1630_02_TEXT
#define ENUM5573_01_TEXT ENUM4133_02_TEXT
#define ENUM5573_02_TEXT ENUM5930_02_TEXT
#define ENUM5573_03_TEXT ENUM5930_03_TEXT
#define ENUM5573_04_TEXT ENUM5930_04_TEXT
#define ENUM5573_05_TEXT ENUM4133_03_TEXT
#define ENUM5573_06_TEXT ENUM4133_04_TEXT
#define ENUM5573_07_TEXT ENUM5930_07_TEXT
#define ENUM5573_08_TEXT ENUM5930_08_TEXT
#define ENUM5573_09_TEXT ENUM5930_09_TEXT
#define ENUM5573_0a_TEXT ENUM5930_0a_TEXT
#define ENUM5573_0b_TEXT ENUM5930_0b_TEXT
#define ENUM5573_0c_TEXT ENUM5930_0c_TEXT
#define ENUM5573_0d_TEXT ENUM5930_0d_TEXT
#define ENUM5573_0e_TEXT ENUM5930_0e_TEXT
#define ENUM5573_10_TEXT ENUM5930_10_TEXT
#define ENUM5573_11_TEXT ENUM5930_11_TEXT
#define ENUM5573_12_TEXT ENUM8313_04_TEXT
#define ENUM5573_15_TEXT ENUM6272_15_TEXT
#define ENUM5573_18_TEXT ENUM4133_01_TEXT

#define ENUM5840_01_TEXT ENUM5731_01_TEXT
#define ENUM5840_02_TEXT ENUM5731_02_TEXT
#define ENUM5841_01_TEXT ENUM48_03_TEXT
#define ENUM5841_02_TEXT ENUM_CAT_2e_TEXT
#define ENUM5841_03_TEXT ENUM_CAT_2d_TEXT
#define ENUM5890_00_TEXT ENUM1630_02_TEXT
#define ENUM5890_02_TEXT STR8821_TEXT
#define ENUM5890_05_TEXT STR8304_TEXT
#define ENUM5890_23_TEXT STR5731_TEXT
#define ENUM5890_2_01_TEXT STR8760_TEXT
#define ENUM5895_00_TEXT ENUM1630_02_TEXT
#define ENUM5895_01_TEXT ENUM5890_21_TEXT
#define ENUM5895_09_TEXT ENUM5890_01_TEXT
#define ENUM5895_0a_TEXT ENUM5890_02_TEXT
#define ENUM5895_0c_TEXT ENUM5890_03_TEXT
#define ENUM5895_0d_TEXT ENUM5890_04_TEXT
#define ENUM5895_0e_TEXT ENUM5890_05_TEXT
#define ENUM5895_0f_TEXT ENUM5890_06_TEXT
#define ENUM5895_10_TEXT ENUM5890_07_TEXT
#define ENUM5895_14_TEXT ENUM5890_0b_TEXT
#define ENUM5895_15_TEXT ENUM5890_0c_TEXT
#define ENUM5895_16_TEXT ENUM5890_0d_TEXT
#define ENUM5895_17_TEXT ENUM5890_0f_TEXT
#define ENUM5895_18_TEXT ENUM5890_10_TEXT
#define ENUM5895_19_TEXT ENUM5890_11_TEXT
#define ENUM5895_1b_TEXT ENUM5890_13_TEXT
#define ENUM5895_1c_TEXT ENUM5890_14_TEXT
#define ENUM5895_1d_TEXT ENUM5890_15_TEXT
#define ENUM5895_1e_TEXT ENUM5890_16_TEXT
#define ENUM5895_1f_TEXT ENUM5890_17_TEXT
#define ENUM5895_20_TEXT STR8754_TEXT
#define ENUM5895_21_TEXT ENUM5895_08_TEXT
#define ENUM5895_23_TEXT STR8470_TEXT
#define ENUM5895_24_TEXT STR8406_TEXT
#define ENUM5895_26_TEXT ENUM5890_19_TEXT
#define ENUM5895_27_TEXT ENUM5890_1a_TEXT
#define ENUM5895_28_TEXT ENUM5890_1b_TEXT
#define ENUM5895_29_TEXT ENUM5890_1c_TEXT
#define ENUM5895_2a_TEXT ENUM5890_1d_TEXT
#define ENUM5895_2b_TEXT ENUM5890_1e_TEXT
#define ENUM5920_02_TEXT ENUM5890_2_0b_TEXT
#define ENUM5920_11_TEXT ENUM5890_1b_TEXT
#define ENUM5930_00_TEXT ENUM1630_02_TEXT
#define ENUM5930_01_TEXT ENUM4133_02_TEXT
#define ENUM5930_05_TEXT ENUM4133_03_TEXT
#define ENUM5930_06_TEXT ENUM4133_04_TEXT
#define ENUM5950_00_TEXT ENUM1630_02_TEXT
#define ENUM5950_06_TEXT STR2201_TEXT
#define ENUM5950_09_TEXT STR4141_TEXT
#define ENUM5950_2_00_TEXT ENUM5890_2_00_TEXT
#define ENUM5950_2_01_TEXT STR5957_TEXT
#define ENUM5950_2_03_TEXT ENUM5920_07_TEXT
#define ENUM5950_2_08_TEXT ENUM5950_06_TEXT
#define ENUM5950_3_02_TEXT ENUM5950_02_TEXT
#define ENUM5950_3_03_TEXT ENUM5950_03_TEXT
#define ENUM5950_3_04_TEXT ENUM5950_04_TEXT
#define ENUM5950_3_05_TEXT ENUM5950_05_TEXT
#define ENUM5950_3_06_TEXT ENUM5950_06_TEXT
#define ENUM5950_3_07_TEXT ENUM5950_07_TEXT
#define ENUM5950_3_08_TEXT ENUM5950_08_TEXT
#define ENUM5950_3_09_TEXT ENUM5950_0d_TEXT
#define ENUM5950_4_00_TEXT ENUM48_00_TEXT
#define ENUM5950_4_03_TEXT ENUM5950_02_TEXT
#define ENUM5950_4_04_TEXT ENUM5950_03_TEXT
#define ENUM5950_4_05_TEXT ENUM5950_04_TEXT
#define ENUM5950_4_07_TEXT ENUM5950_06_TEXT
#define ENUM5950_4_08_TEXT ENUM5950_07_TEXT
#define ENUM5950_4_0c_TEXT ENUM5950_09_TEXT
#define ENUM5950_4_1c_TEXT ENUM5950_2_07_TEXT
#define ENUM5950_4_1d_TEXT ENUM2480_00_TEXT
#define ENUM5950_4_36_TEXT ENUM5950_0e_TEXT
#define ENUM5950_5_02_TEXT ENUM5950_02_TEXT
#define ENUM5950_5_03_TEXT ENUM5950_03_TEXT
#define ENUM5950_5_04_TEXT ENUM5950_04_TEXT
#define ENUM5950_5_05_TEXT ENUM5950_05_TEXT
#define ENUM5950_5_06_TEXT ENUM5950_06_TEXT
#define ENUM5950_5_07_TEXT ENUM5950_07_TEXT
#define ENUM5950_5_08_TEXT ENUM5950_08_TEXT
#define ENUM5950_5_09_TEXT ENUM5950_09_TEXT
#define ENUM5950_5_0a_TEXT ENUM5950_0a_TEXT
#define ENUM5950_5_0b_TEXT ENUM5950_0b_TEXT
#define ENUM5950_5_0c_TEXT ENUM5950_0c_TEXT
#define ENUM5950_5_0d_TEXT STR6627_TEXT
#define ENUM5950_5_0e_TEXT ENUM5950_0d_TEXT
#define ENUM5950_7_01_TEXT ENUM5950_2_01_TEXT
#define ENUM5950_7_02_TEXT ENUM5950_2_02_TEXT
#define ENUM5950_7_03_TEXT ENUM5920_07_TEXT
#define ENUM5957_2_00_TEXT ENUM5957_01_TEXT
#define ENUM5957_2_01_TEXT ENUM5957_02_TEXT
#define ENUM5957_2_03_TEXT ENUM5950_6_03_TEXT
#define ENUM5960_3_02_TEXT ENUM5950_6_03_TEXT
#define ENUM5970_00_TEXT ENUM1630_02_TEXT
#define ENUM5973_00_TEXT ENUM5890_2_00_TEXT
#define ENUM5973_01_TEXT ENUM5950_2_01_TEXT
#define ENUM5973_02_TEXT ENUM5950_2_02_TEXT
#define ENUM5973_03_TEXT ENUM5920_07_TEXT
#define ENUM5973_07_TEXT ENUM5950_2_07_TEXT
#define ENUM5973_08_TEXT ENUM5950_06_TEXT
#define ENUM5973_09_TEXT ENUM5950_2_09_TEXT
#define ENUM5978_00_TEXT ENUM5731_00_TEXT
#define ENUM5980_00_TEXT ENUM48_00_TEXT
#define ENUM5980_0a_TEXT STR7889_TEXT
#define ENUM5980_0b_TEXT STR7890_TEXT
#define ENUM5980_0f_TEXT ENUM5950_07_TEXT
#define ENUM5980_16_TEXT ENUM5950_02_TEXT
#define ENUM5982_02_TEXT ENUM5950_06_TEXT
#define ENUM5982_03_TEXT ENUM5950_07_TEXT
#define ENUM5988_00_TEXT ENUM48_00_TEXT
#define ENUM5988_01_TEXT ENUM5980_01_TEXT
#define ENUM5988_02_TEXT ENUM5980_02_TEXT
#define ENUM5988_03_TEXT ENUM5980_03_TEXT
#define ENUM5988_04_TEXT ENUM5980_04_TEXT
#define ENUM5988_05_TEXT ENUM5980_05_TEXT
#define ENUM5988_06_TEXT ENUM5980_06_TEXT
#define ENUM5988_07_TEXT ENUM5980_07_TEXT
#define ENUM5988_08_TEXT ENUM5980_08_TEXT
#define ENUM5988_09_TEXT ENUM5980_09_TEXT
#define ENUM5988_0a_TEXT ENUM5980_0a_TEXT
#define ENUM5988_0b_TEXT ENUM5980_0b_TEXT
#define ENUM5988_0c_TEXT ENUM5980_0c_TEXT
#define ENUM5988_0d_TEXT ENUM5950_07_TEXT
#define ENUM6014_00_TEXT ENUM48_00_TEXT
#define ENUM6014_01_TEXT ENUM_CAT_11_TEXT
#define ENUM6014_05_TEXT ENUM_CAT_2f_TEXT
#define ENUM6020_00_TEXT ENUM5890_2_00_TEXT
#define ENUM6020_02_TEXT ENUM_CAT_14_TEXT
#define ENUM6020_03_TEXT ENUM6014_02_TEXT
#define ENUM6020_05_TEXT ENUM6014_03_TEXT
#define ENUM6020_06_TEXT ENUM6014_04_TEXT
#define ENUM6020_07_TEXT ENUM_CAT_2f_TEXT
#define ENUM6020_08_TEXT ENUM6014_06_TEXT
#define ENUM6024_00_TEXT ENUM48_00_TEXT
#define ENUM6030_00_TEXT ENUM1630_02_TEXT
#define ENUM6030_01_TEXT ENUM5890_21_TEXT
#define ENUM6030_02_TEXT ENUM5895_02_TEXT
#define ENUM6030_03_TEXT ENUM5895_03_TEXT
#define ENUM6030_04_TEXT ENUM5895_04_TEXT
#define ENUM6030_05_TEXT ENUM5895_05_TEXT
#define ENUM6030_08_TEXT ENUM5895_08_TEXT
#define ENUM6030_09_TEXT ENUM5890_01_TEXT
#define ENUM6030_0a_TEXT ENUM5890_02_TEXT
#define ENUM6030_0b_TEXT ENUM5895_0b_TEXT
#define ENUM6030_0c_TEXT ENUM5890_03_TEXT
#define ENUM6030_0d_TEXT ENUM5890_04_TEXT
#define ENUM6030_0e_TEXT ENUM5890_05_TEXT
#define ENUM6030_0f_TEXT ENUM5890_06_TEXT
#define ENUM6030_10_TEXT ENUM5890_07_TEXT
#define ENUM6030_11_TEXT ENUM5895_11_TEXT
#define ENUM6030_12_TEXT ENUM5895_12_TEXT
#define ENUM6030_13_TEXT ENUM5895_13_TEXT
#define ENUM6030_14_TEXT ENUM5890_0b_TEXT
#define ENUM6030_15_TEXT ENUM5890_0c_TEXT
#define ENUM6030_16_TEXT ENUM5890_0d_TEXT
#define ENUM6030_17_TEXT ENUM5890_0e_TEXT
#define ENUM6030_18_TEXT ENUM5890_0f_TEXT
#define ENUM6030_19_TEXT ENUM5890_10_TEXT
#define ENUM6030_1a_TEXT ENUM5890_11_TEXT
#define ENUM6030_1b_TEXT ENUM5890_12_TEXT
#define ENUM6030_1c_TEXT ENUM5890_13_TEXT
#define ENUM6030_1d_TEXT ENUM5890_14_TEXT
#define ENUM6030_1e_TEXT ENUM5890_15_TEXT
#define ENUM6030_1f_TEXT ENUM5890_16_TEXT
#define ENUM6030_20_TEXT ENUM5890_17_TEXT
#define ENUM6030_21_TEXT ENUM5895_20_TEXT
#define ENUM6030_22_TEXT ENUM5895_08_TEXT
#define ENUM6030_23_TEXT ENUM5895_22_TEXT
#define ENUM6030_24_TEXT STR8470_TEXT
#define ENUM6030_25_TEXT ENUM5895_24_TEXT
#define ENUM6030_26_TEXT ENUM5895_25_TEXT
#define ENUM6030_27_TEXT ENUM5890_19_TEXT
#define ENUM6030_28_TEXT ENUM5890_1a_TEXT
#define ENUM6030_29_TEXT ENUM5890_1b_TEXT
#define ENUM6030_2a_TEXT ENUM5890_1c_TEXT
#define ENUM6030_2b_TEXT ENUM5890_1d_TEXT
#define ENUM6030_2c_TEXT ENUM5895_2b_TEXT
#define ENUM6030_2d_TEXT ENUM5895_2c_TEXT
#define ENUM6030_2e_TEXT ENUM5895_2d_TEXT
#define ENUM6040_00_TEXT ENUM1630_02_TEXT
#define ENUM6040_01_TEXT ENUM4133_02_TEXT
#define ENUM6040_02_TEXT ENUM5930_02_TEXT
#define ENUM6040_04_TEXT ENUM5930_04_TEXT
#define ENUM6040_05_TEXT ENUM4133_03_TEXT
#define ENUM6040_06_TEXT ENUM4133_04_TEXT
#define ENUM6040_07_TEXT ENUM5930_07_TEXT
#define ENUM6040_08_TEXT ENUM5930_08_TEXT
#define ENUM6040_09_TEXT ENUM5930_09_TEXT
#define ENUM6040_0a_TEXT ENUM5930_0a_TEXT
#define ENUM6040_0b_TEXT ENUM5930_0b_TEXT
#define ENUM6040_0c_TEXT ENUM5930_0c_TEXT
#define ENUM6040_0d_TEXT ENUM5930_0d_TEXT
#define ENUM6040_0e_TEXT ENUM5930_0e_TEXT
#define ENUM6040_0f_TEXT ENUM5930_0f_TEXT
#define ENUM6040_10_TEXT ENUM5930_10_TEXT
#define ENUM6040_11_TEXT ENUM5930_11_TEXT
#define ENUM6054_00_TEXT ENUM48_00_TEXT
#define ENUM6054_02_TEXT ENUM5950_4_02_TEXT
#define ENUM6054_07_TEXT STR2201_TEXT
#define ENUM6054_0b_TEXT ENUM5950_4_0b_TEXT
#define ENUM6054_0c_TEXT STR4141_TEXT
#define ENUM6054_0e_TEXT ENUM5950_4_0e_TEXT
#define ENUM6054_0f_TEXT ENUM5950_4_0f_TEXT
#define ENUM6054_10_TEXT ENUM5950_4_10_TEXT
#define ENUM6054_11_TEXT ENUM5950_4_11_TEXT
#define ENUM6054_12_TEXT ENUM5950_4_12_TEXT
#define ENUM6054_13_TEXT ENUM5950_4_13_TEXT
#define ENUM6054_14_TEXT ENUM5950_4_14_TEXT
#define ENUM6054_16_TEXT ENUM5950_4_16_TEXT
#define ENUM6054_19_TEXT ENUM6024_19_TEXT
#define ENUM6054_1d_TEXT ENUM2480_00_TEXT
#define ENUM6054_1f_TEXT ENUM5950_4_1f_TEXT
#define ENUM6054_20_TEXT ENUM5950_4_20_TEXT
#define ENUM6054_36_TEXT ENUM5950_0e_TEXT
#define ENUM6070_00_TEXT ENUM2320_02_TEXT
#define ENUM6085_00_TEXT ENUM48_00_TEXT
#define ENUM6085_01_TEXT ENUM5890_05_TEXT
#define ENUM6085_02_TEXT STR8820_TEXT
#define ENUM6085_04_TEXT ENUM5890_21_TEXT
#define ENUM6085_05_TEXT ENUM5890_22_TEXT
#define ENUM6085_07_TEXT ENUM5890_03_TEXT
#define ENUM6131_00_TEXT ENUM780_00_TEXT
#define ENUM6131_01_TEXT ENUM2205_01_TEXT
#define ENUM6131_02_TEXT ENUM1600_01_TEXT
#define ENUM6136_03_TEXT ENUM_CAT_0c_TEXT
#define ENUM6148_00_TEXT ENUM48_00_TEXT
#define ENUM6240_2_00_TEXT ENUM48_00_TEXT
#define ENUM6240_2_01_TEXT STR8304_TEXT
#define ENUM6240_2_02_TEXT STR8820_TEXT
#define ENUM6240_2_03_TEXT ENUM5890_1c_TEXT
#define ENUM6240_2_04_TEXT ENUM5890_21_TEXT
#define ENUM6240_2_05_TEXT ENUM5890_22_TEXT
#define ENUM6240_2_06_TEXT ENUM6085_06_TEXT
#define ENUM6240_2_07_TEXT ENUM5890_03_TEXT
#define ENUM6240_2_09_TEXT ENUM5890_13_TEXT
#define ENUM6240_2_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6240_2_0e_TEXT ENUM5890_06_TEXT
#define ENUM6240_2_1e_TEXT STR8326_TEXT
#define ENUM6243_00_TEXT ENUM48_00_TEXT
#define ENUM6243_01_TEXT STR8304_TEXT
#define ENUM6243_02_TEXT STR8820_TEXT
#define ENUM6243_03_TEXT ENUM5890_1c_TEXT
#define ENUM6243_04_TEXT ENUM5890_21_TEXT
#define ENUM6243_05_TEXT ENUM5890_22_TEXT
#define ENUM6243_06_TEXT ENUM6085_06_TEXT
#define ENUM6243_07_TEXT ENUM5890_03_TEXT
#define ENUM6243_08_TEXT ENUM6240_2_08_TEXT
#define ENUM6243_09_TEXT ENUM5890_13_TEXT
#define ENUM6243_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM6243_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM6243_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6243_0e_TEXT ENUM5890_06_TEXT
#define ENUM6243_1e_TEXT STR8326_TEXT
#define ENUM6246_00_TEXT ENUM48_00_TEXT
#define ENUM6246_01_TEXT STR8304_TEXT
#define ENUM6246_02_TEXT STR8820_TEXT
#define ENUM6246_03_TEXT ENUM5890_1c_TEXT
#define ENUM6246_04_TEXT ENUM5890_21_TEXT
#define ENUM6246_05_TEXT ENUM5890_22_TEXT
#define ENUM6246_06_TEXT ENUM6085_06_TEXT
#define ENUM6246_07_TEXT ENUM5890_03_TEXT
#define ENUM6246_08_TEXT ENUM6240_2_08_TEXT
#define ENUM6246_09_TEXT ENUM5890_13_TEXT
#define ENUM6246_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM6246_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM6246_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6246_0e_TEXT ENUM5890_06_TEXT
#define ENUM6246_1e_TEXT STR8326_TEXT
#define ENUM6249_00_TEXT ENUM48_00_TEXT
#define ENUM6249_01_TEXT STR8304_TEXT
#define ENUM6249_02_TEXT STR8820_TEXT
#define ENUM6249_03_TEXT ENUM5890_1c_TEXT
#define ENUM6249_04_TEXT ENUM5890_21_TEXT
#define ENUM6249_05_TEXT ENUM5890_22_TEXT
#define ENUM6249_06_TEXT ENUM6085_06_TEXT
#define ENUM6249_07_TEXT ENUM5890_03_TEXT
#define ENUM6249_08_TEXT ENUM6240_2_08_TEXT
#define ENUM6249_09_TEXT ENUM5890_13_TEXT
#define ENUM6249_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM6249_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM6249_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6249_0e_TEXT ENUM5890_06_TEXT
#define ENUM6249_1e_TEXT STR8326_TEXT
#define ENUM6252_00_TEXT ENUM48_00_TEXT
#define ENUM6252_01_TEXT STR8304_TEXT
#define ENUM6252_02_TEXT STR8820_TEXT
#define ENUM6252_03_TEXT ENUM5890_1c_TEXT
#define ENUM6252_04_TEXT ENUM5890_21_TEXT
#define ENUM6252_05_TEXT ENUM5890_22_TEXT
#define ENUM6252_06_TEXT ENUM6085_06_TEXT
#define ENUM6252_07_TEXT ENUM5890_03_TEXT
#define ENUM6252_08_TEXT ENUM6240_2_08_TEXT
#define ENUM6252_09_TEXT ENUM5890_13_TEXT
#define ENUM6252_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM6252_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM6252_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6252_0e_TEXT ENUM5890_06_TEXT
#define ENUM6252_1e_TEXT STR8326_TEXT
#define ENUM6255_00_TEXT ENUM48_00_TEXT
#define ENUM6255_01_TEXT STR8304_TEXT
#define ENUM6255_02_TEXT STR8820_TEXT
#define ENUM6255_03_TEXT ENUM5890_1c_TEXT
#define ENUM6255_04_TEXT ENUM5890_21_TEXT
#define ENUM6255_05_TEXT ENUM5890_22_TEXT
#define ENUM6255_06_TEXT ENUM6085_06_TEXT
#define ENUM6255_07_TEXT ENUM5890_03_TEXT
#define ENUM6255_08_TEXT ENUM6240_2_08_TEXT
#define ENUM6255_09_TEXT ENUM5890_13_TEXT
#define ENUM6255_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM6255_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM6255_0d_TEXT ENUM5890_0f_TEXT
#define ENUM6255_0e_TEXT ENUM5890_06_TEXT
#define ENUM6255_1e_TEXT STR8326_TEXT
#define ENUM6272_00_TEXT ENUM1630_02_TEXT
#define ENUM6272_06_TEXT ENUM4133_04_TEXT
#define ENUM6272_07_TEXT ENUM5930_07_TEXT
#define ENUM6272_08_TEXT ENUM5930_08_TEXT
#define ENUM6272_09_TEXT ENUM5930_09_TEXT
#define ENUM6272_0B_TEXT ENUM5930_0b_TEXT
#define ENUM6272_0C_TEXT ENUM5930_0c_TEXT
#define ENUM6272_0D_TEXT ENUM5930_0d_TEXT
#define ENUM6272_0E_TEXT ENUM5930_0e_TEXT
#define ENUM6272_18_TEXT ENUM4133_01_TEXT
#define ENUM6351_00_TEXT ENUM48_00_TEXT
#define ENUM6375_00_TEXT ENUM1630_02_TEXT
#define ENUM6375_02_TEXT ENUM5895_04_TEXT
#define ENUM6375_03_TEXT ENUM5895_05_TEXT
#define ENUM6375_04_TEXT ENUM5895_06_TEXT
#define ENUM6375_05_TEXT ENUM5895_07_TEXT
#define ENUM6375_06_TEXT ENUM5895_08_TEXT
#define ENUM6375_07_TEXT ENUM5890_0d_TEXT
#define ENUM6375_08_TEXT ENUM5890_19_TEXT
#define ENUM6375_09_TEXT ENUM5890_0e_TEXT
#define ENUM6375_0a_TEXT ENUM5890_02_TEXT
#define ENUM6375_0b_TEXT ENUM5890_01_TEXT
#define ENUM6375_0c_TEXT ENUM5890_1a_TEXT
#define ENUM6375_0d_TEXT ENUM5890_1c_TEXT
#define ENUM6375_0e_TEXT ENUM5890_1b_TEXT
#define ENUM6375_0f_TEXT ENUM5890_03_TEXT
#define ENUM6375_10_TEXT ENUM5890_15_TEXT
#define ENUM6375_11_TEXT ENUM5890_12_TEXT
#define ENUM6375_12_TEXT ENUM5890_13_TEXT
#define ENUM6375_13_TEXT ENUM5890_14_TEXT
#define ENUM6375_14_TEXT ENUM5895_0b_TEXT
#define ENUM6375_18_TEXT ENUM6085_06_TEXT
#define ENUM6375_19_TEXT ENUM5895_11_TEXT
#define ENUM6375_1a_TEXT ENUM5895_12_TEXT
#define ENUM6375_1d_TEXT ENUM5895_25_TEXT
#define ENUM6375_1e_TEXT ENUM5890_1d_TEXT
#define ENUM6375_1f_TEXT ENUM5895_2b_TEXT
#define ENUM6375_20_TEXT ENUM5890_07_TEXT
#define ENUM6375_21_TEXT ENUM5890_10_TEXT
#define ENUM6375_22_TEXT ENUM5890_21_TEXT
#define ENUM6375_23_TEXT ENUM5895_02_TEXT
#define ENUM6375_25_TEXT ENUM5895_24_TEXT
#define ENUM6375_26_TEXT ENUM5895_2c_TEXT
#define ENUM6375_27_TEXT ENUM5895_2d_TEXT
#define ENUM6375_29_TEXT ENUM6085_05_TEXT
#define ENUM6375_2a_TEXT ENUM5890_24_TEXT
#define ENUM6375_2b_TEXT ENUM6375_28_TEXT
#define ENUM6375_2c_TEXT ENUM6375_28_TEXT
#define ENUM6375_32_TEXT ENUM5890_0f_TEXT
#define ENUM6375_33_TEXT ENUM5890_17_TEXT
#define ENUM6375_34_TEXT ENUM5890_18_TEXT
#define ENUM6420_00_TEXT ENUM5700_05_TEXT
#define ENUM6420_06_TEXT ENUM5700_05_TEXT
#define ENUM6420_07_TEXT ENUM5700_05_TEXT
#define ENUM6420_08_TEXT ENUM5700_05_TEXT
#define ENUM6420_09_TEXT ENUM5700_05_TEXT
#define ENUM6420_0a_TEXT ENUM5700_05_TEXT
#define ENUM6420_0c_TEXT ENUM5700_05_TEXT
#define ENUM6420_0d_TEXT ENUM5700_05_TEXT
#define ENUM6604_00_TEXT ENUM780_00_TEXT
#define ENUM6604_01_TEXT ENUM5040_02_TEXT
//#define ENUM6620_ff_TEXT ENUM6620_01_TEXT
//#define ENUM6621_ff_TEXT ENUM6621_01_TEXT
#define ENUM6630_01_TEXT ENUM861_02_TEXT
#define ENUM6630_02_TEXT ENUM5040_02_TEXT
#define ENUM6631_00_TEXT ENUM780_00_TEXT
#define ENUM6631_01_TEXT ENUM2205_01_TEXT
#define ENUM6631_02_TEXT ENUM1600_01_TEXT
#define ENUM6653_02_TEXT ENUM48_00_TEXT
#define ENUM6670_00_TEXT ENUM2320_02_TEXT
#define ENUM6670_01_TEXT ENUM6070_01_TEXT
#define ENUM6670_02_TEXT ENUM6070_02_TEXT
#define ENUM6706_00_TEXT ENUM2206_01_TEXT
#define ENUM6706_01_TEXT ENUM2480_00_TEXT
#define ENUM6706_63_TEXT ENUM2480_ff_TEXT
#define ENUM6706_0a_TEXT ENUM861_01_TEXT

#define ENUM7142_01_TEXT ENUM850_05_TEXT
#define ENUM7142_02_TEXT ENUM5040_02_TEXT
#define ENUM7147_00_TEXT ENUM48_00_TEXT
#define ENUM7244_01_TEXT ENUM3095_01_TEXT
#define ENUM7244_02_TEXT ENUM3095_02_TEXT
#define ENUM7244_03_TEXT ENUM3095_03_TEXT
#define ENUM7244_04_TEXT ENUM3095_04_TEXT
#define ENUM7244_05_TEXT ENUM3095_0b_TEXT
#define ENUM7300_00_TEXT ENUM5890_2_00_TEXT
#define ENUM7300_01_TEXT ENUM6020_01_TEXT
#define ENUM7300_02_TEXT ENUM_CAT_11_TEXT
#define ENUM7300_03_TEXT ENUM_CAT_14_TEXT
#define ENUM7300_04_TEXT STR5721_TEXT
#define ENUM7300_05_TEXT ENUM6014_02_TEXT
#define ENUM7300_06_TEXT ENUM6020_04_TEXT
#define ENUM7300_07_TEXT ENUM_CAT_20_TEXT
#define ENUM7300_0a_TEXT ENUM6014_06_TEXT
#define ENUM7300_0b_TEXT ENUM_CAT_12_TEXT
#define ENUM7300_0d_TEXT ENUM_CAT_2c_TEXT
#define ENUM7301_00_TEXT ENUM1630_02_TEXT
#define ENUM7301_01_TEXT ENUM5890_01_TEXT
#define ENUM7301_02_TEXT STR8821_TEXT
#define ENUM7301_04_TEXT ENUM5896_15_TEXT
#define ENUM7301_05_TEXT STR8304_TEXT
#define ENUM7301_07_TEXT ENUM5890_07_TEXT
#define ENUM7301_0b_TEXT ENUM6085_06_TEXT
#define ENUM7301_0c_TEXT ENUM5896_16_TEXT
#define ENUM7301_0d_TEXT ENUM5890_0d_TEXT
#define ENUM7301_0e_TEXT ENUM5890_0e_TEXT
#define ENUM7301_10_TEXT ENUM5890_10_TEXT
#define ENUM7301_14_TEXT ENUM6240_2_0a_TEXT
#define ENUM7301_16_TEXT ENUM6375_17_TEXT
#define ENUM7301_19_TEXT ENUM5890_19_TEXT
#define ENUM7301_1b_TEXT ENUM5890_1b_TEXT
#define ENUM7301_1c_TEXT ENUM5890_1c_TEXT
#define ENUM7301_1d_TEXT ENUM5890_1d_TEXT
#define ENUM7301_21_TEXT ENUM5890_21_TEXT
#define ENUM7301_22_TEXT ENUM5890_22_TEXT
#define ENUM7301_28_TEXT ENUM5890_28_TEXT
#define ENUM7301_29_TEXT ENUM5890_29_TEXT
#define ENUM7301_2b_TEXT ENUM5890_2b_TEXT
#define ENUM7301_2d_TEXT ENUM5896_3b_TEXT
#define ENUM7301_2e_TEXT ENUM5896_3c_TEXT
#define ENUM7302_00_TEXT ENUM1630_02_TEXT
#define ENUM7302_01_TEXT ENUM5890_01_TEXT
#define ENUM7302_02_TEXT STR8821_TEXT
#define ENUM7302_04_TEXT ENUM7301_04_TEXT
#define ENUM7302_05_TEXT STR8304_TEXT
#define ENUM7302_07_TEXT ENUM5890_07_TEXT
#define ENUM7302_0b_TEXT ENUM6085_06_TEXT
#define ENUM7302_0c_TEXT ENUM7301_0c_TEXT
#define ENUM7302_0d_TEXT ENUM5890_0d_TEXT
#define ENUM7302_0e_TEXT ENUM5890_0e_TEXT
#define ENUM7302_10_TEXT ENUM5890_10_TEXT
#define ENUM7302_14_TEXT ENUM6240_2_0a_TEXT
#define ENUM7302_16_TEXT ENUM6375_17_TEXT
#define ENUM7302_19_TEXT ENUM5890_19_TEXT
#define ENUM7302_1b_TEXT ENUM5890_1b_TEXT
#define ENUM7302_1c_TEXT ENUM5890_1c_TEXT
#define ENUM7302_1d_TEXT ENUM5890_1d_TEXT
#define ENUM7302_21_TEXT ENUM5890_21_TEXT
#define ENUM7302_22_TEXT ENUM5890_22_TEXT
#define ENUM7302_28_TEXT ENUM5890_28_TEXT
#define ENUM7302_29_TEXT ENUM5890_29_TEXT
#define ENUM7302_2b_TEXT ENUM5890_2b_TEXT
#define ENUM7302_2d_TEXT ENUM7301_2d_TEXT
#define ENUM7302_2e_TEXT ENUM7301_2e_TEXT
#define ENUM7307_00_TEXT ENUM1630_02_TEXT
#define ENUM7307_01_TEXT ENUM4133_02_TEXT
#define ENUM7307_08_TEXT ENUM5930_08_TEXT
#define ENUM7307_0a_TEXT ENUM5930_0a_TEXT
#define ENUM7307_0c_TEXT ENUM5930_0c_TEXT
#define ENUM7307_0d_TEXT ENUM5930_0d_TEXT
#define ENUM7307_0e_TEXT ENUM5930_0e_TEXT
#define ENUM7307_10_TEXT ENUM5930_10_TEXT
#define ENUM7307_11_TEXT ENUM5930_11_TEXT
#define ENUM7321_00_TEXT ENUM48_00_TEXT
#define ENUM7321_02_TEXT ENUM5950_4_02_TEXT
#define ENUM7321_03_TEXT ENUM6054_03_TEXT
#define ENUM7321_04_TEXT ENUM6054_04_TEXT
#define ENUM7321_05_TEXT ENUM6054_05_TEXT
#define ENUM7321_06_TEXT ENUM6054_06_TEXT
#define ENUM7321_07_TEXT STR2201_TEXT
#define ENUM7321_08_TEXT ENUM6054_08_TEXT
#define ENUM7321_09_TEXT ENUM6054_09_TEXT
#define ENUM7321_0a_TEXT ENUM6054_0a_TEXT
#define ENUM7321_0b_TEXT ENUM5950_4_0b_TEXT
#define ENUM7321_0c_TEXT STR4141_TEXT
#define ENUM7321_0e_TEXT ENUM5950_4_0e_TEXT
#define ENUM7321_0f_TEXT ENUM5950_4_0f_TEXT
#define ENUM7321_10_TEXT ENUM5950_4_10_TEXT
#define ENUM7321_11_TEXT ENUM5950_4_11_TEXT
#define ENUM7321_12_TEXT ENUM5950_4_12_TEXT
#define ENUM7321_13_TEXT ENUM5950_4_13_TEXT
#define ENUM7321_14_TEXT ENUM5950_4_14_TEXT
#define ENUM7321_19_TEXT ENUM6024_19_TEXT
#define ENUM7321_1d_TEXT ENUM2480_00_TEXT
#define ENUM7321_33_TEXT ENUM6054_33_TEXT
#define ENUM7321_34_TEXT ENUM6054_34_TEXT
#define ENUM7321_3a_TEXT ENUM6054_3a_TEXT
#define ENUM7322_00_TEXT ENUM6055_00_TEXT
#define ENUM7322_01_TEXT ENUM6055_01_TEXT
#define ENUM7348_00_TEXT ENUM48_00_TEXT
#define ENUM7348_01_TEXT STR8304_TEXT
#define ENUM7348_02_TEXT STR8820_TEXT
#define ENUM7348_03_TEXT ENUM5890_1c_TEXT
#define ENUM7348_04_TEXT ENUM5890_21_TEXT
#define ENUM7348_05_TEXT ENUM5890_22_TEXT
#define ENUM7348_06_TEXT ENUM6085_06_TEXT
#define ENUM7348_07_TEXT ENUM5890_03_TEXT
#define ENUM7348_08_TEXT ENUM6240_2_08_TEXT
#define ENUM7348_09_TEXT ENUM5890_13_TEXT
#define ENUM7348_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM7348_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM7348_0d_TEXT ENUM5890_0f_TEXT
#define ENUM7348_0e_TEXT ENUM5890_06_TEXT
#define ENUM7348_1e_TEXT STR8326_TEXT
#define ENUM7348_2_00_TEXT ENUM48_00_TEXT
#define ENUM7348_2_01_TEXT ENUM5896_24_TEXT
#define ENUM7348_2_02_TEXT STR8820_TEXT
#define ENUM7348_2_03_TEXT ENUM5890_1c_TEXT
#define ENUM7348_2_04_TEXT ENUM5890_21_TEXT
#define ENUM7348_2_05_TEXT ENUM5890_22_TEXT
#define ENUM7348_2_06_TEXT ENUM5896_18_TEXT
#define ENUM7348_2_07_TEXT ENUM5890_03_TEXT
#define ENUM7348_2_08_TEXT ENUM6240_2_08_TEXT
#define ENUM7348_2_09_TEXT ENUM5890_13_TEXT
#define ENUM7348_2_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM7348_2_0b_TEXT ENUM5890_15_TEXT
#define ENUM7348_2_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM7348_2_0d_TEXT ENUM5890_0f_TEXT
#define ENUM7348_2_0f_TEXT STR8406_TEXT
#define ENUM7348_2_1a_TEXT ENUM2790_01_TEXT
#define ENUM7348_2_1b_TEXT ENUM6070_01_TEXT
#define ENUM7348_2_1c_TEXT ENUM6070_02_TEXT
#define ENUM7348_2_1d_TEXT STR6627_TEXT
#define ENUM7348_2_1e_TEXT ENUM5909_1e_TEXT
#define ENUM7348_2_21_TEXT ENUM5909_21_TEXT
#define ENUM7348_2_22_TEXT ENUM5909_22_TEXT
#define ENUM7348_2_23_TEXT ENUM5909_23_TEXT
#define ENUM7375_00_TEXT ENUM5890_2_00_TEXT
#define ENUM7375_01_TEXT ENUM6020_01_TEXT
#define ENUM7375_02_TEXT ENUM_CAT_11_TEXT
#define ENUM7375_03_TEXT ENUM_CAT_14_TEXT
#define ENUM7375_04_TEXT STR5721_TEXT
#define ENUM7375_05_TEXT ENUM6014_02_TEXT
#define ENUM7375_06_TEXT ENUM6020_04_TEXT
#define ENUM7375_07_TEXT ENUM_CAT_20_TEXT
#define ENUM7375_08_TEXT ENUM7300_08_TEXT
#define ENUM7375_09_TEXT ENUM7300_09_TEXT
#define ENUM7375_0a_TEXT ENUM6014_06_TEXT
#define ENUM7375_0b_TEXT ENUM_CAT_12_TEXT
#define ENUM7375_0c_TEXT ENUM7300_0c_TEXT
#define ENUM7375_0d_TEXT ENUM_CAT_2c_TEXT
#define ENUM7375_00_TEXT ENUM5890_2_00_TEXT
#define ENUM7375_01_TEXT ENUM6020_01_TEXT
#define ENUM7375_02_TEXT ENUM_CAT_11_TEXT
#define ENUM7375_03_TEXT ENUM_CAT_14_TEXT
#define ENUM7375_04_TEXT STR5721_TEXT
#define ENUM7375_06_TEXT ENUM6020_04_TEXT
#define ENUM7375_07_TEXT ENUM_CAT_20_TEXT
#define ENUM7375_08_TEXT ENUM7300_08_TEXT
#define ENUM7375_09_TEXT ENUM7300_09_TEXT
#define ENUM7375_0b_TEXT ENUM_CAT_12_TEXT
#define ENUM7375_0c_TEXT ENUM7300_0c_TEXT
#define ENUM7375_0d_TEXT ENUM_CAT_2c_TEXT
#define ENUM7375_10_TEXT ENUM_CAT_15_TEXT
#define ENUM7375_11_TEXT ENUM7300_11_TEXT
#define ENUM7375_14_TEXT ENUM7300_14_TEXT
#define ENUM7376_00_TEXT ENUM1630_02_TEXT
#define ENUM7376_01_TEXT ENUM5890_01_TEXT
#define ENUM7376_02_TEXT ENUM5890_02_TEXT
#define ENUM7376_03_TEXT ENUM5890_03_TEXT
#define ENUM7376_04_TEXT ENUM6375_15_TEXT
#define ENUM7376_05_TEXT ENUM5890_05_TEXT
#define ENUM7376_06_TEXT ENUM5890_06_TEXT
#define ENUM7376_07_TEXT ENUM5890_07_TEXT
#define ENUM7376_08_TEXT ENUM5890_08_TEXT
#define ENUM7376_09_TEXT ENUM5890_09_TEXT
#define ENUM7376_0a_TEXT ENUM5890_0a_TEXT
#define ENUM7376_0b_TEXT ENUM5890_0b_TEXT
#define ENUM7376_0c_TEXT ENUM5890_0c_TEXT
#define ENUM7376_0d_TEXT ENUM5890_0d_TEXT
#define ENUM7376_0e_TEXT ENUM5890_0e_TEXT
#define ENUM7376_0f_TEXT ENUM5890_0f_TEXT
#define ENUM7376_10_TEXT ENUM5890_10_TEXT
#define ENUM7376_11_TEXT ENUM5890_11_TEXT
#define ENUM7376_12_TEXT ENUM5890_12_TEXT
#define ENUM7376_13_TEXT ENUM5890_13_TEXT
#define ENUM7376_14_TEXT ENUM5890_14_TEXT
#define ENUM7376_15_TEXT ENUM5890_15_TEXT
#define ENUM7376_16_TEXT ENUM5890_16_TEXT
#define ENUM7376_17_TEXT ENUM5890_17_TEXT
#define ENUM7376_19_TEXT ENUM5890_19_TEXT
#define ENUM7376_1a_TEXT ENUM5890_1a_TEXT
#define ENUM7376_1b_TEXT ENUM5890_1b_TEXT
#define ENUM7376_1c_TEXT ENUM5890_1c_TEXT
#define ENUM7376_1d_TEXT ENUM5890_1d_TEXT
#define ENUM7376_21_TEXT ENUM5890_21_TEXT
#define ENUM7376_28_TEXT ENUM5890_28_TEXT
#define ENUM7376_29_TEXT ENUM5890_29_TEXT

#define ENUM7450_00_TEXT ENUM5890_2_00_TEXT
#define ENUM7450_01_TEXT ENUM6020_01_TEXT
#define ENUM7450_02_TEXT ENUM_CAT_11_TEXT
#define ENUM7450_03_TEXT ENUM_CAT_14_TEXT
#define ENUM7450_04_TEXT STR5721_TEXT
#define ENUM7450_05_TEXT ENUM6014_02_TEXT
#define ENUM7450_06_TEXT ENUM6020_04_TEXT
#define ENUM7450_07_TEXT ENUM_CAT_20_TEXT
#define ENUM7450_08_TEXT ENUM7300_08_TEXT
#define ENUM7450_09_TEXT ENUM7300_09_TEXT
#define ENUM7450_0a_TEXT ENUM6014_06_TEXT
#define ENUM7450_0b_TEXT ENUM_CAT_12_TEXT
#define ENUM7450_0c_TEXT ENUM7300_0c_TEXT
#define ENUM7450_0d_TEXT ENUM_CAT_2c_TEXT
#define ENUM7472_00_TEXT ENUM6055_00_TEXT
#define ENUM7472_01_TEXT ENUM6055_01_TEXT
#define ENUM7492_00_TEXT ENUM48_00_TEXT
#define ENUM7492_19_TEXT ENUM6024_19_TEXT
#define ENUM7498_00_TEXT ENUM48_00_TEXT
#define ENUM7498_01_TEXT STR8304_TEXT
#define ENUM7498_02_TEXT STR8820_TEXT
#define ENUM7498_03_TEXT ENUM5890_1c_TEXT
#define ENUM7498_04_TEXT ENUM5890_21_TEXT
#define ENUM7498_05_TEXT ENUM5890_22_TEXT
#define ENUM7498_06_TEXT ENUM6085_06_TEXT
#define ENUM7498_07_TEXT ENUM5890_03_TEXT
#define ENUM7498_08_TEXT ENUM6240_2_08_TEXT
#define ENUM7498_09_TEXT ENUM5890_13_TEXT
#define ENUM7498_0a_TEXT ENUM6240_2_0a_TEXT
#define ENUM7498_0c_TEXT ENUM6240_2_0c_TEXT
#define ENUM7498_0d_TEXT ENUM5890_0f_TEXT
#define ENUM7498_0e_TEXT ENUM5890_06_TEXT
#define ENUM7450_00_TEXT ENUM5890_2_00_TEXT
#define ENUM7450_01_TEXT ENUM6020_01_TEXT
#define ENUM7450_02_TEXT ENUM_CAT_11_TEXT
#define ENUM7450_03_TEXT ENUM_CAT_14_TEXT
#define ENUM7450_04_TEXT STR5721_TEXT
#define ENUM7450_05_TEXT ENUM6014_02_TEXT
#define ENUM7450_06_TEXT ENUM6020_04_TEXT
#define ENUM7450_07_TEXT ENUM_CAT_20_TEXT
#define ENUM7450_08_TEXT ENUM7300_08_TEXT
#define ENUM7450_09_TEXT ENUM7300_09_TEXT
#define ENUM7450_0a_TEXT ENUM6014_06_TEXT
#define ENUM7450_0b_TEXT ENUM_CAT_12_TEXT
#define ENUM7450_0c_TEXT ENUM7300_0c_TEXT
#define ENUM7450_0d_TEXT ENUM_CAT_2c_TEXT

#define ENUM7700_02_TEXT ENUM6040_03_TEXT
#define ENUM7700_03_TEXT ENUM6040_03_TEXT
#define ENUM7700_04_TEXT ENUM6085_02_TEXT
#define ENUM7700_05_TEXT STR8730_TEXT
#define ENUM7700_06_TEXT STR8731_TEXT
#define ENUM7700_07_TEXT STR8732_TEXT
#define ENUM7700_0b_TEXT STR5890_TEXT
#define ENUM7700_0c_TEXT STR5891_TEXT
#define ENUM7700_0d_TEXT STR5892_TEXT
#define ENUM7700_0e_TEXT STR5894_TEXT
#define ENUM7700_0f_TEXT STR6030_TEXT
#define ENUM7700_10_TEXT STR6031_TEXT
#define ENUM7700_11_TEXT STR6032_TEXT
#define ENUM7700_12_TEXT STR6033_TEXT
#define ENUM7700_13_TEXT STR6034_TEXT
#define ENUM7700_14_TEXT STR6035_TEXT
#define ENUM7717_00_TEXT ENUM1630_02_TEXT
#define ENUM7717_03_TEXT ENUM7999_03_TEXT
#define ENUM7717_04_TEXT ENUM7999_04_TEXT
#define ENUM7999_00_TEXT ENUM48_00_TEXT
#define ENUM7999_01_TEXT ENUM7717_01_TEXT
#define ENUM8000_00_TEXT ENUM6040_03_TEXT
#define ENUM8000_18_TEXT ENUM780_00_TEXT
#define ENUM8000_70_TEXT STR2262_TEXT
#define ENUM8000_71_TEXT STR770_TEXT
#define ENUM8000_76_TEXT ENUM702_00_TEXT
#define ENUM8000_7a_TEXT STR760_TEXT
#define ENUM8000_f8_TEXT STR809_TEXT
#define ENUM8003_00_TEXT ENUM6040_03_TEXT
#define ENUM8003_03_TEXT ENUM8000_03_TEXT
#define ENUM8003_04_TEXT ENUM8000_04_TEXT
#define ENUM8003_11_TEXT ENUM8000_11_TEXT
#define ENUM8003_18_TEXT ENUM8000_17_TEXT
#define ENUM8003_19_TEXT ENUM780_00_TEXT
#define ENUM8004_00_TEXT ENUM6040_03_TEXT
#define ENUM8004_04_TEXT ENUM8000_04_TEXT
#define ENUM8004_11_TEXT ENUM8000_11_TEXT
#define ENUM8004_17_TEXT ENUM8000_16_TEXT
#define ENUM8004_18_TEXT ENUM8000_17_TEXT
#define ENUM8004_19_TEXT MENU_TEXT_OFF
#define ENUM8004_75_TEXT ENUM8000_75_TEXT
#define ENUM8004_77_TEXT MENU_TEXT_OFF
#define ENUM8004_7a_TEXT STR760_TEXT
#define ENUM8004_88_TEXT STR947_TEXT
#define ENUM8004_95_TEXT ENUM8000_16_TEXT
#define ENUM8005_00_TEXT ENUM6040_03_TEXT
#define ENUM8005_02_TEXT ENUM8004_02_TEXT
#define ENUM8005_03_TEXT ENUM8000_03_TEXT
#define ENUM8005_04_TEXT ENUM8000_04_TEXT
#define ENUM8005_0a_TEXT ENUM2706_00_TEXT
#define ENUM8005_0f_TEXT ENUM2920_01_TEXT
#define ENUM8005_11_TEXT ENUM8000_11_TEXT
#define ENUM8005_12_TEXT ENUM130_01_TEXT
#define ENUM8005_13_TEXT ENUM2920_01_TEXT
#define ENUM8005_17_TEXT ENUM8000_16_TEXT
#define ENUM8005_18_TEXT ENUM8000_17_TEXT
#define ENUM8005_19_TEXT ENUM780_00_TEXT
#define ENUM8005_dc_TEXT ENUM_SWCODE_a9_TEXT
#define ENUM8006_00_TEXT ENUM6040_03_TEXT
#define ENUM8006_02_TEXT ENUM8005_02_TEXT
#define ENUM8006_0A_TEXT ENUM2706_00_TEXT
#define ENUM8006_11_TEXT ENUM8000_11_TEXT
#define ENUM8006_18_TEXT ENUM8000_17_TEXT
#define ENUM8006_19_TEXT ENUM780_00_TEXT
#define ENUM8006_1a_TEXT STR7141_TEXT
#define ENUM8006_27_TEXT STR2886_TEXT
#define ENUM8006_89_TEXT ENUM861_01_TEXT
#define ENUM8006_b0_TEXT ENUM8005_b0_TEXT
#define ENUM8006_c6_TEXT ENUM8005_c6_TEXT
#define ENUM8006_01_00_TEXT STR7153_TEXT
#define ENUM8007_00_TEXT ENUM6040_03_TEXT
#define ENUM8007_04_TEXT ENUM8000_04_TEXT
#define ENUM8007_02_TEXT ENUM8005_02_TEXT
#define ENUM8007_35_TEXT ENUM8003_35_TEXT
#define ENUM8007_38_TEXT ENUM8000_38_TEXT
#define ENUM8007_3b_TEXT ENUM8005_3b_TEXT
#define ENUM8008_00_TEXT ENUM6040_03_TEXT
#define ENUM8008_02_TEXT ENUM8005_02_TEXT
#define ENUM8008_04_TEXT ENUM8000_04_TEXT
#define ENUM8008_08_TEXT ENUM8005_08_TEXT
#define ENUM8008_09_TEXT ENUM8005_09_TEXT
#define ENUM8008_0a_TEXT ENUM2706_00_TEXT
#define ENUM8008_0b_TEXT ENUM8005_0b_TEXT
#define ENUM8008_0c_TEXT ENUM8005_0c_TEXT
#define ENUM8008_0d_TEXT ENUM8005_0d_TEXT
#define ENUM8008_0e_TEXT ENUM8005_0e_TEXT
#define ENUM8008_11_TEXT ENUM8000_11_TEXT
#define ENUM8008_12_TEXT ENUM130_01_TEXT
#define ENUM8008_13_TEXT ENUM2920_01_TEXT
#define ENUM8008_14_TEXT ENUM8005_14_TEXT
#define ENUM8008_15_TEXT ENUM8005_15_TEXT
#define ENUM8008_16_TEXT ENUM8005_16_TEXT
#define ENUM8008_17_TEXT ENUM8000_16_TEXT
#define ENUM8008_18_TEXT ENUM8000_17_TEXT
#define ENUM8008_19_TEXT ENUM780_00_TEXT
#define ENUM8008_38_TEXT ENUM8000_38_TEXT
#define ENUM8008_3a_TEXT ENUM8007_3a_TEXT
#define ENUM8008_3b_TEXT ENUM8005_3b_TEXT
#define ENUM8008_a6_TEXT ENUM8005_a6_TEXT
#define ENUM8008_a7_TEXT ENUM8005_a7_TEXT
#define ENUM8008_a8_TEXT ENUM8005_a8_TEXT
#define ENUM8008_a9_TEXT ENUM8005_a9_TEXT
#define ENUM8008_aa_TEXT ENUM8005_aa_TEXT
#define ENUM8008_ab_TEXT ENUM8005_ab_TEXT
#define ENUM8009_2_00_TEXT ENUM6040_03_TEXT
#define ENUM8009_2_01_TEXT ENUM2480_ff_TEXT
#define ENUM8009_2_02_TEXT ENUM2480_00_TEXT
#define ENUM8009_2_04_TEXT ENUM130_01_TEXT
#define ENUM8009_2_09_TEXT ENUM8009_09_TEXT
#define ENUM8009_2_12_TEXT ENUM130_01_TEXT
#define ENUM8009_2_D6_TEXT STR9518_TEXT
#define ENUM8009_2_D8_TEXT ENUM2206_01_TEXT
#define ENUM8009_00_TEXT ENUM8009_2_00_TEXT
#define ENUM8009_01_TEXT ENUM2480_ff_TEXT
#define ENUM8009_02_TEXT ENUM2480_00_TEXT
#define ENUM8009_09_TEXT ENUM6706_16_TEXT
#define ENUM8009_12_TEXT ENUM130_01_TEXT
#define ENUM8009_D6_TEXT ENUM8009_2_D6_TEXT
#define ENUM8009_DA_TEXT ENUM8009_2_DA_TEXT
#define ENUM8009_D7_TEXT ENUM8009_2_D7_TEXT
#define ENUM8009_D8_TEXT ENUM2206_01_TEXT
#define ENUM8009_D9_TEXT ENUM8009_2_D9_TEXT
#define ENUM8009_DB_TEXT ENUM8009_2_DB_TEXT
#define ENUM8010_00_TEXT ENUM6040_03_TEXT
#define ENUM8010_18_TEXT ENUM8000_17_TEXT
#define ENUM8010_35_TEXT ENUM8003_35_TEXT
#define ENUM8010_42_TEXT ENUM8003_42_TEXT
#define ENUM8010_43_TEXT ENUM8003_43_TEXT
#define ENUM8010_45_TEXT ENUM8003_45_TEXT
#define ENUM8010_46_TEXT ENUM8003_46_TEXT
#define ENUM8010_47_TEXT ENUM8003_47_TEXT
#define ENUM8010_4b_TEXT ENUM8003_4b_TEXT
#define ENUM8010_4d_TEXT ENUM8003_4d_TEXT
#define ENUM8010_51_TEXT ENUM8003_51_TEXT
#define ENUM8010_68_TEXT ENUM8000_68_TEXT
#define ENUM8010_87_TEXT ENUM8004_87_TEXT
#define ENUM8011_00_TEXT ENUM6040_03_TEXT
#define ENUM8011_02_TEXT ENUM8005_02_TEXT
#define ENUM8011_04_TEXT ENUM8000_04_TEXT
#define ENUM8011_4c_TEXT ENUM8010_4c_TEXT
#define ENUM8011_6a_TEXT ENUM8000_6a_TEXT
#define ENUM8011_6e_TEXT ENUM8000_6e_TEXT
#define ENUM8011_89_TEXT ENUM861_01_TEXT
#define ENUM8022_00_TEXT ENUM6040_03_TEXT
#define ENUM8022_02_TEXT ENUM8005_02_TEXT
#define ENUM8022_0a_TEXT ENUM8005_0a_TEXT
#define ENUM8022_11_TEXT ENUM8005_11_TEXT
#define ENUM8022_19_TEXT ENUM8005_19_TEXT
#define ENUM8022_3b_TEXT ENUM8005_3b_TEXT
#define ENUM8022_a6_TEXT ENUM8005_a6_TEXT
#define ENUM8022_a8_TEXT ENUM8005_a8_TEXT
#define ENUM8022_aa_TEXT ENUM8005_aa_TEXT
#define ENUM8022_ac_TEXT ENUM8005_ac_TEXT
#define ENUM8022_ad_TEXT ENUM8005_ad_TEXT
#define ENUM8022_ae_TEXT ENUM8005_ae_TEXT
#define ENUM8022_b0_TEXT ENUM8005_b0_TEXT
#define ENUM8022_c6_TEXT ENUM8005_c6_TEXT
#define ENUM8101_00_TEXT ENUM130_00_TEXT
#define ENUM8101_02_TEXT ENUM8000_04_TEXT
#define ENUM8101_04_TEXT ENUM8005_07_TEXT
#define ENUM8101_08_TEXT ENUM2920_01_TEXT
#define ENUM8304_00_TEXT ENUM780_00_TEXT
#define ENUM8304_01_TEXT ENUM1600_01_TEXT
#define ENUM8304_ff_TEXT ENUM1600_01_TEXT
#define ENUM8304_01_00_TEXT ENUM5890_2_00_TEXT
#define ENUM8749_01_TEXT ENUM2320_01_TEXT
#define ENUM9614_00_TEXT ENUM2206_00_TEXT
#define ENUM10100_01_TEXT ENUM_CAT_34_TEXT
#define ENUM14088_01_TEXT ENUM1630_00_TEXT
#define ENUM_ERROR_4d_TEXT ENUM_ERROR_49_TEXT
#define ENUM_ERROR_5d_TEXT ENUM130_03_TEXT
#define ENUM_ERROR_bc_TEXT ENUM8101_03_TEXT
#define ENUM_ERROR_e1_TEXT ENUM8006_b5_TEXT
#define ENUM_ERROR_e2_TEXT ENUM8006_b7_TEXT
#define ENUM_ERROR_e3_TEXT ENUM8006_b8_TEXT
#define ENUM_ERROR_e4_TEXT ENUM8006_1e_TEXT
#define ENUM_ERROR_e5_TEXT ENUM8006_1f_TEXT
#define ENUM_ERROR_e6_TEXT ENUM8006_b9_TEXT
#define ENUM_ERROR_01_51_TEXT ENUM_ERROR_01_4a_TEXT
#define ENUM_ERROR_01_81_TEXT ENUM8006_f6_TEXT
#define ENUM_SWCODE_6e_TEXT ENUM_ERROR_a1_TEXT
#define ENUM_SWCODE_01_03_TEXT ENUM_ERROR_99_TEXT
#define ENUM_SWCODE_02_09_TEXT ENUM_ERROR_8c_TEXT
#define ENUM_SWCODE_02_5a_TEXT ENUM_ERROR_b8_TEXT
#define ENUM_INTCODE_01_46_TEXT ENUM_INTCODE_01_45_TEXT
#define ENUM_INTCODE_01_47_TEXT ENUM_INTCODE_01_45_TEXT
#define ENUM_INTCODE_01_48_TEXT ENUM_INTCODE_01_45_TEXT
#define ENUM_INTCODE_01_49_TEXT ENUM_INTCODE_01_45_TEXT
#define ENUM_INTCODE_01_65_TEXT ENUM_INTCODE_dd_TEXT
#define ENUM_INTCODE_01_74_TEXT ENUM_INTCODE_01_73_TEXT

/*
#define WEEKDAY_MON_TEXT STR500_TEXT
#define WEEKDAY_TUE_TEXT STR501_TEXT
#define WEEKDAY_WED_TEXT STR502_TEXT
#define WEEKDAY_THU_TEXT STR503_TEXT
#define WEEKDAY_FRI_TEXT STR504_TEXT
#define WEEKDAY_SAT_TEXT STR505_TEXT
#define WEEKDAY_SUN_TEXT STR506_TEXT
*/

/* ENUM tables */

const char ENUM20[] = { // numerical values are hypothetical
"\x01 " ENUM20_01_TEXT "\0"
"\x02 " ENUM20_02_TEXT "\0"
"\x03 " ENUM20_03_TEXT "\0"
"\x04 " ENUM20_04_TEXT "\0"
"\x05 " ENUM20_05_TEXT "\0"
"\x06 " ENUM20_06_TEXT "\0"
"\x07 " ENUM20_07_TEXT "\0"
"\x07 " ENUM20_08_TEXT "\0"
"\x07 " ENUM20_09_TEXT "\0"
"\x08 " ENUM20_10_TEXT
};
// numerical values are hypothetical
const char ENUM22[] = {
"\x01 " ENUM22_01_TEXT "\0"
"\x02 " ENUM22_02_TEXT
};
const char ENUM23[] = {
"\x00 " "?" ENUM23_00_TEXT "\0"
"\x01 " "?" ENUM23_01_TEXT
};
const char ENUM28[] = {
"\x01 " ENUM28_01_TEXT "\0"
"\x02 " ENUM28_02_TEXT
};
const char ENUM29[] = {
"\x01 " ENUM29_01_TEXT "\0"
"\x02 " ENUM29_02_TEXT
};
const char ENUM40[] = {
"\x00 " "?" ENUM40_00_TEXT "\0"
"\x01 " "?" ENUM40_01_TEXT "\0"
"\x02 " "?" ENUM40_02_TEXT "\0"
"\x03 " "?" ENUM40_03_TEXT "\0"
"\x04 " "?" ENUM40_04_TEXT "\0"
"\x05 " ENUM40_05_TEXT
};
const char ENUM42[] = {	// numerical values are hypothetical
"\x00 " "?" ENUM42_00_TEXT "\0"
"\x01 " "?" ENUM42_01_TEXT "\0"
"\x02 " "?" ENUM42_02_TEXT "\0"
"\x03 " "?" ENUM42_03_TEXT
};
const char ENUM44[] = {
"\x01 " ENUM44_01_TEXT "\0"
"\x02 " ENUM44_02_TEXT
};
#define ENUM46 ENUM44
const char ENUM47[] = {  // NovoCondens WOB20C / WOB25C
"\x01 " "?" ENUM47_01_TEXT "\0"
"\x02 " "?" ENUM47_02_TEXT
};
// Nur am Raumgerät sichtbar, numerical values are hypothetical
const char ENUM48[] = {
"\x00 " "?" ENUM48_00_TEXT "\0"
"\x01 " "?" ENUM48_01_TEXT "\0"
"\x02 " "?" ENUM48_02_TEXT "\0"
"\x03 " "?" ENUM48_03_TEXT
};

const char ENUM130[] = {
"\x00 " ENUM130_00_TEXT "\0"
"\x01 " ENUM130_01_TEXT "\0"
"\x02 " "?" ENUM130_02_TEXT "\0"
"\x03 " "?" ENUM130_03_TEXT
};
#define ENUM131 ENUM130
#define ENUM132 ENUM130
#define ENUM133 ENUM130
#define ENUM134 ENUM130
#define ENUM135 ENUM130
#define ENUM136 ENUM130
#define ENUM137 ENUM130
#define ENUM138 ENUM130

/*
const char ENUM648[] = {
"\x00 " ENUM648_00_TEXT "\0"
"\x01 " ENUM648_01_TEXT
};
#define ENUM658 ENUM648
#define ENUM668 ENUM648
*/

const char ENUM648[] = {
"\x00 " ENUM648_00_TEXT "\0"
"\x01 " ENUM648_01_TEXT
};
#define ENUM665 ENUM648
#define ENUM682 ENUM648

const char ENUM700[] = {
"\x00 " ENUM700_00_TEXT "\0"
"\x01 " ENUM700_01_TEXT "\0"
"\x02 " ENUM700_02_TEXT "\0"
"\x03 " ENUM700_03_TEXT
};

// Parameters 702 and 703 are virtual Weishaupt parameters based on one and the same command ID, using new data type VT_CUSTOM_ENUM

const char ENUM702[] = {
"\x00\x01 " ENUM702_01_TEXT "\0"
"\x00\x02 " ENUM702_02_TEXT "\0"
"\x00\x00 " ENUM702_00_TEXT "\0"
"\x00\x03 " ENUM702_03_TEXT "\0"
"\x00\x04 " ENUM702_04_TEXT "\0"
"\x00\x05 " ENUM702_05_TEXT "\0"
"\x00\x06 " ENUM702_06_TEXT
};

const char ENUM703[] = {
"\x01\x00 " ENUM703_00_TEXT "\0"
"\x01\x01 " ENUM703_01_TEXT
};

// The following parameters are all listed as 701, moved to 704/705/706 respectively.
// 701 - Wärmer / Kälter
const char ENUM704[] = {
"\x00 " "?" ENUM704_00_TEXT "\0"
"\x01 " "?" ENUM704_01_TEXT "\0"
"\x02 " "?" ENUM704_02_TEXT
};
// 701 - Temporär wärmer
#define ENUM705 ENUM704
// 701 - Temporär kälter
#define ENUM706 ENUM704

const char ENUM780[] = {
"\x00 " ENUM780_00_TEXT "\0"
"\x01 " ENUM780_01_TEXT "\0"
"\x02 " ENUM780_02_TEXT
};
const char ENUM832[] = {
"\x00 " ENUM832_00_TEXT "\0"
"\x01 " ENUM832_01_TEXT
};

// 843 - Zusätzl' Wirkung TW-Eingang HK1
const char ENUM843[] = {
"\x00 " "?" ENUM843_00_TEXT "\0"
"\x01 " "?" ENUM843_01_TEXT "\0"
"\x02 " "?" ENUM843_02_TEXT
};

const char ENUM850[] = {
"\x00 " ENUM850_00_TEXT "\0"
"\x01 " ENUM850_01_TEXT "\0"
"\x02 " ENUM850_02_TEXT "\0"
"\x03 " ENUM850_03_TEXT "\0"
"\x04 " ENUM850_04_TEXT "\0"
"\x05 " ENUM850_05_TEXT
};
// 860 - Rückkühlung Speicher
const char ENUM860[] = {
"\x00 " "?" ENUM860_00_TEXT "\0"
"\x01 " "?" ENUM860_01_TEXT "\0"
"\x02 " "?" ENUM860_02_TEXT "\0"
"\x03 " "?" ENUM860_03_TEXT
};
const char ENUM861[] = {
"\x00 " ENUM861_00_TEXT "\0"
"\x01 " ENUM861_01_TEXT "\0"
"\x02 " ENUM861_02_TEXT
};
const char ENUM880[] = {
"\x00 " ENUM880_00_TEXT "\0"
"\x01 " ENUM880_01_TEXT "\0"
"\x02 " ENUM880_02_TEXT
};
const char ENUM898[] = {
"\x00 " ENUM898_00_TEXT "\0"
"\x01 " ENUM898_01_TEXT "\0"
"\x02 " ENUM898_02_TEXT
};

const char ENUM900[] = {
"\x00 " ENUM900_00_TEXT "\0"
"\x01 " ENUM900_01_TEXT "\0"
"\x02 " ENUM900_02_TEXT "\0"
"\x03 " ENUM900_03_TEXT "\0"
"\x04 " ENUM900_04_TEXT
};
const char ENUM900_2[] = {
"\x00 " ENUM900_2_00_TEXT "\0"
"\x01 " ENUM900_2_01_TEXT "\0"
"\x03 " ENUM900_2_03_TEXT "\0"
"\x04 " ENUM900_2_04_TEXT
};

// 907 - Trinkwasserfreigabe
const char ENUM907[] = {
"\x01 " "?" ENUM907_01_TEXT "\0"
"\x02 " "?" ENUM907_02_TEXT "\0"
"\x03 " "?" ENUM907_03_TEXT "\0"
"\x04 " "?" ENUM907_04_TEXT
};

// 925 - Trinkwasser Temperaturanforderungsauswahl
const char ENUM925[] = {
"\x01 " "?" ENUM925_01_TEXT "\0"
"\x02 " "?" ENUM925_02_TEXT
};

#define ENUM939 ENUM832

// 945 - Mischventil Kühlkreis 1 im Heizbetrieb
const char ENUM945[] = {
"\x01 " "?" ENUM945_01_TEXT "\0"
"\x02 " "?" ENUM945_02_TEXT "\0"
"\x03 " "?" ENUM945_03_TEXT
};

const char ENUM1000[] = {
"\x00 " ENUM1000_00_TEXT "\0"
"\x01 " ENUM1000_01_TEXT "\0"
"\x02 " ENUM1000_02_TEXT "\0"
"\x03 " ENUM1000_03_TEXT
};

#define ENUM1080 ENUM780         // Schnellabsenkung HK2
#define ENUM1132 ENUM832         // Antrieb Typ HK2

// 1143 - Zusätzl' Wirkung TW-Eingang HK2
#define ENUM1143 ENUM843

#define ENUM1150 ENUM850         // Estrichfunktion HK2
#define ENUM1160 ENUM860
#define ENUM1180 ENUM880
#define ENUM1161 ENUM861         // Übertemperaturabnahme HK2
#define ENUM1198 ENUM898         // Betriebsniveauumschaltung HK2
#define ENUM1200 ENUM900         // Betriebsartumschaltung HK2
#define ENUM1200_2 ENUM900_2         // Betriebsartumschaltung HK2

const char ENUM1300[] = {
"\x00 " ENUM1300_00_TEXT "\0"
"\x01 " ENUM1300_01_TEXT "\0"
"\x02 " ENUM1300_02_TEXT "\0"
"\x03 " ENUM1300_03_TEXT
};
#define ENUM1350 ENUM850
#define ENUM1380 ENUM780

#define ENUM1432 ENUM832
#define ENUM1443 ENUM843
#define ENUM1450 ENUM850

#define ENUM1460 ENUM860
#define ENUM1461 ENUM861         // Uebertemperaturabnahme HK P/3
#define ENUM1480 ENUM880         // Pumpe Drehzahlreduktion
#define ENUM1498 ENUM898         // Betriebsniveauumschaltung HP P/3
#define ENUM1500 ENUM900         // Betriebsartumschaltung HK P/3
#define ENUM1500_2 ENUM900_2         // Betriebsartumschaltung HK P/3

const char ENUM1600[] = {
"\x00 " ENUM1600_00_TEXT "\0"
"\x01 " ENUM1600_01_TEXT "\0"
"\x02 " ENUM1600_02_TEXT
};

const char ENUM1601[] = {
"\x00 " ENUM1601_00_TEXT "\0"
"\x02 " ENUM1601_02_TEXT
};

const char ENUM1602[] = {
"\x00\x02 " ENUM1602_00_02_TEXT "\0"
"\x02\x02 " ENUM1602_02_02_TEXT "\0"
"\x00\x04 " ENUM1602_00_04_TEXT "\0"
"\x04\x04 " ENUM1602_04_04_TEXT "\0"
"\x00\x08 " ENUM1602_00_08_TEXT "\0"
"\x08\x08 " ENUM1602_08_08_TEXT
};

const char ENUM1620[] = {
"\x00 " ENUM1620_00_TEXT "\0"
"\x01 " ENUM1620_01_TEXT "\0"
"\x02 " ENUM1620_02_TEXT
};
const char ENUM1620_2[] = {
"\x00 " ENUM1620_2_00_TEXT "\0"
"\x01 " ENUM1620_2_01_TEXT "\0"
"\x04 " ENUM1620_2_04_TEXT
};
const char ENUM1620_3[] = {
"\x00 " ENUM1620_00_TEXT "\0"
"\x01 " ENUM1620_3_01_TEXT "\0"
"\x02 " ENUM1620_02_TEXT "\0"
"\x03 " ENUM1620_3_03_TEXT "\0"
"\x04 " ENUM1620_3_04_TEXT
};

const char ENUM1630[] = {
"\x00 " ENUM1630_00_TEXT "\0"
"\x01 " ENUM1630_01_TEXT "\0"
"\x02 " ENUM1630_02_TEXT "\0"
"\x03 " ENUM1630_03_TEXT "\0"
"\x04 " ENUM1630_04_TEXT
};
const char ENUM1640[] = {
"\x00 " ENUM1640_00_TEXT "\0"
"\x01 " ENUM1640_01_TEXT "\0"
"\x02 " ENUM1640_02_TEXT
};
const char ENUM1660[] = {
"\x01 " ENUM1660_01_TEXT "\0"
"\x02 " ENUM1660_02_TEXT "\0"
"\x03 " ENUM1660_03_TEXT "\0"
"\x04 " ENUM1660_04_TEXT
};
const char ENUM1680[] = {
"\x00 " ENUM1680_00_TEXT "\0"
"\x01 " ENUM1680_01_TEXT "\0"
"\x02 " ENUM1680_02_TEXT "\0"
"\x03 " ENUM1680_03_TEXT
};

// 2015 - H1 Kälteanforderung
const char ENUM2015[] = {
"\x01 " "?" ENUM2015_01_TEXT "\0"
"\x02 " "?" ENUM2015_02_TEXT "\0"
"\x03 " "?" ENUM2015_03_TEXT
};

// 2040 - H2 Kälteanforderung
const char ENUM2040[] = {
"\x01 " "?" ENUM2040_01_TEXT "\0"
"\x02 " "?" ENUM2040_02_TEXT "\0"
"\x03 " "?" ENUM2040_03_TEXT
};

// Vorregler/Zubringerpumpe

const char ENUM2132[] = {  // ENUM values hypothetical
"\x00 " ENUM2132_00_TEXT "\0"
"\x01 " ENUM2132_01_TEXT
};

const char ENUM2150[] = {  // ENUM values hypothetical
"\x00 " ENUM2150_00_TEXT "\0"
"\x01 " ENUM2150_01_TEXT
};

// Kessel
const char ENUM2200[] = {
"\x00 " ENUM2200_00_TEXT "\0"
"\x01 " ENUM2200_01_TEXT "\0"
"\x02 " ENUM2200_02_TEXT
};
const char ENUM2205[] = {
"\x00 " ENUM2205_00_TEXT "\0"
"\x01 " ENUM2205_01_TEXT "\0"
"\x02 " ENUM2205_02_TEXT
};
const char ENUM2206[] = {
"\x00 " ENUM2206_00_TEXT "\0"
"\x01 " ENUM2206_01_TEXT
};
const char ENUM2291[] = {
"\x00 " ENUM2291_00_TEXT "\0"
"\x01 " ENUM2291_01_TEXT
};

const char ENUM2305[] = {
"\x00 " ENUM2305_00_TEXT "\0"
"\x01 " ENUM2305_01_TEXT
};

const char ENUM2305_2[] = {
"\x01 " ENUM2305_2_01_TEXT "\0"
"\x02 " ENUM2305_2_02_TEXT
};

const char ENUM2320[] = {
"\x00 " ENUM2320_00_TEXT "\0"
"\x01 " ENUM2320_01_TEXT "\0"
"\x02 " ENUM2320_02_TEXT "\0"
"\x03 " ENUM2320_03_TEXT "\0"
"\x04 " ENUM2320_04_TEXT
};

const char ENUM2450[] = {
"\x00 " ENUM2450_00_TEXT "\0"
"\x01 " ENUM2450_01_TEXT "\0"
"\x02 " ENUM2450_02_TEXT "\0"
"\x03 " ENUM2450_03_TEXT
};

const char ENUM2476[] = {
"\x00 " ENUM2480_00_TEXT "\0"
"\xff " ENUM2476_ff_TEXT
};

const char ENUM2480[] = {
"\x00 " ENUM2480_00_TEXT "\0"
"\xff " ENUM2480_ff_TEXT
};

#define ENUM2490 ENUM2476

const char ENUM2500[] = {
"\x00 " ENUM2500_00_TEXT "\0"
"\x01 " ENUM2500_01_TEXT
};

// 2501 - Durchflussmessung
const char ENUM2501[] = {
"\x00 " "?" ENUM2501_00_TEXT "\0"
"\x01 " "?" ENUM2501_01_TEXT "\0"
"\x02 " "?" ENUM2501_02_TEXT
};

#define ENUM2502 ENUM2476

// Sitherm Pro
const char ENUM2706[] = {
"\x00 " ENUM2706_00_TEXT "\0"
"\x01 " ENUM2706_01_TEXT "\0"
"\x02 " ENUM2706_02_TEXT "\0"
"\x03 " ENUM2706_03_TEXT "\0"                     // verifiziert an WMS (LP)
"\x04 " ENUM2706_04_TEXT "\0"
"\x05 " ENUM2706_05_TEXT "\0"
"\x06 " ENUM2706_06_TEXT "\0"
"\x07 " ENUM2706_07_TEXT "\0"                  // verifiziert an WMS (LP)
"\x08 " ENUM2706_08_TEXT "\0"              // verifiziert an WMS (LP)
"\x09 " ENUM2706_09_TEXT "\0"                      // verifiziert an WMS (LP)
"\x0a " ENUM2706_0a_TEXT "\0"
"\x0b " ENUM2706_0b_TEXT "\0"
"\x0c " ENUM2706_0c_TEXT "\0"
"\x0d " ENUM2706_0d_TEXT "\0"
"\x12 " ENUM2706_12_TEXT        // verifiziert an WMS (LP)
}; // todo Hinweis: x03, x07, x08, x12 sind definitiv richtig. Die anderen muessen noch verifiziert werden.

// 2710 - Obergrenze Drifttest Störung
const char ENUM2710[] = {
"\x00 " "?" ENUM2710_00_TEXT "\0"
"\x01 " "?" ENUM2710_01_TEXT "\0"
"\x02 " "?" ENUM2710_02_TEXT "\0"
"\x03 " "?" ENUM2710_03_TEXT "\0"
"\x04 " "?" ENUM2710_04_TEXT
};

// 2726 - Freigabe Einstellung Gasart
const char ENUM2726[] = {
"\x01 " "?" ENUM2726_01_TEXT "\0"
"\x02 " "?" ENUM2726_02_TEXT
};

const char ENUM2721[] = {
"\x01 " ENUM2721_01_TEXT "\0"
"\x02 " ENUM2721_02_TEXT
}; // todo Hinweis: x01 Erdgas ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2727[] = {
"\x01 " ENUM2727_01_TEXT "\0"
"\x02 " ENUM2727_02_TEXT "\0"
"\x03 " ENUM2727_03_TEXT
};

const char ENUM2740[] = {
"\x00 " ENUM2740_00_TEXT "\0"
"\x01 " ENUM2740_01_TEXT "\0"
"\x02 " ENUM2740_02_TEXT "\0"
"\x03 " ENUM2740_03_TEXT "\0"
"\x04 " ENUM2740_04_TEXT "\0"
"\x05 " ENUM2740_05_TEXT "\0"
"\x06 " ENUM2740_06_TEXT "\0"
"\x07 " ENUM2740_07_TEXT "\0"
"\x08 " ENUM2740_08_TEXT "\0"
"\x09 " ENUM2740_09_TEXT
}; // todo Hinweis: x00 Nein ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2749[] = {
"\x00 " ENUM2749_00_TEXT "\0"
"\x01 " ENUM2749_01_TEXT "\0"
"\x02 " ENUM2749_02_TEXT
}; // todo Hinweis: x00 Nein ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2790[] = {
"\x00 " ENUM2790_00_TEXT "\0"
"\x01 " ENUM2790_01_TEXT "\0"
"\x02 " ENUM2790_02_TEXT "\0"
"\x03 " ENUM2790_03_TEXT
};

const char ENUM2801[] = {
"\x01 " ENUM2801_01_TEXT "\0"
"\x02 " ENUM2801_02_TEXT "\0"
"\x03 " ENUM2801_03_TEXT
};

// [Ersatz, Ergänzung HK, Ergänzung TWW, Ergänzung HK+TWW, Beenden TWW Ladung, Notbetrieb, Legionellenfunktion]
const char ENUM2880[] = {
"\x01 " ENUM2880_01_TEXT "\0"
"\x02 " ENUM2880_02_TEXT "\0"
"\x03 " ENUM2880_03_TEXT "\0"
"\x04 " ENUM2880_04_TEXT "\0"
"\x05 " ENUM2880_05_TEXT "\0"
"\x06 " ENUM2880_06_TEXT "\0"
"\x07 " ENUM2880_07_TEXT
};

const char ENUM2900[] = {
"\x00 " ENUM2900_00_TEXT "\0"
"\x01 " ENUM2900_01_TEXT "\0"
"\x02 " ENUM2900_02_TEXT "\0"
"\x03 " ENUM2900_03_TEXT "\0"
"\x04 " ENUM2900_04_TEXT "\0"
"\x05 " ENUM2900_05_TEXT "\0"
"\x06 " ENUM2900_06_TEXT "\0"
"\x07 " ENUM2900_07_TEXT "\0"
"\x08 " ENUM2900_08_TEXT "\0"
"\x09 " ENUM2900_09_TEXT "\0"
"\x10 " ENUM2900_10_TEXT "\0"
"\x11 " ENUM2900_11_TEXT "\0"
"\x12 " ENUM2900_12_TEXT "\0"
"\x13 " ENUM2900_13_TEXT "\0"
"\x14 " ENUM2900_14_TEXT "\0"
"\x15 " ENUM2900_15_TEXT "\0"
"\x16 " ENUM2900_16_TEXT "\0"
"\x17 " ENUM2900_17_TEXT "\0"
"\x18 " ENUM2900_18_TEXT "\0"
"\x19 " ENUM2900_19_TEXT
};

const char ENUM2903[] = {
"\x01 " ENUM2903_01_TEXT "\0"
"\x02 " ENUM2903_02_TEXT "\0"
"\x03 " ENUM2903_03_TEXT "\0"
"\x04 " ENUM2903_04_TEXT
};

const char ENUM2908[] = {
"\x00 " ENUM2908_00_TEXT "\0"
"\x01 " ENUM2908_01_TEXT
};

const char ENUM2911[] = {
"\x00 " ENUM2911_00_TEXT "\0"
"\x01 " ENUM2911_01_TEXT
};

// ProgNr 2920 "Bei EW Sperre" FUJITSU
const char ENUM2920[] = {
"\x00 " ENUM2920_00_TEXT "\0"
"\x01 " ENUM2920_01_TEXT
};

const char ENUM2922[] = {
"\x00 " ENUM2922_00_TEXT "\0"
"\x01 " ENUM2922_01_TEXT "\0"
"\x02 " ENUM2922_02_TEXT
};

const char ENUM2923[] = {
"\x00 " ENUM2923_00_TEXT "\0"
"\x01 " ENUM2923_01_TEXT "\0"
"\x02 " ENUM2923_02_TEXT "\0"
"\x03 " ENUM2923_03_TEXT
};

const char ENUM2941[] = {
"\x01 " ENUM2941_01_TEXT "\0"
"\x02 " ENUM2941_02_TEXT
};

const char ENUM3007[] = {
"\x00 " ENUM3007_00_TEXT "\0"
"\x01 " ENUM3007_01_TEXT
};

const char ENUM3009[] = {
"\x00 " ENUM3009_00_TEXT "\0"
"\x01 " ENUM3009_01_TEXT "\0"
"\x02 " ENUM3009_02_TEXT
};

const char ENUM3030[] = {
"\x00 " ENUM3030_00_TEXT "\0"
"\x01 " ENUM3030_01_TEXT "\0"
"\x02 " ENUM3030_02_TEXT
};

const char ENUM3033[] = {
"\x00 " ENUM3033_00_TEXT "\0"
"\x01 " ENUM3033_01_TEXT "\0"
"\x02 " ENUM3033_02_TEXT "\0"
"\x03 " ENUM3033_03_TEXT
};

// Energiezähler

// "Durchflussmessung Wärme"
const char ENUM3090[] = {
"\x00 " ENUM3090_00_TEXT
};

const char ENUM3092[] = {
"\x00 " ENUM3092_00_TEXT
};

const char ENUM3095[] = {
"\x00 " ENUM3095_00_TEXT "\0"
"\x01 " ENUM3095_01_TEXT "\0"
"\x02 " ENUM3095_02_TEXT "\0"
"\x03 " ENUM3095_03_TEXT "\0"
"\x04 " ENUM3095_04_TEXT "\0"
"\x05 " ENUM3095_05_TEXT "\0"
"\x06 " ENUM3095_06_TEXT "\0"
"\x07 " ENUM3095_07_TEXT "\0"
"\x08 " ENUM3095_08_TEXT "\0"
"\x09 " ENUM3095_09_TEXT "\0"
"\x0a " ENUM3095_0a_TEXT "\0"
"\x0b " ENUM3095_0b_TEXT "\0"
"\x0c " ENUM3095_0c_TEXT "\0"
"\x0d " ENUM3095_0d_TEXT
};
// "Impulszählung Energie"
const char ENUM3100[] = {
"\x00 " ENUM3100_00_TEXT "\0"
"\x01 " ENUM3100_01_TEXT "\0"
"\x02 " ENUM3100_02_TEXT "\0"
"\x03 " ENUM3100_03_TEXT "\0"
"\x04 " ENUM3100_04_TEXT "\0"
"\x05 " ENUM3100_05_TEXT "\0"
"\x06 " ENUM3100_06_TEXT "\0"
"\x07 " ENUM3100_07_TEXT "\0"
"\x08 " ENUM3100_08_TEXT "\0"
"\x09 " ENUM3100_09_TEXT "\0"
"\x0a " ENUM3100_0a_TEXT
};
// "Impulseinheit Energie"
const char ENUM3102[] = {
"\x00 " ENUM3102_00_TEXT "\0"
"\x01 " ENUM3102_01_TEXT "\0"
"\x02 " ENUM3102_02_TEXT
};
// "Zählung Intern Elektro Vorl’"
const char ENUM3109[] = {
"\x00 " ENUM3109_00_TEXT "\0"
"\x01 " ENUM3109_01_TEXT "\0"
"\x02 " ENUM3109_02_TEXT "\0"
"\x03 " ENUM3109_03_TEXT
};

const char ENUM3192[] = {
"\x00 " ENUM3192_00_TEXT "\0"
"\x01 " ENUM3192_01_TEXT "\0"
"\x02 " ENUM3192_02_TEXT "\0"
"\x03 " ENUM3192_03_TEXT
};

#define ENUM3193 ENUM3192
#define ENUM3260 ENUM3880

// Kaskade
const char ENUM3510[] = {  // numerical values are hypothetical
"\x01 " ENUM3510_01_TEXT "\0"
"\x02 " ENUM3510_02_TEXT "\0"
"\x03 " ENUM3510_03_TEXT
};
const char ENUM3541[] = {  // numerical values are hypothetical
"\x00 " ENUM3541_00_TEXT "\0"
"\x01 " ENUM3541_01_TEXT "\0"
"\x02 " ENUM3541_02_TEXT "\0"
"\x03 " ENUM3541_03_TEXT
};
const char ENUM3544[] = {  // numerical values are hypothetical
"\x01 " ENUM3544_01_TEXT "\0"
"\x02 " ENUM3544_02_TEXT "\0"
"\x03 " ENUM3544_03_TEXT "\0"
"\x04 " ENUM3544_04_TEXT "\0"
"\x05 " ENUM3544_05_TEXT "\0"
"\x06 " ENUM3544_06_TEXT "\0"
"\x07 " ENUM3544_07_TEXT "\0"
"\x08 " ENUM3544_08_TEXT "\0"
"\x09 " ENUM3544_09_TEXT "\0"
"\x0a " ENUM3544_0a_TEXT "\0"
"\x0b " ENUM3544_0b_TEXT "\0"
"\x0c " ENUM3544_0c_TEXT "\0"
"\x0d " ENUM3544_0d_TEXT "\0"
"\x0e " ENUM3544_0e_TEXT "\0"
"\x0f " ENUM3544_0f_TEXT "\0"
"\x10 " ENUM3544_10_TEXT
};

// Zusatzerzeuger
const char ENUM3692[] = {
"\x00 " ENUM3692_00_TEXT "\0"
"\x01 " ENUM3692_01_TEXT "\0"
"\x02 " ENUM3692_02_TEXT "\0"
"\x03 " ENUM3692_03_TEXT "\0"
"\x04 " ENUM3692_04_TEXT "\0"
"\x05 " ENUM3692_05_TEXT
};

const char ENUM3694[] = {
"\x00 " ENUM3694_00_TEXT "\0"
"\x01 " ENUM3694_01_TEXT
};

const char ENUM3725[] = {
"\x01 " ENUM3725_01_TEXT "\0"
"\x02 " ENUM3725_02_TEXT
};

const char ENUM3750[] = {
"\x00 " ENUM3750_00_TEXT "\0"
"\x01 " ENUM3750_01_TEXT "\0"
"\x02 " ENUM3750_02_TEXT "\0"
"\x03 " ENUM3750_03_TEXT
};

// Solar
const char ENUM3822[] = {
"\x00 " ENUM3822_00_TEXT "\0"
"\x01 " ENUM3822_01_TEXT "\0"
"\x02 " ENUM3822_02_TEXT
};
const char ENUM3880[] = {
"\x01 " ENUM3880_01_TEXT "\0"
"\x02 " ENUM3880_02_TEXT "\0"
"\x03 " ENUM3880_03_TEXT "\0"
"\x04 " ENUM3880_04_TEXT
};
const char ENUM3887[] = {
"\x01 " ENUM3887_01_TEXT "\0"
"\x02 " ENUM3887_02_TEXT "\0"
"\x03 " ENUM3887_03_TEXT
};

// Feststoffkessel
const char ENUM4133[] = {
"\x01 " ENUM4133_01_TEXT "\0"
"\x02 " ENUM4133_02_TEXT "\0"
"\x03 " ENUM4133_03_TEXT "\0"
"\x04 " ENUM4133_04_TEXT "\0"
"\x05 " ENUM4133_05_TEXT "\0"
"\x06 " ENUM4133_06_TEXT
};

const char ENUM4134[] = {
"\x00 " ENUM4134_00_TEXT "\0"
"\x01 " "?" ENUM4134_01_TEXT "\0"
"\x02 " "?" ENUM4134_02_TEXT "\0"
"\x03 " "?" ENUM4134_03_TEXT
}; // todo Hinweis: x00 Keine ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM4135[] = {
"\x01 " ENUM4135_01_TEXT "\0"
"\x02 " "?" ENUM4135_02_TEXT "\0"
"\x03 " "?" ENUM4135_03_TEXT
}; // todo Hinweis: x01 Speichertemperatur ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM4137[] = {
"\x00 " "?" ENUM4137_00_TEXT "\0"
"\x01 " ENUM4137_01_TEXT "\0"
"\x02 " "?" ENUM4137_02_TEXT "\0"
"\x03 " "?" ENUM4137_03_TEXT
}; // todo Hinweis: x01 Mit B4 ist definitiv richtig. Die anderen muessen noch verifiziert werden.

#define ENUM4138 ENUM4135

const char ENUM4192[] = {
"\x00 " ENUM4192_00_TEXT "\0"
"\x01 " ENUM4192_01_TEXT
};

// Pufferspeicher
const char ENUM4720[] = {
"\x00 " ENUM4720_00_TEXT "\0"
"\x01 " ENUM4720_01_TEXT "\0"
"\x02 " ENUM4720_02_TEXT
};
// 4739 - Pufferspeicher Schichtschutz
const char ENUM4739[] = {
"\x00 " "?" ENUM4739_00_TEXT "\0"
"\x01 " "?" ENUM4739_01_TEXT "\0"
"\x02 " "?" ENUM4739_02_TEXT
};
const char ENUM4757[] = {
"\x00 " ENUM4757_00_TEXT "\0"
"\x01 " ENUM4757_01_TEXT "\0"
"\x02 " ENUM4757_02_TEXT
};
const char ENUM4795[] = {
"\x01 " ENUM4795_01_TEXT "\0"
"\x02 " ENUM4795_02_TEXT "\0"
"\x03 " ENUM4795_03_TEXT
};
const char ENUM4796[] = {
"\x01 " ENUM4796_01_TEXT "\0"
"\x02 " ENUM4796_02_TEXT
};
const char ENUM4810[] = {
"\x00 " ENUM4810_00_TEXT "\0"
"\x01 " ENUM4810_01_TEXT "\0"
"\x02 " ENUM4810_02_TEXT
};
const char ENUM4813[] = {
"\x01 " ENUM4813_01_TEXT "\0"
"\x02 " ENUM4813_02_TEXT
};
// Trinkwasserspeicher
const char ENUM5007[] = {
"\x02 " ENUM5007_02_TEXT "\0"
"\x03 " ENUM5007_03_TEXT
};
const char ENUM5010[] = {
"\x00 " ENUM5010_00_TEXT "\0"
"\xff " ENUM5010_ff_TEXT
};
const char ENUM5013[] = {
"\x00 " ENUM5013_00_TEXT "\0"
"\x01 " ENUM5013_01_TEXT "\0"
"\x02 " ENUM5013_02_TEXT
};
const char ENUM5016[] = {
"\x00 " ENUM5016_00_TEXT "\0"
"\x01 " ENUM5016_01_TEXT "\0"
"\x02 " ENUM5016_02_TEXT
};
const char ENUM5022[] = {
"\x01 " ENUM5022_01_TEXT "\0"
"\x02 " ENUM5022_02_TEXT "\0"
"\x03 " ENUM5022_03_TEXT
};
const char ENUM5022_2[] = {
"\x01 " ENUM5022_2_01_TEXT "\0"
"\x02 " ENUM5022_2_02_TEXT "\0"
"\x03 " ENUM5022_2_03_TEXT "\0"
"\x04 " ENUM5022_2_04_TEXT "\0"
"\x05 " ENUM5022_2_05_TEXT
};
const char ENUM5040[] = {
"\x00 " ENUM5040_00_TEXT "\0"
"\x01 " ENUM5040_01_TEXT "\0"
"\x02 " ENUM5040_02_TEXT
};
const char ENUM5041[] = {
"\x01 " ENUM5041_01_TEXT "\0"
"\x02 " ENUM5041_02_TEXT
};
const char ENUM5057[] = {
"\x00 " ENUM5057_00_TEXT "\0"
"\x01 " ENUM5057_01_TEXT "\0"
"\x02 " ENUM5057_02_TEXT
};
const char ENUM5060[] = {
"\x01 " ENUM5060_01_TEXT "\0"
"\x02 " ENUM5060_02_TEXT "\0"
"\x03 " ENUM5060_03_TEXT "\0"
"\x04 " ENUM5060_04_TEXT "\0"
"\x05 " ENUM5060_05_TEXT "\0"
"\x06 " ENUM5060_06_TEXT
};
const char ENUM5061[] = {
"\x01 " ENUM5061_01_TEXT "\0"
"\x02 " ENUM5061_02_TEXT "\0"
"\x03 " ENUM5061_03_TEXT
};
const char ENUM5062[] = {
"\x01 " ENUM5062_01_TEXT "\0"
"\x02 " ENUM5062_02_TEXT
};

#define ENUM5122 ENUM832

const char ENUM5130[] = {
"\x00 " ENUM5130_00_TEXT "\0"
"\x01 " ENUM5130_01_TEXT
};
const char ENUM5130_2[] = {
"\x00 " MENU_TEXT_OFF "\0"
"\x01 " ENUM5130_00_TEXT "\0"
"\x02 " ENUM5130_01_TEXT
};
const char ENUM5131[] = {
"\x00 " ENUM5131_00_TEXT "\0"
"\x01 " ENUM5131_01_TEXT
};
const char ENUM5131_2[] = {
"\x01 " ENUM5131_00_TEXT "\0"
"\x02 " ENUM5131_01_TEXT
};

#define ENUM5441 ENUM2501

// 5464 - Warmhaltung Freigabe
const char ENUM5464[] = {
"\x00 " "?" ENUM5464_00_TEXT "\0"
"\x01 " "?" ENUM5464_01_TEXT "\0"
"\x02 " "?" ENUM5464_02_TEXT "\0"
"\x03 " "?" ENUM5464_03_TEXT "\0"
"\x04 " "?" ENUM5464_04_TEXT "\0"
"\x05 " "?" ENUM5464_05_TEXT
};

// 5475 - Regelfühler Warmhaltung
const char ENUM5475[] = {
"\x00 " "?" ENUM5475_00_TEXT "\0"
"\x01 " "?" ENUM5475_01_TEXT "\0"
"\x02 " "?" ENUM5475_02_TEXT "\0"
"\x03 " "?" ENUM5475_03_TEXT
};

// 5491 - Lernzeitraum Warmhaltung
const char ENUM5491[] = {
"\x00 " "?" ENUM5491_00_TEXT "\0"
"\x01 " "?" ENUM5491_01_TEXT "\0"
"\x02 " "?" ENUM5491_02_TEXT "\0"
"\x03 " "?" ENUM5491_03_TEXT
};

// 5550 - Aqua booster
const char ENUM5550[] = {
"\x00 " "?" ENUM5550_00_TEXT "\0"
"\x01 " "?" ENUM5550_01_TEXT "\0"
"\x02 " "?" ENUM5550_02_TEXT
};

// Allgemeine Funktionen
const char ENUM5573[] = { //Fühler 1 dT-Regler 1 - Baxi Luna Platinum+
"\x00 " ENUM5573_00_TEXT "\0" //none
"\x01 " ENUM5573_01_TEXT "\0" //B31
"\x02 " ENUM5573_02_TEXT "\0" //B6
"\x03 " ENUM5573_03_TEXT "\0" //B7
"\x04 " ENUM5573_04_TEXT "\0" //B39
"\x05 " ENUM5573_03_TEXT "\0" //B4
"\x06 " ENUM5573_04_TEXT "\0" //B41
"\x07 " ENUM5573_07_TEXT "\0" //B8
"\x08 " ENUM5573_08_TEXT "\0" //B10
"\x09 " ENUM5573_09_TEXT "\0" //B22
"\x0a " ENUM5573_0a_TEXT "\0" //B36
"\x0b " ENUM5573_0b_TEXT "\0" //B42
"\x0c " ENUM5573_0c_TEXT "\0" //B73
"\x0d " ENUM5573_0d_TEXT "\0" //B70
"\x0e " ENUM5573_0e_TEXT "\0" //B13
"\x10 " ENUM5573_10_TEXT "\0" //B63
"\x11 " ENUM5573_11_TEXT "\0" //B64
"\x12 " ENUM5573_12_TEXT "\0" //B38
"\x13 " ENUM5573_13_TEXT "\0" //B26 Primärtauscherfühler B26
"\x15 " ENUM5573_15_TEXT "\0" //B2
"\x16 " ENUM5573_16_TEXT "\0" //B62 Solarfühler ext.Tausch B62
"\x18 " ENUM5573_18_TEXT "\0" //B3 Trinkwasserfühler B3
"\x1b " ENUM5573_1b_TEXT "\0" //B9 Außentemperaturfühler B9
"\x1c " ENUM5573_1c_TEXT "\0" //B15 Vorreglerfühler B15
"\x1d " ENUM5573_1d_TEXT "\0" //B5 Raumfühler B5
"\x1e " ENUM5573_1e_TEXT "\0" //B52 Raumfühler B52
"\x1f " ENUM5573_1f_TEXT "\0" //B53 Raumfühler B53
"\x20 " ENUM5573_20_TEXT "\0" //B1 Vorlauftemperaturfühler HK1 B1
"\x21 " ENUM5573_21_TEXT "\0" //B12 Vorlauftemperaturfühler HK2 B12
"\x22 " ENUM5573_22_TEXT //B14 Vorlauftemperaturfühler HK3 B14
};

#define ENUM5574 ENUM5573               // Fühler 2 dT-Regler 1
#define ENUM5583 ENUM5573               // Fühler 1 dT-Regler 2
#define ENUM5584 ENUM5573               // Fühler 2 dT-Regler 2

// Konfiguration
const char ENUM5700[] = { //FUJITSU
"\x01 " ENUM5700_01_TEXT "\0"
"\x02 " ENUM5700_02_TEXT "\0"
"\x03 " ENUM5700_03_TEXT "\0"
"\x04 " ENUM5700_04_TEXT "\0"
"\x05 " ENUM5700_05_TEXT
};
const char ENUM5711[] = { //FUJITSU
"\x00 " ENUM5711_00_TEXT "\0"
"\x01 " ENUM5711_01_TEXT "\0"
"\x02 " ENUM5711_02_TEXT
};

const char ENUM5712[] = {
"\x01 " ENUM5712_01_TEXT "\0"
"\x02 " ENUM5712_02_TEXT "\0"
"\x03 " ENUM5712_03_TEXT
};

const char ENUM5715[] = {
"\x00 " ENUM5715_00_TEXT "\0"
"\x01 " ENUM5715_01_TEXT "\0"
"\x03 " ENUM5715_03_TEXT
};

const char ENUM5730[] = {
"\x00 " ENUM5730_00_TEXT "\0"
"\x01 " ENUM5730_01_TEXT
};
const char ENUM5730_2[] = {
"\x01 " ENUM5730_2_01_TEXT "\0"
"\x02 " ENUM5730_01_TEXT "\0"
"\x03 " ENUM5730_2_03_TEXT
};
const char ENUM5731[] = {
"\x00 " ENUM5731_00_TEXT "\0"
"\x01 " ENUM5731_01_TEXT "\0"
"\x02 " ENUM5731_02_TEXT
};
const char ENUM5734[] = {
"\x00 " ENUM5734_00_TEXT "\0"
"\x01 " ENUM5734_01_TEXT "\0"
"\x02 " ENUM5734_02_TEXT
};
const char ENUM5737[] = {
"\x00 " ENUM5737_00_TEXT "\0"
"\xff " ENUM5737_FF_TEXT
};

const char ENUM5760[] = {
"\x00 " ENUM5760_00_TEXT "\0"
"\x01 " ENUM5760_01_TEXT
};

const char ENUM5761[] = {
"\x01\x01 " ENUM5761_01_01_TEXT "\0"
"\x02\x02 " ENUM5761_02_02_TEXT "\0"
"\x04\x04 " ENUM5761_04_04_TEXT "\0"
"\x08\x08 " ENUM5761_08_08_TEXT
};

const char ENUM5770[] = {
"\x00 " ENUM5770_00_TEXT "\0"
"\x01 " ENUM5770_01_TEXT "\0"
"\x02 " ENUM5770_02_TEXT "\0"
"\x03 " ENUM5770_03_TEXT "\0"
"\x04 " ENUM5770_04_TEXT "\0"
"\x05 " ENUM5770_05_TEXT
};

const char ENUM5774[] = {
"\x00 " ENUM5774_00_TEXT "\0"
"\xFF " ENUM5774_ff_TEXT};

const char ENUM5806[] = { //FUJITSU
"\x01 " ENUM5806_01_TEXT "\0"
"\x02 " ENUM5806_02_TEXT "\0"
"\x03 " ENUM5806_03_TEXT "\0"
"\x04 " ENUM5806_04_TEXT
};
const char ENUM5840[] = {
//"\x00 " ENUM5840_00_TEXT "\0"   -- O does not exits
"\x01 " ENUM5840_01_TEXT "\0"
"\x02 " ENUM5840_02_TEXT
};

const char ENUM5841[] = {
"\x01 " ENUM5841_01_TEXT "\0"
"\x02 " ENUM5841_02_TEXT "\0"
"\x03 " ENUM5841_03_TEXT
};

const char ENUM5841_2[] = {
"\x01 " ENUM5841_01_TEXT "\0"
"\x02 " ENUM5841_02_TEXT "\0"
"\x03 " ENUM5841_03_TEXT
};

// Konfiguration - Relaisausgang QX1
const char ENUM5890[] = {
"\x00 " ENUM5890_00_TEXT "\0"
"\x01 " ENUM5890_01_TEXT "\0"
"\x02 " ENUM5890_02_TEXT "\0"
"\x03 " ENUM5890_03_TEXT "\0"
"\x04 " ENUM5890_04_TEXT "\0"
"\x05 " ENUM5890_05_TEXT "\0"
"\x06 " ENUM5890_06_TEXT "\0"
"\x07 " ENUM5890_07_TEXT "\0"
"\x08 " ENUM5890_08_TEXT "\0"
"\x09 " ENUM5890_09_TEXT "\0"
"\x0a " ENUM5890_0a_TEXT "\0"
"\x0b " ENUM5890_0b_TEXT "\0"
"\x0c " ENUM5890_0c_TEXT "\0"
"\x0d " ENUM5890_0d_TEXT "\0"
"\x0e " ENUM5890_0e_TEXT "\0"
"\x0f " ENUM5890_0f_TEXT "\0"
"\x10 " ENUM5890_10_TEXT "\0"
"\x11 " ENUM5890_11_TEXT "\0"
"\x12 " ENUM5890_12_TEXT "\0"
"\x13 " ENUM5890_13_TEXT "\0"
"\x14 " ENUM5890_14_TEXT "\0"
"\x15 " ENUM5890_15_TEXT "\0"
"\x16 " ENUM5890_16_TEXT "\0"
"\x17 " ENUM5890_17_TEXT "\0"
"\x18 " ENUM5890_18_TEXT "\0"
"\x19 " ENUM5890_19_TEXT "\0"
"\x1a " ENUM5890_1a_TEXT "\0"
"\x1b " ENUM5890_1b_TEXT "\0"
"\x1c " ENUM5890_1c_TEXT "\0"
"\x1d " ENUM5890_1d_TEXT "\0"
"\x1e " ENUM5890_1e_TEXT "\0"
"\x21 " ENUM5890_21_TEXT "\0"
"\x22 " ENUM5890_22_TEXT "\0"
"\x23 " ENUM5890_23_TEXT "\0"
"\x24 " ENUM5890_24_TEXT "\0"
"\x26 " ENUM5890_26_TEXT "\0"
"\x27 " ENUM5890_27_TEXT "\0"
"\x28 " ENUM5890_28_TEXT "\0"
"\x29 " ENUM5890_29_TEXT "\0"
"\x2a " ENUM5890_2a_TEXT "\0"
"\x2b " ENUM5890_2b_TEXT "\0"
"\x2d " ENUM5890_2d_TEXT "\0"
"\x2e " ENUM5890_2e_TEXT
};

const char ENUM5890_2[] = {
"\x00 " ENUM5890_2_00_TEXT "\0"
"\x01 " ENUM5890_2_01_TEXT "\0"
"\x02 " ENUM5890_2_02_TEXT "\0"
"\x03 " ENUM5890_2_03_TEXT "\0"
"\x04 " ENUM5890_2_04_TEXT "\0"
"\x05 " ENUM5890_2_05_TEXT "\0"
"\x06 " ENUM5890_2_06_TEXT "\0"
"\x07 " ENUM5890_2_07_TEXT "\0"
"\x08 " ENUM5890_2_08_TEXT "\0"
"\x09 " ENUM5890_2_09_TEXT "\0"
"\x0a " ENUM5890_2_0a_TEXT "\0"
"\x0b " ENUM5890_2_0b_TEXT
};

#define ENUM5891 ENUM5890               // Relaisausgang QX2
#define ENUM5892 ENUM5890               // Relaisausgang QX3
#define ENUM5894 ENUM5890               // Relaisausgang QX4
#define ENUM5902 ENUM5890               // Relaisausgang QX21
#define ENUM5904 ENUM5890               // Relaisausgang QX23
#define ENUM5908 ENUM5890               // Relaisausgang QX3-Mod
#define ENUM5909 ENUM5890               // Relaisausgang QX4-Mod

// The numerical values are undocumented in the Broetje Systemhandbuch
// Values here are hypothetical.
const char ENUM5895[] = {        // Relaisausgang QX5
"\x00 " "?" ENUM5895_00_TEXT "\0"
"\x01 " "?" ENUM5895_01_TEXT "\0"
"\x02 " "?" ENUM5895_02_TEXT "\0"
"\x03 " "?" ENUM5895_03_TEXT "\0"
"\x04 " "?" ENUM5895_04_TEXT "\0"
"\x05 " "?" ENUM5895_05_TEXT "\0"
"\x06 " "?" ENUM5895_06_TEXT "\0"
"\x07 " "?" ENUM5895_07_TEXT "\0"
"\x08 " "?" ENUM5895_08_TEXT "\0"
"\x09 " "?" ENUM5895_09_TEXT "\0"
"\x0a " "?" ENUM5895_0a_TEXT "\0"
"\x0b " "?" ENUM5895_0b_TEXT "\0"
"\x0c " "?" ENUM5895_0c_TEXT "\0"
"\x0d " "?" ENUM5895_0d_TEXT "\0"
"\x0e " "?" ENUM5895_0e_TEXT "\0"
"\x0f " "?" ENUM5895_0f_TEXT "\0"
"\x10 " "?" ENUM5895_10_TEXT "\0"
"\x11 " "?" ENUM5895_11_TEXT "\0"
"\x12 " "?" ENUM5895_12_TEXT "\0"
"\x13 " "?" ENUM5895_13_TEXT "\0"
"\x14 " "?" ENUM5895_14_TEXT "\0"
"\x15 " "?" ENUM5895_15_TEXT "\0"
"\x16 " "?" ENUM5895_16_TEXT "\0"
"\x17 " "?" ENUM5895_17_TEXT "\0"
"\x18 " "?" ENUM5895_18_TEXT "\0"
"\x19 " "?" ENUM5895_19_TEXT "\0"
"\x1a " "?" ENUM5895_1a_TEXT "\0"
"\x1b " "?" ENUM5895_1b_TEXT "\0"
"\x1c " "?" ENUM5895_1c_TEXT "\0"
"\x1d " "?" ENUM5895_1d_TEXT "\0"
"\x1e " "?" ENUM5895_1e_TEXT "\0"
"\x1f " "?" ENUM5895_1f_TEXT "\0"
"\x20 " "?" ENUM5895_20_TEXT "\0"
"\x21 " "?" ENUM5895_21_TEXT "\0"
"\x22 " "?" ENUM5895_22_TEXT "\0"
"\x23 " "?" ENUM5895_23_TEXT "\0"
"\x24 " "?" ENUM5895_24_TEXT "\0"
"\x25 " "?" ENUM5895_25_TEXT "\0"
"\x26 " "?" ENUM5895_26_TEXT "\0"
"\x27 " "?" ENUM5895_27_TEXT "\0"
"\x28 " "?" ENUM5895_28_TEXT "\0"
"\x29 " "?" ENUM5895_29_TEXT "\0"
"\x2a " "?" ENUM5895_2a_TEXT "\0"
"\x2b " "?" ENUM5895_2b_TEXT "\0"
"\x2c " "?" ENUM5895_2c_TEXT "\0"
"\x2d " "?" ENUM5895_2d_TEXT
};

// Konfiguration - Thision 5922 Relaisausgang 1 RelCl
const char ENUM5920[] = {
"\x00 " ENUM5920_00_TEXT "\0"
"\x01 " ENUM5920_01_TEXT "\0"
"\x02 " ENUM5920_02_TEXT "\0"
"\x03 " ENUM5920_03_TEXT "\0"
"\x04 " ENUM5920_04_TEXT "\0"
"\x05 " ENUM5920_05_TEXT "\0"
"\x06 " ENUM5920_06_TEXT "\0"
"\x07 " ENUM5920_07_TEXT "\0"
"\x08 " ENUM5920_08_TEXT "\0"
"\x09 " ENUM5920_09_TEXT "\0"
"\x0a " ENUM5920_0a_TEXT "\0"
"\x0b " ENUM5920_0b_TEXT "\0"
"\x0c " ENUM5920_0c_TEXT "\0"
"\x0d " ENUM5920_0d_TEXT "\0"
"\x0e " ENUM5920_0e_TEXT "\0"
"\x0f " ENUM5920_0f_TEXT "\0"
"\x10 " ENUM5920_10_TEXT "\0"
"\x11 " ENUM5920_11_TEXT
};
#define ENUM5922 ENUM5920               // Thision 5923 Relaisausgang 2 RelCl
#define ENUM5923 ENUM5920               // Thision 5923 Relaisausgang 2 RelCl
#define ENUM5924 ENUM5920               // Thision 5924 Relaisausgang 3 RelCl
#define ENUM5926 ENUM5920               // Thision 5926 Relaisausgang 1 SolCl
#define ENUM5927 ENUM5920               // Thision 5927 Relaisausgang 2 SolCl
#define ENUM5928 ENUM5920               // Thision 5928 Relaisausgang 3 SolCl

// Konfiguration - Fuehlereingang BX1
const char ENUM5930[] = {
"\x00 " ENUM5930_00_TEXT "\0"
"\x01 " ENUM5930_01_TEXT "\0" //B31
"\x02 " ENUM5930_02_TEXT "\0" //B6
"\x03 " ENUM5930_03_TEXT "\0" //B7
"\x04 " ENUM5930_04_TEXT "\0" //B39
"\x05 " ENUM5930_05_TEXT "\0" //B4
"\x06 " ENUM5930_06_TEXT "\0" //B41
"\x07 " ENUM5930_07_TEXT "\0" //B8
"\x08 " ENUM5930_08_TEXT "\0" //B10
"\x09 " ENUM5930_09_TEXT "\0" //B22
"\x0a " ENUM5930_0a_TEXT "\0" //B36
"\x0b " ENUM5930_0b_TEXT "\0" //B42
"\x0c " ENUM5930_0c_TEXT "\0" //B73
"\x0d " ENUM5930_0d_TEXT "\0" //B70
"\x0e " ENUM5930_0e_TEXT "\0" //B13
"\x0f " ENUM5930_0f_TEXT "\0" //B61
"\x10 " ENUM5930_10_TEXT "\0" //B63
"\x11 " ENUM5930_11_TEXT      //B64
};

#define ENUM5931 ENUM5930               // Konfiguration - Fühlereingang BX 2
#define ENUM5932 ENUM5930               // Konfiguration - Fühlereingang BX 3
#define ENUM5933 ENUM5930               // Konfiguration - Fühlereingang BX 4
#define ENUM5941 ENUM5930               // Konfiguration - Fühlereingang BX21
#define ENUM5942 ENUM5930               // Konfiguration - Fühlereingang BX22


// Konfiguration - Funktion Eingang H1 (LOGON B)
const char ENUM5950[] = {
"\x00 " ENUM5950_00_TEXT "\0"
"\x01 " ENUM5950_01_TEXT "\0"
"\x02 " ENUM5950_02_TEXT "\0"
"\x03 " ENUM5950_03_TEXT "\0"
"\x04 " ENUM5950_04_TEXT "\0"
"\x05 " ENUM5950_05_TEXT "\0"
"\x06 " ENUM5950_06_TEXT "\0"
"\x07 " ENUM5950_07_TEXT "\0"
"\x08 " ENUM5950_08_TEXT "\0"
"\x09 " ENUM5950_09_TEXT "\0"
"\x0a " ENUM5950_0a_TEXT "\0"
"\x0b " ENUM5950_0b_TEXT "\0"
"\x0c " ENUM5950_0c_TEXT "\0"
"\x0d " ENUM5950_0d_TEXT "\0"
"\x0e " ENUM5950_0e_TEXT "\0"
"\x34 " ENUM5950_34_TEXT
};

// Konfiguration - Funktion Eingang H1 THISION
const char ENUM5950_2[] = {
"\x00 " ENUM5950_2_00_TEXT "\0"
"\x01 " ENUM5950_2_01_TEXT "\0"
"\x02 " ENUM5950_2_02_TEXT "\0"
"\x03 " ENUM5950_2_03_TEXT "\0"
"\x07 " ENUM5950_2_07_TEXT "\0"
"\x08 " ENUM5950_2_08_TEXT "\0"
"\x09 " ENUM5950_2_09_TEXT
};

// Konfiguration - Funktion Eingang H1 Brötje
const char ENUM5950_3[] = {
"\x01 " ENUM5950_3_01_TEXT "\0"
"\x02 " ENUM5950_3_02_TEXT "\0"
"\x03 " ENUM5950_3_03_TEXT "\0"
"\x04 " ENUM5950_3_04_TEXT "\0"
"\x05 " ENUM5950_3_05_TEXT "\0"
"\x06 " ENUM5950_3_06_TEXT "\0"
"\x07 " ENUM5950_3_07_TEXT "\0"
"\x08 " ENUM5950_3_08_TEXT "\0"
"\x09 " ENUM5950_3_09_TEXT
};

// Konfiguration - Funktion Eingang H1 Brötje BOB
const char ENUM5950_4[] = {
"\x00 " ENUM5950_4_00_TEXT "\0"
"\x01 " ENUM5950_4_01_TEXT "\0"
"\x02 " ENUM5950_4_02_TEXT "\0"
"\x03 " ENUM5950_4_03_TEXT "\0"
"\x04 " ENUM5950_4_04_TEXT "\0"
"\x05 " ENUM5950_4_05_TEXT "\0"
"\x06 " ENUM5950_4_06_TEXT "\0"
"\x07 " ENUM5950_4_07_TEXT "\0"
"\x08 " ENUM5950_4_08_TEXT "\0"
"\x09 " ENUM5950_4_09_TEXT "\0"
"\x0a " ENUM5950_4_0a_TEXT "\0"
"\x0b " ENUM5950_4_0b_TEXT "\0"
"\x0c " ENUM5950_4_0c_TEXT "\0"
"\x0d " ENUM5950_4_0d_TEXT "\0"
"\x0e " ENUM5950_4_0e_TEXT "\0"
"\x0f " ENUM5950_4_0f_TEXT "\0"
"\x10 " ENUM5950_4_10_TEXT "\0"
"\x11 " ENUM5950_4_11_TEXT "\0"
"\x12 " ENUM5950_4_12_TEXT "\0"
"\x13 " ENUM5950_4_13_TEXT "\0"
"\x14 " ENUM5950_4_14_TEXT "\0"
"\x15 " ENUM5950_4_15_TEXT "\0"
"\x16 " ENUM5950_4_16_TEXT "\0"
"\x17 " ENUM5950_4_17_TEXT "\0"
"\x18 " ENUM5950_4_18_TEXT "\0"
"\x1c " ENUM5950_4_1c_TEXT "\0"
"\x1d " ENUM5950_4_1d_TEXT "\0"
"\x1e " ENUM5950_4_1e_TEXT "\0"
"\x1f " ENUM5950_4_1f_TEXT "\0"
"\x20 " ENUM5950_4_20_TEXT "\0"
"\x32 " ENUM5950_4_32_TEXT "\0"
"\x33 " ENUM5950_4_33_TEXT "\0"
"\x34 " ENUM5950_4_34_TEXT "\0"
"\x36 " ENUM5950_4_36_TEXT "\0" //Baxi Luna Platinum+: Druckmessung 10V
"\x38 " ENUM5950_4_38_TEXT
};

#define ENUM5950_5_12_TEXT ENUM5950_4_38_TEXT

const char ENUM5950_5[] = {
"\x01 " ENUM5950_5_01_TEXT "\0"
"\x02 " ENUM5950_5_02_TEXT "\0"
"\x03 " ENUM5950_5_03_TEXT "\0"
"\x04 " ENUM5950_5_04_TEXT "\0"
"\x05 " ENUM5950_5_05_TEXT "\0"
"\x06 " ENUM5950_5_06_TEXT "\0"
"\x07 " ENUM5950_5_07_TEXT "\0"
"\x08 " ENUM5950_5_08_TEXT "\0"
"\x09 " ENUM5950_5_09_TEXT "\0"
"\x0a " ENUM5950_5_0a_TEXT "\0"
"\x0b " ENUM5950_5_0b_TEXT "\0"
"\x0c " ENUM5950_5_0c_TEXT "\0"
"\x0d " ENUM5950_5_0d_TEXT "\0"
"\x0e " ENUM5950_5_0e_TEXT "\0"
"\x0f " ENUM5950_5_0f_TEXT "\0"
"\x11 " ENUM5950_5_11_TEXT "\0"
"\x12 " ENUM5950_5_12_TEXT};

// Konfiguration - Funktion Eingang H1 RVA63.244
const char ENUM5950_6[] = {
"\x00 " ENUM5950_6_00_TEXT "\0"
"\x01 " ENUM5950_6_01_TEXT "\0"
"\x02 " ENUM5950_6_02_TEXT "\0"
"\x03 " ENUM5950_6_03_TEXT "\0"
"\x04 " ENUM5950_6_04_TEXT
};

// Konfiguration - Funktion Eingang H1 LMU64
const char ENUM5950_7[] = {
"\x00 " ENUM5950_7_00_TEXT "\0"
"\x01 " ENUM5950_7_01_TEXT "\0"
"\x02 " ENUM5950_7_02_TEXT "\0"
"\x03 " ENUM5950_7_03_TEXT
};

// Konfiguration - Funktion Eingang H1/F2 LMU64
const char ENUM5950_8[] = {
"\x00 " ENUM5950_2_00_TEXT "\0"
"\x01 " ENUM5950_2_01_TEXT "\0"
"\x02 " ENUM5950_2_02_TEXT "\0"
"\x07 " ENUM5950_2_03_TEXT
};

const char ENUM5951[] = {
"\x00 " ENUM5951_00_TEXT "\0"
"\x01 " ENUM5951_01_TEXT
};

// Konfiguration - 5957 BA-Umschaltung HK's+TWW
const char ENUM5957[] = {
"\x01 " ENUM5957_01_TEXT "\0"
"\x02 " ENUM5957_02_TEXT "\0"
"\x03 " ENUM5957_03_TEXT "\0"
"\x04 " ENUM5957_04_TEXT
};

const char ENUM5957_2[] = {
"\x00 " ENUM5957_2_00_TEXT "\0"
"\x01 " ENUM5957_2_01_TEXT "\0"
"\x02 " ENUM5957_2_02_TEXT "\0"
"\x03 " ENUM5957_2_03_TEXT "\0"
"\x04 " ENUM5957_2_04_TEXT
};

#define ENUM5960 ENUM5950               // Konfiguration - Funktion Eingang H3
#define ENUM5960_2 ENUM5950_2           // Konfiguration - Funktion Eingang H3

const char ENUM5960_3[] = {
"\x00 " ENUM5960_3_00_TEXT "\0"
"\x01 " ENUM5960_3_01_TEXT "\0"
"\x02 " ENUM5960_3_02_TEXT "\0"
"\x03 " ENUM5960_3_03_TEXT
};

const char ENUM5960_4[] = {
"\x00 " ENUM5960_4_00_TEXT
};

#define ENUM5961 ENUM5951               // Konfiguration - Wirksinn Kontakt H3
#define ENUM5961_2 ENUM5951             // Konfiguration - Wirksinn Kontakt H3

// Konfiguration - Thision 5970 Konfig Raumthermostat 1
const char ENUM5970[] = {
"\x00 " ENUM5970_00_TEXT "\0"
"\x01 " ENUM5970_01_TEXT "\0"
"\x02 " ENUM5970_02_TEXT "\0"
"\x03 " ENUM5970_03_TEXT "\0"
"\x04 " ENUM5970_04_TEXT
};
#define ENUM5970_2 ENUM5950_4

#define ENUM5971 ENUM5970               // Thision 5971 Konfig Raumthermostat 2
#define ENUM5971_2 ENUM5951

// Konfiguration - Thision 5973 Funktion Eingang RelCl
const char ENUM5973[] = {
"\x00 " ENUM5973_00_TEXT "\0"
"\x01 " ENUM5973_01_TEXT "\0"
"\x02 " ENUM5973_02_TEXT "\0"
"\x03 " ENUM5973_03_TEXT "\0"
"\x04 " ENUM5973_04_TEXT "\0"
"\x05 " ENUM5973_05_TEXT "\0"
"\x06 " ENUM5973_06_TEXT "\0"
"\x07 " ENUM5973_07_TEXT "\0"
"\x08 " ENUM5973_08_TEXT "\0"
"\x09 " ENUM5973_09_TEXT "\0"
"\x0b " ENUM5973_0b_TEXT
};

#define ENUM5977_2 ENUM5970_2

// Konfiguration - Thision 5978 Funktion Eingang SolCl
const char ENUM5978[] = {
"\x00 " ENUM5978_00_TEXT "\0"
"\x0a " ENUM5978_0a_TEXT
};

#define ENUM5978_2 ENUM5971_2

// 5980 Konfiguration - Funktion Eingang EX1
// The System-Handbuch does not document numerical values.
const char ENUM5980[] = {
"\x00 " ENUM5980_00_TEXT "\0"
"\x01 " ENUM5980_01_TEXT "\0"
"\x02 " ENUM5980_02_TEXT "\0"
"\x03 " "?" ENUM5980_03_TEXT "\0"
"\x04 " "?" ENUM5980_04_TEXT "\0"
"\x05 " "?" ENUM5980_05_TEXT "\0"
"\x06 " "?" ENUM5980_06_TEXT "\0"
"\x07 " "?" ENUM5980_07_TEXT "\0"
"\x08 " "?" ENUM5980_08_TEXT "\0"
"\x09 " "?" ENUM5980_09_TEXT "\0"
"\x0a " "?" ENUM5980_0a_TEXT "\0"
"\x0b " "?" ENUM5980_0b_TEXT "\0"
"\x0c " "?" ENUM5980_0c_TEXT "\0"
"\x0f " ENUM5980_0f_TEXT "\0"
"\x10 " "?" ENUM5980_10_TEXT "\0"
"\x11 " "?" ENUM5980_11_TEXT "\0"
"\x12 " "?" ENUM5980_12_TEXT "\0"
"\x13 " "?" ENUM5980_13_TEXT "\0"
"\x14 " "?" ENUM5980_14_TEXT "\0"
"\x15 " "?" ENUM5980_15_TEXT "\0"
"\x16 " "?" ENUM5980_16_TEXT "\0"
"\x1a " ENUM5980_1a_TEXT
};

#define ENUM5981 ENUM5951               // Konfiguration - Wirksinn Eingang EX1

// Konfiguration - Funktion Eingang EX2
const char ENUM5982[] = {
"\x01 " ENUM5982_01_TEXT "\0"
"\x02 " ENUM5982_02_TEXT "\0"
"\x03 " ENUM5982_03_TEXT "\0"
"\x04 " ENUM5982_04_TEXT "\0"
"\x05 Übertemperaturableitung"};

#define ENUM5983 ENUM5951               // Konfiguration - Wirksinn Eingang EX2
#define ENUM5984 ENUM5980               // Konfiguration - 5984 Funktion Eingang EX3
#define ENUM5985 ENUM5951               // Konfiguration - Wirksinn Eingang EX3
#define ENUM5986 ENUM5980               // Konfiguration - 5986 Funktion Eingang EX4
#define ENUM5987 ENUM5951               // Konfiguration - Wirksinn Eingang EX4
#define ENUM5989 ENUM5951               // Konfiguration - Wirksinn Eingang EX5

// Konfiguration - 5988 Funktion Eingang EX5
// The System-Handbuch does not document numerical values.
// !FIXME! Values here are hypothetical.
const char ENUM5988[] = {
"\x00 " "?" ENUM5988_00_TEXT "\0"
"\x01 " "?" ENUM5988_01_TEXT "\0"
"\x02 " "?" ENUM5988_02_TEXT "\0"
"\x03 " "?" ENUM5988_03_TEXT "\0"
"\x04 " "?" ENUM5988_04_TEXT "\0"
"\x05 " "?" ENUM5988_05_TEXT "\0"
"\x06 " "?" ENUM5988_06_TEXT "\0"
"\x07 " "?" ENUM5988_07_TEXT "\0"
"\x08 " "?" ENUM5988_08_TEXT "\0"
"\x09 " "?" ENUM5988_09_TEXT "\0"
"\x0a " "?" ENUM5988_0a_TEXT "\0"
"\x0b " "?" ENUM5988_0b_TEXT "\0"
"\x0c " "?" ENUM5988_0c_TEXT "\0"
"\x0d " "?" ENUM5988_0d_TEXT "\0"
"\x0e " "?" ENUM5988_0e_TEXT "\0"
"\x0f " "?" ENUM5988_0f_TEXT "\0"
"\x10 " "?" ENUM5988_10_TEXT
};
#define ENUM5990 ENUM5988           // Konfiguration - 5990 Funktion Eingang EX6
#define ENUM5992 ENUM5988           // Konfiguration - 5992 Funktion Eingang EX7

#define ENUM6008_2 ENUM5950_4
#define ENUM6009_2 ENUM5951
#define ENUM6011_2 ENUM5950_4
#define ENUM6012_2 ENUM5951

// Konfiguration - Funktion Mischergruppe 1
const char ENUM6014[] = {
"\x00 " ENUM6014_00_TEXT "\0"
"\x01 " ENUM6014_01_TEXT "\0"
"\x02 " ENUM6014_02_TEXT "\0"           // ISR-SSR Solarsystemregler Handbuch
"\x03 " ENUM6014_03_TEXT "\0"
"\x04 " ENUM6014_04_TEXT "\0"
"\x05 " ENUM6014_05_TEXT "\0"
"\x06 " ENUM6014_06_TEXT
};
#define ENUM6015 ENUM6014           // Konfiguration - 6015 Funktion Mischergruppe 2

// Konfiguration - Funktion Erweiterungsmodul 1
const char ENUM6020[] = {
"\x00 " ENUM6020_00_TEXT "\0"
"\x01 " ENUM6020_01_TEXT "\0"
"\x02 " ENUM6020_02_TEXT "\0"
"\x03 " ENUM6020_03_TEXT "\0"
"\x04 " ENUM6020_04_TEXT "\0"
"\x05 " ENUM6020_05_TEXT "\0"
"\x06 " ENUM6020_06_TEXT "\0"
"\x07 " ENUM6020_07_TEXT "\0"
"\x08 " ENUM6020_08_TEXT
};
#define ENUM6021 ENUM6020           // Konfiguration - Funktion Erweiterungsmodul 2
#define ENUM6022 ENUM6020           // Konfiguration - Funktion Erweiterungsmodul 3


// Konfiguration - Funktion Eingang EX21 Modul 1
const char ENUM6024[] = {
"\x00 " ENUM6024_00_TEXT "\0"
"\x19 " ENUM6024_19_TEXT
};
#define ENUM6026 ENUM6024           // Konfiguration - Funktion Eingang EX21 Modul 2
#define ENUM6028 ENUM6024           // Konfiguration - Funktion Eingang EX21 Modul 3

// The predominant reason why this ProgNr (6030) has been included is the mention of
// Solarstellglied Puffer and Solarstellglied Schwimmbad. My search for these
// names lead me here.  It seems that Relaisausgang QX21 is (a) unused and
// (b) not supported in all installations. (comment by miwi)

// Konfiguration - Relaisausgang QX21
// The Broetje System-Handbuch ISR Plus does not document numerical values;
// inserting hypothetical values.
// !FIXME! !TODO! Figure out the real numerical values.
const char ENUM6030[] = {
"\x00 " ENUM6030_00_TEXT "\0"                           // with all controllers, confirmed
"\x01 " "?" ENUM6030_01_TEXT "\0"          // with      BSW,BLW
"\x02 " "?" ENUM6030_02_TEXT "\0"       // with      BSW,BLW
"\x03 " "?" ENUM6030_03_TEXT "\0"           // with      BSW
"\x04 " "?" ENUM6030_04_TEXT "\0"        // with      BSW,BLW
"\x05 " "?" ENUM6030_05_TEXT "\0"         // with      BSW,BLW
"\x06 " "?" ENUM6030_06_TEXT "\0"   // with      BSW,BLW
"\x07 " "?" ENUM6030_07_TEXT "\0"   // with      BSW,BLW
"\x08 " "?" ENUM6030_08_TEXT "\0"   // with      BSW,BLW
"\x09 " "?" ENUM6030_09_TEXT "\0"           // with      BSW,BLW, BCA,        Kessel L,TE,SOB
"\x0a " "?" ENUM6030_0a_TEXT "\0"          // with SSR, BSW,BLW, BCA,        Kessel L,TE,SOB
"\x0b " "?" ENUM6030_0b_TEXT "\0"      // with SSR, BSW,BLW
"\x0c " "?" ENUM6030_0c_TEXT "\0"              // with SSR, BSW,BLW,             Kessel L,TE,SOB
"\x0d " "?" ENUM6030_0d_TEXT "\0"                   // all controllers
"\x0e " "?" ENUM6030_0e_TEXT "\0"                 // with SSR, BSW,     BCA,        Kessel L,TE,SOB
"\x0f " "?" ENUM6030_0f_TEXT "\0"                // with SSR, BSW,BLW, BCA, ZR1/2, Kessel L,TE,SOB
"\x10 " "?" ENUM6030_10_TEXT "\0"               // with all controllers
"\x11 " "?" ENUM6030_11_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x12 " "?" ENUM6030_12_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x13 " "?" ENUM6030_13_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x14 " "?" ENUM6030_14_TEXT "\0"         // with all controllers
"\x15 " "?" ENUM6030_15_TEXT "\0"                   // with all controllers
"\x16 " "?" ENUM6030_16_TEXT "\0"             // with all controllers
"\x17 " "?" ENUM6030_17_TEXT "\0"         // with SSR, BSW,                 Kessel L,TE,SOB
"\x18 " "?" ENUM6030_18_TEXT "\0"       // with SSR, BSW,BLW, BCA
"\x19 " "?" ENUM6030_19_TEXT "\0"             // with SSR, BSW           ZR1/2
"\x1a " "?" ENUM6030_1a_TEXT "\0"       // with SSR, BSW
"\x1b " "?" ENUM6030_1b_TEXT "\0"    // with SSR, BSW,BLW
"\x1c " "?" ENUM6030_1c_TEXT "\0"      // with SSR, BSW,BLW
"\x1d " "?" ENUM6030_1d_TEXT "\0" // with SSR, BSW,BLW
"\x1e " "?" ENUM6030_1e_TEXT "\0"           // with SSR, BSW
"\x1f " "?" ENUM6030_1f_TEXT "\0"                   // with      BSW,BLW
"\x20 " "?" ENUM6030_20_TEXT "\0"                // with      BSW,     BCA
"\x21 " "?" ENUM6030_21_TEXT "\0"        // with      BSW,BLW,      ZR1/2
"\x22 " "?" ENUM6030_22_TEXT "\0"   // with      BSW
"\x23 " "?" ENUM6030_23_TEXT "\0"                 // with      BSW,BLW
"\x24 " "?" ENUM6030_24_TEXT "\0"                 // with      BSW
"\x25 " "?" ENUM6030_25_TEXT "\0"            // with SSR, BSW,BLW
"\x26 " "?" ENUM6030_26_TEXT "\0"            // with SSR, BSW,BLW       ZR1/2
"\x27 " "?" ENUM6030_27_TEXT "\0"              // with SSR, BSW,BLW, BCA
"\x28 " "?" ENUM6030_28_TEXT "\0"        // with SSR, BSW
"\x29 " "?" ENUM6030_29_TEXT "\0"        // with BSW,          BCA
"\x2a " "?" ENUM6030_2a_TEXT "\0"      // with SSR, BSW,     BCA
"\x2b " "?" ENUM6030_2b_TEXT "\0"           // with      BSW,BLW  BCA, ZR1/2
"\x2c " "?" ENUM6030_2c_TEXT "\0"           // with      BSW,BLW       ZR1/2
"\x2d " "?" ENUM6030_2d_TEXT "\0"           // with          BLW
"\x2e " "?" ENUM6030_2e_TEXT    // with          BLW
};

#define ENUM6030_2 ENUM5890               // Relaisausgang QX21 Modul 1 / Baxi Luna Platinum
#define ENUM6031 ENUM6030
#define ENUM6031_2 ENUM5890               // Relaisausgang QX22 Modul 1 / Baxi Luna Platinum
#define ENUM6032 ENUM6030
#define ENUM6032_2 ENUM5890               // Relaisausgang QX23 Modul 1 / Baxi Luna Platinum

#define ENUM6033 ENUM6030     // Relaisausgang QX21 Modul 2 / identity with 6030: analogous guess
#define ENUM6033_2 ENUM5890               // Relaisausgang QX21 Modul 2 / Baxi Luna Platinum
#define ENUM6034 ENUM6030     // Relaisausgang QX22 Modul 2 / identity with 6030: analogous guess
#define ENUM6034_2 ENUM5890               // Relaisausgang QX22 Modul 2 / Baxi Luna Platinum
#define ENUM6035 ENUM6030     // Relaisausgang QX23 Modul 2 / identity with 6030: analogous guess
#define ENUM6035_2 ENUM5890               // Relaisausgang QX23 Modul 2 / Baxi Luna Platinum

#define ENUM6036 ENUM6030     // Relaisausgang QX21 Modul 3 / identity with 6030: analogous guess
#define ENUM6036_2 ENUM5890               // Relaisausgang QX21 Modul 3 / Baxi Luna Platinum
#define ENUM6037 ENUM6030     // Relaisausgang QX22 Modul 3 / identity with 6030: analogous guess
#define ENUM6037_2 ENUM5890               // Relaisausgang QX22 Modul 3 / Baxi Luna Platinum
#define ENUM6038 ENUM6030     // Relaisausgang QX23 Modul 3 / identity with 6030: analogous guess
#define ENUM6038_2 ENUM5890               // Relaisausgang QX23 Modul 3 / Baxi Luna Platinum

// Konfiguration - 6040 Fühlereingang BX21
const char ENUM6040[] = {
"\x00 " ENUM6040_00_TEXT "\0"
"\x01 " ENUM6040_01_TEXT "\0"
"\x02 " ENUM6040_02_TEXT "\0"
"\x03 " ENUM6040_03_TEXT "\0"
"\x04 " ENUM6040_04_TEXT "\0"
"\x05 " ENUM6040_05_TEXT "\0"
"\x06 " ENUM6040_06_TEXT "\0"
"\x07 " ENUM6040_07_TEXT "\0"
"\x08 " ENUM6040_08_TEXT "\0"
"\x09 " ENUM6040_09_TEXT "\0"
"\x0a " ENUM6040_0a_TEXT "\0"
"\x0b " ENUM6040_0b_TEXT "\0"
"\x0c " ENUM6040_0c_TEXT "\0"
"\x0d " ENUM6040_0d_TEXT "\0"
"\x0e " ENUM6040_0e_TEXT "\0"
"\x0f " ENUM6040_0f_TEXT "\0"
"\x10 " ENUM6040_10_TEXT "\0"
"\x11 " ENUM6040_11_TEXT
};
#define ENUM6041 ENUM6040	// Konfiguration - 6041 Fühlereingang BX22
#define ENUM6042 ENUM6040 // Fühlereingang BX21 Modul 2 / identity with 6040: analogous guess
#define ENUM6043 ENUM6040 // Fühlereingang BX22 Modul 2 / identity with 6040: analogous guess
#define ENUM6044 ENUM6040 // Fühlereingang BX21 Modul 3 / identity with 6040: analogous guess
#define ENUM6045 ENUM6040 // Fühlereingang BX22 Modul 3 / identity with 6040: analogous guess
#define ENUM6046 ENUM5950	// Konfiguration - Funktion Eingang H2
#define ENUM6046_2 ENUM5977_2  // Konfiguration - Funktion Kontakt H2 EM1
#define ENUM6047 ENUM5951	// Konfiguration - Wirksinn Kontakt H2
#define ENUM6047_2 ENUM5978_2  // Konfiguration - Wirksinn Eingang H2 EM1

// 6054 - Eingang H2 Modul 2 Funktionswahl
const char ENUM6054[] = {
"\x00 " "?" ENUM6054_00_TEXT "\0"
"\x01 " "?" ENUM6054_01_TEXT "\0"
"\x02 " "?" ENUM6054_02_TEXT "\0"
"\x03 " "?" ENUM6054_03_TEXT "\0"
"\x04 " "?" ENUM6054_04_TEXT "\0"
"\x05 " "?" ENUM6054_05_TEXT "\0"
"\x06 " "?" ENUM6054_06_TEXT "\0"
"\x07 " "?" ENUM6054_07_TEXT "\0"
"\x08 " "?" ENUM6054_08_TEXT "\0"
"\x09 " "?" ENUM6054_09_TEXT "\0"
"\x0a " "?" ENUM6054_0a_TEXT "\0"
"\x0b " "?" ENUM6054_0b_TEXT "\0"
"\x0c " "?" ENUM6054_0c_TEXT "\0"
"\x0d " "?" ENUM6054_0d_TEXT "\0"
"\x0e " "?" ENUM6054_0e_TEXT "\0"
"\x0f " "?" ENUM6054_0f_TEXT "\0"
"\x10 " "?" ENUM6054_10_TEXT "\0"
"\x11 " "?" ENUM6054_11_TEXT "\0"
"\x12 " "?" ENUM6054_12_TEXT "\0"
"\x13 " "?" ENUM6054_13_TEXT "\0"
"\x14 " "?" ENUM6054_14_TEXT "\0"
"\x15 " "?" ENUM6054_15_TEXT "\0"
"\x16 " "?" ENUM6054_16_TEXT "\0"
"\x19 " "?" ENUM6054_19_TEXT "\0"
"\x1d " "?" ENUM6054_1d_TEXT "\0"
"\x1f " "?" ENUM6054_1f_TEXT "\0"
"\x20 " "?" ENUM6054_20_TEXT "\0"
"\x33 " "?" ENUM6054_33_TEXT "\0"
"\x34 " "?" ENUM6054_34_TEXT "\0"
"\x36 " "?" ENUM6054_36_TEXT "\0"
"\x3a " "?" ENUM6054_3a_TEXT
};

// 6055 - Kontaktart H2 Modul 2
const char ENUM6055[] = {
"\x00 " "?" ENUM6055_00_TEXT "\0"
"\x01 " "?" ENUM6055_01_TEXT
};

// Konfiguration - 6070 Funktion Ausgang UX
const char ENUM6070[] = {
"\x00 " ENUM6070_00_TEXT "\0"
"\x01 " ENUM6070_01_TEXT "\0"
"\x02 " ENUM6070_02_TEXT
};
// Konfiguration - 6071 Signallogik Ausgang UX
const char ENUM6071[] = {
"\x00 " ENUM6071_00_TEXT "\0"
"\x01 " ENUM6071_01_TEXT
};

// 6079 - Signallogik Ausgang UX2
#define ENUM6079 ENUM6071

const char ENUM6085[] = {
"\x00 " ENUM6085_00_TEXT "\0"
"\x01 " ENUM6085_01_TEXT "\0"
"\x02 " ENUM6085_02_TEXT "\0"
"\x04 " ENUM6085_04_TEXT "\0"
"\x05 " ENUM6085_05_TEXT "\0"
"\x06 " ENUM6085_06_TEXT "\0"
"\x07 " ENUM6085_07_TEXT
};

// 6086 - Signallogik Ausgang P1
#define ENUM6086 ENUM6071


// 6090 - Signallogik Ausgang UX3
#define ENUM6090 ENUM6071

// Konfiguration - Fühlertyp Kollektor
const char ENUM6097[] = {
"\x01 " ENUM6097_01_TEXT "\0"
"\x02 " ENUM6097_02_TEXT "\0"
"\x03 " ENUM6097_03_TEXT
};
#define ENUM6101 ENUM6097           // Fühlertyp Abgastemperatur

// Konfiguration - Wärm'anfo bei Ökobetrieb AUS| EIN Trinkwasser | ein
const char ENUM6131[] = {
"\x00 " ENUM6131_00_TEXT "\0"
"\x01 " ENUM6131_01_TEXT "\0"
"\x02 " ENUM6131_02_TEXT
};

const char ENUM6136[] = {
"\x01 " ENUM6136_01_TEXT "\0"
"\x02 " ENUM6136_02_TEXT "\0"
"\x03 " ENUM6136_03_TEXT
};

const char ENUM6148[] = {
"\x00 " ENUM6148_00_TEXT
};

// Konfiguration - KonfigRG0

const char ENUM6230[] = {
"\x00\x01 " ENUM6230_00_01_TEXT "\0"
"\x01\x01 " ENUM6230_01_01_TEXT "\0"
"\x00\x02 " ENUM6230_00_02_TEXT "\0"
"\x02\x02 " ENUM6230_02_02_TEXT "\0"
"\x00\x04 " ENUM6230_00_04_TEXT "\0"
"\x04\x04 " ENUM6230_04_04_TEXT "\0"
"\x00\x08 " ENUM6230_00_08_TEXT "\0"
"\x08\x08 " ENUM6230_08_08_TEXT "\0"
"\x00\x10 " ENUM6230_00_10_TEXT "\0"
"\x10\x10 " ENUM6230_10_10_TEXT "\0"
"\x00\x20 " ENUM6230_00_20_TEXT "\0"
"\x20\x20 " ENUM6230_20_20_TEXT "\0"
"\x00\x40 " ENUM6230_00_40_TEXT "\0"
"\x40\x40 " ENUM6230_40_40_TEXT
};

/*
const char ENUM6344[] = {
"\x06\x04 "
};
*/

// Konfiguration - KonfigRG1

const char ENUM6240[] = {
"\x00\x03 " ENUM6240_00_03_TEXT "\0"
"\x01\x03 " ENUM6240_01_03_TEXT "\0"
"\x02\x03 " ENUM6240_02_03_TEXT "\0"
"\x00\x04 " ENUM6240_00_04_TEXT "\0"
"\x04\x04 " ENUM6240_04_04_TEXT "\0"
"\x00\x08 " ENUM6240_00_08_TEXT "\0"
"\x08\x08 " ENUM6240_08_08_TEXT "\0"
"\x00\x10 " ENUM6240_00_10_TEXT "\0"
"\x10\x10 " ENUM6240_10_10_TEXT "\0"
"\x00\x20 " ENUM6240_00_20_TEXT "\0"
"\x20\x20 " ENUM6240_20_20_TEXT "\0"
"\x00\x80 " ENUM6240_00_80_TEXT "\0"
"\x80\x80 " ENUM6240_80_80_TEXT
};

// 6240 - Funktion Ausgang UX21 Modul 1
const char ENUM6240_2[] = {
"\x00 " "?" ENUM6240_2_00_TEXT "\0"
"\x01 " "?" ENUM6240_2_01_TEXT "\0"
"\x02 " "?" ENUM6240_2_02_TEXT "\0"
"\x03 " "?" ENUM6240_2_03_TEXT "\0"
"\x04 " "?" ENUM6240_2_04_TEXT "\0"
"\x05 " "?" ENUM6240_2_05_TEXT "\0"
"\x06 " "?" ENUM6240_2_06_TEXT "\0"
"\x07 " "?" ENUM6240_2_07_TEXT "\0"
"\x08 " "?" ENUM6240_2_08_TEXT "\0"
"\x09 " "?" ENUM6240_2_09_TEXT "\0"
"\x0a " "?" ENUM6240_2_0a_TEXT "\0"
"\x0c " "?" ENUM6240_2_0c_TEXT "\0"
"\x0d " "?" ENUM6240_2_0d_TEXT "\0"
"\x0e " "?" ENUM6240_2_0e_TEXT "\0"
"\x1e " "?" ENUM6240_2_1e_TEXT
};

// 6241 - Signallogik Ausgang UX21 Modul 1
#define ENUM6241 ENUM6071

// 6242 - Signal Ausgang UX21 Modul 1
#define ENUM6242 ENUM7425

// 6243 - Funktion Ausgang UX22 Modul 1
const char ENUM6243[] = {
"\x00 " "?" ENUM6243_00_TEXT "\0"
"\x01 " "?" ENUM6243_01_TEXT "\0"
"\x02 " "?" ENUM6243_02_TEXT "\0"
"\x03 " "?" ENUM6243_03_TEXT "\0"
"\x04 " "?" ENUM6243_04_TEXT "\0"
"\x05 " "?" ENUM6243_05_TEXT "\0"
"\x06 " "?" ENUM6243_06_TEXT "\0"
"\x07 " "?" ENUM6243_07_TEXT "\0"
"\x08 " "?" ENUM6243_08_TEXT "\0"
"\x09 " "?" ENUM6243_09_TEXT "\0"
"\x0a " "?" ENUM6243_0a_TEXT "\0"
"\x0c " "?" ENUM6243_0c_TEXT "\0"
"\x0d " "?" ENUM6243_0d_TEXT "\0"
"\x0e " "?" ENUM6243_0e_TEXT "\0"
"\x1e " "?" ENUM6243_1e_TEXT
};

// 6244 - Signallogik Ausgang UX22 Modul 1
#define ENUM6244 ENUM6071

// 6245 - Signal Ausgang UX22 Modul 1
#define ENUM6245 ENUM7425

// 6246 - Funktion Ausgang UX21 Modul 2
#define ENUM6246 ENUM6243

// 6247 - Signallogik Ausgang UX21 Modul 2
#define ENUM6247 ENUM6071

// 6248 - Signal Ausgang UX21 Modul 2
#define ENUM6248 ENUM7425

// 6249 - Funktion Ausgang UX22 Modul 2
#define ENUM6249 ENUM6243

// Konfiguration - KonfigRG2

const char ENUM6250[] = {
"\x00\x01 " ENUM6250_00_01_TEXT "\0"
"\x01\x01 " ENUM6250_01_01_TEXT "\0"
"\x00\x02 " ENUM6250_00_02_TEXT "\0"
"\x02\x02 " ENUM6250_02_02_TEXT "\0"
"\x00\x0B " ENUM6250_00_0B_TEXT "\0"
"\x04\x0B " ENUM6250_04_0B_TEXT "\0"
"\x08\x0B " ENUM6250_08_0B_TEXT "\0"
"\x00\x30 " ENUM6250_00_30_TEXT "\0"
"\x10\x30 " ENUM6250_10_30_TEXT "\0"
"\x20\x30 " ENUM6250_20_30_TEXT
};

// 6250 - Signallogik Ausgang UX22 Modul 2
#define ENUM6250_2 ENUM6071

// 6251 - Signal Ausgang UX22 Modul 2
#define ENUM6251 ENUM7425

// 6252 - Funktion Ausgang UX21 Modul 3
#define ENUM6252 ENUM6243

// 6253 - Signallogik Ausgang UX21 Modul 3
#define ENUM6253 ENUM6071

// 6254 - Signal Ausgang UX21 Modul 3
#define ENUM6254 ENUM7425

// 6255 - Funktion Ausgang UX22 Modul 3
#define ENUM6255 ENUM6243

// 6256 - Signallogik Ausgang UX22 Modul 3
#define ENUM6256 ENUM6071

// 6257 - Signal Ausgang UX22 Modul 3
#define ENUM6257 ENUM7425

// Konfiguration - KonfigRG3

const char ENUM6260[] = {
"\x01\x1F " ENUM6260_01_1F_TEXT "\0"
"\x02\x1F " ENUM6260_02_1F_TEXT "\0"
"\x03\x1F " ENUM6260_03_1F_TEXT "\0"
"\x04\x1F " ENUM6260_04_1F_TEXT "\0"
"\x05\x1F " ENUM6260_05_1F_TEXT "\0"
"\x06\x1F " ENUM6260_06_1F_TEXT "\0"
"\x07\x1F " ENUM6260_07_1F_TEXT "\0"
"\x00\x20 " ENUM6260_00_20_TEXT "\0"
"\x20\x20 " ENUM6260_20_20_TEXT "\0"
"\x00\x40 " ENUM6260_00_40_TEXT "\0"
"\x40\x40 " ENUM6260_40_40_TEXT "\0"
"\x00\x80 " ENUM6260_00_80_TEXT "\0"
"\x80\x80 " ENUM6260_80_80_TEXT
};

// Konfiguration - KonfigRG4

const char ENUM6270[] = {
"\x00\x01 " ENUM6270_00_01_TEXT "\0"
"\x01\x01 " ENUM6270_01_01_TEXT "\0"
"\x00\x02 " ENUM6270_00_02_TEXT "\0"
"\x02\x02 " ENUM6270_02_02_TEXT "\0"
"\x00\x04 " ENUM6270_00_04_TEXT "\0"
"\x04\x04 " ENUM6270_04_04_TEXT "\0"
"\x00\xE0 " ENUM6270_00_E0_TEXT "\0"
"\x20\xE0 " ENUM6270_20_E0_TEXT "\0"
"\x40\xE0 " ENUM6270_40_E0_TEXT "\0"
"\x60\xE0 " ENUM6270_60_E0_TEXT
};

const char ENUM6272[] = {
"\x00 " ENUM6272_00_TEXT "\0"
"\x06 " ENUM6272_06_TEXT "\0"
"\x07 " ENUM6272_07_TEXT "\0"
"\x08 " ENUM6272_08_TEXT "\0"
"\x09 " ENUM6272_09_TEXT "\0"
"\x0B " ENUM6272_0B_TEXT "\0"
"\x0C " ENUM6272_0C_TEXT "\0"
"\x0D " ENUM6272_0D_TEXT "\0"
"\x0E " ENUM6272_0E_TEXT "\0"
"\x15 " ENUM6272_15_TEXT "\0"
"\x18 " ENUM6272_18_TEXT
};

// Konfiguration - KonfigRG5

const char ENUM6280[] = {
"\x00\x03 " ENUM6280_00_03_TEXT "\0"
"\x01\x03 " ENUM6280_01_03_TEXT "\0"
"\x02\x03 " ENUM6280_02_03_TEXT "\0"
"\x03\x03 " ENUM6280_03_03_TEXT "\0"
"\x00\x04 " ENUM6280_00_04_TEXT "\0"
"\x04\x04 " ENUM6280_04_04_TEXT "\0"
"\x00\xF8 " ENUM6280_00_F8_TEXT
};

// Konfiguration - KonfigRG6

const char ENUM6290[] = {
"\x00\x01 " ENUM6290_00_01_TEXT "\0"
"\x01\x01 " ENUM6290_01_01_TEXT "\0"
"\x00\x02 " ENUM6290_00_02_TEXT "\0"
"\x02\x02 " ENUM6290_02_02_TEXT "\0"
"\x00\x04 " ENUM6290_00_04_TEXT "\0"
"\x04\x04 " ENUM6290_04_04_TEXT "\0"
"\x00\x08 " ENUM6290_00_08_TEXT "\0"
"\x08\x08 " ENUM6290_08_08_TEXT "\0"
"\x00\x20 " ENUM6290_00_20_TEXT "\0"
"\x20\x20 " ENUM6290_20_20_TEXT "\0"
"\x00\x40 " ENUM6290_00_40_TEXT "\0"
"\x40\x40 " ENUM6290_40_40_TEXT "\0"
"\x00\x80 " ENUM6290_00_80_TEXT "\0"
"\x80\x80 " ENUM6290_80_80_TEXT
};

// Konfiguration - KonfigRG7

const char ENUM6300[] = {
"\x00\x01 " ENUM6300_00_01_TEXT "\0"
"\x01\x01 " ENUM6300_01_01_TEXT "\0"
"\x00\x02 " ENUM6300_00_02_TEXT "\0"
"\x02\x02 " ENUM6300_02_02_TEXT "\0"
"\x00\x04 " ENUM6300_00_04_TEXT "\0"
"\x04\x04 " ENUM6300_04_04_TEXT "\0"
"\x00\x18 " ENUM6300_00_18_TEXT "\0"
"\x08\x18 " ENUM6300_08_18_TEXT "\0"
"\x10\x18 " ENUM6300_10_18_TEXT "\0"
"\x00\x20 " ENUM6300_00_20_TEXT "\0"
"\x20\x20 " ENUM6300_20_20_TEXT "\0"
"\x00\x40 " ENUM6300_00_40_TEXT "\0"
"\x40\x40 " ENUM6300_40_40_TEXT "\0"
"\x00\x80 " ENUM6300_00_80_TEXT "\0"
"\x80\x80 " ENUM6300_80_80_TEXT
};

// Konfiguration - KonfigRG8

const char ENUM6310[] = {
"\x00\x0F " ENUM6310_00_0F_TEXT "\0"
"\x01\x0F " ENUM6310_01_0F_TEXT "\0"
"\x02\x0F " ENUM6310_02_0F_TEXT "\0"
"\x00\x10 " ENUM6310_00_10_TEXT "\0"
"\x10\x10 " ENUM6310_10_10_TEXT "\0"
"\x00\x20 " ENUM6310_00_20_TEXT "\0"
"\x20\x20 " ENUM6310_20_20_TEXT "\0"
"\x00\x40 " ENUM6310_00_40_TEXT "\0"
"\x40\x40 " ENUM6310_40_40_TEXT
};

// Konfiguration - KonfigRG10

const char ENUM6330[] = {
"\x00\x01 " ENUM6330_00_01_TEXT "\0"
"\x01\x01 " ENUM6330_01_01_TEXT "\0"
"\x00\x02 " ENUM6330_00_02_TEXT "\0"
"\x02\x02 " ENUM6330_02_02_TEXT "\0"
"\x00\x04 " ENUM6330_00_04_TEXT "\0"
"\x04\x04 " ENUM6330_04_04_TEXT "\0"
"\x00\x08 " ENUM6330_00_08_TEXT "\0"
"\x08\x08 " ENUM6330_08_08_TEXT "\0"
"\x00\x10 " ENUM6330_00_10_TEXT "\0"
"\x10\x10 " ENUM6330_10_10_TEXT "\0"
"\x00\x20 " ENUM6330_00_20_TEXT "\0"
"\x20\x20 " ENUM6330_20_20_TEXT "\0"
"\x00\x40 " ENUM6330_00_40_TEXT "\0"
"\x40\x40 " ENUM6330_40_40_TEXT
};

// 6351 - Funktion OT Kanal 1 logged from 92/100/AVS37.294/100
const char ENUM6351[] = {
"\x00 " "?" ENUM6351_00_TEXT "\0"
"\x01 " "?" ENUM6351_01_TEXT "\0"
"\x02 " "?" ENUM6351_02_TEXT "\0"
"\x03 " "?" ENUM6351_03_TEXT "\0"
"\x04 " "?" ENUM6351_04_TEXT
};

#define ENUM6352 ENUM6351
#define ENUM6359 ENUM6351

// Konfiguration - Relaisausgang QX35  //FUJITSU
const char ENUM6375[] = {
"\x00 " ENUM6375_00_TEXT "\0"
"\x02 " ENUM6375_02_TEXT "\0"
"\x03 " ENUM6375_03_TEXT "\0"
"\x04 " ENUM6375_04_TEXT "\0"
"\x05 " ENUM6375_05_TEXT "\0"
"\x06 " ENUM6375_06_TEXT "\0"
"\x07 " ENUM6375_07_TEXT "\0"
"\x08 " ENUM6375_08_TEXT "\0"
"\x09 " ENUM6375_09_TEXT "\0"
"\x0a " ENUM6375_0a_TEXT "\0"
"\x0b " ENUM6375_0b_TEXT "\0"
"\x0c " ENUM6375_0c_TEXT "\0"
"\x0d " ENUM6375_0d_TEXT "\0"
"\x0e " ENUM6375_0e_TEXT "\0"
"\x0f " ENUM6375_0f_TEXT "\0"
"\x10 " ENUM6375_10_TEXT "\0"
"\x11 " ENUM6375_11_TEXT "\0"
"\x12 " ENUM6375_12_TEXT "\0"
"\x13 " ENUM6375_13_TEXT "\0"
"\x14 " ENUM6375_14_TEXT "\0"
"\x15 " ENUM6375_15_TEXT "\0"
"\x16 " ENUM6375_16_TEXT "\0"
"\x17 " ENUM6375_17_TEXT "\0"
"\x18 " ENUM6375_18_TEXT "\0"
"\x19 " ENUM6375_19_TEXT "\0"
"\x1a " ENUM6375_1a_TEXT "\0"
"\x1b " ENUM6375_1b_TEXT "\0"
"\x1c " ENUM6375_1c_TEXT "\0"
"\x1d " ENUM6375_1d_TEXT "\0"
"\x1e " ENUM6375_1e_TEXT "\0"
"\x1f " ENUM6375_1f_TEXT "\0"
"\x20 " ENUM6375_20_TEXT "\0"
"\x21 " ENUM6375_21_TEXT "\0"
"\x22 " ENUM6375_22_TEXT "\0"
"\x23 " ENUM6375_23_TEXT "\0"
"\x24 " ENUM6375_24_TEXT "\0"
"\x25 " ENUM6375_25_TEXT "\0"
"\x26 " ENUM6375_26_TEXT "\0"
"\x27 " ENUM6375_27_TEXT "\0"
"\x28 " ENUM6375_28_TEXT "\0"
"\x29 " ENUM6375_29_TEXT "\0"
"\x2a " ENUM6375_2a_TEXT "\0"
"\x2b " ENUM6375_2b_TEXT "\0"
"\x2c " ENUM6375_2c_TEXT "\0"
"\x2d " ENUM6375_2d_TEXT "\0"
"\x2e " ENUM6375_2e_TEXT "\0"
"\x2f " ENUM6375_2f_TEXT "\0"
"\x30 " ENUM6375_30_TEXT "\0"
"\x31 " ENUM6375_31_TEXT "\0"
"\x32 " ENUM6375_32_TEXT "\0"
"\x33 " ENUM6375_33_TEXT "\0"
"\x34 " ENUM6375_34_TEXT "\0"
"\x35 " ENUM6375_35_TEXT "\0"
"\x36 " ENUM6375_36_TEXT "\0"
"\x37 " ENUM6375_37_TEXT "\0"
"\x38 " ENUM6375_38_TEXT "\0"
"\x39 " ENUM6375_39_TEXT "\0"
"\x3a " ENUM6375_3a_TEXT "\0"
"\x3b " ENUM6375_3b_TEXT "\0"
"\x3c " ENUM6375_3c_TEXT
};

// Konfiguration - Funktion Eingang H33  //FUJITSU
const char ENUM6420[] = {
"\x00 " ENUM6420_00_TEXT "\0"
"\x01 " ENUM6420_01_TEXT "\0"
"\x02 " ENUM6420_02_TEXT "\0"
"\x03 " ENUM6420_03_TEXT "\0"
"\x04 " ENUM6420_04_TEXT "\0"
"\x05 " ENUM6420_05_TEXT "\0"
"\x06 " ENUM6420_06_TEXT "\0"
"\x07 " ENUM6420_07_TEXT "\0"
"\x08 " ENUM6420_08_TEXT "\0"
"\x09 " ENUM6420_09_TEXT "\0"
"\x0a " ENUM6420_0a_TEXT "\0"
"\x0b " ENUM6420_0b_TEXT "\0"
"\x0c " ENUM6420_0c_TEXT "\0"
"\x0d " ENUM6420_0d_TEXT
};

#define ENUM6421 ENUM5951               // Konfiguration - Wirksinn Kontakt H33 //FUJITSU

// LPB   - Busspeisung Funktion
const char ENUM6604[] = {
"\x00 " ENUM6604_00_TEXT "\0"
"\x01 " ENUM6604_01_TEXT
};

// LPB   - LPBKonfig0

const char ENUM6606[] = {
"\x00\x03 " ENUM6606_00_03_TEXT "\0"
"\x01\x03 " ENUM6606_01_03_TEXT "\0"
"\x02\x03 " ENUM6606_02_03_TEXT "\0"
"\x03\x03 " ENUM6606_03_03_TEXT "\0"
"\x00\x04 " ENUM6606_00_04_TEXT "\0"
"\x04\x04 " ENUM6606_04_04_TEXT "\0"
"\x00\x08 " ENUM6606_00_08_TEXT "\0"
"\x08\x08 " ENUM6606_08_08_TEXT "\0"
"\x00\x10 " ENUM6606_00_10_TEXT "\0"
"\x10\x10 " ENUM6606_10_10_TEXT "\0"
"\x00\x60 " ENUM6606_00_60_TEXT "\0"
"\x20\x60 " ENUM6606_20_60_TEXT "\0"
"\x40\x60 " ENUM6606_40_60_TEXT "\0"
"\x00\x80 " ENUM6606_00_80_TEXT "\0"
"\x80\x80 " ENUM6606_80_80_TEXT
};

// LPB   - Wirkbereich Umschaltungen
// Looks like a choice (VT_YESNO, VT_ONOFF, etc)
const char ENUM6620[] = {
"\x00 " ENUM6620_00_TEXT "\0"
"\x01 " ENUM6620_01_TEXT
//"\xff " ENUM6620_ff_TEXT
};

// LPB   - Sommerumschaltung
// Looks like a choice (VT_YESNO, VT_ONOFF, etc)
const char ENUM6621[] = {
"\x00 " ENUM6621_00_TEXT "\0"
"\x01 " ENUM6621_01_TEXT
//"\xff " ENUM6621_ff_TEXT
};

#define ENUM6623 ENUM6621
#define ENUM6624 ENUM6621

// LPB   - Trinkwasserzuordnung
// Texts in the ACS Programm: "Eigener Regler", "Alle Regler im eigenen Segment", "Alle Regler im Verbund"
const char ENUM6625[] = {
"\x00 " ENUM6625_00_TEXT "\0"
"\x01 " ENUM6625_01_TEXT "\0"
"\x02 " ENUM6625_02_TEXT
};

#define ENUM6627 ENUM6623

const char ENUM6630[] = { // numerical values are hypothetical
"\x01 " ENUM6630_01_TEXT "\0"
"\x02 " ENUM6630_02_TEXT
};

const char ENUM6631[] = {	// numerical values are hypothetical
"\x00 " ENUM6631_00_TEXT "\0"
"\x01 " ENUM6631_01_TEXT "\0"
"\x02 " ENUM6631_02_TEXT
};

// LPB   - Uhrbetrieb
const char ENUM6640[] = {
"\x00 " ENUM6640_00_TEXT "\0"
"\x01 " ENUM6640_01_TEXT "\0"
"\x02 " ENUM6640_02_TEXT "\0"
"\x03 " ENUM6640_03_TEXT
};

// 6652 - Modbus Baudrate
const char ENUM6652[] = {
"\x00 " "?" ENUM6652_00_TEXT "\0"
"\x01 " "?" ENUM6652_01_TEXT "\0"
"\x02 " "?" ENUM6652_02_TEXT "\0"
"\x03 " "?" ENUM6652_03_TEXT "\0"
"\x04 " "?" ENUM6652_04_TEXT "\0"
"\x05 " "?" ENUM6652_05_TEXT "\0"
"\x06 " "?" ENUM6652_06_TEXT "\0"
"\x07 " "?" ENUM6652_07_TEXT "\0"
"\x08 " "?" ENUM6652_08_TEXT
};

// 6653 - Modbus Parität
const char ENUM6653[] = {
"\x00 " "?" ENUM6653_00_TEXT "\0"
"\x01 " "?" ENUM6653_01_TEXT "\0"
"\x02 " "?" ENUM6653_02_TEXT
};

// FA Phase
const char ENUM6706[] = {
"\x00 " ENUM6706_00_TEXT "\0"
"\x01 " ENUM6706_01_TEXT "\0"
"\x02 " ENUM6706_02_TEXT "\0"
"\x03 " ENUM6706_03_TEXT "\0"
"\x04 " ENUM6706_04_TEXT "\0"
"\x05 " ENUM6706_05_TEXT "\0"
"\x06 " ENUM6706_06_TEXT "\0"
"\x07 " ENUM6706_07_TEXT "\0"
"\x0a " ENUM6706_0a_TEXT "\0"
"\x0b " ENUM6706_0b_TEXT "\0"
"\x0c " ENUM6706_0c_TEXT "\0"
"\x14 " ENUM6706_14_TEXT "\0"
"\x15 " ENUM6706_15_TEXT "\0"
"\x16 " ENUM6706_16_TEXT "\0"
"\x63 " ENUM6706_63_TEXT
};

// !TODO! ProgNo 6670 is not defined elsewhere
const char ENUM6670[] = {
"\x00 " ENUM6670_00_TEXT "\0"
"\x01 " ENUM6670_01_TEXT "\0"
"\x02 " ENUM6670_02_TEXT
};

#define ENUM7119 ENUM2920    // ProgNr 7119 "Ökofunktion" FUJITSU

const char ENUM7131[] = {
"\x01 " ENUM7131_01_TEXT "\0"         // ENUM-Wert überprüfen!
"\x02 " ENUM7131_02_TEXT "\0"
"\x03 " ENUM7131_03_TEXT  // ENUM-Wert überprüfen!
};

const char ENUM7142[] = {
"\x01 " ENUM7142_01_TEXT "\0"
"\x02 " ENUM7142_02_TEXT
};

const char ENUM7147[] = {
"\x00 " ENUM7147_00_TEXT "\0"
"\x01 " ENUM7147_01_TEXT "\0"
"\x02 " ENUM7147_02_TEXT "\0"
"\x03 " ENUM7147_03_TEXT "\0"
"\x04 " ENUM7147_04_TEXT
}; // todo Hinweis: x00 Keine ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM7244[] = {
"\x00 " ENUM6024_00_TEXT "\0" //"Keine"
"\x01 " ENUM7244_01_TEXT "\0"
"\x02 " ENUM7244_02_TEXT "\0"
"\x03 " ENUM7244_03_TEXT "\0"
"\x04 " ENUM7244_04_TEXT "\0"
"\x05 " ENUM7244_05_TEXT
};

const char ENUM7252[] = {
"\x00 " ENUM7252_00_TEXT "\0"
"\x01 " ENUM7252_01_TEXT "\0"
"\x02 " ENUM7252_02_TEXT
};

// 7300 - Funktion Erweiterungsmodul 1
const char ENUM7300[] = {
"\x00 " "?" ENUM7300_00_TEXT "\0"
"\x01 " "?" ENUM7300_01_TEXT "\0"
"\x02 " "?" ENUM7300_02_TEXT "\0"
"\x03 " "?" ENUM7300_03_TEXT "\0"
"\x04 " "?" ENUM7300_04_TEXT "\0"
"\x05 " "?" ENUM7300_05_TEXT "\0"
"\x06 " "?" ENUM7300_06_TEXT "\0"
"\x07 " "?" ENUM7300_07_TEXT "\0"
"\x08 " "?" ENUM7300_08_TEXT "\0"
"\x09 " "?" ENUM7300_09_TEXT "\0"
"\x0a " "?" ENUM7300_0a_TEXT "\0"
"\x0b " "?" ENUM7300_0b_TEXT "\0"
"\x0c " "?" ENUM7300_0c_TEXT "\0"
"\x0d " "?" ENUM7300_0d_TEXT
};

// 7301 - Relaisausgang QX21 Modul 1
const char ENUM7301[] = {
"\x00 " "?" ENUM7301_00_TEXT "\0"
"\x01 " "?" ENUM7301_01_TEXT "\0"
"\x02 " "?" ENUM7301_02_TEXT "\0"
"\x04 " "?" ENUM7301_04_TEXT "\0"
"\x05 " "?" ENUM7301_05_TEXT "\0"
"\x07 " "?" ENUM7301_07_TEXT "\0"
"\x0b " "?" ENUM7301_0b_TEXT "\0"
"\x0c " "?" ENUM7301_0c_TEXT "\0"
"\x0d " "?" ENUM7301_0d_TEXT "\0"
"\x0e " "?" ENUM7301_0e_TEXT "\0"
"\x10 " "?" ENUM7301_10_TEXT "\0"
"\x14 " "?" ENUM7301_14_TEXT "\0"
"\x16 " "?" ENUM7301_16_TEXT "\0"
"\x19 " "?" ENUM7301_19_TEXT "\0"
"\x1b " "?" ENUM7301_1b_TEXT "\0"
"\x1c " "?" ENUM7301_1c_TEXT "\0"
"\x1d " "?" ENUM7301_1d_TEXT "\0"
"\x21 " "?" ENUM7301_21_TEXT "\0"
"\x22 " "?" ENUM7301_22_TEXT "\0"
"\x28 " "?" ENUM7301_28_TEXT "\0"
"\x29 " "?" ENUM7301_29_TEXT "\0"
"\x2b " "?" ENUM7301_2b_TEXT "\0"
"\x2d " "?" ENUM7301_2d_TEXT "\0"
"\x2e " "?" ENUM7301_2e_TEXT
};

#define ENUM7302 ENUM7301
#define ENUM7303 ENUM7301

// 7307 - Fühlereingang BX21 Modul 1
const char ENUM7307[] = {
"\x00 " "?" ENUM7307_00_TEXT "\0"
"\x01 " "?" ENUM7307_01_TEXT "\0"
"\x04 " "?" ENUM7307_04_TEXT "\0"
"\x08 " "?" ENUM7307_08_TEXT "\0"
"\x0a " "?" ENUM7307_0a_TEXT "\0"
"\x0c " "?" ENUM7307_0c_TEXT "\0"
"\x0d " "?" ENUM7307_0d_TEXT "\0"
"\x0e " "?" ENUM7307_0e_TEXT "\0"
"\x10 " "?" ENUM7307_10_TEXT "\0"
"\x11 " "?" ENUM7307_11_TEXT
};

#define ENUM7308 ENUM7307

// 7321 - Eingang H2/H21 Modul 1 Funktionswahl
const char ENUM7321[] = {
"\x00 " "?" ENUM7321_00_TEXT "\0"
"\x01 " "?" ENUM7321_01_TEXT "\0"
"\x02 " "?" ENUM7321_02_TEXT "\0"
"\x03 " "?" ENUM7321_03_TEXT "\0"
"\x04 " "?" ENUM7321_04_TEXT "\0"
"\x05 " "?" ENUM7321_05_TEXT "\0"
"\x06 " "?" ENUM7321_06_TEXT "\0"
"\x07 " "?" ENUM7321_07_TEXT "\0"
"\x08 " "?" ENUM7321_08_TEXT "\0"
"\x09 " "?" ENUM7321_09_TEXT "\0"
"\x0a " "?" ENUM7321_0a_TEXT "\0"
"\x0b " "?" ENUM7321_0b_TEXT "\0"
"\x0c " "?" ENUM7321_0c_TEXT "\0"
"\x0e " "?" ENUM7321_0e_TEXT "\0"
"\x0f " "?" ENUM7321_0f_TEXT "\0"
"\x10 " "?" ENUM7321_10_TEXT "\0"
"\x11 " "?" ENUM7321_11_TEXT "\0"
"\x12 " "?" ENUM7321_12_TEXT "\0"
"\x13 " "?" ENUM7321_13_TEXT "\0"
"\x14 " "?" ENUM7321_14_TEXT "\0"
"\x19 " "?" ENUM7321_19_TEXT "\0"
"\x1d " "?" ENUM7321_1d_TEXT "\0"
"\x33 " "?" ENUM7321_33_TEXT "\0"
"\x34 " "?" ENUM7321_34_TEXT "\0"
"\x3a " "?" ENUM7321_3a_TEXT
};

// 7322 - Kontaktart H2/H21 Modul 1
const char ENUM7322[] = {
"\x00 " "?" ENUM7322_00_TEXT "\0"
"\x01 " "?" ENUM7322_01_TEXT
};

#define ENUM7342 ENUM7492

// 7348 - Funktion Ausgang UX21 Modul 1

const char ENUM7348[] = {
"\x00 " "?" ENUM7348_00_TEXT "\0"
"\x01 " "?" ENUM7348_01_TEXT "\0"
"\x02 " "?" ENUM7348_02_TEXT "\0"
"\x03 " "?" ENUM7348_03_TEXT "\0"
"\x04 " "?" ENUM7348_04_TEXT "\0"
"\x05 " "?" ENUM7348_05_TEXT "\0"
"\x06 " "?" ENUM7348_06_TEXT "\0"
"\x07 " "?" ENUM7348_07_TEXT "\0"
"\x08 " "?" ENUM7348_08_TEXT "\0"
"\x09 " "?" ENUM7348_09_TEXT "\0"
"\x0a " "?" ENUM7348_0a_TEXT "\0"
"\x0c " "?" ENUM7348_0c_TEXT "\0"
"\x0d " "?" ENUM7348_0d_TEXT "\0"
"\x0e " "?" ENUM7348_0e_TEXT "\0"
"\x1e " "?" ENUM7348_1e_TEXT
};

const char ENUM7348_2[] = {
"\x00 " "?" ENUM7348_2_00_TEXT "\0"
"\x01 " "?" ENUM7348_2_01_TEXT "\0"
"\x02 " "?" ENUM7348_2_02_TEXT "\0"
"\x03 " "?" ENUM7348_2_03_TEXT "\0"
"\x04 " "?" ENUM7348_2_04_TEXT "\0"
"\x05 " "?" ENUM7348_2_05_TEXT "\0"
"\x06 " "?" ENUM7348_2_06_TEXT "\0"
"\x07 " "?" ENUM7348_2_07_TEXT "\0"
"\x08 " "?" ENUM7348_2_08_TEXT "\0"
"\x09 " "?" ENUM7348_2_09_TEXT "\0"
"\x0a " "?" ENUM7348_2_0a_TEXT "\0"
"\x0b " "?" ENUM7348_2_0b_TEXT "\0"
"\x0c " "?" ENUM7348_2_0c_TEXT "\0"
"\x0d " "?" ENUM7348_2_0d_TEXT "\0"
"\x0f " "?" ENUM7348_2_0f_TEXT "\0"
"\x1a " "?" ENUM7348_2_1a_TEXT "\0"
"\x1b " "?" ENUM7348_2_1b_TEXT "\0"
"\x1c " "?" ENUM7348_2_1c_TEXT "\0"
"\x1d " "?" ENUM7348_2_1d_TEXT "\0"
"\x1e " "?" ENUM7348_2_1e_TEXT "\0"
"\x1f " "?" ENUM7348_2_1f_TEXT "\0"
"\x20 " "?" ENUM7348_2_20_TEXT "\0"
"\x21 " "?" ENUM7348_2_21_TEXT "\0"
"\x22 " "?" ENUM7348_2_22_TEXT "\0"
"\x23 " "?" ENUM7348_2_23_TEXT
};

#define ENUM7349 ENUM6071
#define ENUM7350 ENUM7425
#define ENUM7357 ENUM7425
#define ENUM7356 ENUM6071
#define ENUM7355 ENUM6243

// 7375 - Funktion Erweiterungsmodul 2
const char ENUM7375[] = {
"\x00 " "?" ENUM7375_00_TEXT "\0"
"\x01 " "?" ENUM7375_01_TEXT "\0"
"\x02 " "?" ENUM7375_02_TEXT "\0"
"\x03 " "?" ENUM7375_03_TEXT "\0"
"\x04 " "?" ENUM7375_04_TEXT "\0"
"\x06 " "?" ENUM7375_06_TEXT "\0"
"\x07 " "?" ENUM7375_07_TEXT "\0"
"\x08 " "?" ENUM7375_08_TEXT "\0"
"\x09 " "?" ENUM7375_09_TEXT "\0"
"\x0b " "?" ENUM7375_0b_TEXT "\0"
"\x0c " "?" ENUM7375_0c_TEXT "\0"
"\x0d " "?" ENUM7375_0d_TEXT "\0"
"\x10 " "?" ENUM7375_10_TEXT "\0"
"\x11 " "?" ENUM7375_11_TEXT "\0"
"\x14 " "?" ENUM7375_14_TEXT
};

// Konfiguration Erweit'module - Relaisausgang QX21 Modul 2
const char ENUM7376[] = {
"\x00 " ENUM7376_00_TEXT "\0"
"\x01 " ENUM7376_01_TEXT "\0"
"\x02 " ENUM7376_02_TEXT "\0"
"\x03 " ENUM7376_03_TEXT "\0"
"\x04 " ENUM7376_04_TEXT "\0"
"\x05 " ENUM7376_05_TEXT "\0"
"\x06 " ENUM7376_06_TEXT "\0"
"\x07 " ENUM7376_07_TEXT "\0"
"\x08 " ENUM7376_08_TEXT "\0"
"\x09 " ENUM7376_09_TEXT "\0"
"\x0a " ENUM7376_0a_TEXT "\0"
"\x0b " ENUM7376_0b_TEXT "\0"
"\x0c " ENUM7376_0c_TEXT "\0"
"\x0d " ENUM7376_0d_TEXT "\0"
"\x0e " ENUM7376_0e_TEXT "\0"
"\x0f " ENUM7376_0f_TEXT "\0"
"\x10 " ENUM7376_10_TEXT "\0"
"\x11 " ENUM7376_11_TEXT "\0"
"\x12 " ENUM7376_12_TEXT "\0"
"\x13 " ENUM7376_13_TEXT "\0"
"\x14 " ENUM7376_14_TEXT "\0"
"\x15 " ENUM7376_15_TEXT "\0"
"\x16 " ENUM7376_16_TEXT "\0"
"\x17 " ENUM7376_17_TEXT "\0"
"\x19 " ENUM7376_19_TEXT "\0"
"\x1a " ENUM7376_1a_TEXT "\0"
"\x1b " ENUM7376_1b_TEXT "\0"
"\x1c " ENUM7376_1c_TEXT "\0"
"\x1d " ENUM7376_1d_TEXT "\0"
"\x21 " ENUM7376_21_TEXT "\0"
"\x28 " ENUM7376_28_TEXT "\0"
"\x29 " ENUM7376_29_TEXT };

#define ENUM7396 ENUM7321
#define ENUM7397 ENUM6055
#define ENUM7424 ENUM6071

const char ENUM7425[] = {
"\x00 " ENUM7425_00_TEXT "\0"
"\x01 " ENUM7425_01_TEXT
};

#define ENUM7431 ENUM6071

// 7450 - Funktion Erweiterungsmodul 3
const char ENUM7450[] = {
"\x00 " "?" ENUM7450_00_TEXT "\0"
"\x01 " "?" ENUM7450_01_TEXT "\0"
"\x02 " "?" ENUM7450_02_TEXT "\0"
"\x03 " "?" ENUM7450_03_TEXT "\0"
"\x04 " "?" ENUM7450_04_TEXT "\0"
"\x05 " "?" ENUM7450_05_TEXT "\0"
"\x06 " "?" ENUM7450_06_TEXT "\0"
"\x07 " "?" ENUM7450_07_TEXT "\0"
"\x08 " "?" ENUM7450_08_TEXT "\0"
"\x09 " "?" ENUM7450_09_TEXT "\0"
"\x0a " "?" ENUM7450_0a_TEXT "\0"
"\x0b " "?" ENUM7450_0b_TEXT "\0"
"\x0c " "?" ENUM7450_0c_TEXT "\0"
"\x0d " "?" ENUM7450_0d_TEXT
};

#define ENUM7451 ENUM7302
#define ENUM7452 ENUM7302
#define ENUM7453 ENUM7302
#define ENUM7457 ENUM7307
#define ENUM7458 ENUM7307
#define ENUM7471 ENUM7396
#define ENUM7472 ENUM6055

// 7492 - Funktion Eingang EX21 Modul 3
const char ENUM7492[] = {
"\x00 " "?" ENUM7492_00_TEXT "\0"
"\x19 " "?" ENUM7492_19_TEXT
};

#define ENUM7498 ENUM6243
#define ENUM7499 ENUM6071
#define ENUM7500 ENUM7425
#define ENUM7505 ENUM6243
#define ENUM7506 ENUM6071
#define ENUM7507 ENUM7425

// Ein-/Ausgangstest - Relaistest
const char ENUM7700[] = {
"\x00 " ENUM7700_00_TEXT "\0"
"\x01 " ENUM7700_01_TEXT "\0"
"\x02 " ENUM7700_02_TEXT "\0"
"\x03 " ENUM7700_03_TEXT "\0"
"\x04 " ENUM7700_04_TEXT "\0"
"\x05 " ENUM7700_05_TEXT "\0"
"\x06 " ENUM7700_06_TEXT "\0"
"\x07 " ENUM7700_07_TEXT "\0"
"\x08 " ENUM7700_08_TEXT "\0"
"\x09 " ENUM7700_09_TEXT "\0"
"\x0a " ENUM7700_0a_TEXT "\0"
"\x0b " ENUM7700_0b_TEXT "\0"
"\x0c " ENUM7700_0c_TEXT "\0"
"\x0d " ENUM7700_0d_TEXT "\0"
"\x0e " ENUM7700_0e_TEXT "\0"
"\x0f " ENUM7700_0f_TEXT "\0"
"\x10 " ENUM7700_10_TEXT "\0"
"\x11 " ENUM7700_11_TEXT "\0"
"\x12 " ENUM7700_12_TEXT "\0"
"\x13 " ENUM7700_13_TEXT "\0"
"\x14 " ENUM7700_14_TEXT
};

const char ENUM7700_2[] = {
"\x00 " ENUM7700_2_00_TEXT "\0"
"\x01 " ENUM7700_2_01_TEXT "\0"
"\x02 " ENUM7700_2_02_TEXT "\0"
"\x03 " ENUM7700_2_03_TEXT "\0"
"\x04 " ENUM7700_2_04_TEXT "\0"
"\x05 " ENUM7700_2_05_TEXT "\0"
"\x06 " ENUM7700_2_06_TEXT "\0"
"\x07 " ENUM7700_2_07_TEXT "\0"
"\x08 " ENUM7700_2_08_TEXT "\0"
"\x09 " ENUM7700_2_09_TEXT
};

// 7717 - Ausgangssignal UX2
const char ENUM7717[] = {
"\x00 " "?" ENUM7717_00_TEXT "\0"
"\x01 " "?" ENUM7717_01_TEXT "\0"
"\x02 " "?" ENUM7717_02_TEXT "\0"
"\x03 " "?" ENUM7717_03_TEXT "\0"
"\x04 " "?" ENUM7717_04_TEXT "\0"
"\x05 " "?" ENUM7717_05_TEXT "\0"
"\x06 " "?" ENUM7717_06_TEXT
};

#define ENUM7725 ENUM7717

//Eingangssignal H33  //FUJITSU
const char ENUM7999[] = {
"\x00 " ENUM7999_00_TEXT "\0"
"\x01 " ENUM7999_01_TEXT "\0"
"\x02 " "?" ENUM7999_02_TEXT "\0"
"\x03 " "?" ENUM7999_03_TEXT "\0"
"\x04 " "?" ENUM7999_04_TEXT
};

// Status Heizkreis 1, 2, 3
const char ENUM8000[] = {
"\x00 " ENUM8000_00_TEXT "\0"
"\x03 " ENUM8000_03_TEXT "\0"
"\x04 " ENUM8000_04_TEXT "\0"
"\x11 " ENUM8000_11_TEXT "\0"
"\x16 " ENUM8000_16_TEXT "\0"
"\x17 " ENUM8000_17_TEXT "\0"
"\x18 " ENUM8000_18_TEXT "\0"
"\x38 " ENUM8000_38_TEXT "\0"
"\x65 " ENUM8000_65_TEXT "\0"
"\x66 " ENUM8000_66_TEXT "\0"
"\x67 " ENUM8000_67_TEXT "\0"
"\x68 " ENUM8000_68_TEXT "\0"
"\x69 " ENUM8000_69_TEXT "\0"
"\x6a " ENUM8000_6a_TEXT "\0"
"\x6b " ENUM8000_6b_TEXT "\0"
"\x6c " ENUM8000_6c_TEXT "\0"
"\x6d " ENUM8000_6d_TEXT "\0"
"\x6e " ENUM8000_6e_TEXT "\0"
"\x6f " ENUM8000_6f_TEXT "\0"
"\x70 " ENUM8000_70_TEXT "\0"
"\x71 " ENUM8000_71_TEXT "\0"
"\x72 " ENUM8000_72_TEXT "\0"
"\x73 " ENUM8000_73_TEXT "\0"
"\x74 " ENUM8000_74_TEXT "\0"
"\x75 " ENUM8000_75_TEXT "\0"
"\x76 " ENUM8000_76_TEXT "\0"
"\x77 " ENUM8000_77_TEXT "\0"
"\x78 " ENUM8000_78_TEXT "\0"
"\x79 " ENUM8000_79_TEXT "\0"
"\x7a " ENUM8000_7a_TEXT "\0"
"\xf8 " ENUM8000_f8_TEXT
};

#define ENUM8001 ENUM8000               // Status - Status Heizkreis 2
#define ENUM8002 ENUM8000               // Status - Status Heizkreis P/3


//Status Trinkwasser
const char ENUM8003[] = {
"\x00 " ENUM8003_00_TEXT "\0"
"\x03 " ENUM8003_03_TEXT "\0"
"\x04 " ENUM8003_04_TEXT "\0"
"\x11 " ENUM8003_11_TEXT "\0"
"\x18 " ENUM8003_18_TEXT "\0"
"\x19 " ENUM8003_19_TEXT "\0"
"\x35 " ENUM8003_35_TEXT "\0"
"\x42 " ENUM8003_42_TEXT "\0"
"\x43 " ENUM8003_43_TEXT "\0"
"\x45 " ENUM8003_45_TEXT "\0"
"\x46 " ENUM8003_46_TEXT "\0"
"\x47 " ENUM8003_47_TEXT "\0"
"\x4b " ENUM8003_4b_TEXT "\0"
"\x4d " ENUM8003_4d_TEXT "\0"
"\x4e " ENUM8003_4e_TEXT "\0"
"\x4f " ENUM8003_4f_TEXT "\0"
"\x50 " ENUM8003_50_TEXT "\0"
"\x51 " ENUM8003_51_TEXT "\0"
"\x52 " ENUM8003_52_TEXT "\0"
"\x53 " ENUM8003_53_TEXT "\0"
"\x54 " ENUM8003_54_TEXT "\0"
"\x55 " ENUM8003_55_TEXT "\0"
"\x56 " ENUM8003_56_TEXT "\0"
"\x57 " ENUM8003_57_TEXT "\0"
"\x58 " ENUM8003_58_TEXT "\0"
"\x59 " ENUM8003_59_TEXT "\0"
"\x5a " ENUM8003_5a_TEXT "\0"
"\x5b " ENUM8003_5b_TEXT "\0"
"\x5c " ENUM8003_5c_TEXT "\0"
"\x5d " ENUM8003_5d_TEXT "\0"
"\x5e " ENUM8003_5e_TEXT "\0"
"\x5f " ENUM8003_5f_TEXT "\0"
"\x60 " ENUM8003_60_TEXT "\0"
"\x61 " ENUM8003_61_TEXT "\0"
"\x62 " ENUM8003_62_TEXT "\0"
"\x63 " ENUM8003_63_TEXT "\0"
"\x64 " ENUM8003_64_TEXT "\0"
"\xc7 " ENUM8003_c7_TEXT "\0"
"\xc8 " ENUM8003_c8_TEXT "\0"
"\xc9 " ENUM8003_c9_TEXT
};

//Status Kühlkreis 1  //FUJITSU
const char ENUM8004[] = {
"\x00 " ENUM8004_00_TEXT "\0"
"\x02 " ENUM8004_02_TEXT "\0"
"\x04 " ENUM8004_04_TEXT "\0"
"\x11 " ENUM8004_11_TEXT "\0"
"\x17 " ENUM8004_17_TEXT "\0"
"\x18 " ENUM8004_18_TEXT "\0"
"\x19 " ENUM8004_19_TEXT "\0"
"\x75 " ENUM8004_75_TEXT "\0"
"\x77 " ENUM8004_77_TEXT "\0"
"\x7a " ENUM8004_7a_TEXT "\0"
"\x85 " ENUM8004_85_TEXT "\0"
"\x86 " ENUM8004_86_TEXT "\0"
"\x87 " ENUM8004_87_TEXT "\0"
"\x88 " ENUM8004_88_TEXT "\0"
"\x8a " ENUM8004_8a_TEXT "\0"
"\x90 " ENUM8004_90_TEXT "\0"
"\x92 " ENUM8004_92_TEXT "\0"
"\x95 " ENUM8004_95_TEXT "\0"
"\x96 " ENUM8004_96_TEXT "\0"
"\xb1 " ENUM8004_b1_TEXT "\0"
"\xb2 " ENUM8004_b2_TEXT "\0"
"\xb3 " ENUM8004_b3_TEXT "\0"
"\xcc " ENUM8004_cc_TEXT "\0"
"\xcd " ENUM8004_cd_TEXT "\0"
"\xce " ENUM8004_ce_TEXT "\0"
"\xff " ENUM8004_ff_TEXT "\0"
"\x01\x1d " ENUM8004_11d_TEXT
};

//Status Kessel
const char ENUM8005[] = {
"\x00 " ENUM8005_00_TEXT "\0"
"\x01 " ENUM8005_01_TEXT "\0"
"\x02 " ENUM8005_02_TEXT "\0"
"\x03 " ENUM8005_03_TEXT "\0"
"\x04 " ENUM8005_04_TEXT "\0"
"\x05 " ENUM8005_05_TEXT "\0"
"\x06 " ENUM8005_06_TEXT "\0"
"\x07 " ENUM8005_07_TEXT "\0"
"\x08 " ENUM8005_08_TEXT "\0"
"\x09 " ENUM8005_09_TEXT "\0"
"\x0a " ENUM8005_0a_TEXT "\0"
"\x0b " ENUM8005_0b_TEXT "\0"
"\x0c " ENUM8005_0c_TEXT "\0"
"\x0d " ENUM8005_0d_TEXT "\0"
"\x0e " ENUM8005_0e_TEXT "\0"
"\x0f " ENUM8005_0f_TEXT "\0"
"\x10 " ENUM8005_10_TEXT "\0"
"\x11 " ENUM8005_11_TEXT "\0"
"\x12 " ENUM8005_12_TEXT "\0"
"\x13 " ENUM8005_13_TEXT "\0"
"\x14 " ENUM8005_14_TEXT "\0"
"\x15 " ENUM8005_15_TEXT "\0"
"\x16 " ENUM8005_16_TEXT "\0"
"\x17 " ENUM8005_17_TEXT "\0"
"\x18 " ENUM8005_18_TEXT "\0"
"\x19 " ENUM8005_19_TEXT "\0"
"\x3b " ENUM8005_3b_TEXT "\0"
"\x7b " ENUM8005_7b_TEXT "\0"
"\xa6 " ENUM8005_a6_TEXT "\0"
"\xa7 " ENUM8005_a7_TEXT "\0"
"\xa8 " ENUM8005_a8_TEXT "\0"
"\xa9 " ENUM8005_a9_TEXT "\0"
"\xaa " ENUM8005_aa_TEXT "\0"
"\xab " ENUM8005_ab_TEXT "\0"
"\xac " ENUM8005_ac_TEXT "\0"
"\xad " ENUM8005_ad_TEXT "\0"
"\xae " ENUM8005_ae_TEXT "\0"
"\xaf " ENUM8005_af_TEXT "\0"
"\xb0 " ENUM8005_b0_TEXT "\0"
"\xc6 " ENUM8005_c6_TEXT "\0"
"\xdc " ENUM8005_dc_TEXT
};

//Status Waermepumpe  //FUJITSU
const char ENUM8006[] = {
"\x00 " ENUM8006_00_TEXT "\0"
"\x02 " ENUM8006_02_TEXT "\0"
"\x0A " ENUM8006_0A_TEXT "\0"      //10
"\x11 " ENUM8006_11_TEXT "\0"      //17
"\x17 " ENUM8006_17_TEXT "\0"
"\x18 " ENUM8006_18_TEXT "\0"      //24
"\x19 " ENUM8006_19_TEXT "\0"      //25
"\x1a " ENUM8006_1a_TEXT "\0"
"\x1b " ENUM8006_1b_TEXT "\0"      //27
"\x1d " ENUM8006_1d_TEXT "\0"      //29
"\x1e " ENUM8006_1e_TEXT "\0"      //30
"\x1f " ENUM8006_1f_TEXT "\0"      //31
"\x20 " ENUM8006_20_TEXT "\0"      //32
"\x21 " ENUM8006_21_TEXT "\0"      //33
"\x22 " ENUM8006_22_TEXT "\0"      //34
"\x23 " ENUM8006_23_TEXT "\0"
"\x24 " ENUM8006_24_TEXT "\0"      //36
"\x25 " ENUM8006_25_TEXT "\0"      //37
"\x26 " ENUM8006_26_TEXT "\0"
"\x27 " ENUM8006_27_TEXT "\0"      //39
"\x28 " ENUM8006_28_TEXT "\0"      //40
"\x29 " ENUM8006_29_TEXT "\0"      //41
"\x2a " ENUM8006_2a_TEXT "\0"      //42
"\x2b " ENUM8006_2b_TEXT "\0"      //43
"\x2c " ENUM8006_2c_TEXT "\0"      //44
"\x2d " ENUM8006_2d_TEXT "\0"      //45
"\x2e " ENUM8006_2e_TEXT "\0"
"\x2f " ENUM8006_2f_TEXT "\0"      //47
"\x30 " ENUM8006_30_TEXT "\0"      //48
"\x31 " ENUM8006_31_TEXT "\0"
"\x32 " ENUM8006_32_TEXT "\0"
"\x33 " ENUM8006_33_TEXT "\0"      //51
"\x7d " ENUM8006_7d_TEXT "\0"
"\x7e " ENUM8006_7e_TEXT "\0"      //126
"\x7f " ENUM8006_7f_TEXT "\0"      //127
"\x80 " ENUM8006_80_TEXT "\0"      //128
"\x81 " ENUM8006_81_TEXT "\0"      //129
"\x82 " ENUM8006_82_TEXT "\0"      //130
"\x89 " ENUM8006_89_TEXT "\0"      //137
"\x8b " ENUM8006_8b_TEXT "\0"      //139
"\x91 " ENUM8006_91_TEXT "\0"      //145
"\xb0 " ENUM8006_b0_TEXT "\0"
"\xb4 " ENUM8006_b4_TEXT "\0"      //180
"\xb5 " ENUM8006_b5_TEXT "\0"      //181
"\xb6 " ENUM8006_b6_TEXT "\0"      //182
"\xb7 " ENUM8006_b7_TEXT "\0"      //183
"\xb8 " ENUM8006_b8_TEXT "\0"      //184
"\xb9 " ENUM8006_b9_TEXT "\0"      //185
"\xba " ENUM8006_ba_TEXT "\0"      //186
"\xbb " ENUM8006_bb_TEXT "\0"      //187
"\xbc " ENUM8006_bc_TEXT "\0"      //188
"\xbd " ENUM8006_bd_TEXT "\0"      //189
"\xbe " ENUM8006_be_TEXT "\0"      //190
"\xbf " ENUM8006_bf_TEXT "\0"      //191
"\xc0 " ENUM8006_c0_TEXT "\0"      //192
"\xc1 " ENUM8006_c1_TEXT "\0"      //193
"\xc2 " ENUM8006_c2_TEXT "\0"      //194
"\xc3 " ENUM8006_c3_TEXT "\0"      //195
"\xc4 " ENUM8006_c4_TEXT "\0"      //196
"\xc5 " ENUM8006_c5_TEXT "\0"      //197
"\xc6 " ENUM8006_c6_TEXT "\0"      //198
"\xcf " ENUM8006_cf_TEXT "\0"      //207
"\xd0 " ENUM8006_d0_TEXT "\0"      //208
"\xd1 " ENUM8006_d1_TEXT "\0"      //209
"\xd2 " ENUM8006_d2_TEXT "\0"      //210
"\xeb " ENUM8006_eb_TEXT "\0"
"\xf2 " ENUM8006_f2_TEXT "\0"      //242
"\xf6 " ENUM8006_f6_TEXT "\0"      //246
"\xfe " ENUM8006_fe_TEXT "\0"      //254
"\x01\x00 " ENUM8006_01_00_TEXT "\0"      //256
"\x01\x01 " ENUM8006_01_01_TEXT "\0"      //257
"\x01\x02 " ENUM8006_01_02_TEXT "\0"      //258
"\x01\x03 " ENUM8006_01_03_TEXT "\0"      //259
"\x01\x04 " ENUM8006_01_04_TEXT "\0"      //260
"\x01\x05 " ENUM8006_01_05_TEXT "\0"      //261
"\x01\x06 " ENUM8006_01_06_TEXT "\0"      //262
"\x01\x07 " ENUM8006_01_07_TEXT "\0"      //263
"\x01\x08 " ENUM8006_01_08_TEXT "\0"      //264
"\x01\x09 " ENUM8006_01_09_TEXT "\0"      //265
"\x01\x0a " ENUM8006_01_0a_TEXT "\0"      //266
"\x01\x0b " ENUM8006_01_0b_TEXT "\0"      //267
"\x01\x0c " ENUM8006_01_0c_TEXT "\0"      //268
"\x01\x0d " ENUM8006_01_0d_TEXT "\0"      //269
"\x01\x0e " ENUM8006_01_0e_TEXT      //270
};


//Status Solar
const char ENUM8007[] = {
"\x00 " ENUM8007_00_TEXT "\0"
"\x04 " ENUM8007_04_TEXT "\0"
"\x02 " ENUM8007_02_TEXT "\0"
"\x34 " ENUM8007_34_TEXT "\0"
"\x35 " ENUM8007_35_TEXT "\0"
"\x36 " ENUM8007_36_TEXT "\0"
"\x37 " ENUM8007_37_TEXT "\0"
"\x38 " ENUM8007_38_TEXT "\0"
"\x39 " ENUM8007_39_TEXT "\0"
"\x3a " ENUM8007_3a_TEXT "\0"
"\x3b " ENUM8007_3b_TEXT "\0"
"\x3c " ENUM8007_3c_TEXT "\0"
"\x3d " ENUM8007_3d_TEXT "\0"
"\x3e " ENUM8007_3e_TEXT "\0"
"\x3f " ENUM8007_3f_TEXT "\0"
"\x97 " ENUM8007_97_TEXT "\0"
"\x98 " ENUM8007_98_TEXT "\0"
"\x99 " ENUM8007_99_TEXT "\0"
"\x9a " ENUM8007_9a_TEXT
};


//Status Feststoffkessel
const char ENUM8008[] = {
"\x00 " ENUM8008_00_TEXT "\0"
"\x02 " ENUM8008_02_TEXT "\0"
"\x04 " ENUM8008_04_TEXT "\0"
"\x08 " ENUM8008_08_TEXT "\0"
"\x09 " ENUM8008_09_TEXT "\0"
"\x0a " ENUM8008_0a_TEXT "\0"
"\x0b " ENUM8008_0b_TEXT "\0"
"\x0c " ENUM8008_0c_TEXT "\0"
"\x0d " ENUM8008_0d_TEXT "\0"
"\x0e " ENUM8008_0e_TEXT "\0"
"\x11 " ENUM8008_11_TEXT "\0"
"\x12 " ENUM8008_12_TEXT "\0"
"\x13 " ENUM8008_13_TEXT "\0"
"\x14 " ENUM8008_14_TEXT "\0"
"\x15 " ENUM8008_15_TEXT "\0"
"\x16 " ENUM8008_16_TEXT "\0"
"\x17 " ENUM8008_17_TEXT "\0"
"\x18 " ENUM8008_18_TEXT "\0"
"\x19 " ENUM8008_19_TEXT "\0"
"\x38 " ENUM8008_38_TEXT "\0"
"\x3a " ENUM8008_3a_TEXT "\0"
"\x3b " ENUM8008_3b_TEXT "\0"
"\x8d " ENUM8008_8d_TEXT "\0"
"\xa3 " ENUM8008_a3_TEXT "\0"
"\xa6 " ENUM8008_a6_TEXT "\0"
"\xa7 " ENUM8008_a7_TEXT "\0"
"\xa8 " ENUM8008_a8_TEXT "\0"
"\xa9 " ENUM8008_a9_TEXT "\0"
"\xaa " ENUM8008_aa_TEXT "\0"
"\xab " ENUM8008_ab_TEXT "\0"
"\xf1 " ENUM8008_f1_TEXT
};

// Status Brenner
// Text messages are taken from Installationshandbuch NovoCondens WOB 20-25
// The enum numerical values with question marks are unknown and are placeholders
// !TODO! Determine the enum numerical values

// Thision
const char ENUM8009_2[] = {
"\x00 " "?" ENUM8009_2_00_TEXT "\0" // !TODO! "no text" is only an analogous deduction
"\x01 " "?" ENUM8009_2_01_TEXT "\0"        // !TODO! enum value is hypothetical
"\x02 " "?" ENUM8009_2_02_TEXT "\0"   // !TODO! enum value is hypothetical
"\x04 " ENUM8009_2_04_TEXT "\0"
"\x12 " ENUM8009_2_12_TEXT "\0"
"\xD6 " "?" ENUM8009_2_D6_TEXT "\0"
"\xDA " "?" ENUM8009_2_DA_TEXT "\0"
"\xD7 " "?" ENUM8009_2_D7_TEXT "\0"
"\xD8 " ENUM8009_2_D8_TEXT "\0"
"\x09 " "?" ENUM8009_2_09_TEXT "\0" // !TODO! enum value is hypothetical
"\xD9 " "?" ENUM8009_2_D9_TEXT "\0"
"\xDB " "?" ENUM8009_2_DB_TEXT
};

// Brötje BSW / WMS / WMC
const char ENUM8009[] = {
"\x00 " "?" ENUM8009_00_TEXT "\0" // !TODO! "no text" is only an analogous deduction
"\x01 " "?" ENUM8009_01_TEXT "\0"        // !TODO! enum value is hypothetical
"\x02 " "?" ENUM8009_02_TEXT "\0"   // !TODO! enum value is hypothetical
"\x12 " ENUM8009_12_TEXT "\0"           // verifiziert an WMS (LP)
"\xD6 " ENUM8009_D6_TEXT "\0"
"\xDA " ENUM8009_DA_TEXT "\0"
"\xD7 " ENUM8009_D7_TEXT "\0"     // verifiziert an WMS (LP)
"\xD8 " ENUM8009_D8_TEXT "\0"              // verifiziert an WMS (LP)
"\x09 " "?" ENUM8009_09_TEXT "\0" // !TODO! enum value is hypothetical
"\xD9 " ENUM8009_D9_TEXT "\0"
"\xDB " ENUM8009_DB_TEXT "\0"
"\xE0 " ENUM8009_E0_TEXT "\0"               // verifiziert an WMS (LP)
"\xE1 " ENUM8009_E1_TEXT         // verifiziert an WMS (LP)
};

//Status Pufferspeicher
const char ENUM8010[] = {
"\x00 " ENUM8010_00_TEXT "\0"
"\x18 " ENUM8010_18_TEXT "\0"
"\x33 " ENUM8010_33_TEXT "\0"
"\x35 " ENUM8010_35_TEXT "\0"
"\x40 " ENUM8010_40_TEXT "\0"
"\x41 " ENUM8010_41_TEXT "\0"
"\x42 " ENUM8010_42_TEXT "\0"
"\x43 " ENUM8010_43_TEXT "\0"
"\x44 " ENUM8010_44_TEXT "\0"
"\x45 " ENUM8010_45_TEXT "\0"
"\x46 " ENUM8010_46_TEXT "\0"
"\x47 " ENUM8010_47_TEXT "\0"
"\x48 " ENUM8010_48_TEXT "\0"
"\x49 " ENUM8010_49_TEXT "\0"
"\x4a " ENUM8010_4a_TEXT "\0"
"\x4b " ENUM8010_4b_TEXT "\0"
"\x4c " ENUM8010_4c_TEXT "\0"
"\x4d " ENUM8010_4d_TEXT "\0"
"\x51 " ENUM8010_51_TEXT "\0"
"\x68 " ENUM8010_68_TEXT "\0"
"\x7c " ENUM8010_7c_TEXT "\0"
"\x83 " ENUM8010_83_TEXT "\0"
"\x87 " ENUM8010_87_TEXT "\0"
"\x8e " ENUM8010_8e_TEXT "\0"
"\x8f " ENUM8010_8f_TEXT "\0"
"\x93 " ENUM8010_93_TEXT "\0"
"\xa4 " ENUM8010_a4_TEXT "\0"
"\xa5 " ENUM8010_a5_TEXT "\0"
"\xca " ENUM8010_ca_TEXT "\0"
"\xcb " ENUM8010_cb_TEXT "\0"
"\xf4 " ENUM8010_f4_TEXT
};

// Status Schwimmbad
const char ENUM8011[] = {
"\x00 " ENUM8011_00_TEXT "\0"
"\x02 " ENUM8011_02_TEXT "\0"
"\x04 " ENUM8011_04_TEXT "\0"
"\x4c " ENUM8011_4c_TEXT "\0"
"\x6a " ENUM8011_6a_TEXT "\0"
"\x6e " ENUM8011_6e_TEXT "\0"
"\x89 " ENUM8011_89_TEXT "\0"
"\x9b " ENUM8011_9b_TEXT "\0"
"\x9c " ENUM8011_9c_TEXT "\0"
"\x9d " ENUM8011_9d_TEXT "\0"
"\x9e " ENUM8011_9e_TEXT "\0"
"\x9f " ENUM8011_9f_TEXT "\0"
"\xa0 " ENUM8011_a0_TEXT "\0"
"\xa1 " ENUM8011_a1_TEXT "\0"
"\xa2 " ENUM8011_a2_TEXT
};

//Status Zusatzerzeuger  //FUJITSU
// note: unverified values are taken from http://www.mhg-schweiz.ch/de/downloads/aid!7b786239-40bf-4077-9a19-e2c97ebab6c5/id!187/
const char ENUM8022[] = {
"\x00 " ENUM8022_00_TEXT "\0"
"\x02 " ENUM8022_02_TEXT "\0"
"\x0a " ENUM8022_0a_TEXT "\0"
"\x11 " ENUM8022_11_TEXT "\0"
"\x19 " ENUM8022_19_TEXT "\0"
"\x3b " ENUM8022_3b_TEXT "\0"
"\xa6 " ENUM8022_a6_TEXT "\0"
"\xa8 " ENUM8022_a8_TEXT "\0"
"\xaa " ENUM8022_aa_TEXT "\0"
"\xac " ENUM8022_ac_TEXT "\0"
"\xad " ENUM8022_ad_TEXT "\0"
"\xae " ENUM8022_ae_TEXT "\0"
"\xb0 " ENUM8022_b0_TEXT "\0"
"\xc6 " ENUM8022_c6_TEXT
};

#define ENUM8051 ENUM8006               // Status - Status Historie 1
#define ENUM8053 ENUM8051               // Status - Status Historie 2
#define ENUM8055 ENUM8051               // Status - Status Historie 3
#define ENUM8057 ENUM8051               // Status - Status Historie 4
#define ENUM8059 ENUM8051               // Status - Status Historie 5
#define ENUM8061 ENUM8051               // Status - Status Historie 6
#define ENUM8063 ENUM8051               // Status - Status Historie 7
#define ENUM8065 ENUM8051               // Status - Status Historie 8
#define ENUM8067 ENUM8051               // Status - Status Historie 9
#define ENUM8069 ENUM8051               // Status - Status Historie 10

#define ENUM8099 ENUM8006               // Status - Hauptdisplay. Achtung! 8099 kann zukünftig direkt von einem Hersteller vergeben werden, dann muss dieser Parameter "umziehen"...

// Diagnose Kaskade
const char ENUM8101[] = { // numerical values are hypothetical
"\x00 " "?" ENUM8101_00_TEXT "\0"
"\x01 " "?" ENUM8101_01_TEXT "\0"
"\x02 " "?" ENUM8101_02_TEXT "\0"
"\x03 " "?" ENUM8101_03_TEXT "\0"
"\x04 " "?" ENUM8101_04_TEXT "\0"
"\x05 " "?" ENUM8101_05_TEXT "\0"
"\x06 " "?" ENUM8101_06_TEXT "\0"
"\x07 " "?" ENUM8101_07_TEXT "\0"
"\x08 " "?" ENUM8101_08_TEXT
};
#define ENUM8103 ENUM8101
#define ENUM8105 ENUM8101
#define ENUM8107 ENUM8101
#define ENUM8109 ENUM8101
#define ENUM8111 ENUM8101
#define ENUM8113 ENUM8101
#define ENUM8115 ENUM8101
#define ENUM8117 ENUM8101
#define ENUM8119 ENUM8101
#define ENUM8121 ENUM8101
#define ENUM8123 ENUM8101
#define ENUM8125 ENUM8101
#define ENUM8127 ENUM8101
#define ENUM8129 ENUM8101
#define ENUM8131 ENUM8101

// Diagnose Erzeuger - 8304 Kesselpumpe Q1
// NovoCondens WOB 20-25
// !TODO! Collect the other possible values (probably 0=Aus, 1=Ein, 255=Ein)
const char ENUM8304[] = {
"\x00 " ENUM8304_00_TEXT "\0"    // precision guesswork
"\x01 " ENUM8304_01_TEXT "\0"    // precision guesswork
"\xff " ENUM8304_ff_TEXT "\0"    // vom LCD abgelesen (Python code)
"\x01\x00 " ENUM8304_01_00_TEXT
};

const char ENUM8313[] = {
"\x01 " ENUM8313_01_TEXT "\0"               // verifiziert an WMS (LP)
"\x02 " ENUM8313_02_TEXT "\0"
"\x03 " ENUM8313_03_TEXT "\0"
"\x04 " ENUM8313_04_TEXT "\0"
"\x05 " ENUM8313_05_TEXT "\0"
"\x06 " ENUM8313_06_TEXT
}; // todo Hinweis: x01 ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM8390[] = {
"\x01 " ENUM8390_01_TEXT "\0"
"\x02 " ENUM8390_02_TEXT "\0"
"\x03 " ENUM8390_03_TEXT "\0"        // verifiziert an WMS (LP)
"\x04 " ENUM8390_04_TEXT "\0"        // verifiziert an WMS (LP)
"\x05 " ENUM8390_05_TEXT "\0"
"\x06 " ENUM8390_06_TEXT "\0"
"\x07 " ENUM8390_07_TEXT "\0"
"\x08 " ENUM8390_08_TEXT "\0"
"\x09 " ENUM8390_09_TEXT "\0"
"\x0a " ENUM8390_0a_TEXT "\0"
"\x0b " ENUM8390_0b_TEXT "\0"
"\x0c " ENUM8390_0c_TEXT "\0"
"\x0d " ENUM8390_0d_TEXT "\0"        // verifiziert an WMS (LP)
"\x0e " ENUM8390_0e_TEXT "\0"
"\x0f " ENUM8390_0f_TEXT "\0"
"\x10 " ENUM8390_10_TEXT "\0"        // verifiziert an WMS (LP)
"\x11 " ENUM8390_11_TEXT "\0"
"\x12 " ENUM8390_12_TEXT "\0"
"\x13 " ENUM8390_13_TEXT "\0"
"\x14 " ENUM8390_14_TEXT "\0"
"\x15 " ENUM8390_15_TEXT "\0"
"\x16 " ENUM8390_16_TEXT "\0"
"\x17 " ENUM8390_17_TEXT "\0"
"\x18 " ENUM8390_18_TEXT           // verifiziert an WMS (LP)
};

// Diagnose Verbraucher 8749 Raumthermostat 1
// Texts taken from manual
const char ENUM8749[] = {     // numerical values unverified
"\x00 " ENUM8749_00_TEXT "\0"
"\x01 " ENUM8749_01_TEXT
};
#define ENUM8779 ENUM8749  // 8779 Raumthermostat 2
#define ENUM8809 ENUM8749  // 8809 Raumthermostat 3


//Here can be additional values
const char ENUM9610[] = {
"\x00 " ENUM9610_00_TEXT "\0"
"\x01 " "?" ENUM9610_01_TEXT
};

//Here can be additional values
const char ENUM9611[] = {
"\x00 " ENUM9611_00_TEXT "\0"
"\x01 " "?" ENUM9611_01_TEXT
};

//Here can be additional values
const char ENUM9612[] = {
"\x00 " ENUM9612_00_TEXT "\0"
"\x01 " "?" ENUM9612_01_TEXT
};

// 9613 - Heimlaufmodus
const char ENUM9613[] = {
"\x00 " "?" ENUM9613_00_TEXT "\0"
"\x01 " "?" ENUM9613_01_TEXT
};

//Here can be additional values
const char ENUM9614[] = {
"\x00 " ENUM9614_00_TEXT "\0"
"\x01 " "?" ENUM9614_01_TEXT
};

const char ENUM10100[] = {
"\x00" // index for payload byte
"\x01\x01 " ENUM10100_01_TEXT "\0"
"\x02\x02 " ENUM10100_02_TEXT "\0"
"\x04\x04 " ENUM10100_04_TEXT "\0"
"\x08\x08 " ENUM10100_08_TEXT "\0"
"\x10\x10 " ENUM10100_10_TEXT "\0"
"\x20\x20 " ENUM10100_20_TEXT "\0"
"\x40\x40 " ENUM10100_40_TEXT "\0"
"\x80\x80 " ENUM10100_80_TEXT
};

// RVD/RVP

// Externer Wärmebedarf Vorrang
const char ENUM14088[] = {
"\x00 " ENUM14088_00_TEXT "\0"
"\x01 " ENUM14088_01_TEXT
};

/* SPECIAL ENUM tables */
//Fehlercodes
const char ENUM_ERROR[] = {
"\x00 " ENUM_ERROR_00_TEXT "\0"
"\x0a " ENUM_ERROR_0a_TEXT "\0"
"\x14 " ENUM_ERROR_14_TEXT "\0"
"\x16 " ENUM_ERROR_16_TEXT "\0"
"\x19 " ENUM_ERROR_19_TEXT "\0"
"\x1a " ENUM_ERROR_1a_TEXT "\0"
"\x1b " ENUM_ERROR_1b_TEXT "\0"
"\x1c " ENUM_ERROR_1c_TEXT "\0"
"\x1e " ENUM_ERROR_1e_TEXT "\0"
"\x1f " ENUM_ERROR_1f_TEXT "\0"
"\x20 " ENUM_ERROR_20_TEXT "\0"
"\x21 " ENUM_ERROR_21_TEXT "\0"
"\x22 " ENUM_ERROR_22_TEXT "\0"
"\x23 " ENUM_ERROR_23_TEXT "\0"
"\x24 " ENUM_ERROR_24_TEXT "\0"
"\x25 " ENUM_ERROR_25_TEXT "\0"
"\x26 " ENUM_ERROR_26_TEXT "\0"
"\x27 " ENUM_ERROR_27_TEXT "\0"
"\x28 " ENUM_ERROR_28_TEXT "\0"
"\x2a " ENUM_ERROR_2a_TEXT "\0"
"\x2b " ENUM_ERROR_2b_TEXT "\0"
"\x2c " ENUM_ERROR_2c_TEXT "\0"
"\x2d " ENUM_ERROR_2d_TEXT "\0"
"\x2e " ENUM_ERROR_2e_TEXT "\0"
"\x2f " ENUM_ERROR_2f_TEXT "\0"
"\x30 " ENUM_ERROR_30_TEXT "\0"
"\x32 " ENUM_ERROR_32_TEXT "\0"
"\x34 " ENUM_ERROR_34_TEXT "\0"
"\x36 " ENUM_ERROR_36_TEXT "\0"
"\x37 " ENUM_ERROR_37_TEXT "\0"
"\x38 " ENUM_ERROR_38_TEXT "\0"
"\x39 " ENUM_ERROR_39_TEXT "\0"
"\x3a " ENUM_ERROR_3a_TEXT "\0"
"\x3c " ENUM_ERROR_3c_TEXT "\0"
"\x3d " ENUM_ERROR_3d_TEXT "\0"
"\x3e " ENUM_ERROR_3e_TEXT "\0"
"\x40 " ENUM_ERROR_40_TEXT "\0"
"\x41 " ENUM_ERROR_41_TEXT "\0"
"\x42 " ENUM_ERROR_42_TEXT "\0"
"\x43 " ENUM_ERROR_43_TEXT "\0"
"\x44 " ENUM_ERROR_44_TEXT "\0"
"\x45 " ENUM_ERROR_45_TEXT "\0"
"\x46 " ENUM_ERROR_46_TEXT "\0"
"\x47 " ENUM_ERROR_47_TEXT "\0"
"\x48 " ENUM_ERROR_48_TEXT "\0"
"\x49 " ENUM_ERROR_49_TEXT "\0"
"\x4a " ENUM_ERROR_4a_TEXT "\0"
"\x50 " ENUM_ERROR_50_TEXT "\0"
"\x51 " ENUM_ERROR_51_TEXT "\0"
"\x52 " ENUM_ERROR_52_TEXT "\0"
"\x53 " ENUM_ERROR_53_TEXT "\0"
"\x54 " ENUM_ERROR_54_TEXT "\0"
"\x55 " ENUM_ERROR_55_TEXT "\0"
"\x56 " ENUM_ERROR_56_TEXT "\0"
"\x57 " ENUM_ERROR_57_TEXT "\0"
"\x58 " ENUM_ERROR_58_TEXT "\0"
"\x59 " ENUM_ERROR_59_TEXT "\0"
"\x5a " ENUM_ERROR_5a_TEXT "\0"
"\x5b " ENUM_ERROR_5b_TEXT "\0"
"\x5c " ENUM_ERROR_5c_TEXT "\0"
"\x5d " ENUM_ERROR_5d_TEXT "\0"
"\x5e " ENUM_ERROR_5e_TEXT "\0"
"\x5f " ENUM_ERROR_5f_TEXT "\0"
"\x60 " ENUM_ERROR_60_TEXT "\0"
"\x61 " ENUM_ERROR_61_TEXT "\0"
"\x62 " ENUM_ERROR_62_TEXT "\0"
"\x63 " ENUM_ERROR_63_TEXT "\0"
"\x64 " ENUM_ERROR_64_TEXT "\0"
"\x65 " ENUM_ERROR_65_TEXT "\0"
"\x66 " ENUM_ERROR_66_TEXT "\0"
"\x67 " ENUM_ERROR_67_TEXT "\0"
"\x69 " ENUM_ERROR_69_TEXT "\0"
"\x6a " ENUM_ERROR_6a_TEXT "\0"
"\x6b " ENUM_ERROR_6b_TEXT "\0"
"\x6c " ENUM_ERROR_6c_TEXT "\0"
"\x6d " ENUM_ERROR_6d_TEXT "\0"
"\x6e " ENUM_ERROR_6e_TEXT "\0"
"\x6f " ENUM_ERROR_6f_TEXT "\0"
"\x70 " ENUM_ERROR_70_TEXT "\0"
"\x71 " ENUM_ERROR_71_TEXT "\0"
"\x72 " ENUM_ERROR_72_TEXT "\0"
"\x73 " ENUM_ERROR_73_TEXT "\0"
"\x74 " ENUM_ERROR_74_TEXT "\0"
"\x75 " ENUM_ERROR_75_TEXT "\0"
"\x76 " ENUM_ERROR_76_TEXT "\0"
"\x77 " ENUM_ERROR_77_TEXT "\0"
"\x78 " ENUM_ERROR_78_TEXT "\0"
"\x79 " ENUM_ERROR_79_TEXT "\0"
"\x7a " ENUM_ERROR_7a_TEXT "\0"
"\x7b " ENUM_ERROR_7b_TEXT "\0"
"\x7c " ENUM_ERROR_7c_TEXT "\0"
"\x7d " ENUM_ERROR_7d_TEXT "\0"
"\x7e " ENUM_ERROR_7e_TEXT "\0"
"\x7f " ENUM_ERROR_7f_TEXT "\0"
"\x80 " ENUM_ERROR_80_TEXT "\0"
"\x81 " ENUM_ERROR_81_TEXT "\0"
"\x82 " ENUM_ERROR_82_TEXT "\0"
"\x83 " ENUM_ERROR_83_TEXT "\0"
"\x84 " ENUM_ERROR_84_TEXT "\0"
"\x85 " ENUM_ERROR_85_TEXT "\0"
"\x86 " ENUM_ERROR_86_TEXT "\0"
"\x87 " ENUM_ERROR_87_TEXT "\0"
"\x88 " ENUM_ERROR_88_TEXT "\0"
"\x89 " ENUM_ERROR_89_TEXT "\0"
"\x8a " ENUM_ERROR_8a_TEXT "\0"
"\x8c " ENUM_ERROR_8c_TEXT "\0"
"\x8c " ENUM_ERROR_8c_TEXT "\0"
"\x8d " ENUM_ERROR_8d_TEXT "\0"
"\x8e " ENUM_ERROR_8e_TEXT "\0"
"\x91 " ENUM_ERROR_91_TEXT "\0"
"\x92 " ENUM_ERROR_92_TEXT "\0"
"\x93 " ENUM_ERROR_93_TEXT "\0"
"\x94 " ENUM_ERROR_94_TEXT "\0"
"\x95 " ENUM_ERROR_95_TEXT "\0"
"\x96 " ENUM_ERROR_96_TEXT "\0"
"\x97 " ENUM_ERROR_97_TEXT "\0"
"\x98 " ENUM_ERROR_98_TEXT "\0"
"\x99 " ENUM_ERROR_99_TEXT "\0"
"\x9a " ENUM_ERROR_9a_TEXT "\0"
"\x9b " ENUM_ERROR_9b_TEXT "\0"
"\x9d " ENUM_ERROR_9d_TEXT "\0"
"\x9e " ENUM_ERROR_9e_TEXT "\0"
"\xa0 " ENUM_ERROR_a0_TEXT "\0"
"\xa1 " ENUM_ERROR_a1_TEXT "\0"
"\xa2 " ENUM_ERROR_a2_TEXT "\0"
"\xa3 " ENUM_ERROR_a3_TEXT "\0"
"\xa4 " ENUM_ERROR_a4_TEXT "\0"
"\xa5 " ENUM_ERROR_a5_TEXT "\0"
"\xa6 " ENUM_ERROR_a6_TEXT "\0"
"\xa9 " ENUM_ERROR_a9_TEXT "\0"
"\xaa " ENUM_ERROR_aa_TEXT "\0"
"\xab " ENUM_ERROR_ab_TEXT "\0"
"\xac " ENUM_ERROR_ac_TEXT "\0"
"\xad " ENUM_ERROR_ad_TEXT "\0"
"\xae " ENUM_ERROR_ae_TEXT "\0"
"\xaf " ENUM_ERROR_af_TEXT "\0"
"\xb0 " ENUM_ERROR_b0_TEXT "\0"
"\xb1 " ENUM_ERROR_b1_TEXT "\0"
"\xb2 " ENUM_ERROR_b2_TEXT "\0"
"\xb3 " ENUM_ERROR_b3_TEXT "\0"
"\xb4 " ENUM_ERROR_b4_TEXT "\0"
"\xb5 " ENUM_ERROR_b5_TEXT "\0"
"\xb6 " ENUM_ERROR_b6_TEXT "\0"
"\xb7 " ENUM_ERROR_b7_TEXT "\0"
"\xb8 " ENUM_ERROR_b8_TEXT "\0"
"\xb9 " ENUM_ERROR_b9_TEXT "\0"
"\xba " ENUM_ERROR_ba_TEXT "\0"
"\xbb " ENUM_ERROR_bb_TEXT "\0"
"\xbc " ENUM_ERROR_bc_TEXT "\0"
"\xbe " ENUM_ERROR_be_TEXT "\0"
"\xbf " ENUM_ERROR_bf_TEXT "\0"
"\xc0 " ENUM_ERROR_c0_TEXT "\0"
"\xc1 " ENUM_ERROR_c1_TEXT "\0"
"\xc3 " ENUM_ERROR_c3_TEXT "\0"
"\xc4 " ENUM_ERROR_c4_TEXT "\0"
"\xc8 " ENUM_ERROR_c8_TEXT "\0"
"\xc9 " ENUM_ERROR_c9_TEXT "\0"
"\xca " ENUM_ERROR_ca_TEXT "\0"
"\xcb " ENUM_ERROR_cb_TEXT "\0"
"\xcc " ENUM_ERROR_cc_TEXT "\0"
"\xcd " ENUM_ERROR_cd_TEXT "\0"
"\xce " ENUM_ERROR_ce_TEXT "\0"
"\xcf " ENUM_ERROR_cf_TEXT "\0"
"\xd0 " ENUM_ERROR_d0_TEXT "\0"
"\xd1 " ENUM_ERROR_d1_TEXT "\0"
"\xd2 " ENUM_ERROR_d2_TEXT "\0"
"\xd3 " ENUM_ERROR_d3_TEXT "\0"
"\xd4 " ENUM_ERROR_d4_TEXT "\0"
"\xd5 " ENUM_ERROR_d5_TEXT "\0"
"\xd6 " ENUM_ERROR_d6_TEXT "\0"
"\xd7 " ENUM_ERROR_d7_TEXT "\0"
"\xd8 " ENUM_ERROR_d8_TEXT "\0"
"\xd9 " ENUM_ERROR_d9_TEXT "\0"
"\xda " ENUM_ERROR_da_TEXT "\0"
"\xdb " ENUM_ERROR_db_TEXT "\0"
"\xdc " ENUM_ERROR_dc_TEXT "\0"
"\xdd " ENUM_ERROR_dd_TEXT "\0"
"\xde " ENUM_ERROR_de_TEXT "\0"
"\xdf " ENUM_ERROR_df_TEXT "\0"
"\xe0 " ENUM_ERROR_e0_TEXT "\0"
"\xe1 " ENUM_ERROR_e1_TEXT "\0"
"\xe2 " ENUM_ERROR_e2_TEXT "\0"
"\xe3 " ENUM_ERROR_e3_TEXT "\0"
"\xe4 " ENUM_ERROR_e4_TEXT "\0"
"\xe5 " ENUM_ERROR_e5_TEXT "\0"
"\xe6 " ENUM_ERROR_e6_TEXT "\0"
"\xe7 " ENUM_ERROR_e7_TEXT "\0"
"\xe8 " ENUM_ERROR_e8_TEXT "\0"
"\xe9 " ENUM_ERROR_e9_TEXT "\0"
"\xea " ENUM_ERROR_ea_TEXT "\0"
"\xeb " ENUM_ERROR_eb_TEXT "\0"
"\xec " ENUM_ERROR_ec_TEXT "\0"
"\xed " ENUM_ERROR_ed_TEXT "\0"
"\xee " ENUM_ERROR_ee_TEXT "\0"
"\xef " ENUM_ERROR_ef_TEXT "\0"
"\xf1 " ENUM_ERROR_f1_TEXT "\0"
"\xf2 " ENUM_ERROR_f2_TEXT "\0"
"\xf3 " ENUM_ERROR_f3_TEXT "\0"
"\xf4 " ENUM_ERROR_f4_TEXT "\0"
"\xf7 " ENUM_ERROR_f7_TEXT "\0"
"\xfd " ENUM_ERROR_fd_TEXT "\0"
"\xfe " ENUM_ERROR_fe_TEXT "\0"
"\x01\x04 " ENUM_ERROR_01_04_TEXT "\0"
"\x01\x0e " ENUM_ERROR_01_0e_TEXT "\0"
"\x01\x3d " ENUM_ERROR_01_3d_TEXT "\0"
"\x01\x40 " ENUM_ERROR_01_40_TEXT "\0"
"\x01\x41 " ENUM_ERROR_01_41_TEXT "\0"
"\x01\x42 " ENUM_ERROR_01_42_TEXT "\0"
"\x01\x43 " ENUM_ERROR_01_43_TEXT "\0"
"\x01\x44 " ENUM_ERROR_01_44_TEXT "\0"
"\x01\x45 " ENUM_ERROR_01_45_TEXT "\0"
"\x01\x46 " ENUM_ERROR_01_46_TEXT "\0"
"\x01\x47 " ENUM_ERROR_01_47_TEXT "\0"
"\x01\x48 " ENUM_ERROR_01_48_TEXT "\0"
"\x01\x49 " ENUM_ERROR_01_49_TEXT "\0"
"\x01\x4a " ENUM_ERROR_01_4a_TEXT "\0"
"\x01\x4b " ENUM_ERROR_01_4b_TEXT "\0"
"\x01\x4c " ENUM_ERROR_01_4c_TEXT "\0"
"\x01\x4d " ENUM_ERROR_01_4d_TEXT "\0"
"\x01\x4e " ENUM_ERROR_01_4e_TEXT "\0"
"\x01\x4f " ENUM_ERROR_01_4f_TEXT "\0"
"\x01\x50 " ENUM_ERROR_01_50_TEXT "\0"
"\x01\x51 " ENUM_ERROR_01_51_TEXT "\0"
"\x01\x52 " ENUM_ERROR_01_52_TEXT "\0"
"\x01\x53 " ENUM_ERROR_01_53_TEXT "\0"
"\x01\x54 " ENUM_ERROR_01_54_TEXT "\0"
"\x01\x55 " ENUM_ERROR_01_55_TEXT "\0"
"\x01\x56 " ENUM_ERROR_01_56_TEXT "\0"
"\x01\x57 " ENUM_ERROR_01_57_TEXT "\0"
"\x01\x58 " ENUM_ERROR_01_58_TEXT "\0"
"\x01\x59 " ENUM_ERROR_01_59_TEXT "\0"
"\x01\x5a " ENUM_ERROR_01_5a_TEXT "\0"
"\x01\x5b " ENUM_ERROR_01_5b_TEXT "\0"
"\x01\x5c " ENUM_ERROR_01_5c_TEXT "\0"
"\x01\x5d " ENUM_ERROR_01_5d_TEXT "\0"
"\x01\x5e " ENUM_ERROR_01_5e_TEXT "\0"
"\x01\x5f " ENUM_ERROR_01_5f_TEXT "\0"
"\x01\x60 " ENUM_ERROR_01_60_TEXT "\0"
"\x01\x61 " ENUM_ERROR_01_61_TEXT "\0"
"\x01\x65 " ENUM_ERROR_01_65_TEXT "\0"
"\x01\x6e " ENUM_ERROR_01_6e_TEXT "\0"
"\x01\x6f " ENUM_ERROR_01_6f_TEXT "\0"
"\x01\x72 " ENUM_ERROR_01_72_TEXT "\0"  //FUJITSU
"\x01\x73 " ENUM_ERROR_01_73_TEXT "\0"
"\x01\x74 " ENUM_ERROR_01_74_TEXT "\0"
"\x01\x75 " ENUM_ERROR_01_75_TEXT "\0"
"\x01\x76 " ENUM_ERROR_01_76_TEXT "\0"
"\x01\x77 " ENUM_ERROR_01_77_TEXT "\0"
"\x01\x78 " ENUM_ERROR_01_78_TEXT "\0"
"\x01\x79 " ENUM_ERROR_01_79_TEXT "\0"
"\x01\x7a " ENUM_ERROR_01_7a_TEXT "\0"
"\x01\x7e " ENUM_ERROR_01_7e_TEXT "\0"
"\x01\x80 " ENUM_ERROR_01_80_TEXT "\0"
"\x01\x81 " ENUM_ERROR_01_81_TEXT "\0"
"\x01\x82 " ENUM_ERROR_01_82_TEXT "\0"
"\x01\x83 " ENUM_ERROR_01_83_TEXT "\0"
"\x01\xab " ENUM_ERROR_01_ab_TEXT "\0"
"\x01\xad " ENUM_ERROR_01_ad_TEXT "\0"
"\x01\xae " ENUM_ERROR_01_ae_TEXT "\0"
"\x01\xaf " ENUM_ERROR_01_af_TEXT "\0"
"\x01\xb0 " ENUM_ERROR_01_b0_TEXT "\0"
"\x01\xb1 " ENUM_ERROR_01_b1_TEXT
};

//Internal error codes for Baxi Luna Platinum
const char ENUM_INTCODE[] = {
"\x01 " ENUM_INTCODE_01_TEXT //1
"\x02 " ENUM_INTCODE_02_TEXT //2
"\xdd " ENUM_INTCODE_dd_TEXT //357 same as 221
"\x01\x45 " ENUM_INTCODE_01_45_TEXT //325
"\x01\x46 " ENUM_INTCODE_01_46_TEXT //326 same as 325
"\x01\x47 " ENUM_INTCODE_01_47_TEXT //327 same as 325
"\x01\x48 " ENUM_INTCODE_01_48_TEXT //328 same as 325
"\x01\x49 " ENUM_INTCODE_01_49_TEXT //329 same as 325
"\x01\x4a " ENUM_INTCODE_01_4a_TEXT //330
"\x01\x4b " ENUM_INTCODE_01_4b_TEXT //331
"\x01\x4c " ENUM_INTCODE_01_4c_TEXT //332
"\x01\x4d " ENUM_INTCODE_01_4d_TEXT //333
"\x01\x4e " ENUM_INTCODE_01_4e_TEXT //334
"\x01\x4f " ENUM_INTCODE_01_4f_TEXT //335
"\x01\x50 " ENUM_INTCODE_01_50_TEXT //336
"\x01\x51 " ENUM_INTCODE_01_51_TEXT //337
"\x01\x52 " ENUM_INTCODE_01_52_TEXT  //338
"\x01\x53 " ENUM_INTCODE_01_53_TEXT  //339
"\x01\x59 " ENUM_INTCODE_01_59_TEXT  //345
"\x01\x5a " ENUM_INTCODE_01_5a_TEXT  //346
"\x01\x5b " ENUM_INTCODE_01_5b_TEXT  //347
"\x01\x5c " ENUM_INTCODE_01_5c_TEXT //348
"\x01\x5d " ENUM_INTCODE_01_5d_TEXT  //349
"\x01\x5e " ENUM_INTCODE_01_5e_TEXT  //350
"\x01\x65 " ENUM_INTCODE_01_65_TEXT //357 same as 221
"\x01\x66 " ENUM_INTCODE_01_66_TEXT  //358
"\x01\x67 " ENUM_INTCODE_01_67_TEXT  //359
"\x01\x68 " ENUM_INTCODE_01_68_TEXT  //360
"\x01\x69 " ENUM_INTCODE_01_69_TEXT  //361
"\x01\x6a " ENUM_INTCODE_01_6a_TEXT  //362
"\x01\x6b " ENUM_INTCODE_01_6b_TEXT  //363
"\x01\x6c " ENUM_INTCODE_01_6c_TEXT  //364
"\x01\x6d " ENUM_INTCODE_01_6d_TEXT  //365
"\x01\x6e " ENUM_INTCODE_01_6e_TEXT  //366
"\x01\x6f " ENUM_INTCODE_01_6f_TEXT  //367
"\x01\x70 " ENUM_INTCODE_01_70_TEXT  //368
"\x01\x71 " ENUM_INTCODE_01_71_TEXT  //369
"\x01\x72 " ENUM_INTCODE_01_72_TEXT  //370
"\x01\x73 " ENUM_INTCODE_01_73_TEXT  //371
"\x01\x74 " ENUM_INTCODE_01_74_TEXT  //372 same as 371
"\x01\x75 " ENUM_INTCODE_01_75_TEXT  //373
"\x01\xa2 " ENUM_INTCODE_01_a2_TEXT  //418
"\x01\xa3 " ENUM_INTCODE_01_a3_TEXT  //419
"\x01\xa4 " ENUM_INTCODE_01_a4_TEXT  //420
"\x01\xa5 " ENUM_INTCODE_01_a5_TEXT  //421
"\x01\xaa " ENUM_INTCODE_01_aa_TEXT  //426
"\x01\xab " ENUM_INTCODE_01_ab_TEXT  //427
"\x01\xac " ENUM_INTCODE_01_ac_TEXT  //428
"\x01\xad " ENUM_INTCODE_01_ad_TEXT  //429
"\x01\xaf " ENUM_INTCODE_01_af_TEXT  //431
"\x01\xb4 " ENUM_INTCODE_01_b4_TEXT  //436
"\x01\xb5 " ENUM_INTCODE_01_b5_TEXT  //437
"\x01\xb6 " ENUM_INTCODE_01_b6_TEXT  //438
"\x01\xf3 " ENUM_INTCODE_01_f3_TEXT //499
"\x01\xf4 " ENUM_INTCODE_01_f4_TEXT  //500
"\x01\xf5 " ENUM_INTCODE_01_f5_TEXT //501
"\x01\xf6 " ENUM_INTCODE_01_f6_TEXT  //502
"\x01\xf7 " ENUM_INTCODE_01_f7_TEXT  //503
"\x01\xf8 " ENUM_INTCODE_01_f8_TEXT  //504
"\x01\xfa " ENUM_INTCODE_01_fa_TEXT  //506
"\x01\xfb " ENUM_INTCODE_01_fb_TEXT  //507
"\x01\xfc " ENUM_INTCODE_01_fc_TEXT  //508
"\x01\xfd " ENUM_INTCODE_01_fd_TEXT  //509
"\x02\x1b " ENUM_INTCODE_02_1b_TEXT  //539 same as 506
"\x02\x1c " ENUM_INTCODE_02_1c_TEXT  //540
"\x02\x1f " ENUM_INTCODE_02_1f_TEXT //543
"\x02\x20 " ENUM_INTCODE_02_20_TEXT  //544
"\x02\x23 " ENUM_INTCODE_02_23_TEXT  //547
"\x02\x24 " ENUM_INTCODE_02_24_TEXT  //548
"\x02\x2d " ENUM_INTCODE_02_2d_TEXT  //557
"\x02\x2e " ENUM_INTCODE_02_2e_TEXT  //558
"\x02\x2f " ENUM_INTCODE_02_2f_TEXT  //559
"\x02\x30 " ENUM_INTCODE_02_30_TEXT  //560 same as 543
"\x02\x31 " ENUM_INTCODE_02_31_TEXT  //561
"\x02\x32 " ENUM_INTCODE_02_32_TEXT  //562
"\x02\x33 " ENUM_INTCODE_02_33_TEXT  //563
"\x02\x34 " ENUM_INTCODE_02_34_TEXT  //564
"\x02\x35 " ENUM_INTCODE_02_35_TEXT  //565
"\x02\x36 " ENUM_INTCODE_02_36_TEXT  //566
"\x02\x3c " ENUM_INTCODE_02_3c_TEXT  //572
"\x02\x3d " ENUM_INTCODE_02_3d_TEXT  //573
"\x02\x3e " ENUM_INTCODE_02_3e_TEXT  //574
"\x02\x3f " ENUM_INTCODE_02_3f_TEXT  //575
"\x02\x40 " ENUM_INTCODE_02_40_TEXT //576
"\x02\x41 " ENUM_INTCODE_02_41_TEXT //577
"\x02\x42 " ENUM_INTCODE_02_42_TEXT //578
"\x02\x43 " ENUM_INTCODE_02_43_TEXT //579
"\x02\x44 " ENUM_INTCODE_02_44_TEXT //580
"\x02\x45 " ENUM_INTCODE_02_45_TEXT //581
"\x02\xea " ENUM_INTCODE_02_ea_TEXT //746
"\x02\xeb " ENUM_INTCODE_02_eb_TEXT //747
"\x03\x00 " ENUM_INTCODE_03_00_TEXT //768
"\x03\x01 " ENUM_INTCODE_03_01_TEXT //769
"\x03\x17 " ENUM_INTCODE_03_17_TEXT //791
"\x03\x18 " ENUM_INTCODE_03_18_TEXT  //792
"\x03\x19 " ENUM_INTCODE_03_19_TEXT //793
"\x03\x1b " ENUM_INTCODE_03_1b_TEXT //795
"\x03\x1c " ENUM_INTCODE_03_1c_TEXT //796
"\x03\x1d " ENUM_INTCODE_03_1d_TEXT //797
"\x03\x20 " ENUM_INTCODE_03_20_TEXT //800
"\x03\x21 " ENUM_INTCODE_03_21_TEXT //801
"\x03\x22 " ENUM_INTCODE_03_22_TEXT //802
"\x03\x23 " ENUM_INTCODE_03_23_TEXT //803
"\x03\x24 " ENUM_INTCODE_03_24_TEXT //804
"\x03\x25 " ENUM_INTCODE_03_25_TEXT //805
"\x03\x26 " ENUM_INTCODE_03_26_TEXT //806
"\x03\x27 " ENUM_INTCODE_03_27_TEXT //807
"\x03\x28 " ENUM_INTCODE_03_28_TEXT //808
};

const char ENUM_SWCODE[] = {
"\x11 " ENUM_SWCODE_11_TEXT "\0"
"\x53 " ENUM_SWCODE_53_TEXT "\0"
"\x5f " ENUM_SWCODE_5f_TEXT "\0"
"\x60 " ENUM_SWCODE_60_TEXT "\0"
"\x61 " ENUM_SWCODE_61_TEXT "\0"
"\x69 " ENUM_SWCODE_69_TEXT "\0"
"\x6e " ENUM_SWCODE_6e_TEXT "\0"
"\x73 " ENUM_SWCODE_73_TEXT "\0"
"\x81 " ENUM_SWCODE_81_TEXT "\0"
"\xa2 " ENUM_SWCODE_a2_TEXT "\0"
"\xa8 " ENUM_SWCODE_a8_TEXT "\0"
"\xa9 " ENUM_SWCODE_a9_TEXT "\0"
"\xaa " ENUM_SWCODE_aa_TEXT "\0"
"\x01\x03 " ENUM_SWCODE_01_03_TEXT "\0"
"\x01\x19 " ENUM_SWCODE_01_19_TEXT "\0"
"\x01\x1a " ENUM_SWCODE_01_1a_TEXT "\0"
"\x01\x45 " ENUM_SWCODE_01_45_TEXT "\0"
"\x01\xa6 " ENUM_SWCODE_01_a6_TEXT "\0"
"\x01\xaa " ENUM_SWCODE_01_aa_TEXT "\0"
"\x01\xb1 " ENUM_SWCODE_01_b1_TEXT "\0"
"\x01\xc5 " ENUM_SWCODE_01_c5_TEXT "\0"
"\x01\xc7 " ENUM_SWCODE_01_c7_TEXT "\0"
"\x01\xc8 " ENUM_SWCODE_01_c8_TEXT "\0"
"\x01\xc9 " ENUM_SWCODE_01_c9_TEXT "\0"
"\x01\xca " ENUM_SWCODE_01_ca_TEXT "\0"
"\x01\xcb " ENUM_SWCODE_01_cb_TEXT "\0"
"\x01\xcc " ENUM_SWCODE_01_cc_TEXT "\0"
"\x01\xcd " ENUM_SWCODE_01_cd_TEXT "\0"
"\x01\xd6 " ENUM_SWCODE_01_d6_TEXT "\0"
"\x01\xe3 " ENUM_SWCODE_01_e3_TEXT "\0"
"\x01\xef " ENUM_SWCODE_01_ef_TEXT "\0"
"\x01\xf1 " ENUM_SWCODE_01_f1_TEXT "\0"
"\x02\x04 " ENUM_SWCODE_02_04_TEXT "\0"
"\x02\x06 " ENUM_SWCODE_02_06_TEXT "\0"
"\x02\x07 " ENUM_SWCODE_02_07_TEXT "\0"
"\x02\x08 " ENUM_SWCODE_02_08_TEXT "\0"
"\x02\x09 " ENUM_SWCODE_02_09_TEXT "\0"
"\x02\x1b " ENUM_SWCODE_02_1b_TEXT "\0"
"\x02\x24 " ENUM_SWCODE_02_24_TEXT "\0"
"\x02\x26 " ENUM_SWCODE_02_26_TEXT "\0"
"\x02\x28 " ENUM_SWCODE_02_28_TEXT "\0"
"\x02\x30 " ENUM_SWCODE_02_30_TEXT "\0"
"\x02\x31 " ENUM_SWCODE_02_31_TEXT "\0"
"\x02\x32 " ENUM_SWCODE_02_32_TEXT "\0"
"\x02\x33 " ENUM_SWCODE_02_33_TEXT "\0"
"\x02\x3d " ENUM_SWCODE_02_3d_TEXT "\0"
"\x02\x5a " ENUM_SWCODE_02_5a_TEXT "\0"
"\x02\x5f " ENUM_SWCODE_02_5f_TEXT "\0"
"\x02\x60 " ENUM_SWCODE_02_60_TEXT "\0"
"\x02\x6c " ENUM_SWCODE_02_6c_TEXT "\0"
"\x02\x6d " ENUM_SWCODE_02_6d_TEXT "\0"
"\x02\x6e " ENUM_SWCODE_02_6e_TEXT "\0"
"\x02\x7d " ENUM_SWCODE_02_7d_TEXT
};

// Wartungs-Codes
const char ENUM_WARTUNG[] = {
"\x01 " ENUM_WARTUNG_01_TEXT "\0"
"\x02 " ENUM_WARTUNG_02_TEXT "\0"
"\x03 " ENUM_WARTUNG_03_TEXT "\0"
"\x05 " ENUM_WARTUNG_05_TEXT "\0"
"\x12 " ENUM_WARTUNG_12_TEXT "\0"
"\x0a " ENUM_WARTUNG_0a_TEXT "\0"
"\x15 " ENUM_WARTUNG_15_TEXT "\0"
"\x16 " ENUM_WARTUNG_16_TEXT
};

#define STR_SAVE STR6204
#define STR_GF STR6225
#define STR_GV STR6226
#define S10000 STR10000
#define S10001 STR10001
#define S10002 STR10002

/*
 * Bei der Änderung des Komfortsollwertes durch einfaches Drehen des Rades
 * werden anscheinend die Grenzwerte abgefragt:
HEIZ->DISP ANS  710 11 - Heizkreis 1 - Komfortsollwert 20.00 &deg;C
HEIZ->DISP ANS      2D3D05A5 00 08 C0 (35.0°C)
DC 80 0A 0E 07 2D 3D 05 A5 00 08 C0 3F 7B
HEIZ->DISP ANS  712 11 - Heizkreis 1 - Reduziertsollwert 15.00 &deg;C
*/

/* **********************/
/* global command table */
/* **********************/

const cmd_t cmdtbl[]={
// Uhrzeit und Datum
{0x053D000B,  VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum
{0x0505000B,  VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x0500006C,  VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x053D000B,  VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x053D000B,  VT_TIME,          1,     STR1,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Uhrzeit und Datum - Stunden/Minuten
{0x053D000B,  VT_DAYMONTH,      2,     STR2,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt:MM ] - Uhrzeit und Datum - Tag/Monat
{0x053D000B,  VT_YEAR,          3,     STR3,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [jjjj ] - Uhrzeit und Datum - Jahr
{0x2D3D058E,  VT_TEMP,          710,   STR710,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert
{0x053D0001,  VT_STRING,        6224,  STR6224,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Geräte-Identifikation
{0x053D0002,  VT_UINT,          6225,  STR6225,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Gerätefamilie
{0x053D0003,  VT_UINT,          6226,  STR6226,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Gerätevariante
{0x053D0521,  VT_TEMP,          8700,  STR8700,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Diagnose Verbraucher - Aussentemperatur
{0x2D3D0215,  VT_TEMP,          10000, S10000,   0,                    NULL,         DEFAULT_FLAG+FL_WONLY+FL_FORCE_INF+FL_SPECIAL_INF, DEV_ALL}, // Raumtemperatur 1 (kann als INF geschickt werden)
{0x2E3E0215,  VT_TEMP,          10001, S10001,   0,                    NULL,         DEFAULT_FLAG+FL_WONLY+FL_FORCE_INF+FL_SPECIAL_INF, DEV_ALL}, // Raumtemperatur 2 (kann als INF geschickt werden) / some systems (e.g. RVS21.827D/127) seem to be sensitive to the second byte being 3E in this case instead of the usual 3D.
{0x2F3F0215,  VT_TEMP,          10002, S10002,   0,                    NULL,         DEFAULT_FLAG+FL_WONLY+FL_FORCE_INF+FL_SPECIAL_INF, DEV_ALL}, // Raumtemperatur 3/P (kann als INF geschickt werden)
