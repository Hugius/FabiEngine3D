#include "scene_editor.hpp"

void SceneEditor::_updateWaterMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuWater")
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
				vector<string> waterNames;
				for (const auto& ID : _waterEditor.getLoadedWaterIDs())
				{
					// Check if not engine water & not scene editor water
					if (ID[0] == '@' && ID.substr(0, 2) != "@@")
					{
						waterNames.push_back(ID.substr(1));
					}
				}

				// Add choice list
				_gui.getGlobalScreen()->createChoiceForm("waterList", "Choose Water", Vec2(-0.5f, 0.1f), waterNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_fe3d.waterEntity_delete(_currentWaterID);
				_currentWaterID = "";
			}
		}

		// Update water choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("waterList");
			if (!selectedButtonID.empty())
			{
				// Delete old
				if (_fe3d.waterEntity_isExisting(selectedButtonID))
				{
					_fe3d.waterEntity_delete(selectedButtonID);
				}

				// Create new
				_currentWaterID = selectedButtonID;
				_copyPreviewWater(_currentWaterID, "@" + selectedButtonID);
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
		}

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentWaterID != "");

		// Update water selection
		_fe3d.waterEntity_select(_currentWaterID);
	}
}