#include "animation3d_editor.hpp"

#include <algorithm>

void Animation3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAnimation3d", "Create Animation3D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedAnimation3dIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editAnimation3d", "Edit Animation3D", fvec2(0.0f, 0.1f), ids);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedAnimation3dIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteAnimation3d", "Delete Animation3D", fvec2(0.0f, 0.1f), ids);
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
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				if(_fe3d->model_isAnimationStarted(_previewModelId, _currentAnimation3dId))
				{
					_fe3d->model_stopAnimation(_previewModelId, _currentAnimation3dId);
				}

				for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
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
			_currentAnimation3dId = "";
			_initialModelSize = fvec3(0.0f);
			_currentFrameIndex = 0;
			_gui->getOverlay()->getTextField("animation3dId")->setVisible(false);
			_gui->getOverlay()->getTextField("animation3dFrame")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("preview")->isHovered())
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
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
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

			_fe3d->model_startAnimation(_previewModelId, _currentAnimation3dId, 1);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->model_stopAnimation(_previewModelId, _currentAnimation3dId);

			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
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
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_currentFrameIndex++;

			_fe3d->animation3d_createFrame(_currentAnimation3dId, _currentFrameIndex);

			for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
			{
				const auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimation3dId, (_currentFrameIndex - 1), partId);
				const auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimation3dId, (_currentFrameIndex - 1), partId);
				const auto speed = _fe3d->animation3d_getSpeed(_currentAnimation3dId, (_currentFrameIndex - 1), partId);
				const auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimation3dId, (_currentFrameIndex - 1), partId);
				const auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimation3dId, (_currentFrameIndex - 1), partId);

				_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, partId, targetTransformation);
				_fe3d->animation3d_setRotationOrigin(_currentAnimation3dId, _currentFrameIndex, partId, rotationOrigin);
				_fe3d->animation3d_setSpeed(_currentAnimation3dId, _currentFrameIndex, partId, speed);
				_fe3d->animation3d_setSpeedType(_currentAnimation3dId, _currentFrameIndex, partId, SpeedType(speedType));
				_fe3d->animation3d_setTransformationType(_currentAnimation3dId, _currentFrameIndex, partId, TransformationType(transformationType));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuFrame");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->animation3d_deleteFrame(_currentAnimation3dId, _currentFrameIndex);

			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("prev")->isHovered())
		{
			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("next")->isHovered())
		{
			_currentFrameIndex++;
		}

		auto isStarted = (!_previewModelId.empty() && _fe3d->model_isAnimationStarted(_previewModelId, _currentAnimation3dId));

		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("start")->setHoverable(!isStarted && !_previewModelId.empty() && (_fe3d->animation3d_getFrameCount(_currentAnimation3dId) > 1));
		screen->getButton("stop")->setHoverable(isStarted && !_previewModelId.empty());
		screen->getButton("create")->setHoverable((_fe3d->animation3d_getFrameCount(_currentAnimation3dId) < MAX_FRAME_COUNT) && !isStarted && !_previewModelId.empty());
		screen->getButton("edit")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("delete")->setHoverable((_fe3d->animation3d_getFrameCount(_currentAnimation3dId) > 1) && (_currentFrameIndex > 0) && !isStarted && !_previewModelId.empty());
		screen->getButton("prev")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("next")->setHoverable((_currentFrameIndex < (_fe3d->animation3d_getFrameCount(_currentAnimation3dId) - 1)) && !isStarted && !_previewModelId.empty());

		if(!isStarted)
		{
			_gui->getOverlay()->getTextField("animation3dFrame")->setTextContent("Frame: " + to_string(_currentFrameIndex + 1));
		}
	}
}