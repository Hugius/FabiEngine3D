#include "animation3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void Animation3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "animation3dEditorMenuMain")
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
			_gui->getOverlay()->createChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), getAnimationIDs());
			_isChoosingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), getAnimationIDs());
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

	if(screen->getID() == "animation3dEditorMenuChoice")
	{
		auto currentAnimation = _getAnimation(_currentAnimationID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(isModelAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				stopModelAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());
			}

			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelID()))
			{
				for(const auto& partID : currentAnimation->getPartIDs())
				{
					_fe3d->model_setVisible(currentAnimation->getPreviewModelID(), false);

					if(partID.empty())
					{
						_fe3d->model_setBasePosition(currentAnimation->getPreviewModelID(), fvec3(0.0f));
						_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), fvec3(0.0f));
						_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelID(), fvec3(0.0f));
						_fe3d->model_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
					}
					else
					{
						_fe3d->model_setPartPosition(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
						_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
						_fe3d->model_setPartRotation(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
						_fe3d->model_setPartSize(currentAnimation->getPreviewModelID(), partID, fvec3(1.0f));
					}
				}
			}

			_currentAnimationID = "";
			_currentFrameIndex = 0;
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationID")->getEntityID(), false);
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityID(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			auto modelIDs = _modelEditor->getLoadedIDs();
			for(auto& ID : modelIDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Select Model", fvec2(-0.5f, 0.1f), modelIDs);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			for(const auto& partID : currentAnimation->getPartIDs())
			{
				if(partID.empty())
				{
					_fe3d->model_setBasePosition(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
				}
				else
				{
					_fe3d->model_setPartPosition(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartRotation(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartSize(currentAnimation->getPreviewModelID(), partID, fvec3(1.0f));
				}
			}

			startModelAnimation(_currentAnimationID, currentAnimation->getPreviewModelID(), 0);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			stopModelAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());

			_fe3d->model_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
			for(const auto& partID : currentAnimation->getPartIDs())
			{
				if(partID.empty())
				{
					_fe3d->model_setBasePosition(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelID(), fvec3(0.0f));
					_fe3d->model_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
				}
				else
				{
					_fe3d->model_setPartPosition(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartRotation(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
					_fe3d->model_setPartSize(currentAnimation->getPreviewModelID(), partID, fvec3(1.0f));
				}
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			auto lastFrameCopy = currentAnimation->getFrames()[_currentFrameIndex];

			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelID()) &&
			   _fe3d->model_isMultiParted(currentAnimation->getPreviewModelID()))
			{
				if(currentAnimation->getFrames().size() == 1)
				{
					lastFrameCopy.deleteParts();

					for(const auto& partID : currentAnimation->getPartIDs())
					{
						lastFrameCopy.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
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
			if(isModelAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				stopModelAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());
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

		auto hasPreviewModel = _fe3d->model_isExisting(currentAnimation->getPreviewModelID());
		auto isStarted = isModelAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID());
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
			_fe3d->text_setContent(_gui->getOverlay()->getTextField("animationFrame")->getEntityID(), "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);
		}

		if(_fe3d->model_isExisting(currentAnimation->getPreviewModelID()))
		{
			_fe3d->model_setVisible(currentAnimation->getPreviewModelID(), !_gui->getOverlay()->isChoiceFormExisting("modelList"));
		}

		if(!_hoveredModelID.empty())
		{
			_fe3d->model_setVisible(_hoveredModelID, false);
		}

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("modelList");

		if(!selectedButtonID.empty())
		{
			_hoveredModelID = ("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				bool hasAllParts = true;
				for(const auto& partID : currentAnimation->getPartIDs())
				{
					if(!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d->model_hasPart(_hoveredModelID, partID);
					}
				}

				if(!hasAllParts)
				{
					Logger::throwWarning("Preview model does not have required animation parts!");
					return;
				}

				currentAnimation->setPreviewModelID(_hoveredModelID);
				currentAnimation->setInitialSize(_fe3d->model_getBaseSize(_hoveredModelID));

				if(currentAnimation->getFrames().empty())
				{
					Animation3dFrame defaultFrame;

					currentAnimation->addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
					defaultFrame.addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);

					auto partIDs = _fe3d->model_getPartIDs(_hoveredModelID);
					if(partIDs.size() > 1)
					{
						for(const auto& partID : partIDs)
						{
							currentAnimation->addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));

							defaultFrame.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
						}
					}

					currentAnimation->addFrame(defaultFrame);
				}

				_gui->getOverlay()->deleteChoiceForm("modelList");
				_hoveredModelID = "";
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("modelList"))
		{
			_gui->getOverlay()->deleteChoiceForm("modelList");
		}
		else
		{
			_hoveredModelID = "";
		}

		if(!_hoveredModelID.empty())
		{
			_fe3d->model_setVisible(_hoveredModelID, true);
		}
	}
}