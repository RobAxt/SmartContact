#include "Vin.hpp"

ADC_MODE(ADC_VCC);

Vin::Vin(unsigned long measurementInterval) : _voltage(NAN), _measurementInterval(measurementInterval), _lastMeasurement(-measurementInterval) {
	
}

float 
Vin::read() {
	if (millis() >= _measurementInterval + _lastMeasurement) {
		if(isnan(_voltage))	
			_voltage = (float)ESP.getVcc() / 1024.0f;
		else {
			_voltage += (float)ESP.getVcc() / 1024.0f;
			_voltage /= 2;
		}
		_lastMeasurement = millis();	
	}
	
	return _voltage;
}