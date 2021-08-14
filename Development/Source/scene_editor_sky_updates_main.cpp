#include "scene_editor.hpp"

void SceneEditor::_updateSkyMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSky")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				return;
			}
			else if (screen->getButton("choose")->isHovered())
			{
				// Retrieve created skies
				vector<string> skyNames;
				for (const auto& ID : _skyEditor.getLoadedSkyIDs())
				{
					// Check if not engine sky & not scene editor sky
					if (ID[0] == '@' && ID.substr(0, 2) != "@@")
					{
						skyNames.push_back(ID.substr(1));
					}
				}

				// Add choice list
				_gui.getGlobalScreen()->createChoiceForm("skyList", "Choose Sky", Vec2(-0.5f, 0.1f), skyNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_fe3d.skyEntity_delete(_currentSkyID);
				_currentSkyID = "";
			}
		}

		// Update sky choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("skyList");
			if (!selectedButtonID.empty())
			{
				// Delete old
				if (_fe3d.skyEntity_isExisting(selectedButtonID))
				{
					_fe3d.skyEntity_delete(selectedButtonID);
				}

				// Create new
				_currentSkyID = selectedButtonID;
				_copyPreviewSky(_currentSkyID, "@" + selectedButtonID);
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
			}
		}

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentSkyID != "");

		// Update sky selection
		_fe3d.skyEntity_selectMainSky(_currentSkyID);
	}
}