#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
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

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->graphics_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->graphics_setShadowLookatOffset(cameraLookat);
		_fe3d->graphics_setShadowSize(distance * 2.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void Animation3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}
	}

	if(!_currentAnimationId.empty())
	{
		if(_mustUpdateCurrentFramePreview)
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				if(!_fe3d->model_isAnimationStarted(_previewModelId, _currentAnimationId))
				{
					if(_fe3d->model_isExisting(_previewModelId))
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

						if(_currentFrameIndex > 0)
						{
							for(unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
							{
								for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
								{
									if(_fe3d->model_hasPart(_previewModelId, partId) || partId.empty())
									{
										if(_fe3d->animation3d_getTransformationType(_currentAnimationId, frameIndex, partId) == TransformationType::MOVEMENT)
										{
											auto newPosition = (_initialModelSize * _fe3d->animation3d_getTargetTransformation(_currentAnimationId, frameIndex, partId));
											if(partId.empty())
											{
												_fe3d->model_setBasePosition(_previewModelId, newPosition);
											}
											else
											{
												_fe3d->model_setPartPosition(_previewModelId, partId, newPosition);
											}
										}
										else if(_fe3d->animation3d_getTransformationType(_currentAnimationId, frameIndex, partId) == TransformationType::ROTATION)
										{
											auto currentModelSize = _fe3d->model_getBaseSize(_previewModelId);
											auto newOrigin = (currentModelSize * _fe3d->animation3d_getRotationOrigin(_currentAnimationId, frameIndex, partId));
											if(partId.empty())
											{
												_fe3d->model_setBaseRotationOrigin(_previewModelId, newOrigin);
											}
											else
											{
												_fe3d->model_setPartRotationOrigin(_previewModelId, partId, newOrigin);
											}

											auto newRotation = _fe3d->animation3d_getTargetTransformation(_currentAnimationId, frameIndex, partId);
											if(partId.empty())
											{
												_fe3d->model_setBaseRotation(_previewModelId, newRotation);
											}
											else
											{
												_fe3d->model_setPartRotation(_previewModelId, partId, newRotation);
											}
										}
										else if(_fe3d->animation3d_getTransformationType(_currentAnimationId, frameIndex, partId) == TransformationType::SCALING)
										{
											auto modelSize = (partId.empty() ? _initialModelSize : fvec3(1.0f));
											auto newSize = (modelSize + (modelSize * _fe3d->animation3d_getTargetTransformation(_currentAnimationId, frameIndex, partId)));
											if(partId.empty())
											{
												_fe3d->model_setBaseSize(_previewModelId, newSize);
											}
											else
											{
												_fe3d->model_setPartSize(_previewModelId, partId, newSize);
											}
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
			const auto opacity = _fe3d->model_getOpacity(_previewModelId, partId);

			if(opacity == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			if(opacity == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d->model_setOpacity(_previewModelId, partId, (opacity + speed));
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
			if(any_of(newAnimationId.begin(), newAnimationId.end(), isspace))
			{
				Logger::throwWarning("Animation ID cannot contain any spaces");
				return;
			}

			if(!all_of(newAnimationId.begin(), newAnimationId.end(), isalnum))
			{
				Logger::throwWarning("Animation ID cannot contain any specials");
				return;
			}

			if(any_of(newAnimationId.begin(), newAnimationId.end(), isupper))
			{
				Logger::throwWarning("Animation ID cannot contain any capitals");
				return;
			}

			newAnimationId = ("@" + newAnimationId);

			if(find(_loadedAnimationIds.begin(), _loadedAnimationIds.end(), newAnimationId) != _loadedAnimationIds.end())
			{
				Logger::throwWarning("Animation already exists");
				return;
			}

			_currentAnimationId = newAnimationId;
			_loadedAnimationIds.push_back(newAnimationId);
			sort(_loadedAnimationIds.begin(), _loadedAnimationIds.end());

			_fe3d->animation3d_create(newAnimationId);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
			_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + newAnimationId);
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
				_currentAnimationId = ("@" + selectedButtonId);

				if(!_isDeletingAnimation)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + _currentAnimationId.substr(1));
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
			_fe3d->animation3d_delete(_currentAnimationId);

			_loadedAnimationIds.erase(remove(_loadedAnimationIds.begin(), _loadedAnimationIds.end(), _currentAnimationId), _loadedAnimationIds.end());
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
				for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimationId))
				{
					if(!partId.empty())
					{
						hasAllParts = (hasAllParts && _fe3d->model_hasPart(_hoveredModelId, partId));
					}
				}

				if(!hasAllParts)
				{
					Logger::throwWarning("Preview model does not have the required animation parts");
					return;
				}

				_previewModelId = _hoveredModelId;
				_initialModelSize = _fe3d->model_getBaseSize(_previewModelId);

				if(_fe3d->animation3d_getFrameCount(_currentAnimationId) == 0)
				{
					_fe3d->animation3d_createPart(_currentAnimationId, "");

					for(const auto & partId : _fe3d->model_getPartIds(_previewModelId))
					{
						_fe3d->animation3d_createPart(_currentAnimationId, partId);
					}

					_fe3d->animation3d_createFrame(_currentAnimationId, 0);
				}

				_gui->getOverlay()->deleteChoiceForm("modelList");
				_hoveredModelId = "";
				_isChoosingModel = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("modelList"))
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				_fe3d->model_setVisible(_previewModelId, true);
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
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("partList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredPartId.empty())
			{
				_hoveredPartId = selectedButtonId;
				_originalPartOpacity = _fe3d->model_getOpacity(_previewModelId, _hoveredPartId);
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
				_fe3d->model_setOpacity(_previewModelId, _hoveredPartId, _originalPartOpacity);
				_hoveredPartId = "";
			}
		}
	}
}