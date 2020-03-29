#ifndef vi_hpp
#define vi_hpp

#include <Arduino.h>

class Vin {
    public:
        static const unsigned long INTERVAL = 1000;
        Vin(unsigned long measurementInterval=INTERVAL);
        float read();

    private:
        float _voltage;
        unsigned long _measurementInterval;
        unsigned long _lastMeasurement;
};
#endif //vi_hpp