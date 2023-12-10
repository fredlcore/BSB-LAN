/*
  Modbus-Uni - Most complete Modbus Library for Arduino

  Modbus/TCP Security Server for ESP8266 Example
  
  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <ESP8266WiFi.h>
#include <time.h>
#include <ModbusTLS.h>

// The hardcoded certificate authority for this example.
// Don't use it on your own apps!!!!!

const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICwjCCAaqgAwIBAgIUTz9NFtf8JkdIkrDroXVB/ANtqlYwDQYJKoZIhvcNAQEL
BQAwEjEQMA4GA1UEAwwHcm9vdF9jYTAeFw0yMDA4MjcxMDI4MzFaFw0zMTExMTQx
MDI4MzFaMBIxEDAOBgNVBAMMB3Jvb3RfY2EwggEiMA0GCSqGSIb3DQEBAQUAA4IB
DwAwggEKAoIBAQCpYdVI2PjW+Pdw5bMqxFz0s3jgYgTHyt51NJGlImgJpmjmj16T
rwcqAe70BtsSjOQeWRoF/rk46ZO/ntDbVkP8ZA40Vf8F8Yft64f1OOBf93rTR0sH
oUk+HmE3Iu+bWYSewNMw/LJyF2r95V2xNeX50Y+BhQskBoWYR7C671ifFlsQHI+a
/BpALEi7qt6kGenlhrmRAjweNxVNILHTPH7Fr/TYXWfAb69TzXWTUFy0bdwZfPIP
b2HXyGINGiD6EtZDkybPk17zZgJKMdxpEG5XA/O+daVh3Prlar+amqb30zntOVga
AcyREcmzYFFBWQmuKNw9mz9x09GWLWjBaYP9AgMBAAGjEDAOMAwGA1UdEwQFMAMB
Af8wDQYJKoZIhvcNAQELBQADggEBAIFtNowXu8wfahpKF5MoNKrqA9AG/aGzlmbD
pBKr5Cvvo7NdC6oZMdXlS0VkRmAyw9mEJgwspUvqsLx0/lgN+sE381MUovWL9BIs
o4IOax5473q6ZwV87jwpsrlNHBiolw+WCDKVYuDktaThCaxqxmPKCPMbgYPdqWB0
l1gYDJJ+MwNH/CRsynpM8Hppf88BwwbM6JYegg5/DLxRl5z3HjCAVD8vBoqkWLRD
b9tIER4WDJhZG4tzgMW+lbMJyDoQA1cw4BGag4Ir1er32+w1519UR/VK0ltk9BK9
yHObfUNN6saco1/f4OM4tzaQOKa+6U1iXVBTBjE2IHPchGqctBk=
-----END CERTIFICATE-----
)EOF";

// The server's private key which must be kept secret
const char server_private_key[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA3SpcCq8sUhAbBztc+X69H+miV/Dxw9SH7X5Gtz09vOcEaDQn
D2uXk6OXQUsiTPSYCqahrHZtjO1AQCWQBQUoEIvvqUbjbLLM2tblK3tvE9zx1eOt
zpmue5hX6SJShny/61blJaruIoDSIEE/8ECZsSTvLQ61mk4zM+FYAjZBuMtb3niK
c+/wsvUuQsRCgW4m0J3KVF8leLU0/Tt+6s3tBq/ne3658skzra/NAMDDINT5+tYW
W5LvRC/1RNd6FlQQUl89HsR1RvF/TXuLsrshtxwFoXoJYUO5tkZAcU5A1aJUn+nn
NV4J99eQTAhtXgUwGSjXUUUq+PsetKeO0XmliQIDAQABAoIBAAEFxB0siCjs+CMF
bD2fD2LJYr3DWGrOXb6EWfFY8CMickvFCfUxSyccl4NuxH7Ulqtd79trRMBlDGn/
gnXzeybwbrA6qqyC+x175t1XmcDewaN6hQAyh7L8llN2nCkRBJYi9bZB3w37yHzr
sE79DXjbMdvkeIR5HhV8UjrYY19mVxbJsTokbrDXJEuDvR1kIkYM10UnEqMdDRiV
pSVFS3XkwNfCZHn/f2slcv1Piah8qfTseb5QPNouCZBW+PU5E1BuoFTH2ZtkzlZk
L6lcg42Ameyn5G9w8Walz89zwUIe3sycdJJ8+tRCWA2a2Aj8MeFiLfLxXnTjPNLU
nsVkuH0CgYEA/vbYyef3nzlmV4H+Rk9Rn3nGOeSTQj00avCUQS298bztEvFwcibM
84GOg0j68n/IW6gd4qBJyGpjBYl9ggcSTYBXKEK5FgtO6fM+Rnvnds3/WO7cMz3z
SzGIYranzcpaphj8H2xihW1OLsOUlb0+M71+6Y8P8Yui/mQIRRxHzMsCgYEA3hBc
/lzxs0A/TiwLlCpMIBuadkAxc4zgFY1LYHMveCwCa1cp9lujL5NRVOd8VhmYfpDg
MWAN3q7N/3dOu+hdMDoArXCXS5g5My3c6Ki87aSL1rmHyt9nYIBWZzjnwAii/zqs
kcKaFoEYv1vCuIMDFg+S1f+dpwuYlNn2pcnmwHsCgYEAlm/1+CQbsmI+5ZE5BClX
At7qPEyHKwVMAXFUOKURtyn/RDcbXu9P7Lnb6dDM6PrGsHYgtBBZmJxVMvYuDOO5
Q+tfAc1kwgIIHPg+HX6MU0g2yzWczctW214tl/koR7+G/wws7ymXdBzLjcIu0K9p
nUPJN2wHP0Fh+fHyAz0tjEMCgYB4R9C3Dkz01LX1d7IF3StCsPDnYDno5sNxqQjN
A1cQ9nWRArN994DagicpoAEe+do5o+trkyWwGmsGFu+UpHXla2V2jGfG0HsbF5py
gwNijSAZfIDrCDsMcDdczdvpjkQLjxJuGUQxMFfhPqioHH6Ncn4MX9pa4tMQvUb1
4fiVBQKBgAOtTdRqX66vvcOsjJmr2f+fw5SRXc09hxLaCDNjC6jVbCUw0aj6WKlx
sBfP8fvlHqJ6wA9/W2l+YiIf3G2jY2Z8OlOINs3hdXpH0JBzoeEiFwfcfZPAMFb1
M4JURmEGAriH2lw/5iMQ/YqB9+NoE8t8lBLrhjwXWxN3qxoSruwe
-----END RSA PRIVATE KEY-----
)EOF";

// The server's public certificate which must be shared
const char server_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICrTCCAZUCFEIh1S7CewqVDZ9B78fSCkMQDkN8MA0GCSqGSIb3DQEBCwUAMBIx
EDAOBgNVBAMMB3Jvb3RfY2EwHhcNMjAwODI3MTAyODMxWhcNMzEwODEwMTAyODMx
WjAUMRIwEAYDVQQDDAltb2RidXN0bHMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw
ggEKAoIBAQDdKlwKryxSEBsHO1z5fr0f6aJX8PHD1Iftfka3PT285wRoNCcPa5eT
o5dBSyJM9JgKpqGsdm2M7UBAJZAFBSgQi++pRuNsssza1uUre28T3PHV463Oma57
mFfpIlKGfL/rVuUlqu4igNIgQT/wQJmxJO8tDrWaTjMz4VgCNkG4y1veeIpz7/Cy
9S5CxEKBbibQncpUXyV4tTT9O37qze0Gr+d7frnyyTOtr80AwMMg1Pn61hZbku9E
L/VE13oWVBBSXz0exHVG8X9Ne4uyuyG3HAWheglhQ7m2RkBxTkDVolSf6ec1Xgn3
15BMCG1eBTAZKNdRRSr4+x60p47ReaWJAgMBAAEwDQYJKoZIhvcNAQELBQADggEB
AGqz1benN8ygveD3F/XxCMgEPfI8WhYS3PQ6sPBE850TuQ+9OrHvue8q87/RfJBW
Yllkyi2JHGuY2muMBJWGWTDHK72JwI69hIIwE9bGrvFUwAZjCbK9+gF6UIUDznNN
bSHHSWTfkCMLFz0Q6XbhJvF2AX5dtmYL+AWqD8+G5ZIrbHgd/o4neA21DTYRfUt2
0UQ0RAxKxf/BenJWr8IzvOxo0MHxi7JivgreCfxna1REZYxIwVFlh7O9KhB1QQBJ
oezb4CS0Um9sQowFTZ3AtRxpv1u60ZjTeJwSIL00YEyZ0sEO3K4h3PTbh2VxSoQD
D2fcSb1t+gWsvLVZCmNMbVo=
-----END CERTIFICATE-----
)EOF";


//Modbus Registers Offsets
const int LED_COIL = 100;

//ModbusIP object
ModbusTLS mb;
// Set time via NTP, as required for x.509 validation
void setClock()
{
  
  configTime(5 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}
  bool c(IPAddress ip) {
    Serial.println(ip);
    return true;
  }
void setup() {
  Serial.begin(115200);
 
  WiFi.begin("E2", "fOlissio92");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  setClock();
  mb.server(MODBUSTLS_PORT, server_cert, server_private_key, ca_cert);

  mb.addHreg(0);
}
 
void loop() {
   mb.task();
   delay(100);
}