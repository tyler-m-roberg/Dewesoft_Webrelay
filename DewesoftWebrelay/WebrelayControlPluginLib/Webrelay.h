#pragma once

#include <dcomlib/dcom_output_channel/output_channel.h>
#include <dcomlib/dcom_output_channel/output_factory.h>

enum EdgeTypes
{
    FallingEdge = 0,
    RisingEdge
};


class Webrelay
{
public:
    explicit Webrelay(Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr outputChannel);

    explicit Webrelay(Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr outputChannel,
                      std::string outputChannelName,
                      int relayID,
                      double triggerLevel,
                      std::string ipAddress,
                      int relayNum,
                      EdgeTypes edgeType,
                      std::string triggerChannel);

    Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr getOutputChannel() const;
    std::string getOutputChannelName() const;

    void getData(const double& startTime, const double& sampleRate, const size_t& numSamples);

    void saveSetup(const Dewesoft::Utils::Serialization::NodePtr& node) const;
    void loadSetup(const Dewesoft::Utils::Serialization::NodePtr& node);

    int getRelayID() const;
    double getTriggerLevel() const;
    std::string getIPAddress() const;
    int getRelayNum() const;
    EdgeTypes getEdgeType() const;
    std::string getTriggerChannel() const;

    void setTriggerLevel(double triggerLevel);
    void setIPAddress(std::string ipAddress);
    void setRelayNum(int relayNum);
    void setEdgeType(EdgeTypes edgeType);

    bool operator==(const Webrelay& relay1) const;

    bool operator!=(const Webrelay& relay1) const;

private:
    Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr outputChannel;
    std::string outputChannelName;

    // Store a relay identifier on creation and use to access output channel
    int relayID;
    std::string ipAddress;
    int relayNum;
    std::string triggerChannel;
    EdgeTypes edgeType;
    double triggerLevel;


    
};
