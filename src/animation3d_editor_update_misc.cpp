#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Animation3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));
		const auto lookatOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(-GRID_Y_OFFSET, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
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
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
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
							for(int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
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
	if((_gui->getOverlay()->getValueFormId() == "createAnimation") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newAnimationId = _gui->getOverlay()->getValueFormContent();

		if(newAnimationId.empty())
		{
			Logger::throwWarning("Animation ID cannot be empty");

			return;
		}

		if(any_of(newAnimationId.begin(), newAnimationId.end(), isspace))
		{
			Logger::throwWarning("Animation ID cannot contain any spaces");

			return;
		}

		if(any_of(newAnimationId.begin(), newAnimationId.end(), isupper))
		{
			Logger::throwWarning("Animation ID cannot contain any capitals");

			return;
		}

		newAnimationId = ("@" + newAnimationId);

		if(find(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end(), newAnimationId) != _loadedAnimation3dIds.end())
		{
			Logger::throwWarning("Animation already exists");

			return;
		}

		_currentAnimationId = newAnimationId;
		_loadedAnimation3dIds.push_back(newAnimationId);
		sort(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end());

		_fe3d->animation3d_create(newAnimationId);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
		_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + newAnimationId);
		_gui->getOverlay()->getTextField("animationId")->setVisible(true);
		_gui->getOverlay()->getTextField("animationFrame")->setVisible(true);
	}
}

void Animation3dEditor::_updateAnimationChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAnimation") || (_gui->getOverlay()->getChoiceFormId() == "deleteAnimation"))
	{
		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentAnimationId = ("@" + _gui->getOverlay()->getChoiceFormOptionId());

			if(_gui->getOverlay()->getChoiceFormId() == "deleteAnimation")
			{
				_gui->getOverlay()->openAnswerForm("deleteAnimation", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
			}
			else
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

				_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + _currentAnimationId.substr(1));
				_gui->getOverlay()->getTextField("animationId")->setVisible(true);
				_gui->getOverlay()->getTextField("animationFrame")->setVisible(true);
			}
		}
	}
}

void Animation3dEditor::_updateAnimationDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAnimation") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->animation3d_delete(_currentAnimationId);

			_loadedAnimation3dIds.erase(remove(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end(), _currentAnimationId), _loadedAnimation3dIds.end());
			_currentAnimationId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAnimationId = "";
		}
	}
}

void Animation3dEditor::_updateModelChoosing()
{
	if(_gui->getOverlay()->getChoiceFormId() == "selectModel")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredModelId.empty())
			{
				_fe3d->model_setVisible(_hoveredModelId, false);

				_hoveredModelId = "";
			}
		}
		else
		{
			if(_hoveredModelId.empty())
			{
				_hoveredModelId = ("@" + selectedOptionId);

				_fe3d->model_setVisible(_hoveredModelId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
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

				_hoveredModelId = "";
			}
		}
	}
}

void Animation3dEditor::_updatePartChoosing()
{
	if(_gui->getOverlay()->getChoiceFormId() == "selectPart")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredPartId.empty())
			{
				_fe3d->model_setOpacity(_previewModelId, _hoveredPartId, _originalPartOpacity);

				_hoveredPartId = "";
			}
		}
		else
		{
			if(_hoveredPartId.empty())
			{
				_hoveredPartId = selectedOptionId;
				_originalPartOpacity = _fe3d->model_getOpacity(_previewModelId, _hoveredPartId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentPartId = _hoveredPartId;
				_hoveredPartId = "";
			}
		}
	}
}