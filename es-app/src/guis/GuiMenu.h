#pragma once
#ifndef ES_APP_GUIS_GUI_MENU_H
#define ES_APP_GUIS_GUI_MENU_H

#include "components/MenuComponent.h"
#include "GuiComponent.h"
#include "MenuThemeData.h"

class GuiSettings;

class GuiMenu : public GuiComponent
{
public:
	GuiMenu(Window* window);

	bool input(InputConfig* config, Input input) override;
	void onSizeChanged() override;
	std::vector<HelpPrompt> getHelpPrompts() override;
	HelpStyle getHelpStyle() override;

private:
	void addSettingsEntry(GuiSettings* s, const char* name, bool add_arrow, const std::function<void()>& func);
	void addEntry(const char* name, bool add_arrow, const std::function<void()>& func);
	void addVersionInfo();
	void openCollectionSystemSettings();
	void openConfigInput();
	void openOtherSettings();
	void openQuitMenu();
	void openScraperSettings();
	void openScreensaverOptions();
	void openSoundSettings();
	void openUISettings();

	MenuComponent mMenu;
	TextComponent mVersion;

	std::shared_ptr<MenuTheme> mMenuTheme;
};

#endif // ES_APP_GUIS_GUI_MENU_H
