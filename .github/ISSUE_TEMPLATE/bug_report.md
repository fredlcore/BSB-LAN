---
name: Bug report
about: Create a report to help us improve
title: "[BUG]"
labels: ''
assignees: ''

---

**Before submitting a bug report, please make sure that you have checked the [FAQ](https://docs.bsb-lan.de/faq.html) and [troubleshooting section](https://docs.bsb-lan.de/troubleshooting.html) of the manual**. Most problems that are reported to us can be solved by going through the solutions provided there.

**Do not remove any of these questions! Bug-Reports that do not contain all required information will not be accepted. If you cannot provide any required information, explain why this is the case.**

**Version of the Arduino IDE**  
Please note: Versions 1.8.19 and below are not supported by this project anymore.

**Version of the ESP32 or Arduino framework**  
See ***Tools/Board/Board Manager*** for exact version you are using

**BSB-LAN Version**  
As displayed in the web-configuration or copy from `bsb-version.h` file. Please make sure that you have installed the most recent version from the master repository and also updated your BSB_LAN_config.h accordingly. We don't fix bugs for discontinued platforms (such as Arduino Mega).

**Architecture**  
The architecture BSB-LAN is running on (Arduino Mega, Arduino Due, ESP32 NodeMCU, ESP32 Olimex EVB etc.)

**Bus system**  
Which bus BSB-LAN is running on (BSB, LPB, PPS)?

**Describe the bug**  
A clear and concise description of what the bug is.

**To Reproduce**  
Steps to reproduce the behavior:
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Log files - Bug reports without log files will be closed**  
If you cannot provide a log file, explain here why in order to prevent closing this bug report. Attach or copy/paste the log of the Arduino IDE's serial monitor when performing the actions that lead to the error. If possible start the log right before BSB-LAN boots (pressing the reset button on the board).

**Expected behavior**  
A clear and concise description of what you expected to happen.

**Screenshots**  
If applicable, add screenshots to help explain your problem.

**Desktop (if applicable, please complete the following information):**  
 - OS: [e.g. MacOS 11.1, Windows 11]
 - Browser [e.g. Chrome, Safari]
 - Browser version [e.g. 22]

**Smartphone (if applicable, please complete the following information):**  
 - Device: [e.g. iPhone6]
 - OS: [e.g. iOS8.1]
 - Browser [e.g. Safari, FireFox]
 - Browser version [e.g. 22]

**Additional context**  
Add any other context about the problem here.

**Attach your BSB_LAN_config.h file to your bug report (remove any confidential information if necessary). Do not ZIP or otherwise compress it. Bug reports without this file attached will be closed immediately.**
