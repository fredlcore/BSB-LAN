# Custom functions for BSB-LAN

BSB-LAN allows to add custom functions through the following files:

`BSB_LAN_custom_global.h` -> This file allows you to add global variables.  
`BSB_LAN_custom_setup.h` -> This file is called at the end of the `setup()` function.  
`BSB_LAN_custom.h` -> This file is called with every iteration of the `loop()` function.  
  
In this folder, we collect scripts which add a certain functionality that is too specific to be added to the core functionality of BSB-LAN, but can be added through BSB-LAN's custom functions scripts.  
To use these scripts, you have to do two things:  
1. Copy the files of the example you want to use to BSB-LAN's main directory (where also BSB_LAN.ino and BSB_LAN_config.h can be found).
2. Enable the CUSTOM_COMMANDS definement by removing the to leading slashes at the beginning of the line so that it looks like this:  
`#define CUSTOM_COMMANDS`

Theoretically, you can use several of these custom functions at the same time, and sometimes it's as easy as just copy-pasting each code segment one after the other for each file. But do take note that this is similar to writing code for BSB-LAN itself, so be aware of what you are doing.
**Please understand that we cannot give any individual support in case of errors or problems!**
