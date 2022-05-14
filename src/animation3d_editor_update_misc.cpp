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
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(0.0f, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
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
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_fe3d->model_setVisible("@@grid", !_fe3d->model_isVisible("@@grid"));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}
	}

	if(!_currentAnimation3dId.empty())
	{
		if(_mustUpdateCurrentFramePreview)
		{
			if(_fe3d->model_isExisting(_previewModelId))
			{
				if(!_fe3d->model_isAnimationStarted(_previewModelId, _currentAnimation3dId))
				{
					if(_fe3d->model_isExisting(_previewModelId))
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

						if(_currentFrameIndex > 0)
						{
							for(int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
							{
								for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
								{
									if(_fe3d->model_hasPart(_previewModelId, partId) || partId.empty())
									{
										if(_fe3d->animation3d_getTransformationType(_currentAnimation3dId, frameIndex, partId) == TransformationType::MOVEMENT)
										{
											auto newPosition = (_initialModelSize * _fe3d->animation3d_getTargetTransformation(_currentAnimation3dId, frameIndex, partId));
											if(partId.empty())
											{
												_fe3d->model_setBasePosition(_previewModelId, newPosition);
											}
											else
											{
												_fe3d->model_setPartPosition(_previewModelId, partId, newPosition);
											}
										}
										else if(_fe3d->animation3d_getTransformationType(_currentAnimation3dId, frameIndex, partId) == TransformationType::ROTATION)
										{
											auto currentModelSize = _fe3d->model_getBaseSize(_previewModelId);
											auto newOrigin = (currentModelSize * _fe3d->animation3d_getRotationOrigin(_currentAnimation3dId, frameIndex, partId));
											if(partId.empty())
											{
												_fe3d->model_setBaseRotationOrigin(_previewModelId, newOrigin);
											}
											else
											{
												_fe3d->model_setPartRotationOrigin(_previewModelId, partId, newOrigin);
											}

											auto newRotation = _fe3d->animation3d_getTargetTransformation(_currentAnimation3dId, frameIndex, partId);
											if(partId.empty())
											{
												_fe3d->model_setBaseRotation(_previewModelId, newRotation);
											}
											else
											{
												_fe3d->model_setPartRotation(_previewModelId, partId, newRotation);
											}
										}
										else if(_fe3d->animation3d_getTransformationType(_currentAnimation3dId, frameIndex, partId) == TransformationType::SCALING)
										{
											auto modelSize = (partId.empty() ? _initialModelSize : fvec3(1.0f));
											auto newSize = (modelSize + (modelSize * _fe3d->animation3d_getTargetTransformation(_currentAnimation3dId, frameIndex, partId)));
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

void Animation3dEditor::_updateAnimation3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createAnimation3d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newAnimation3dId = _gui->getOverlay()->getValueFormContent();

		if(newAnimation3dId.empty())
		{
			Logger::throwWarning("Animation3D ID cannot be empty");

			return;
		}

		if(any_of(newAnimation3dId.begin(), newAnimation3dId.end(), isspace))
		{
			Logger::throwWarning("Animation3D ID cannot contain any spaces");

			return;
		}

		if(any_of(newAnimation3dId.begin(), newAnimation3dId.end(), isupper))
		{
			Logger::throwWarning("Animation3D ID cannot contain any capitals");

			return;
		}

		newAnimation3dId = ("@" + newAnimation3dId);

		if(find(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end(), newAnimation3dId) != _loadedAnimation3dIds.end())
		{
			Logger::throwWarning("Animation3D already exists");

			return;
		}

		_currentAnimation3dId = newAnimation3dId;
		_loadedAnimation3dIds.push_back(newAnimation3dId);
		sort(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end());

		_fe3d->animation3d_create(newAnimation3dId);

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
		_gui->getOverlay()->getTextField("animation3dId")->setTextContent("Animation3D: " + newAnimation3dId);
		_gui->getOverlay()->getTextField("animation3dId")->setVisible(true);
		_gui->getOverlay()->getTextField("animation3dFrame")->setVisible(true);
	}
}

void Animation3dEditor::_updateAnimation3dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAnimation3d") || (_gui->getOverlay()->getChoiceFormId() == "deleteAnimation3d"))
	{
		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentAnimation3dId = ("@" + _gui->getOverlay()->getChoiceFormOptionId());

			if(_gui->getOverlay()->getChoiceFormId() == "deleteAnimation3d")
			{
				_gui->getOverlay()->openAnswerForm("deleteAnimation3d", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
			}
			else
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

				_gui->getOverlay()->getTextField("animation3dId")->setTextContent("Animation3D: " + _currentAnimation3dId.substr(1));
				_gui->getOverlay()->getTextField("animation3dId")->setVisible(true);
				_gui->getOverlay()->getTextField("animation3dFrame")->setVisible(true);
			}
		}
	}
}

void Animation3dEditor::_updateAnimation3dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAnimation3d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->animation3d_delete(_currentAnimation3dId);

			_loadedAnimation3dIds.erase(remove(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end(), _currentAnimation3dId), _loadedAnimation3dIds.end());
			_currentAnimation3dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAnimation3dId = "";
		}
	}
}

void Animation3dEditor::_updateModelChoosing()
{
	if(!_hoveredModelId.empty())
	{
		_fe3d->model_setVisible(_hoveredModelId, false);

		_hoveredModelId = "";
	}

	if(_gui->getOverlay()->getChoiceFormId() == "selectModel")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredModelId.empty())
			{
				_hoveredModelId = ("@" + selectedOptionId);

				_fe3d->model_setVisible(_hoveredModelId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				bool hasAllParts = true;

				for(const auto & partId : _fe3d->animation3d_getPartIds(_currentAnimation3dId))
				{
					if(!partId.empty())
					{
						hasAllParts = (hasAllParts && _fe3d->model_hasPart(_hoveredModelId, partId));
					}
				}

				if(!hasAllParts)
				{
					Logger::throwWarning("Preview model does not have the required animation3D parts");

					return;
				}

				_previewModelId = _hoveredModelId;
				_initialModelSize = _fe3d->model_getBaseSize(_previewModelId);

				if(_fe3d->animation3d_getFrameCount(_currentAnimation3dId) == 0)
				{
					_fe3d->animation3d_createPart(_currentAnimation3dId, "");

					for(const auto & partId : _fe3d->model_getPartIds(_previewModelId))
					{
						_fe3d->animation3d_createPart(_currentAnimation3dId, partId);
					}

					_fe3d->animation3d_createFrame(_currentAnimation3dId, 0);
				}

				_hoveredModelId = "";
			}
		}
	}
}

void Animation3dEditor::_updatePartChoosing()
{
	if(!_hoveredPartId.empty())
	{
		_fe3d->model_setOpacity(_previewModelId, _hoveredPartId, _originalPartOpacity);

		_hoveredPartId = "";
	}

	if(_gui->getOverlay()->getChoiceFormId() == "selectPart")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
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