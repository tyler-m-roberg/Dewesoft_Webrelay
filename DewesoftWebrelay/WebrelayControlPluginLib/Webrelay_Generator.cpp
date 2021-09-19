#include "Webrelay_Generator.h"
#include <string>
#include <map>


using namespace Dewesoft::Utils::Dcom::OutputChannel;
using namespace Dewesoft::Utils::Serialization;


WebrelayGenerator::WebrelayGenerator(OutputFactory& outputFactory)
    : defaultOutputChannelName("Webrelay")
    , outputFactory(outputFactory)
    , defaultIPAddress("10.200.47.1")
    , defaultRelayID(0)
    , defaultRelayNum(1)
    , defaultTriggerChannel("")
    , defaultTriggerLevel(1)
    , defaultEdgeType(RisingEdge)
{
}

void WebrelayGenerator::addWebRelay(int relayID)
{
    addWebRelay(defaultOutputChannelName,
                relayID,
                defaultTriggerLevel,
                defaultIPAddress,
                defaultRelayNum,
                defaultEdgeType,
                defaultTriggerChannel);
    
}
 
void WebrelayGenerator::addWebRelay(std::string outputChannelName,                                   
                                    int relayID,
                                    double triggerLevel,
                                    std::string ipAddress,
                                    int relayNum,
                                    EdgeTypes edgeType,
                                    std::string triggerChannel)
{
    const OutputChannelPtr outputChannel = outputFactory.createOutputChannel(WebRelayOutputType, SetWebrelayOutputDefaults);
    SetupCreatedWebrelayOutput(outputChannel, outputChannelName);
    webRelays.emplace_back(outputChannel, outputChannelName, relayID, triggerLevel, ipAddress, relayNum, edgeType, triggerChannel);
    triggerChannels.emplace_back(triggerChannel);
    
    
}

void WebrelayGenerator::getData(const double& startTime, const double& sampleRate, const size_t& numSamples, const TriggerChannelData& triggerChannelData)
{
    for (auto& webrelay : webRelays)
    {
        
        webrelay.getData(startTime, sampleRate, numSamples, triggerChannelData);
    }
}


//Create vector of trigger channels and id's, maybe use a hash map
std::map<int, std::string> WebrelayGenerator::GetTriggerChannels() const
{
    std::map<int, std::string> triggerChannelMap;

    for (auto& webrelay : webRelays)
    {
        triggerChannelMap.emplace(std::make_pair(webrelay.getRelayID(), webrelay.getTriggerChannel()));
    }

    return triggerChannelMap;
} 

void WebrelayGenerator::clear()
{
    webRelays.clear();
    
}

void WebrelayGenerator::saveSettings(const NodePtr& node) const
{
    node->write(u8"DefaultName", defaultOutputChannelName);
}

void WebrelayGenerator::loadSettings(const NodePtr& node)
{
    node->read(u8"DefaultName", defaultOutputChannelName, 2);
}

void WebrelayGenerator::saveSetup(const NodePtr& node) const
{
    const auto webrelayList = node->addChild(u8"WebrelayList");
    for (const auto& webrelay : webRelays)
    {
        const auto webrelayNode = webrelayList->addChild(u8"Webrelay");
        webrelayNode->write(u8"OutputChannelId", webrelay.getOutputChannel()->getId());
        webrelay.saveSetup(webrelayNode);
    }
}

void WebrelayGenerator::loadSetup(const NodePtr& node)
{
    const auto webrelayList = node->findChildNode(u8"WebrelayList");
    if (!webrelayList)
        return;

    for (size_t i = 0; i < webrelayList->getChildCount(); ++i)
    {
        const auto webrelayNode = webrelayList->getChild(i);
        webRelays.emplace_back(loadOutputChannel(webrelayNode));
        webRelays.back().loadSetup(webrelayNode);
    }
}



OutputChannelPtr WebrelayGenerator::loadOutputChannel(const NodePtr& node) const
{
    int32_t outputChannelId;
    node->read(u8"OutputChannelId", outputChannelId, -1);
    return outputFactory.findOutputChannel(outputChannelId, WebRelayOutputType, SetWebrelayOutputDefaults);
    
}

void WebrelayGenerator::SetupCreatedWebrelayOutput(const Dewesoft::Utils::Dcom::OutputChannel::OutputChannelPtr& channel, std::string outputChannelName)
{
    channel->setName(outputChannelName);
    channel->setUserScaleMax(static_cast<float>(5));
    channel->setUserScaleMin(static_cast<float>(-5));
    channel->setUsed(true);
}

void WebrelayGenerator::SetWebrelayOutputDefaults(const OutputChannelPtr& channel)
{
    channel->setName(u8"Webrelay");
    channel->setUserScaleMax(5.0f);
    channel->setUserScaleMin(-5.0f);
    channel->setUsed(true);
}
