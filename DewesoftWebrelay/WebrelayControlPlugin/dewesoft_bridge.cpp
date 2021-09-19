#include "StdAfx.h"
#include "dewesoft_bridge.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Dewesoft::Utils::Dcom::InputChannel;
using namespace Dewesoft::Utils::Dcom::OutputChannel;
using namespace Dewesoft::Utils::Dcom::Utils;

DewesoftBridge::DewesoftBridge(InputManagerImpl& inputManager, OutputFactoryImpl& outputFactory, const IAppPtr app)
    : inputManager(inputManager)
    , outputFactory(outputFactory)
    , app(app)
    , pluginGroup(nullptr)
    , sineGenerator(outputFactory)
    , webrelayGenerator(outputFactory)
{
}

void DewesoftBridge::setPluginProps(const IAppPtr app, const _bstr_t pluginGuid, IPluginGroup* pluginGroup)
{
    this->app = app;
    this->pluginGuid = pluginGuid;
    this->pluginGroup = pluginGroup;
}

bool DewesoftBridge::checkSupportedDewesoftVersion(std::string& errorMessage) const
{
    long major, minor, revision;
    app->GetInterfaceVersion(&major, &minor, &revision);

    // If function returns false, this message will be displayed on Dewesoft startup.
    errorMessage = "Current Test plugin version is supported from DEWESoftX 2020.1 onwards.";

    return true;
}

void DewesoftBridge::onEnterHardwareSetup()
{
}

void DewesoftBridge::onUpdateSettings(NodePtr node)
{
    if (node->isWrite())
    {
        webrelayGenerator.saveSettings(node);
    }
    else
    {
        webrelayGenerator.loadSettings(node);
    }
}

void DewesoftBridge::onInitiateHardware()
{
}

void DewesoftBridge::onSetupEnter(const bool analysisMode)
{
    setupWindow->setupEnter();
}

void DewesoftBridge::onSetupLeave(const bool analysisMode)
{
    setupWindow->setupLeave();
}

void DewesoftBridge::onClearSetup()
{
    webrelayGenerator.clear();
}

void DewesoftBridge::onNewSetup()
{
}

void DewesoftBridge::onLoadSetup(NodePtr node, bool dataFile)
{
    webrelayGenerator.loadSetup(node);
}

void DewesoftBridge::onSaveSetup(NodePtr node, bool dataFile)
{
    webrelayGenerator.saveSetup(node);
}

void DewesoftBridge::onPreInitiate()
{
}

// get vector of trigger channel and id's maybe as hash map
void DewesoftBridge::onStartData()
{

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);  
    triggerChannelMap = webrelayGenerator.GetTriggerChannels();

    for (auto const& pair : triggerChannelMap)
    {
        triggerChannelInterfaceMap.emplace(pair.first, app->Data->FindChannel(pair.second.c_str()));
    }

    lastPosChecked = 0;

}

// Code keeps crashing dewesoft need to investigate a better way to get channels and read data
// Map trigger channel values and send data to get data function of relays

void DewesoftBridge::onGetData(const AcquiredDataInfo& acquiredDataInfo)
{
    const double sampleRate = inputManager.getCurrentSampleRate();
    const double startTime = acquiredDataInfo.beginPos / sampleRate;
    const size_t numSamples = acquiredDataInfo.endPos - acquiredDataInfo.beginPos;

     std::cout << acquiredDataInfo.beginPos << "," << acquiredDataInfo.endPos << std::endl;

    //for (auto const& pair : triggerChannelInterfaceMap)
    //{
    //    int minBlockSize =
    //        (pair.second->DBPos - (lastPosChecked % pair.second->DBBufSize) + pair.second->DBBufSize) %
    //        pair.second->DBBufSize;


    //    for (int i = 0; i < minBlockSize - 1; i++)
    //    {
    //        float currentSample = pair.second->DBValues[lastPosChecked % pair.second->DBBufSize];
    //        float nextSample = pair.second->DBValues[(lastPosChecked + 1) % pair.second->DBBufSize];
                
    //        

    //        lastPosChecked++;
    //    }

    //}

    webrelayGenerator.getData(startTime, sampleRate, numSamples);
}

void DewesoftBridge::onStopData()
{
}

void DewesoftBridge::onStartStoring()
{
}

void DewesoftBridge::onStopStoring()
{
}

void DewesoftBridge::onPrepareAnalysis()
{
}

void DewesoftBridge::onStartAnalysis()
{
}

bool DewesoftBridge::isRecalculationRequired() const
{
    return false;
}

bool DewesoftBridge::showSettings(Dewesoft::MUI::IWindow* window)
{
    try
    {
        settingsWindow = std::make_unique<SettingsWindow>(window, *this);
    }
    catch (const std::exception& e)
    {
        app->WriteErrorMessage(e.what());
        return false;
    }
    return true;
}

void DewesoftBridge::hideSettings()
{
    settingsWindow.reset(nullptr);
}

bool DewesoftBridge::showSetup(Dewesoft::MUI::IWindow* window)
{
    try
    {
        setupWindow = std::make_unique<SetupWindow>(window, *this);
    }
    catch (const std::exception& e)
    {
        std::string msg = e.what();
        app->WriteErrorMessage(e.what());
        return false;
    }
    return true;
}

void DewesoftBridge::hideSetup()
{
    setupWindow.reset(nullptr);
}

std::vector<IChannelPtr> DewesoftBridge::getChannels()
{
    std::vector<IChannelPtr> allChannels;

    app->Data->BuildChannelList();
    IChannelListPtr channels = app->Data->UsedChannels;

    for (int i = 0; i < channels->GetCount(); i++)
    {
        allChannels.push_back(channels->GetItem(i));
    }

    return allChannels;
}

void DewesoftBridge::createWebRelay(std::string outputChannelName,
                                    int relayID,
                                    double triggerLevel,
                                    std::string ipAddress,
                                    int relayNum,
                                    EdgeTypes edgeType,
                                    std::string triggerChannel)
{
    webrelayGenerator.addWebRelay(outputChannelName, relayID, triggerLevel, ipAddress, relayNum, edgeType, triggerChannel);
}

std::vector<Webrelay> DewesoftBridge::getRelayListForUI()
{
    return webrelayGenerator.webRelays;
}

void DewesoftBridge::deleteWebRelay(const int& relayID)
{
    int relayIndex = 0;

    for (auto& webrelay : webrelayGenerator.webRelays)
    {
        if (webrelay.getRelayID() == relayID)
        {
            outputFactory.deleteOutputChannel(webrelay.getOutputChannel());

            webrelayGenerator.webRelays.erase(webrelayGenerator.webRelays.begin() + relayIndex);

            break;
        }

        relayIndex++;
    }
}
