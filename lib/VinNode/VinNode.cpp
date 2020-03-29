#include <VinNode.hpp>

VinNode::VinNode(unsigned long interval) : HomieNode("inputVoltage", "ADC Voltage", "ADC Sensor"), _vin(Vin::INTERVAL), _lastSend(-interval), _sendInterval(interval) {
	
}

void 
VinNode::setup() {
	setRunLoopDisconnected(true);
	advertise("battery").setName("Battery Voltage").setDatatype("float").setFormat("2.5:3.5").setUnit("Volts");;
}

void 
VinNode::loop() {
	float voltage = _vin.read();
	
	if (millis() >= _sendInterval + _lastSend) {
		_lastSend = millis();
		Homie.getLogger() << F("  ◦ Voltage: ") << voltage << F(" Volts") << endl;
		if (Homie.isConnected())
			setProperty("battery").send(String(voltage));
	}
}

void 
VinNode::onReadyToOperate() { // this is execute when MQTT_READY
	float voltage = _vin.read();
	Homie.getLogger() << F("  ◦ Ready To Operate: ") << getName() << F(" -> Voltage: ") << voltage << F(" Volts") << endl;
	setProperty("battery").send(String(voltage));
}

bool 
VinNode::handleInput(const HomieRange& range, const String& property, const String& value) {
	Homie.getLogger() << F("  ◦ ERROR: Input Handle property received: ") << property  << F(" value: ") << value << endl;
	return true;
}
