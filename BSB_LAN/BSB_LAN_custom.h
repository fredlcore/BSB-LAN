/* 
 * This code is run at the end of each main loop and utilizes the main loop variables 
 * custom_timer (set each loop to millis()) and custom_timer_compare.
 * This short example prints a "Ping!" message every 60 seconds.
*/

if (custom_timer > custom_timer_compare+60000) {    // every 60 seconds  
  custom_timer_compare = millis();
  printFmtToDebug("%lu Ping!\r\n", millis());
}
