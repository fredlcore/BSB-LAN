
// By default, wg.begin() sets the WireGuard interface as the default route, which breaks outbound internet traffic if the VPN server doesn't forward it. To keep WiFi/Eth as the default outbound route (split tunnel):

wg_connect();