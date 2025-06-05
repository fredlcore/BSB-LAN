/*
 * This custom function monitors selected parameters (defined below in pushParameters) and sends a push notification once a change occurs.
 * This can be used to send an alarm if the error or maintenance code changes, for example.
 * This script works with pushsafer.com, but it should be easy to adapt it to other services by adjusting the variables below.
 * There is one hard-coded check in BSB_LAN_custom.h that checks for the result string containing "success" or "error" which might have to 
 * be adjusted for the debug messages to work, but it won't do any harm to leave it as it is if debug output is not needed.
*/

const char* pushHost = "www.pushsafer.com";
const char* pushKey = "ENTER-PUSHSAFER.COM-KEY-HERE";
const char* pushSubject = "Heating system in 54321 Springfield";

const char* pushMethod = "POST";
const char* pushPath = "/api";
const char* pushFormatString = "k=%s&t=%s&m=%s";        // first parameter ("k=") = pushKey, second parameter ("t=") = pushSubject, third parameter ("m=") = message body

parameter pushParameters[5] = {    // up to 5 parameter/destination pairs
  // paramater, destination
  {10198, -1},                   // Error Code
  {10199, -1}                    // Maintenance Code
};

char previousErrorValue[5][64];
bool pushFirstRun = true;

