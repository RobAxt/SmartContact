#include <Arduino.h>
#include <Homie.h>
#include <Timer.h>
#include "ContactNode.hpp"
#include "VinNode.hpp"

#define FW_NAME "smart-contact"
#define FW_VERSION "1.0.0"

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

void onHomieEvent(const HomieEvent& event);
void prepareSleep();

ContactNode contactNode;
VinNode inputVoltage(VinNode::INTERVAL);
Timer timer;

void setup() {
  Serial.begin(74880,SERIAL_8N1,SERIAL_TX_ONLY);
  Serial << endl << endl;
  Serial << F("Build Date and Time: ") << __DATE__ << " & " << __TIME__ << endl;

  Homie.disableLedFeedback();
  Homie.disableResetTrigger();
  //Homie.setSetupFunction([](){});
  Homie.setLoopFunction([](){ timer.update(); });
  //Homie.setBroadcastHandler([](const String& level, const String& value){});
  Homie.onEvent(onHomieEvent);
  Homie_setFirmware(FW_NAME, FW_VERSION); // The underscore is not a typo! See Magic bytes

  Homie.setup();
}

void loop() {
  Homie.loop();
}

void prepareSleep() {
  Homie.prepareToSleep();
}

void onHomieEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_READY:
      Homie.getLogger() << "  ◦ MQTT connected, preparing for deep sleep after 100ms..." << endl;
      timer.after(100, prepareSleep);
      break;
    case HomieEventType::READY_TO_SLEEP:
      Homie.getLogger() << "  ◦ Ready to sleep" << endl;
      Homie.doDeepSleep(1000000, WAKE_RF_DISABLED);
      break;
  }
}