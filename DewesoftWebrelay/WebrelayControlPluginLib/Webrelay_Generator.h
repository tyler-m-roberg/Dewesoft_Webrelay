#pragma once
#include <vector>

#include <dcomlib/dcom_output_channel/output_factory.h>
#include <dcomlib/dcom_utils/dcom.h>;
#include <commonlib/serialization/node.h>
#include "Webrelay.h"

class WebrelayGenerator
{
public:
    explicit WebrelayGenerator(Dewesoft::Utils::Dcom::OutputChannel::OutputFactory& outputFactory);

    void addWebRelay(int relayID);
    void addWebRelay(std::string outputChannelName, int relayID,
                     double triggerLevel,
                     std::string ipAddress,
                     int relayNum,
                     EdgeTypes edgeType,
                     std::string triggerChannel);

    void getData(const double& startTime,
                 const double& sampleRate,
                 const size_t& numSamples);

    void clear();

    void saveSettings(const Dewesoft::Utils::Serialization::NodePtr& node) const;
    void loadSettings(const Dewesoft::Utils::Serialization::NodePtr& node);

    void saveSetup(const Dewesoft::Utils::Serialization::NodePtr& node) const;
    void loadSetup(const Dewesoft::Utils::Serialization::NodePtr& node);

    std::vector<std::string> triggerChannels;
    std::vector<Webrelay> webRelays;

private:
    inline static Dewesoft::Utils::Dcom::OutputChannel::OutputType WebRelayOutputType{
        Dewesoft::Utils::Dcom::Utils::ChannelDataType::Double, Dewesoft::Utils::Dcom::Utils::ChannelTimeBase::synchronous};

    static void SetupCreatedWebrelayOutput(const Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr& channel,
                                           std::string outputChannelName);
    static void SetWebrelayOutputDefaults(const Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr& channel);

    Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr loadOutputChannel(const Dewesoft::Utils::Serialization::NodePtr& node) const;

    std::string defaultOutputChannelName;
    int defaultRelayID;
    std::string defaultIPAddress;
    int defaultRelayNum;
    std::string defaultTriggerChannel;
    EdgeTypes defaultEdgeType;
    double defaultTriggerLevel;
    
    Dewesoft::Utils::Dcom::OutputChannel::OutputFactory& outputFactory;
};
