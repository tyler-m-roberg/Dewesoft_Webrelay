#pragma once
#include <memory>
#include "dcomlib/dcom_utils/dewesoft_dcom_node.h"
#include <dcomlib/dcom_utils/plugin_types.h>
#include <dcomlib/dcom_utils/variant_helper.h>
#include "sine_generator.h"
#include "ui/settings_window.h"
#include "ui/setup_window.h"
#include <dcomlib/dcom_input_channel/input_manager_impl.h>
#include <dcomlib/dcom_output_channel/output_factory_impl.h>
#include "Webrelay_Generator.h"

struct IApp;

class DewesoftBridge
{
public:
    using NodePtr = Dewesoft::Utils::Serialization::NodePtr;
    using InputManagerImpl = Dewesoft::Utils::Dcom::InputChannel::InputManagerImpl;
    using OutputFactoryImpl = Dewesoft::Utils::Dcom::OutputChannel::OutputFactoryImpl;

    DewesoftBridge(InputManagerImpl& inputManager, OutputFactoryImpl& outputFactory, IAppPtr app = nullptr);

    void setPluginProps(IAppPtr app, _bstr_t pluginGuid, IPluginGroup* pluginGroup);

    bool checkSupportedDewesoftVersion(std::string& errorMessage) const;

    void onEnterHardwareSetup();
    void onUpdateSettings(NodePtr node);
    void onInitiateHardware();

    void onSetupEnter(bool analysisMode);
    void onSetupLeave(bool analysisMode);

    void onClearSetup();
    void onNewSetup();
    void onLoadSetup(NodePtr node, bool dataFile);
    void onSaveSetup(NodePtr node, bool dataFile);

    void onPreInitiate();

    void onStartData();
    void onGetData(const Dewesoft::Utils::Dcom::InputChannel::AcquiredDataInfo& acquiredDataInfo);
    void onStopData();

    void onStartStoring();
    void onStopStoring();

    void onPrepareAnalysis();
    void onStartAnalysis();
    bool isRecalculationRequired() const;

    bool showSetup(Dewesoft::MUI::IWindow* window);
    void hideSetup();

    bool showSettings(Dewesoft::MUI::IWindow* window);
    void hideSettings();

    void createWebRelay(std::string outputChannelName,
                        int relayID,
                        double triggerLevel,
                        std::string ipAddress,
                        int relayNum,
                        EdgeTypes edgeType,
                        std::string triggerChannel);

    std::vector<Webrelay> getRelayListForUI();

    void deleteWebRelay(const int& relayID);

    static HMODULE DllModule;

    std::vector<IChannelPtr> getChannels();

 private :
    InputManagerImpl& inputManager;
    OutputFactoryImpl& outputFactory;
    IAppPtr app;
    _bstr_t pluginGuid;
    IPluginGroup* pluginGroup;

    std::unique_ptr<SetupWindow> setupWindow;
    std::unique_ptr<SettingsWindow> settingsWindow;

    SineGenerator sineGenerator;
    WebrelayGenerator webrelayGenerator;
    IChannelPtr outputChannel;
    IChannelPtr inputChannel;

    int64_t lastPosChecked;
    std::map<int, std::string> triggerChannelMap;
    std::map<int, IChannelPtr> triggerChannelInterfaceMap;
};
