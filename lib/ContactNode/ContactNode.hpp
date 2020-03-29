#ifndef contactNode_hpp
#define contactNode_hpp

#include <Homie.hpp>
#include "Contact.hpp"

class ContactNode : public HomieNode {
    public:
        ContactNode();

    protected:
        virtual void setup() override;
        virtual void loop() override;
        virtual void onReadyToOperate() override;
        virtual bool handleInput(const HomieRange& range, const String& property, const String& value);

   private:
       Contact _reedSwitch;
};
#endif //contactNode_hpp