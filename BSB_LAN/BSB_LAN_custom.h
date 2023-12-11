/* 
 * If configuration definement CUSTOM_COMMANDS is active, this code is run 
 * at the end of each main loop and utilizes the main loop variables 
 * custom_timer (set each loop to millis()) and custom_timer_compare.
 * This short example prints a "Ping!" message every 20 seconds.
*/

if (custom_timer > custom_timer_compare+20000) {    // every 20 seconds  
  custom_timer_compare = millis();
  Serial.println("Ping!");
}
