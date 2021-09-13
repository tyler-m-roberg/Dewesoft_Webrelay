#pragma once
#include <mui/ds_window.h>
#include <mui/controls.h>
#include <mui/layout.h>
#include "base_setup_window.h"
#include "modal_window.h"
#include <mui/controls/timer_ptr.h>

class DewesoftBridge;

class SetupWindow : public BaseSetupWindow
{
public:
    explicit SetupWindow(Dewesoft::MUI::WindowPtr ui, DewesoftBridge& bridge);
    ~SetupWindow();
	
    void setupEnter();
    void setupLeave();

    void addChannelsToTriggerChannelCBox();
    void addEdgeCondToCBox();
    void addItemsToListBox();

    static int uniqueIDIndex;

    static int getUniqueID();



private:
	Dewesoft::MUI::Timer uiRefreshTimer;
    DewesoftBridge& bridge;

    void onSubmitClick(Dewesoft::MUI::Button& btn, Dewesoft::MUI::EventArgs& args);
    void onDeleteClick(Dewesoft::MUI::Button& btn, Dewesoft::MUI::EventArgs& args);

    Dewesoft::MUI::TextBox ipAddressTxtBox;
    Dewesoft::MUI::TextBox relayNumTxtBox;
    Dewesoft::MUI::ComboBox triggerChannelCBox;
    Dewesoft::MUI::ComboBox edgeTypeCBox;
    Dewesoft::MUI::TextBox triggerLevelTxtBox;
    Dewesoft::MUI::Button submitBtn;
    Dewesoft::MUI::Button deleteBtn;

    Dewesoft::MUI::ListBox listBox;


};

