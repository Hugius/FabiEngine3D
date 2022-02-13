#include "animation3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void Animation3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("animationCreate", "Create Animation", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), _loadedAnimationIds);
			_isChoosingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), _loadedAnimationIds);
			_isChoosingAnimation = true;
			_isDeletingAnimation = true;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void Animation3dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->model_isAnimationStarted(_previewModelId, _currentAnimationId))
			{
				_fe3d->model_stopAnimation(_previewModelId, _currentAnimationId);
			}

			if(_fe3d->model_isExisting(_previewModelId))
			{
				for(const auto& partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
				{
					_fe3d->model_setVisible(_previewModelId, false);

					if(partId.empty())
					{
						_fe3d->model_setBasePosition(_previewModelId, fvec3(0.0f));
						_fe3d->model_setBaseRotationOrigin(_previewModelId, fvec3(0.0f));
						_fe3d->model_setBaseRotation(_previewModelId, fvec3(0.0f));
						_fe3d->model_setBaseSize(_previewModelId, _initialModelSize);
					}
					else
					{
						_fe3d->model_setPartPosition(_previewModelId, partId, fvec3(0.0f));
						_fe3d->model_setPartRotationOrigin(_previewModelId, partId, fvec3(0.0f));
						_fe3d->model_setPartRotation(_previewModelId, partId, fvec3(0.0f));
						_fe3d->model_setPartSize(_previewModelId, partId, fvec3(1.0f));
					}
				}
			}

			_previewModelId = "";
			_currentAnimationId = "";
			_initialModelSize = fvec3(0.0f);
			_currentFrameIndex = 0;
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), false);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityId(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				_fe3d->model_setVisible(_previewModelId, false);
			}

			auto modelIds = _modelEditor->getLoadedEntityIds();
			for(auto& id : modelIds)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Select Model", fvec2(-0.5f, 0.1f), modelIds);
			_isChoosingModel = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			for(const auto& partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
			{
				if(partId.empty())
				{
					_fe3d->model_setBasePosition(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseRotation(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseSize(_previewModelId, _initialModelSize);
				}
				else
				{
					_fe3d->model_setPartPosition(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotation(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartSize(_previewModelId, partId, fvec3(1.0f));
				}
			}

			_fe3d->model_startAnimation(_previewModelId, _currentAnimationId, 1);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->model_stopAnimation(_previewModelId, _currentAnimationId);

			for(const auto& partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
			{
				if(partId.empty())
				{
					_fe3d->model_setBasePosition(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseRotation(_previewModelId, fvec3(0.0f));
					_fe3d->model_setBaseSize(_previewModelId, _initialModelSize);
				}
				else
				{
					_fe3d->model_setPartPosition(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotation(_previewModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartSize(_previewModelId, partId, fvec3(1.0f));
				}
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_currentFrameIndex++;

			_fe3d->animation3d_createFrame(_currentAnimationId, _currentFrameIndex);

			for(const auto& partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
			{
				const auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto speed = _fe3d->animation3d_getSpeed(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimationId, (_currentFrameIndex - 1), partId);

				_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, partId, targetTransformation);
				_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, partId, rotationOrigin);
				_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, partId, speed);
				_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, partId, Animation3dSpeedType(speedType));
				_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, partId, TransformationType(transformationType));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuFrame");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->animation3d_deleteFrame(_currentAnimationId, _currentFrameIndex);

			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("prev")->isHovered())
		{
			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("next")->isHovered())
		{
			_currentFrameIndex++;
		}

		auto isStarted = (!_previewModelId.empty() && _fe3d->model_isAnimationStarted(_previewModelId, _currentAnimationId));
		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("start")->setHoverable(!isStarted && !_previewModelId.empty() && (_fe3d->animation3d_getFrameCount(_currentAnimationId) > 1));
		screen->getButton("stop")->setHoverable(isStarted && !_previewModelId.empty());
		screen->getButton("create")->setHoverable((_fe3d->animation3d_getFrameCount(_currentAnimationId) < MAX_FRAME_COUNT) && !isStarted && !_previewModelId.empty());
		screen->getButton("edit")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("delete")->setHoverable((_fe3d->animation3d_getFrameCount(_currentAnimationId) > 1) && (_currentFrameIndex > 0) && !isStarted && !_previewModelId.empty());
		screen->getButton("prev")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("next")->setHoverable((_currentFrameIndex < (_fe3d->animation3d_getFrameCount(_currentAnimationId) - 1)) && !isStarted && !_previewModelId.empty());

		if(!isStarted)
		{
			_gui->getOverlay()->getTextField("animationFrame")->changeTextContent("Frame: " + to_string(_currentFrameIndex + 1));
		}
	}
}