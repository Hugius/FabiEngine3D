#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateCamera()
{
	if(!_currentWorldID.empty())
	{
		if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getOverlay()->isFocused())
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_fe3d->camera_isFirstPersonViewEnabled())
			{
				_fe3d->camera_enableFirstPersonView(_fe3d->camera_getFirstPersonYaw(), _fe3d->camera_getFirstPersonPitch());
			}

			if(_fe3d->camera_isFirstPersonViewEnabled())
			{
				_fe3d->quad_setVisible("@@cursor", false);
			}
		}
		else
		{
			if(_fe3d->camera_isFirstPersonViewEnabled())
			{
				_fe3d->camera_disableFirstPersonView();
			}

			if(_fe3d->misc_isCursorInsideWindow())
			{
				_fe3d->quad_setVisible("@@cursor", true);
			}
		}

		if(!_gui.getOverlay()->isFocused())
		{
			if(_fe3d->input_isKeyDown(InputType::KEY_A))
			{
				_fe3d->camera_moveFollowX(-_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyDown(InputType::KEY_D))
			{
				_fe3d->camera_moveFollowX(_editorSpeed / 100.0f);
			}

			if(_fe3d->input_isKeyDown(InputType::KEY_SPACE))
			{
				_fe3d->camera_move(fvec3(0.0f, _editorSpeed / 75.0f, 0.0f));
			}
			if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
			{
				_fe3d->camera_move(fvec3(0.0f, -(_editorSpeed / 75.0f), 0.0f));
			}

			if(_fe3d->input_isKeyDown(InputType::KEY_W))
			{
				_fe3d->camera_moveFollowZ(_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyDown(InputType::KEY_S))
			{
				_fe3d->camera_moveFollowZ(-_editorSpeed / 100.0f);
			}
		}
	}
	else
	{
		_fe3d->camera_setYaw(0.0f);
		_fe3d->camera_setPitch(0.0f);
	}
}

void WorldEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_B))
		{
			if(_fe3d->misc_isAabbFrameRenderingEnabled())
			{
				_fe3d->misc_disableAabbFrameRendering();
			}
			else
			{
				_fe3d->misc_enableAabbFrameRendering();
			}

		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_F))
		{
			if(_fe3d->misc_isWireframeRenderingEnabled())
			{
				_fe3d->misc_disableWireframeRendering();
			}
			else
			{
				_fe3d->misc_enableWireframeRendering();
			}
		}
	}

	if(_fe3d->raycast_isTerrainPointingEnabled())
	{
		_fe3d->raycast_disableTerrainPointing();
	}

	if(!_fe3d->terrain_getSelectedID().empty())
	{
		_fe3d->raycast_enableTerrainPointing(_fe3d->terrain_getSize(_fe3d->terrain_getSelectedID()), 0.1f);
	}
}

void WorldEditor::_updateWorldCreating()
{
	if(_isCreatingWorld)
	{
		string newWorldID;

		if(_gui.getOverlay()->checkValueForm("worldCreate", newWorldID, {}))
		{
			if(newWorldID.find(' ') != string::npos)
			{
				Logger::throwWarning("World ID cannot contain any spaces!");
				return;
			}

			if(newWorldID.find('@') != string::npos)
			{
				Logger::throwWarning("World ID cannot contain '@'!");
				return;
			}

			const auto worldNames = _getWorldIDs();

			if(find(worldNames.begin(), worldNames.end(), newWorldID) != worldNames.end())
			{
				Logger::throwWarning("World with ID \"" + newWorldID.substr(1) + "\" already exists!");
				return;
			}

			_currentWorldID = newWorldID;
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
		}
	}
}

void WorldEditor::_updateWorldChoosing()
{
	if(_isChoosingWorld)
	{
		std::cout << "hoi";
		auto selectedButtonID = _gui.getOverlay()->checkChoiceForm("worldList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentWorldID = selectedButtonID;

				if(!_isDeletingWorld)
				{
					if(loadEditorWorldFromFile(_currentWorldID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
				}

				_gui.getOverlay()->deleteChoiceForm("worldList");
				_isChoosingWorld = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("worldList"))
		{
			_gui.getOverlay()->deleteChoiceForm("worldList");
			_isChoosingWorld = false;
			_isDeletingWorld = false;
		}
	}
}

void WorldEditor::_updateWorldDeleting()
{
	if(_isDeletingWorld && !_currentWorldID.empty())
	{
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_deleteWorldFile(_currentWorldID);
			_currentWorldID = "";
			_isDeletingWorld = false;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentWorldID = "";
			_isDeletingWorld = false;
		}
	}
}