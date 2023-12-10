/*
  Modbus-Uni - Most complete Modbus Library for Arduino

  Modbus/TCP Security Client for ESP8266 Example
  
  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error Platform is not supported
#endif
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

// The client's private key which must be kept secret
const char client_private_key[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAyFOAs6+OSYI+04lGxdDErOMnQuNUf6wdnUpcHG65o5mR5SZ9
n4n3FQgbkB+Gv0gm1DQzl89t6djWR3i6XB1fE3rrw6HJqZSSLijaDfAT23mfiEuc
q7xwcwtEtm17NYDpHFsJnQ/OzakA/L+5voWYwSAQ7zwBzwV7BM5DTZap8ntpkWCP
BtLBk6jFlcwrfptpsCSwCMFQlmC1RJ97GP5LFOkq8MjSn56AgsPtIX2jFXVKtrvc
KQw9ovXyk8noUlu9u6+XTrRlG6d4aMYhVswJWqHbyJNHmf9dhDG6HN8uFi2se1tr
3nzXPbCnjOo4GEaKs+GEYCS22c5NbSZNvdudtQIDAQABAoIBAQCQQeGag795G/vW
JTL73JzkyydIuZ/t2KnyzMuMBghU0ZAIbjFko9t0H8SJgspsEK81fOnyVoOWNHoK
Odwp3VTMGGaTGHy6S60A5JYyF0KVd/30Dk8iNK7dia3PmQNywgQcUUqY+fs4io2V
dRNzKY2Y9Vh8jr/WruGp0kcRJn/3hrR7S10UyWDbQYE7R3Hir7V0YMFWEbzgwhRE
6MO6H5obFdZFxy7V+RJLeeq+dKHrvOmtd6F6hWSQUVX9YOVjh820IhhhC3F20EQw
FTiVO9UfpmOzhtBp0vOBCWIHa5Yu+AXufrytfT//DClyiex+kfXrmS+OhZS/zqPf
YjadqQF5AoGBAPXWUUD/jzkE82TPpwtRuIhZtF0kLedpBkzSg0e+Fgbdw4osRbMs
13cXMucWW9wK0TikHeoCcq1N2xDRWGreNqolbj9KEqWG0D2LcTBm0pKXuhAT+bWQ
hJmsiNEQYsM9hJLByLWNp3mwgzDLVjXDAxJgirP1L6Qw65SbQoYMt06bAoGBANCb
i3T0A/YP6ounu2iGiEqrJTU/11zh+ykVSvHd4MpV+szex7pBRlXpkFE2iqElAoja
xVrGsQCTebtJIz58Fy7tJQlTRqilRHCTRR60x+0ab7768OHZNKcSRXFDLVTdEyzv
dKTIZh0IJfbz/DpwyNqTM0GYLhDXJfyJxu7YmeHvAoGAC8N1n+aas9/Ixcop9CC0
89FXEB3rFGeyJXrtTUGLTEjQUoxLyYcbyFcT2Hr5ak4aNNulks0LL7/J+8QItxRr
CTlBTUX+Hm2VCVziza4d5WXdQWezSzzfG3tmEJr4Ht+SuHMNZ6KfoPMRVARm26u5
OefkuzfAT9sHatUDGecB3oECgYEAgWaLOlAHiQJUfq7cTLlvH8pMOVzRrfcsAk8H
/0KgJ0LwYVcsU7gb9jz83bPUiKNZkCUM2QN5Vp8kmu2CZEc7ZkuKdt9mbESgUKi5
7pM7lTOZ78Df3WkMBTsLQnfmTccZFv2uwGzjEs00J50vb9z4asV2vRC2OpILKT0Z
3p0Tz5cCgYEAnFJ5HAVKlzi4k8l7v1SuDb9vCLIG+XQYBNrhW/3BLQftOyEKgK5O
6fkNQT4u7Bgmzu3kpljq7jKBlPdW+l009L0gEEO5QBQLy64IquyydB1kiBIY5jGZ
x7M6SvzBWzC7gzH/P94LxtqM22zzU0LszocV2j1UkxqBVXv0EYVjPB0=
-----END RSA PRIVATE KEY-----
)EOF";

// The server's public certificate which must be shared
const char client_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICqjCCAZICFEIh1S7CewqVDZ9B78fSCkMQDkN9MA0GCSqGSIb3DQEBCwUAMBIx
EDAOBgNVBAMMB3Jvb3RfY2EwHhcNMjAwODI3MTAyODMxWhcNMzEwODEwMTAyODMx
WjARMQ8wDQYDVQQDDAZjbGllbnQwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK
AoIBAQDIU4Czr45Jgj7TiUbF0MSs4ydC41R/rB2dSlwcbrmjmZHlJn2fifcVCBuQ
H4a/SCbUNDOXz23p2NZHeLpcHV8TeuvDocmplJIuKNoN8BPbeZ+IS5yrvHBzC0S2
bXs1gOkcWwmdD87NqQD8v7m+hZjBIBDvPAHPBXsEzkNNlqnye2mRYI8G0sGTqMWV
zCt+m2mwJLAIwVCWYLVEn3sY/ksU6SrwyNKfnoCCw+0hfaMVdUq2u9wpDD2i9fKT
yehSW727r5dOtGUbp3hoxiFWzAlaodvIk0eZ/12EMboc3y4WLax7W2vefNc9sKeM
6jgYRoqz4YRgJLbZzk1tJk292521AgMBAAEwDQYJKoZIhvcNAQELBQADggEBAAeY
SL7wIYQONK2uqhqb9MmbfOZznlaGz6kybB0GtVmZpvBaqZtCmTSOSbs/0YVF3OSv
+L9+kWTGsaWx/6t1fdiDG8DlZCqF3dwbmd0YmV2GYbpRF53rYSUETSsdO2g1Fs0a
lvSVrQvhUj/cXvlTqtvjSVBELwFmlu0qhUHqN8Ap3dgy1YUZvRQcJS1GZ46iZLae
SQYAANvfYXC4gBy1vfgKeDkZD4Qs+NnV6J+aFpXTYsmMMOS/lfLTpWP2tEfuaexW
dGPlQ5dw7JZHcPrD9EdVIvDozACS0Y8B7oP4xvKFJnsqE7RmOsnukO0D7CQkxkBy
hJmblVkcv6VRNS9JHDQ=
-----END CERTIFICATE-----
)EOF";

// The server's public certificate which must be shared
const char server_pk[] PROGMEM = R"EOF(
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA3SpcCq8sUhAbBztc+X69
H+miV/Dxw9SH7X5Gtz09vOcEaDQnD2uXk6OXQUsiTPSYCqahrHZtjO1AQCWQBQUo
EIvvqUbjbLLM2tblK3tvE9zx1eOtzpmue5hX6SJShny/61blJaruIoDSIEE/8ECZ
sSTvLQ61mk4zM+FYAjZBuMtb3niKc+/wsvUuQsRCgW4m0J3KVF8leLU0/Tt+6s3t
Bq/ne3658skzra/NAMDDINT5+tYWW5LvRC/1RNd6FlQQUl89HsR1RvF/TXuLsrsh
txwFoXoJYUO5tkZAcU5A1aJUn+nnNV4J99eQTAhtXgUwGSjXUUUq+PsetKeO0Xml
iQIDAQAB
-----END PUBLIC KEY-----
)EOF";

//Modbus Registers Offsets
const int LED_COIL = 100;

//ModbusIP object
ModbusTLS mb;
// Set time via NTP, as required for x.509 validation
void setClock()
{
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

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
//IPAddress remote(192,168,30,127);
char* remote = "modbustls";
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
  mb.client();
}
uint16_t v;
void loop() {
    if (!mb.isConnected(remote)) {
      delay(1000);
      //mb.connectWithKnownKey(remote, MODBUSTLS_PORT, client_cert, client_private_key, server_pk);
      mb.connect(remote, MODBUSTLS_PORT, client_cert, client_private_key, ca_cert);
      Serial.print(".");
    } else {
        mb.readHreg(remote, 0, &v);
        mb.task();
        delay(100);
    }
}