# Push-button for TWW push and presence button function

The GPIO pins used for connecting the pushbuttons (one pin per pushbutton) must be set in `BSB_LAN_custom_global.h`.  
You have to use digital pins for the push-buttons, not analogue pins. Make sure that the pins you use are not used for other purposes (sometimes a pin may be accessible, but it is used internally). For Arduino Due-users: explicitly don’t use the pins 12, 16-21, 31, 33, 53!

The push-buttons need to be connected between the 3.3V pin (NOT the 5V pin!) and the respective digital input pin. Additionally, a pull-down resistor (approx. 100kOhm) needs to be connected between the digital input pin and GND.
If you are not sure how to connect a pushbutton to an microcontroller, please have a look at the internet, where you can find countless examples.

If you disconnect the pushbutton(s) (e.g. because you don’t want to use them anymore) make sure that you set the corresponding pin to “0” in `BSB_LAN_custom_global.h` again and flash the changed configuration. Otherwise the input pin may still react in undefined ways.

