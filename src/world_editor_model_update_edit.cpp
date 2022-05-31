#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateModelEditing()
{
	if(_currentTemplateModelId.empty() &&
	   _currentTemplateQuad3dId.empty() &&
	   _currentTemplateText3dId.empty() &&
	   _currentTemplateAabbId.empty() &&
	   _currentTemplatePointlightId.empty() &&
	   _currentTemplateSpotlightId.empty() &&
	   _currentTemplateCaptorId.empty() &&
	   _currentTemplateSound3dId.empty())
	{
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedModel)
		{
			_selectedModelId = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		for(const auto & modelId : _loadedModelIds)
		{
			const auto hasParent = (!hoveredAabbId.empty() && _fe3d->aabb_hasParent(hoveredAabbId) && (_fe3d->aabb_getParentType(hoveredAabbId) == AabbParentType::MODEL));
			const auto isHovered = (hasParent && (_fe3d->aabb_getParentId(hoveredAabbId) == modelId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectModel(modelId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedModelId != _activeModelId)
					{
						_activateModel(_selectedModelId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((modelId != _selectedModelId) && (modelId != _activeModelId))
				{
					_deselectModel(modelId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeModelId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedModelId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeModelId = "";
					}
				}
			}
		}

		if(!_activeModelId.empty())
		{
			const auto screen = window->getScreen("modelPropertiesMenu");
			const auto animation3dIds = _fe3d->model_getAnimation3dIds(_activeModelId);
			const auto isAnimations3dPlaying = (animation3dIds.empty() ? false : !_fe3d->model_isAnimation3dPaused(_activeModelId, animation3dIds[0]));
			const auto originalPosition = _fe3d->model_getBasePosition(_activeModelId);
			const auto originalRotation = _fe3d->model_getBaseRotation(_activeModelId);
			const auto originalSize = _fe3d->model_getBaseSize(_activeModelId);

			window->setActiveScreen("modelPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("addAnimation3d")->isHovered())
			{
				auto animation3dIds = _animation3dEditor->getLoadedAnimation3dIds();

				for(auto & animation3dId : animation3dIds)
				{
					animation3dId = animation3dId.substr(1);
				}

				_gui->getOverlay()->openChoiceForm("selectAnimation3d", "Select Animation3D", CENTER_CHOICE_FORM_POSITION, animation3dIds);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("startAnimation3d")->isHovered())
			{
				if(isAnimations3dPlaying)
				{
					for(const auto & animation3dId : animation3dIds)
					{
						_fe3d->model_stopAnimation3d(_activeModelId, animation3dId);
					}

					for(const auto & partId : _fe3d->model_getPartIds(_activeModelId))
					{
						if(!partId.empty())
						{
							_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
						}
					}
				}
				else
				{
					for(const auto & animation3dId : animation3dIds)
					{
						_fe3d->model_resumeAnimation3d(_activeModelId, animation3dId);
					}
				}
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				for(const auto & animation3dId : animation3dIds)
				{
					_fe3d->model_stopAnimation3d(_activeModelId, animation3dId);
				}

				_duplicator->deleteCopiedModel(_activeModelId);

				window->setActiveScreen("empty");

				_originalModelPositions.erase(_activeModelId);
				_originalModelRotations.erase(_activeModelId);
				_originalModelSizes.erase(_activeModelId);

				_loadedModelIds.erase(remove(_loadedModelIds.begin(), _loadedModelIds.end(), _activeModelId), _loadedModelIds.end());

				_activeModelId = "";

				return;
			}

			auto position = originalPosition;
			auto rotation = originalRotation;
			auto size = originalSize;

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("modelPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / MODEL_POSITION_SPEED_DIVIDER));
				_handleInputBox("modelPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / MODEL_POSITION_SPEED_DIVIDER));
				_handleInputBox("modelPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / MODEL_POSITION_SPEED_DIVIDER));

				_fe3d->model_setBasePosition(_activeModelId, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("modelPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, MODEL_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("modelPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, MODEL_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("modelPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, MODEL_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);

				_fe3d->model_setBaseRotation(_activeModelId, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("modelPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / MODEL_SIZE_SPEED_DIVIDER), MODEL_SIZE_FACTOR, 0.0f);
				_handleInputBox("modelPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / MODEL_SIZE_SPEED_DIVIDER), MODEL_SIZE_FACTOR, 0.0f);
				_handleInputBox("modelPropertiesMenu", "zMinus", "z", "zPlus", size.z, (_editorSpeed / MODEL_SIZE_SPEED_DIVIDER), MODEL_SIZE_FACTOR, 0.0f);

				_fe3d->model_setBaseSize(_activeModelId, size);
			}

			if((position != originalPosition) || (rotation != originalRotation) || (size != originalSize))
			{
				_originalModelPositions.at(_activeModelId) = position;
				_originalModelRotations.at(_activeModelId) = rotation;
				_originalModelSizes.at(_activeModelId) = size;

				if(isAnimations3dPlaying)
				{
					for(const auto & animation3dId : animation3dIds)
					{
						_fe3d->model_stopAnimation3d(_activeModelId, animation3dId);
						_fe3d->model_startAnimation3d(_activeModelId, animation3dId, -1);
					}

					for(const auto & partId : _fe3d->model_getPartIds(_activeModelId))
					{
						if(!partId.empty())
						{
							_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
						}
					}
				}
			}

			screen->getButton("addAnimation3d")->setHoverable(!isAnimations3dPlaying);
			screen->getButton("startAnimation3d")->setHoverable(!animation3dIds.empty());
			screen->getButton("startAnimation3d")->setTextContent(isAnimations3dPlaying ? "Stop Animation3D" : "Start Animation3D");
		}
	}
}