#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad_setVisible("@@cursor", false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->gfx_setShadowEyePosition(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d->gfx_setShadowCenterPosition(cameraLookat);
		_fe3d->gfx_setShadowSize(distance * 4.0f);
		_fe3d->gfx_setShadowReach(distance * 8.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->camera_isThirdPersonViewEnabled())
			{
				_fe3d->camera_disableThirdPersonView();
			}
			else
			{
				_fe3d->camera_enableThirdPersonView(_fe3d->camera_getThirdPersonYaw(), _fe3d->camera_getThirdPersonPitch());
			}
		}
	}

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		if(_gui->getOverlay()->isFocused())
		{
			_fe3d->camera_disableThirdPersonView();
		}
	}
}

void Animation3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d->model_isVisible("@@box"))
			{
				_fe3d->model_setVisible("@@box", false);
			}
			else
			{
				_fe3d->model_setVisible("@@box", true);
			}
		}
	}

	if(!_currentAnimationID.empty())
	{
		auto currentAnimation = _getAnimation(_currentAnimationID);

		if(_mustUpdateCurrentFramePreview)
		{
			if(!isModelAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				if(_fe3d->model_isExisting(currentAnimation->getPreviewModelID()))
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

					if(_currentFrameIndex > 0)
					{
						for(unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
						{
							auto frame = currentAnimation->getFrames()[frameIndex];

							for(const auto& partID : currentAnimation->getPartIDs())
							{
								if(_fe3d->model_hasPart(currentAnimation->getPreviewModelID(), partID) || partID.empty())
								{
									if(frame.getTransformationTypes().at(partID) == TransformationType::MOVEMENT)
									{
										auto newPosition = (currentAnimation->getInitialSize() * frame.getTargetTransformations().at(partID));
										if(partID.empty())
										{
											_fe3d->model_setBasePosition(currentAnimation->getPreviewModelID(), newPosition);
										}
										else
										{
											_fe3d->model_setPartPosition(currentAnimation->getPreviewModelID(), partID, newPosition);
										}
									}
									else if(frame.getTransformationTypes().at(partID) == TransformationType::ROTATION)
									{
										auto currentModelSize = _fe3d->model_getBaseSize(currentAnimation->getPreviewModelID());
										auto newOrigin = (currentModelSize * frame.getRotationOrigins().at(partID));
										if(partID.empty())
										{
											_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), newOrigin);
										}
										else
										{
											_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, newOrigin);
										}

										auto newRotation = frame.getTargetTransformations().at(partID);
										if(partID.empty())
										{
											_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelID(), newRotation);
										}
										else
										{
											_fe3d->model_setPartRotation(currentAnimation->getPreviewModelID(), partID, newRotation);
										}
									}
									else if(frame.getTransformationTypes().at(partID) == TransformationType::SCALING)
									{
										auto modelSize = (partID.empty() ? currentAnimation->getInitialSize() : fvec3(1.0f));
										auto newSize = (modelSize + (modelSize * frame.getTargetTransformations().at(partID)));
										if(partID.empty())
										{
											_fe3d->model_setBaseSize(currentAnimation->getPreviewModelID(), newSize);
										}
										else
										{
											_fe3d->model_setPartSize(currentAnimation->getPreviewModelID(), partID, newSize);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		auto partID = (_hoveredPartID.empty() ? _currentPartID : _hoveredPartID);
		if(partID.empty())
		{
			_selectedPartHighlightDirection = 1;
		}
		else
		{
			const auto transparency = _fe3d->model_getTransparency(currentAnimation->getPreviewModelID(), partID);

			if(transparency == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			if(transparency == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d->model_setTransparency(currentAnimation->getPreviewModelID(), partID, (transparency + speed));
		}
	}
}

void Animation3dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		string newAnimationID;

		if(_gui->getOverlay()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			if(newAnimationID.find(' ') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain any spaces!");
				return;
			}

			if(newAnimationID.find('@') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain '@'!");
				return;
			}

			auto animationIDs = getAnimationIDs();
			if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) != animationIDs.end())
			{
				Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
				return;
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

			_animations.push_back(make_shared<Animation3d>(newAnimationID));

			_currentAnimationID = newAnimationID;

			_fe3d->text_setContent(_gui->getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationID")->getEntityID(), true);
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityID(), true);
			_isCreatingAnimation = false;
		}
	}
}

void Animation3dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("animationList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAnimationID = selectedButtonID;

				if(!_isDeletingAnimation)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

					if(_fe3d->model_isExisting(_getAnimation(selectedButtonID)->getPreviewModelID()))
					{
						_fe3d->model_setVisible(_getAnimation(selectedButtonID)->getPreviewModelID(), true);
					}

					_fe3d->text_setContent(_gui->getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationID")->getEntityID(), true);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityID(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
		{
			_gui->getOverlay()->deleteChoiceForm("animationList");
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
		}
	}
}

void Animation3dEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && !_currentAnimationID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			if(!_getAnimation(_currentAnimationID)->getPreviewModelID().empty())
			{
				_fe3d->model_setVisible(_getAnimation(_currentAnimationID)->getPreviewModelID(), false);
			}

			_deleteAnimation(_currentAnimationID);

			_currentAnimationID = "";
			_isDeletingAnimation = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentAnimationID = "";
			_isDeletingAnimation = false;
		}
	}
}