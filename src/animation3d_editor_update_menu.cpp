#include "animation3d_editor.hpp"

#include <algorithm>

void Animation3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAnimation", "Create Animation", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedAnimationIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editAnimation", "Edit Animation", fvec2(0.0f, 0.1f), ids);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedAnimationIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteAnimation", "Delete Animation", fvec2(0.0f, 0.1f), ids);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveAnimationsToFile();
				unload();
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}

void Animation3dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				if(_fe3d->model_isAnimationStarted(_previewModelId, _currentAnimationId))
				{
					_fe3d->model_stopAnimation(_previewModelId, _currentAnimationId);
				}

				for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
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
			_gui->getOverlay()->getTextField("animationId")->setVisible(false);
			_gui->getOverlay()->getTextField("animationFrame")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				_fe3d->model_setVisible(_previewModelId, false);
			}

			auto modelIds = _modelEditor->getLoadedEntityIds();

			for(auto & id : modelIds)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("selectModel", "Select Model", fvec2(-0.5f, 0.1f), modelIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
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
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->model_stopAnimation(_previewModelId, _currentAnimationId);

			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
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
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_currentFrameIndex++;

			_fe3d->animation3d_createFrame(_currentAnimationId, _currentFrameIndex);

			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
			{
				const auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto speed = _fe3d->animation3d_getSpeed(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimationId, (_currentFrameIndex - 1), partId);
				const auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimationId, (_currentFrameIndex - 1), partId);

				_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, partId, targetTransformation);
				_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, partId, rotationOrigin);
				_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, partId, speed);
				_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, partId, SpeedType(speedType));
				_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, partId, TransformationType(transformationType));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuFrame");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->animation3d_deleteFrame(_currentAnimationId, _currentFrameIndex);

			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("prev")->isHovered())
		{
			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("next")->isHovered())
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
			_gui->getOverlay()->getTextField("animationFrame")->setTextContent("Frame: " + to_string(_currentFrameIndex + 1));
		}
	}
}