#pragma once
#include <string>
#include <Webrelay.h>

class WebRelayUI
{
public:

    //constructor

   int getUniqueRelayID() const;
    std::string getIPAddress() const;
   int getRelayNum() const;
   double getTriggerLevel
        

private:
    int uniqueRelayID;
    std::string ipAddress;
    int relayNum;
    double triggerLevel;
    std::string triggerChannel;
    EdgeTypes edgeType;
    std::string listBoxString;
};
