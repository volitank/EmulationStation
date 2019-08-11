#include "Log.h"
#include "MenuThemeData.h"
#include "Settings.h"
#include "ThemeData.h"
#include "Renderer.h"
#include "resources/Font.h"

std::shared_ptr<MenuThemeData> MenuThemeData::sInstance = nullptr;

std::shared_ptr<MenuThemeData> MenuThemeData::getInstance() {
	if (sInstance == nullptr)
		sInstance = std::shared_ptr<MenuThemeData>(new MenuThemeData());
	return sInstance;
}

MenuThemeData::MenuThemeData(){
}

void MenuThemeData::loadTheme()
{
	std::shared_ptr<ThemeData> mTheme = std::make_shared<ThemeData>();

	std::string path = ThemeData::getDefaultThemeFromCurrentSet();

	if(!Utils::FileSystem::exists(path)) // no theme available for this platform
		return;

	try
	{
		std::map<std::string, std::string> sysData;
		mTheme->loadFile(sysData, path);
	} catch(ThemeException& e)
	{
		LOG(LogError) << e.what();
		mTheme = std::make_shared<ThemeData>(); // reset to empty
	}

	mCurrent = std::shared_ptr<MenuTheme>(new MenuTheme);

	auto elem = mTheme->getElement("menu", "menubg", "menuBackground");

	if (elem)
	{
		if (elem->has("path"))
			mCurrent->background.path = elem->get<std::string>("path");
		if (elem->has("fadePath"))
			mCurrent->background.fadePath = elem->get<std::string>("fadePath");
		if (elem->has("color"))
			mCurrent->background.color = elem->get<unsigned int>("color");
	}

	elem = mTheme->getElement("menu", "menutitle", "menuText");

	if (elem)
	{
		if(elem->has("fontPath") || elem->has("fontSize"))
			mCurrent->title.font = Font::getFromTheme(elem, ThemeFlags::ALL, Font::get(FONT_SIZE_LARGE));
		if(elem->has("color"))
			mCurrent->title.color = elem->get<unsigned int>("color");
	}

	elem = mTheme->getElement("menu", "menufooter", "menuText");

	if (elem)
	{
		if(elem->has("fontPath") || elem->has("fontSize"))
			mCurrent->footer.font = Font::getFromTheme(elem, ThemeFlags::ALL, Font::get(FONT_SIZE_SMALL));
		if(elem->has("color"))
			mCurrent->footer.color = elem->get<unsigned int>("color");
	}

	elem = mTheme->getElement("menu", "menutext", "menuText");

	if (elem)
	{
		if(elem->has("fontPath") || elem->has("fontSize"))
		{
			mCurrent->text.font = Font::getFromTheme(elem, ThemeFlags::ALL, Font::get(FONT_SIZE_MEDIUM));
		}

		if(elem->has("color"))
			mCurrent->text.color = elem->get<unsigned int>("color");
		if(elem->has("separatorColor"))
			mCurrent->text.separatorColor = elem->get<unsigned int>("separatorColor");
		if(elem->has("selectedColor"))
			mCurrent->text.selectedColor = elem->get<unsigned int>("selectedColor");
		if(elem->has("selectorColor"))
			mCurrent->text.selectorColor = elem->get<unsigned int>("selectorColor");
	}

	elem = mTheme->getElement("menu", "menutextsmall", "menuTextSmall");

	if (elem)
	{
		if(elem->has("fontPath") || elem->has("fontSize"))
		{
			mCurrent->textSmall.font = Font::getFromTheme(elem, ThemeFlags::ALL, Font::get(FONT_SIZE_SMALL));
		}

		if(elem->has("color"))
			mCurrent->textSmall.color = elem->get<unsigned int>("color");
		if(elem->has("selectedColor"))
			mCurrent->text.selectedColor = elem->get<unsigned int>("selectedColor");
		if(elem->has("selectorColor"))
			mCurrent->text.selectedColor = elem->get<unsigned int>("selectorColor");
	}

	elem = mTheme->getElement("menu", "menubutton", "menuButton");

	if (elem)
	{
		if(elem->has("path"))
			mCurrent->iconSet.button = elem->get<std::string>("path");
		if(elem->has("filledPath"))
			mCurrent->iconSet.button_filled = elem->get<std::string>("filledPath");
	}

	elem = mTheme->getElement("menu", "menuswitch", "menuSwitch");

	if (elem)
	{
		if(elem->has("pathOn"))
			mCurrent->iconSet.on = elem->get<std::string>("pathOn");
		if(elem->has("pathOff"))
			mCurrent->iconSet.off = elem->get<std::string>("pathOff");
	}

	elem = mTheme->getElement("menu", "menuslider", "menuSlider");

	if (elem)
		if(elem->has("path"))
			mCurrent->iconSet.knob = elem->get<std::string>("path");

	elem = mTheme->getElement("menu", "menuicons", "menuIcons");

	if (elem) {
		if (elem->has("iconSystem"))
			mCurrent->menuIconSet.system = elem->get<std::string>("iconSystem");

		if (elem->has("iconUpdates"))
			mCurrent->menuIconSet.updates = elem->get<std::string>("iconUpdates");

		if (elem->has("iconGames"))
			mCurrent->menuIconSet.games = elem->get<std::string>("iconGames");

		if (elem->has("iconControllers"))
			mCurrent->menuIconSet.controllers = elem->get<std::string>("iconControllers");

		if (elem->has("iconUI"))
			mCurrent->menuIconSet.ui = elem->get<std::string>("iconUI");

		if (elem->has("iconSound"))
			mCurrent->menuIconSet.sound = elem->get<std::string>("iconSound");

		if (elem->has("iconNetwork"))
			mCurrent->menuIconSet.network = elem->get<std::string>("iconNetwork");

		if (elem->has("iconScraper"))
			mCurrent->menuIconSet.scraper = elem->get<std::string>("iconScraper");

		if (elem->has("iconAdvanced"))
			mCurrent->menuIconSet.advanced = elem->get<std::string>("iconAdvanced");

		if (elem->has("iconQuit"))
			mCurrent->menuIconSet.quit = elem->get<std::string>("iconQuit");
	}
	
}