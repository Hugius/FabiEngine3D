#include "animation3d_editor.hpp"
#include "tools.hpp"

void Animation3dEditor::_updateFrameMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuFrame")
	{
		const auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId);
		const auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimation3dId, _currentFrameIndex, _currentPartId);
		const auto speed = _fe3d->animation3d_getSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId);
		const auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimation3dId, _currentFrameIndex, _currentPartId);
		const auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimation3dId, _currentFrameIndex, _currentPartId);
		const auto transformationMultiplier = (transformationType == TransformationType::MOVEMENT) ? MOVEMENT_FACTOR : (transformationType == TransformationType::ROTATION) ? ROTATION_FACTOR : SCALING_FACTOR;

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);

				_currentPartId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartId.empty())
			{
				auto partIds = _fe3d->animation3d_getPartIds(_currentAnimation3dId);

				partIds.erase(partIds.begin());

				_gui->getOverlay()->openChoiceForm("selectPart", "Select Part", RIGHT_CHOICE_FORM_POSITION, partIds);
			}
			else
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);

				_currentPartId = "";
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui->getOverlay()->openValueForm("targetTransformationX", "X", (targetTransformation.x * transformationMultiplier), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("targetTransformationY", "Y", (targetTransformation.y * transformationMultiplier), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("targetTransformationZ", "Z", (targetTransformation.z * transformationMultiplier), VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("transformationType")->isHovered())
		{
			switch(transformationType)
			{
				case TransformationType::MOVEMENT:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, TransformationType::ROTATION);
					_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(0.0f));

					break;
				}
				case TransformationType::ROTATION:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, TransformationType::SCALING);
					_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(0.0f));

					break;
				}
				case TransformationType::SCALING:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, TransformationType::MOVEMENT);
					_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(0.0f));

					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("speedX", "X", (speed.x * SPEED_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("speedY", "Y", (speed.y * SPEED_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("speedZ", "Z", (speed.z * SPEED_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			switch(speedType)
			{
				case SpeedType::LINEAR:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, SpeedType::EXPONENTIAL);

					break;
				}
				case SpeedType::EXPONENTIAL:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, SpeedType::INSTANTLY);

					break;
				}
				case SpeedType::INSTANTLY:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimation3dId, _currentFrameIndex, _currentPartId, SpeedType::LINEAR);
					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rotationOriginX", "X", (rotationOrigin.x * ROTATION_ORIGIN_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationOriginY", "Y", (rotationOrigin.y * ROTATION_ORIGIN_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationOriginZ", "Z", (rotationOrigin.z * ROTATION_ORIGIN_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "targetTransformationX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3((value / transformationMultiplier), targetTransformation.y, targetTransformation.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "targetTransformationY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(targetTransformation.x, (value / transformationMultiplier), targetTransformation.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "targetTransformationZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setTargetTransformation(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(targetTransformation.x, targetTransformation.y, (value / transformationMultiplier)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "speedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3((value / SPEED_FACTOR), speed.y, speed.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "speedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(speed.x, (value / SPEED_FACTOR), speed.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "speedZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(speed.x, speed.y, (value / SPEED_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rotationOriginX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setRotationOrigin(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3((value / ROTATION_ORIGIN_FACTOR), rotationOrigin.y, rotationOrigin.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rotationOriginY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setRotationOrigin(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(rotationOrigin.x, (value / ROTATION_ORIGIN_FACTOR), rotationOrigin.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rotationOriginZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->animation3d_setRotationOrigin(_currentAnimation3dId, _currentFrameIndex, _currentPartId, fvec3(rotationOrigin.x, rotationOrigin.y, (value / ROTATION_ORIGIN_FACTOR)));
		}

		screen->getButton("part")->setTextContent(_currentPartId.empty() ? "Select Part" : "Unselect Part");

		switch(transformationType)
		{
			case TransformationType::MOVEMENT:
			{
				screen->getButton("transformationType")->setTextContent("Type: MOVE");

				break;
			}
			case TransformationType::ROTATION:
			{
				screen->getButton("transformationType")->setTextContent("Type: ROTATE");

				break;
			}
			case TransformationType::SCALING:
			{
				screen->getButton("transformationType")->setTextContent("Type: SCALE");

				break;
			}
		}
		switch(speedType)
		{
			case SpeedType::LINEAR:
			{
				screen->getButton("speedType")->setTextContent("Type: LINEAR");

				break;
			}
			case SpeedType::EXPONENTIAL:
			{
				screen->getButton("speedType")->setTextContent("Type: EXPONENT");

				break;
			}
			case SpeedType::INSTANTLY:
			{
				screen->getButton("speedType")->setTextContent("Type: INSTANT");

				break;
			}
		}

		_mustUpdateCurrentFramePreview = true;

		if((_gui->getOverlay()->getValueFormId() == "rotationOriginX") || (_gui->getOverlay()->getValueFormId() == "rotationOriginY") || (_gui->getOverlay()->getValueFormId() == "rotationOriginZ"))
		{
			if(!_gui->getOverlay()->isValueFormConfirmed())
			{
				if(_currentPartId.empty())
				{
					_fe3d->model_rotateBase(_previewModelId, _fe3d->animation3d_getSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId));
				}
				else
				{
					_fe3d->model_rotatePart(_previewModelId, _currentPartId, _fe3d->animation3d_getSpeed(_currentAnimation3dId, _currentFrameIndex, _currentPartId));
				}

				_mustUpdateCurrentFramePreview = false;
			}
		}
	}
}