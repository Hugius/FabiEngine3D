#include "animation3d_editor.hpp"
#include "tools.hpp"

void Animation3dEditor::_updateFrameMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuFrame")
	{
		const auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId);
		const auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId);
		const auto speed = _fe3d->animation3d_getSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId);
		const auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId);
		const auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId);
		const auto multiplier = (transformationType == TransformationType::MOVEMENT) ? 1000.0f : (transformationType == TransformationType::SCALING) ? 100.0f : 1.0f;

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartId.empty())
			{
				auto partIds = _fe3d->animation3d_getPartIds(_currentAnimationId);
				partIds.erase(partIds.begin());
				_gui->getOverlay()->openChoiceForm("selectPart", "Select Part", fvec2(-0.5f, 0.1f), partIds);
			}
			else
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui->getOverlay()->openValueForm("targetTransformationX", "X", (targetTransformation.x * multiplier), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("targetTransformationY", "Y", (targetTransformation.y * multiplier), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("targetTransformationZ", "Z", (targetTransformation.z * multiplier), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("transformationType")->isHovered())
		{
			switch(transformationType)
			{
				case TransformationType::MOVEMENT:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId, TransformationType::ROTATION);

					break;
				}
				case TransformationType::ROTATION:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId, TransformationType::SCALING);

					break;
				}
				case TransformationType::SCALING:
				{
					_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId, TransformationType::MOVEMENT);

					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("speedX", "X", (speed.x * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("speedY", "Y", (speed.y * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("speedZ", "Z", (speed.z * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			switch(speedType)
			{
				case SpeedType::LINEAR:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId, SpeedType::EXPONENTIAL);

					break;
				}
				case SpeedType::EXPONENTIAL:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId, SpeedType::INSTANTLY);

					break;
				}
				case SpeedType::INSTANTLY:
				{
					_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId, SpeedType::LINEAR);
					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rotationOriginX", "X", (rotationOrigin.x * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationOriginY", "Y", (rotationOrigin.y * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationOriginZ", "Z", (rotationOrigin.z * 1000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "targetTransformationX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3((content * multiplier), targetTransformation.y, targetTransformation.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "targetTransformationY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(targetTransformation.x, (content * multiplier), targetTransformation.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "targetTransformationZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(targetTransformation.x, targetTransformation.y, (content * multiplier)));
		}
		if((_gui->getOverlay()->getValueFormId() == "speedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3((content / 1000.0f), speed.y, speed.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "speedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(speed.x, (content / 1000.0f), speed.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "speedZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(speed.x, speed.y, (content / 1000.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "rotationOriginX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3((content / 1000.0f), rotationOrigin.y, rotationOrigin.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "rotationOriginY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(rotationOrigin.x, (content / 1000.0f), rotationOrigin.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "rotationOriginZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, fvec3(rotationOrigin.x, rotationOrigin.y, (content / 1000.0f)));
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

		if((_gui->getOverlay()->getValueFormId() == "rotationOriginX") && (_gui->getOverlay()->getValueFormId() == "rotationOriginY") && (_gui->getOverlay()->getValueFormId() == "rotationOriginZ"))
		{
			if(_currentPartId.empty())
			{
				_fe3d->model_rotateBase(_previewModelId, _fe3d->animation3d_getSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId));
			}
			else
			{
				_fe3d->model_rotatePart(_previewModelId, _currentPartId, _fe3d->animation3d_getSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId));
			}

			_mustUpdateCurrentFramePreview = false;
		}
		else
		{
			_mustUpdateCurrentFramePreview = true;
		}
	}
}