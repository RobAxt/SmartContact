#ifndef contact_hpp
#define contact_hpp

#include <Arduino.h>

class Contact {
    public:
        Contact(unsigned long measurementInterval=INTERVAL, int inputPin=INPUTPIN, int enablePin=ENABLEPIN);
        void setup();
        void loop();
		bool getState();
		bool stateChanged();
        static const unsigned long INTERVAL = 1000;
        static const int INPUTPIN = 3; //gpio3
        static const int ENABLEPIN = 0; //gpio0

   private:
       int _inputPin;
	   int _enablePin;
       int _lastState;
	   int _currentState;
	   int _stateReaded;
	   unsigned long _measurementInterval;
       unsigned long _lastMeasurement;   
};
#endif //contact_hpp