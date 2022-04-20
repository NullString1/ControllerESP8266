
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL7Ij4jdrx"
#define BLYNK_DEVICE_NAME "Controller"

#define BLYNK_FIRMWARE_VERSION        "0.1.1"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#ifdef serialLog
#define BLYNK_PRINT Serial
#define sLog(x) Serial.println(x)
#else
#define sLog(x)
#endif
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  sLog("V0 is now" + String(param.asInt()));
  if (param.asInt() == 1){
    sRelay(1, 1);
    sLog("Enabled relay 1");
    Blynk.logEvent("relay_1_closed");
  } else {
    sRelay(1, 0);
    sLog("Disabled relay 1");
    Blynk.logEvent("relay_1_opened");
  }
}

BLYNK_WRITE(V1)
{
  // Set incoming value from pin V0 to a variable
  sLog("V0 is now" + String(param.asInt()));
  if (param.asInt() == 1){
    sRelay(2, 1);
    sLog("Enabled relay 2");
    Blynk.logEvent("relay_2_closed");
  } else {
    sRelay(2, 0);
    sLog("Disabled relay 2");
    Blynk.logEvent("relay_2_opened");
  }
}

BLYNK_WRITE(V2)
{
  Blynk.virtualWrite(V2, 0);
  enterResetConfig();
}
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  delay(10);
  Blynk.syncVirtual(V1);
}
void sRelay(byte rNum, bool state) {
  byte message[] = {0xA0, rNum, state, (0xA0+rNum+state)};
  Serial.write(message, sizeof(message));
}
