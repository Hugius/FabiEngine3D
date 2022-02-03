#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateCamera()
{
	if(!_currentWorldId.empty())
	{
		if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui->getOverlay()->isFocused())
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->camera_setFirstPersonEnabled(true);
			}

			if(_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->quad2d_setVisible("@@cursor", false);
			}
		}
		else
		{
			_fe3d->camera_setFirstPersonEnabled(false);

			if(_fe3d->misc_isCursorInsideWindow())
			{
				_fe3d->quad2d_setVisible("@@cursor", true);
			}
		}

		if(!_gui->getOverlay()->isFocused())
		{
			if(_fe3d->input_isKeyDown(InputType::KEY_A))
			{
				_fe3d->camera_followRightXZ(-_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyDown(InputType::KEY_D))
			{
				_fe3d->camera_followRightXZ(_editorSpeed / 100.0f);
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
				_fe3d->camera_followFrontXZ(_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyDown(InputType::KEY_S))
			{
				_fe3d->camera_followFrontXZ(-_editorSpeed / 100.0f);
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
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_F))
		{
			_isWireframeModeEnabled = !_isWireframeModeEnabled;
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_B))
		{
			_isAabbModeEnabled = !_isAabbModeEnabled;
		}

		if(!_loadedSkyId.empty())
		{
			_fe3d->sky_setWireframed(_loadedSkyId, _isWireframeModeEnabled);
		}

		if(!_loadedTerrainId.empty())
		{
			_fe3d->terrain_setWireframed(_loadedTerrainId, _isWireframeModeEnabled);
		}

		if(!_loadedWaterId.empty())
		{
			_fe3d->water_setWireframed(_loadedWaterId, _isWireframeModeEnabled);
		}

		for(const auto& modelId : _fe3d->model_getIds())
		{
			for(const auto& partId : _fe3d->model_getPartIds(modelId))
			{
				_fe3d->model_setWireframed(modelId, partId, _isWireframeModeEnabled);
			}

			for(const auto& aabbId : _fe3d->aabb_getChildIds(modelId, AabbParentEntityType::MODEL))
			{
				_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
			}
		}

		for(const auto& quadId : _fe3d->quad3d_getIds())
		{
			_fe3d->quad3d_setWireframed(quadId, _isWireframeModeEnabled);

			for(const auto& aabbId : _fe3d->aabb_getChildIds(quadId, AabbParentEntityType::QUAD3D))
			{
				_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
			}
		}

		for(const auto& textId : _fe3d->text3d_getIds())
		{
			_fe3d->text3d_setWireframed(textId, _isWireframeModeEnabled);

			for(const auto& aabbId : _fe3d->aabb_getChildIds(textId, AabbParentEntityType::TEXT3D))
			{
				_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
			}
		}
	}

	if(_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->collision_setCameraTerrainResponseEnabled(false);
		_fe3d->collision_setCameraTerrainResponseHeight(0.0f);
		_fe3d->collision_setCameraTerrainResponseSpeed(0.0f);
		_fe3d->raycast_setTerrainPointingEnabled(false);
		_fe3d->raycast_setTerrainPointingDistance(0.0f);
		_fe3d->raycast_setTerrainPointingPrecision(0.0f);
	}
	else
	{
		_fe3d->collision_setCameraTerrainResponseEnabled(true);
		_fe3d->collision_setCameraTerrainResponseHeight(1.0f);
		_fe3d->collision_setCameraTerrainResponseSpeed(_editorSpeed);
		_fe3d->raycast_setTerrainPointingEnabled(true);
		_fe3d->raycast_setTerrainPointingDistance(Math::calculateDistance(fvec3(_fe3d->terrain_getSize(_fe3d->terrain_getSelectedId())), fvec3(0.0f)));
		_fe3d->raycast_setTerrainPointingPrecision(0.1f);
	}
}

void WorldEditor::_updateWorldCreating()
{
	if(_isCreatingWorld)
	{
		string newWorldId;

		if(_gui->getOverlay()->checkValueForm("worldCreate", newWorldId, {}))
		{
			if(newWorldId.find('@') != string::npos)
			{
				Logger::throwWarning("World ID cannot contain '@'");
				return;
			}

			if(newWorldId.find(' ') != string::npos)
			{
				Logger::throwWarning("World ID cannot contain any spaces");
				return;
			}

			const auto worldNames = _getWorldIds();

			if(find(worldNames.begin(), worldNames.end(), newWorldId) != worldNames.end())
			{
				Logger::throwWarning("World already exists");
				return;
			}

			_currentWorldId = newWorldId;
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
		}
	}
}

void WorldEditor::_updateWorldChoosing()
{
	if(_isChoosingWorld)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("worldList");

		if(!selectedButtonId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentWorldId = selectedButtonId;

				if(!_isDeletingWorld)
				{
					if(loadEditorWorldFromFile(_currentWorldId))
					{
						_fe3d->misc_setVsyncEnabled(false);
						_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
				}

				_gui->getOverlay()->deleteChoiceForm("worldList");
				_isChoosingWorld = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("worldList"))
		{
			_gui->getOverlay()->deleteChoiceForm("worldList");
			_isChoosingWorld = false;
			_isDeletingWorld = false;
		}
	}
}

void WorldEditor::_updateWorldDeleting()
{
	if(_isDeletingWorld && !_currentWorldId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_deleteWorldFile(_currentWorldId);
			_currentWorldId = "";
			_isDeletingWorld = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentWorldId = "";
			_isDeletingWorld = false;
		}
	}
}