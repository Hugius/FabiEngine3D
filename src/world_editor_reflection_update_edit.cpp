#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateReflectionEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedCamera)
		{
			_selectedCameraId = "";
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
						if(_selectedCameraId != _activeCameraId)
						{
							_activateReflection(_selectedCameraId.substr(string("@@camera_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedCameraId) && (id != _activeCameraId))
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
				if(!_activeCameraId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedCameraId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeCameraId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedCameraId != _activeCameraId)
		{
			_updateCameraHighlighting(_selectedCameraId, _selectedCameraHighlightDirection);
		}
		_updateCameraHighlighting(_activeCameraId, _activeCameraHighlightDirection);

		if(!_activeCameraId.empty())
		{
			const string activeReflectionId = _activeCameraId.substr(string("@@camera_").size());
			auto screen = rightWindow->getScreen("reflectionPropertiesMenu");

			rightWindow->setActiveScreen("reflectionPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("capture")->isHovered())
				{
					_fe3d->reflection_capture(activeReflectionId);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeCameraId);
					_fe3d->reflection_delete(activeReflectionId);
					_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), activeReflectionId), _loadedReflectionIds.end());
					_activeCameraId = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeCameraId);
				_fe3d->reflection_delete(activeReflectionId);
				_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), activeReflectionId), _loadedReflectionIds.end());
				_activeCameraId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->reflection_getPosition(activeReflectionId);

			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));

			_fe3d->reflection_setPosition(activeReflectionId, position);
			_fe3d->model_setBasePosition(_activeCameraId, position);
		}
	}
}