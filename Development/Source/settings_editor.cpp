#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"

#define GET_WIDTH(text) LVC::calcTextWidth(text, 0.15f, 1.8f)

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - settingsEditorMenuMain
	screenID = "settingsEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("mouseSensitivity", vec2(0.0f, 0.7875f), vec2(GET_WIDTH("Mouse speed"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Mouse speed", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("msaaQuality", vec2(0.0f, 0.525f), vec2(GET_WIDTH("MSAA quality"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "MSAA quality", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("shadowQuality", vec2(0.0f, 0.2625f), vec2(GET_WIDTH("Shadow quality"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Shadow quality", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("reflectionQuality", vec2(0.0f, 0.0f), vec2(GET_WIDTH("Reflection quality"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Reflection quality", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("refractionQuality", vec2(0.0f, -0.2625f), vec2(GET_WIDTH("Refraction quality"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Refraction quality", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("maxAudioChannels", vec2(0.0f, -0.525f), vec2(GET_WIDTH("Audio channels"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Audio channels", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GET_WIDTH("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
}

void SettingsEditor::load()
{
	_isLoaded = true;
	_fe3d.gfx_setMsaaQuality(16);
	_fe3d.gfx_setShadowQuality(4096);
	_fe3d.gfx_setRefractionQuality(512);
	_fe3d.gfx_setReflectionQuality(512);
	_fe3d.camera_setMouseSensitivity(5.0f);
}

void SettingsEditor::save()
{

}

void SettingsEditor::update()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "settingsEditorMenuMain")
		{
			auto screen = _leftWindow->getScreen("settingsEditorMenuMain");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mouseSensitivity")->isHovered())
				{
					
				}
				else if (screen->getButton("msaaQuality")->isHovered())
				{
					
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{

				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{

				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("main");
				}
			}
		}
	}
}