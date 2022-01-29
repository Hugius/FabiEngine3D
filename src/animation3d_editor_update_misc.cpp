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

		_fe3d->quad2d_setVisible("@@cursor", false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->gfx_setShadowEyeOffset(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d->gfx_setShadowCenterOffset(cameraLookat);
		_fe3d->gfx_setShadowSize(distance * 4.0f);
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

	if(!_currentAnimationId.empty())
	{
		auto currentAnimation = _getAnimation(_currentAnimationId);

		if(_mustUpdateCurrentFramePreview)
		{
			if(!isModelAnimationStarted(_currentAnimationId, currentAnimation->getPreviewModelId()))
			{
				if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()))
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

					if(_currentFrameIndex > 0)
					{
						for(unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
						{
							auto frame = currentAnimation->getFrames()[frameIndex];

							for(const auto& partId : currentAnimation->getPartIds())
							{
								if(_fe3d->model_hasPart(currentAnimation->getPreviewModelId(), partId) || partId.empty())
								{
									if(frame.getTransformationTypes().at(partId) == TransformationType::MOVEMENT)
									{
										auto newPosition = (currentAnimation->getInitialSize() * frame.getTargetTransformations().at(partId));
										if(partId.empty())
										{
											_fe3d->model_setBasePosition(currentAnimation->getPreviewModelId(), newPosition);
										}
										else
										{
											_fe3d->model_setPartPosition(currentAnimation->getPreviewModelId(), partId, newPosition);
										}
									}
									else if(frame.getTransformationTypes().at(partId) == TransformationType::ROTATION)
									{
										auto currentModelSize = _fe3d->model_getBaseSize(currentAnimation->getPreviewModelId());
										auto newOrigin = (currentModelSize * frame.getRotationOrigins().at(partId));
										if(partId.empty())
										{
											_fe3d->model_setBaseRotationOrigin(currentAnimation->getPreviewModelId(), newOrigin);
										}
										else
										{
											_fe3d->model_setPartRotationOrigin(currentAnimation->getPreviewModelId(), partId, newOrigin);
										}

										auto newRotation = frame.getTargetTransformations().at(partId);
										if(partId.empty())
										{
											_fe3d->model_setBaseRotation(currentAnimation->getPreviewModelId(), newRotation);
										}
										else
										{
											_fe3d->model_setPartRotation(currentAnimation->getPreviewModelId(), partId, newRotation);
										}
									}
									else if(frame.getTransformationTypes().at(partId) == TransformationType::SCALING)
									{
										auto modelSize = (partId.empty() ? currentAnimation->getInitialSize() : fvec3(1.0f));
										auto newSize = (modelSize + (modelSize * frame.getTargetTransformations().at(partId)));
										if(partId.empty())
										{
											_fe3d->model_setBaseSize(currentAnimation->getPreviewModelId(), newSize);
										}
										else
										{
											_fe3d->model_setPartSize(currentAnimation->getPreviewModelId(), partId, newSize);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		auto partId = (_hoveredPartId.empty() ? _currentPartId : _hoveredPartId);
		if(partId.empty())
		{
			_selectedPartHighlightDirection = 1;
		}
		else
		{
			const auto opacity = _fe3d->model_getOpacity(currentAnimation->getPreviewModelId(), partId);

			if(opacity == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			if(opacity == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d->model_setOpacity(currentAnimation->getPreviewModelId(), partId, (opacity + speed));
		}
	}
}

void Animation3dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		string newAnimationId;

		if(_gui->getOverlay()->checkValueForm("animationCreate", newAnimationId, {_currentAnimationId}))
		{
			if(newAnimationId.find(' ') != string::npos)
			{
				Logger::throwWarning("Animation id cannot contain any spaces!");
				return;
			}

			if(newAnimationId.find('@') != string::npos)
			{
				Logger::throwWarning("Animation id cannot contain '@'!");
				return;
			}

			auto animationIds = getAnimationIds();
			if(find(animationIds.begin(), animationIds.end(), newAnimationId) != animationIds.end())
			{
				Logger::throwWarning("Animation id \"" + newAnimationId + "\" already exists!");
				return;
			}

			_animations.push_back(make_shared<Animation3d>(newAnimationId));

			_currentAnimationId = newAnimationId;

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
			_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationId")->getEntityId(), "Animation: " + newAnimationId, 0.025f);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), true);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityId(), true);
			_isCreatingAnimation = false;
		}
	}
}

void Animation3dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("animationList");

		if(!selectedButtonId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAnimationId = selectedButtonId;

				if(!_isDeletingAnimation)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

					if(_fe3d->model_isExisting(_getAnimation(selectedButtonId)->getPreviewModelId()))
					{
						_fe3d->model_setVisible(_getAnimation(selectedButtonId)->getPreviewModelId(), true);
					}

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationId")->getEntityId(), "Animation: " + selectedButtonId, 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), true);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationFrame")->getEntityId(), true);
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
	if(_isDeletingAnimation && !_currentAnimationId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			if(!_getAnimation(_currentAnimationId)->getPreviewModelId().empty())
			{
				_fe3d->model_setVisible(_getAnimation(_currentAnimationId)->getPreviewModelId(), false);
			}

			_deleteAnimation(_currentAnimationId);

			_currentAnimationId = "";
			_isDeletingAnimation = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentAnimationId = "";
			_isDeletingAnimation = false;
		}
	}
}

void Animation3dEditor::_updateModelChoosing()
{
	if(_isChoosingModel)
	{
		auto currentAnimation = _getAnimation(_currentAnimationId);
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
				currentAnimation->setInitialSize(_fe3d->model_getBaseSize(currentAnimation->getPreviewModelId()));

				if(currentAnimation->getFrames().empty())
				{
					Animation3dFrame defaultFrame;

					currentAnimation->addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
					defaultFrame.addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);

					auto partIds = _fe3d->model_getPartIds(currentAnimation->getPreviewModelId());
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
				_isChoosingModel = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("modelList"))
		{
			if(_fe3d->model_isExisting(currentAnimation->getPreviewModelId()))
			{
				_fe3d->model_setVisible(currentAnimation->getPreviewModelId(), true);
			}

			_gui->getOverlay()->deleteChoiceForm("modelList");
			_isChoosingModel = false;
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

void Animation3dEditor::_updatePartChoosing()
{
	if(_isChoosingPart)
	{
		auto currentAnimation = _getAnimation(_currentAnimationId);
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("partList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredPartId.empty())
			{
				_hoveredPartId = selectedButtonId;
				_originalPartOpacity = _fe3d->model_getOpacity(currentAnimation->getPreviewModelId(), _hoveredPartId);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentPartId = _hoveredPartId;
				_hoveredPartId = "";
				_gui->getOverlay()->deleteChoiceForm("partList");
				_isChoosingPart = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("partList"))
		{
			_gui->getOverlay()->deleteChoiceForm("partList");
			_isChoosingPart = false;
		}
		else
		{
			if(!_hoveredPartId.empty())
			{
				_fe3d->model_setOpacity(currentAnimation->getPreviewModelId(), _hoveredPartId, _originalPartOpacity);
				_hoveredPartId = "";
			}
		}
	}
}