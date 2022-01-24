#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateReflectionEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedCamera)
		{
			_selectedCameraID = "";
		}
		else
		{
			_dontResetSelectedCamera = false;
		}

		auto hoveredAabbId = _fe3d->raycast_checkCursorInAny().first;

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@camera").size()) == "@@camera")
			{
				if(hoveredAabbId == id && _fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectReflection(id.substr(string("@@camera_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedCameraID != _activeCameraID)
						{
							_activateReflection(_selectedCameraID.substr(string("@@camera_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedCameraID) && (id != _activeCameraID))
					{
						_unselectReflection(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeCameraID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedCameraID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeCameraID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedCameraID != _activeCameraID)
		{
			_updateCameraHighlighting(_selectedCameraID, _selectedCameraHighlightDirection);
		}
		_updateCameraHighlighting(_activeCameraID, _activeCameraHighlightDirection);

		if(!_activeCameraID.empty())
		{
			const string activeReflectionID = _activeCameraID.substr(string("@@camera_").size());
			auto screen = rightWindow->getScreen("reflectionPropertiesMenu");

			rightWindow->setActiveScreen("reflectionPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("capture")->isHovered())
				{
					_fe3d->reflection_capture(activeReflectionID);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeCameraID);
					_fe3d->reflection_delete(activeReflectionID);
					_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), activeReflectionID), _loadedReflectionIds.end());
					_activeCameraID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeCameraID);
				_fe3d->reflection_delete(activeReflectionID);
				_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), activeReflectionID), _loadedReflectionIds.end());
				_activeCameraID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->reflection_getPosition(activeReflectionID);

			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));

			_fe3d->reflection_setPosition(activeReflectionID, position);
			_fe3d->model_setBasePosition(_activeCameraID, position);
		}
	}
}