#include <ContactNode.hpp>

ContactNode::ContactNode() : HomieNode("reedSwitch", "Smart ReedSwitch", "Switch"), _reedSwitch(Contact::INTERVAL, Contact::INPUTPIN,Contact::ENABLEPIN) {
	
}

void 
ContactNode::setup() {
	_reedSwitch.setup();
	setRunLoopDisconnected(true);
	advertise("open").setName("Open").setDatatype("boolean").setFormat("true,false");
}

void 
ContactNode::loop() {
	_reedSwitch.loop();
	if(_reedSwitch.stateChanged()) {
		Homie.getLogger() << F("  ◦ The ") << Homie.getConfiguration().deviceId << F(" is ") << (_reedSwitch.getState()?"open":"close") << endl;
		if (Homie.isConnected())
			setProperty("open").send(_reedSwitch.getState()? "true":"false");
	}
}

void 
ContactNode::onReadyToOperate() { // this is execute when MQTT_READY
	_reedSwitch.loop();
	Homie.getLogger() << F("  ◦ Ready To Operate: ") << getName() << F(" -> The ") << Homie.getConfiguration().deviceId << F(" is ") << (_reedSwitch.getState()?"open":"close") << endl;
	setProperty("open").send(_reedSwitch.getState()? "true":"false");
}

bool 
ContactNode::handleInput(const HomieRange& range, const String& property, const String& value) {
	Homie.getLogger() << F("  ◦ ERROR: Input Handle property received: ") << property  << F(" value: ") << value << endl;
	return true;
}
