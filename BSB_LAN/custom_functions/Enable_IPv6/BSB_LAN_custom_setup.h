// The following code enables IPv6 support for various network interfaces in BSB-LAN.
// It does not hurt to leave all three lines enabled, even if only one or two network interfaces are used.
// Please take note that so far, the BSB-LAN web interface does not support IPv6 addresses
// for functions such as trusted IP addresses or DHCP configuration.
// Therefore, enabling IPv6 may lead to unexpected behavior in these functions.
// No support fo IPv6 is provided in the BSB-LAN project beyond enabling it on the respective network interfaces.

WiFi.enableIPv6();          // enable IPv6 for station mode
WiFi.softAPenableIPv6();    // enable IPv6 for SoftAP as well
Ethernet.enableIPv6();      // enable IPv6 for Ethernet as well