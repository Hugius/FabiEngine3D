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
			_gui->getOverlay()->createChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), getAnimationIds());
			_isChoosingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), getAnimationIds());
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
		auto currentAnimation = _getAnimation(_currentAnimationId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(isModelAnimationStarted(_currentAnimationId, currentAnimation->getPreviewModelId()))
			{
				stopModelAnimation(_currentAnimationId, currentAnimation->getPreviewModelId());
			}

			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()))
			{
				for(const auto& partId : currentAnimation->getPartIds())
				{
					_fe3d->model_setVisible(currentAnimation->getPreviewModelId(), false);

					if(partId.empty())
					{
						_fe3d->model_setBasePosition(currentAnimation->getPreviewModelId(), fvec3(0.0f));
						_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelId(), fvec3(0.0f));
						_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelId(), fvec3(0.0f));
						_fe3d->model_setBaseSize(currentAnimation->getPreviewModelId(), currentAnimation->getInitialSize());
					}
					else
					{
						_fe3d->model_setPartPosition(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
						_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
						_fe3d->model_setPartRotation(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
						_fe3d->model_setPartSize(currentAnimation->getPreviewModelId(), partId, fvec3(1.0f));
					}
				}
			}

			_currentAnimationId = "";
			_currentFrameIndex = 0;
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), false);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityId(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()))
			{
				_fe3d->model_setVisible(currentAnimation->getPreviewModelId(), false);
			}

			auto modelIds = _modelEditor->getLoadedIds();
			for(auto& id : modelIds)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Select Model", fvec2(-0.5f, 0.1f), modelIds);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			for(const auto& partId : currentAnimation->getPartIds())
			{
				if(partId.empty())
				{
					_fe3d->model_setBasePosition(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseSize(currentAnimation->getPreviewModelId(), currentAnimation->getInitialSize());
				}
				else
				{
					_fe3d->model_setPartPosition(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartRotation(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartSize(currentAnimation->getPreviewModelId(), partId, fvec3(1.0f));
				}
			}

			startModelAnimation(_currentAnimationId, currentAnimation->getPreviewModelId(), 0);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			stopModelAnimation(_currentAnimationId, currentAnimation->getPreviewModelId());

			_fe3d->model_setBaseSize(currentAnimation->getPreviewModelId(), currentAnimation->getInitialSize());
			for(const auto& partId : currentAnimation->getPartIds())
			{
				if(partId.empty())
				{
					_fe3d->model_setBasePosition(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelId(), fvec3(0.0f));
					_fe3d->model_setBaseSize(currentAnimation->getPreviewModelId(), currentAnimation->getInitialSize());
				}
				else
				{
					_fe3d->model_setPartPosition(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartRotation(currentAnimation->getPreviewModelId(), partId, fvec3(0.0f));
					_fe3d->model_setPartSize(currentAnimation->getPreviewModelId(), partId, fvec3(1.0f));
				}
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			auto lastFrameCopy = currentAnimation->getFrames()[_currentFrameIndex];

			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()) &&
			   _fe3d->model_isMultiParted(currentAnimation->getPreviewModelId()))
			{
				if(currentAnimation->getFrames().size() == 1)
				{
					lastFrameCopy.deleteParts();

					for(const auto& partId : currentAnimation->getPartIds())
					{
						lastFrameCopy.addPart(partId, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
					}
				}
			}

			auto frames = currentAnimation->getFrames();
			frames.insert((frames.begin() + _currentFrameIndex), lastFrameCopy);
			currentAnimation->setFrames(frames);
			_currentFrameIndex++;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			if(isModelAnimationStarted(_currentAnimationId, currentAnimation->getPreviewModelId()))
			{
				stopModelAnimation(_currentAnimationId, currentAnimation->getPreviewModelId());
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuFrame");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto frames = currentAnimation->getFrames();
			frames.erase(frames.begin() + _currentFrameIndex);
			currentAnimation->setFrames(frames);

			if(_currentFrameIndex == currentAnimation->getFrames().size())
			{
				_currentFrameIndex--;
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("prev")->isHovered())
		{
			_currentFrameIndex--;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("next")->isHovered())
		{
			_currentFrameIndex++;
		}

		auto hasPreviewModel = _fe3d->model_isExisting(currentAnimation->getPreviewModelId());
		auto isStarted = isModelAnimationStarted(_currentAnimationId, currentAnimation->getPreviewModelId());
		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("start")->setHoverable(!isStarted && hasPreviewModel && (currentAnimation->getFrames().size() > 1));
		screen->getButton("stop")->setHoverable(isStarted && hasPreviewModel);
		screen->getButton("create")->setHoverable((currentAnimation->getFrames().size() < MAX_FRAME_COUNT) && !isStarted && hasPreviewModel);
		screen->getButton("edit")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("delete")->setHoverable((currentAnimation->getFrames().size() > 1) && (_currentFrameIndex > 0) && !isStarted && hasPreviewModel);
		screen->getButton("prev")->setHoverable((_currentFrameIndex > 0) && !isStarted);
		screen->getButton("next")->setHoverable((_currentFrameIndex < (currentAnimation->getFrames().size() - 1)) && !isStarted && hasPreviewModel);

		if(!isStarted)
		{
			_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationFrame")->getEntityId(), "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);
		}

		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("modelList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredModelId.empty())
			{
				_hoveredModelId = ("@" + selectedButtonId);
				_fe3d->model_setVisible(_hoveredModelId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				bool hasAllParts = true;
				for(const auto& partId : currentAnimation->getPartIds())
				{
					if(!partId.empty())
					{
						hasAllParts = hasAllParts && _fe3d->model_hasPart(_hoveredModelId, partId);
					}
				}

				if(!hasAllParts)
				{
					Logger::throwWarning("Preview model does not have required animation parts!");
					return;
				}

				currentAnimation->setPreviewModelId(_hoveredModelId);
				currentAnimation->setInitialSize(_fe3d->model_getBaseSize(_hoveredModelId));

				if(currentAnimation->getFrames().empty())
				{
					Animation3dFrame defaultFrame;

					currentAnimation->addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
					defaultFrame.addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);

					auto partIds = _fe3d->model_getPartIds(_hoveredModelId);
					if(partIds.size() > 1)
					{
						for(const auto& partId : partIds)
						{
							currentAnimation->addPart(partId, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));

							defaultFrame.addPart(partId, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
						}
					}

					currentAnimation->addFrame(defaultFrame);
				}

				_gui->getOverlay()->deleteChoiceForm("modelList");
				_hoveredModelId = "";
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("modelList"))
		{
			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()))
			{
				_fe3d->model_setVisible(currentAnimation->getPreviewModelId(), true);
			}

			_gui->getOverlay()->deleteChoiceForm("modelList");
		}
		else
		{
			if(!_hoveredModelId.empty())
			{
				_fe3d->model_setVisible(_hoveredModelId, false);
				_hoveredModelId = "";
			}
		}
	}
}