#include "Contact.hpp"

Contact::Contact(unsigned long measurementInterval, int inputPin, int enablePin) : _inputPin(inputPin), _enablePin(enablePin), _measurementInterval(measurementInterval) {
    _lastState = false;
	_currentState = false;
	_stateReaded = false;
	_lastMeasurement = 0;
}

void 
Contact::setup() {
	pinMode(_inputPin, INPUT_PULLUP);
	pinMode(_enablePin, OUTPUT);
	digitalWrite(_enablePin, HIGH);
}

void 
Contact::loop(){
	if (millis() >= _measurementInterval + _lastMeasurement) {
		_lastState = _currentState;
		
		digitalWrite(_enablePin, LOW);
		_currentState = digitalRead(_inputPin);
		digitalWrite(_enablePin, HIGH);
		
		_lastMeasurement = millis();
		_stateReaded  = false;
	}
}

bool 
Contact::getState() {
	return _currentState;
}

bool 
Contact::stateChanged() {
	if((_currentState != _lastState) && !_stateReaded) {
		_stateReaded = true;
		return true;
	}
	return false;
}