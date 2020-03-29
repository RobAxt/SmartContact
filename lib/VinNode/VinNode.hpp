#ifndef vinNode_hpp
#define vinNode_hpp

#include <Homie.hpp>
#include <Vin.hpp>

class VinNode : public HomieNode {
    public:
        static const unsigned long INTERVAL = 300000;
        VinNode(unsigned long interval = INTERVAL);
        float read();

    protected:
        virtual void setup() override;
        virtual void loop() override;
        virtual void onReadyToOperate() override;
        virtual bool handleInput(const HomieRange& range, const String& property, const String& value);

   private:
        Vin _vin;
        unsigned long _lastSend;
        unsigned long _sendInterval;
};
#endif //vinNode_hpp