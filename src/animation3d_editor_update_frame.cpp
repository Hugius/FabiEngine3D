#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateFrameMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuFrame")
	{
		auto targetTransformation = _fe3d->animation3d_getTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId);
		auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId);
		auto speed = _fe3d->animation3d_getSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId);
		auto speedType = _fe3d->animation3d_getSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId);
		auto transformationType = _fe3d->animation3d_getTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId);
		auto multiplier = (transformationType == TransformationType::MOVEMENT) ? 1000.0f : (transformationType == TransformationType::SCALING) ? 100.0f : 1.0f;

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartId.empty())
			{
				auto partIds = _fe3d->animation3d_getPartIds(_currentAnimationId);
				partIds.erase(partIds.begin());
				_gui->getOverlay()->enableChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), partIds);
				_isChoosingPart = true;
			}
			else
			{
				_fe3d->model_setOpacity(_previewModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui->getOverlay()->enableValueForm("targetTransformationX", "X", (targetTransformation.x * multiplier), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("targetTransformationY", "Y", (targetTransformation.y * multiplier), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("targetTransformationZ", "Z", (targetTransformation.z * multiplier), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformationType")->isHovered())
		{
			if(transformationType == TransformationType::MOVEMENT)
			{
				transformationType = TransformationType::ROTATION;
			}
			else if(transformationType == TransformationType::ROTATION)
			{
				transformationType = TransformationType::SCALING;
			}
			else if(transformationType == TransformationType::SCALING)
			{
				transformationType = TransformationType::MOVEMENT;
			}

			_fe3d->animation3d_setTransformationType(_currentAnimationId, _currentFrameIndex, _currentPartId, transformationType);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->enableValueForm("speedX", "X", (speed.x * 1000.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("speedY", "Y", (speed.y * 1000.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("speedZ", "Z", (speed.z * 1000.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			if(speedType == SpeedType::LINEAR)
			{
				speedType = SpeedType::EXPONENTIAL;
			}
			else if(speedType == SpeedType::EXPONENTIAL)
			{
				speedType = SpeedType::INSTANTLY;
			}
			else
			{
				speedType = SpeedType::LINEAR;
			}

			_fe3d->animation3d_setSpeedType(_currentAnimationId, _currentFrameIndex, _currentPartId, speedType);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui->getOverlay()->enableValueForm("rotationOriginX", "X", rotationOrigin.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("rotationOriginY", "Y", rotationOrigin.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->enableValueForm("rotationOriginZ", "Z", rotationOrigin.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->isValueFormActive("rotationOriginX") &&
		   _gui->getOverlay()->isValueFormActive("rotationOriginY") &&
		   _gui->getOverlay()->isValueFormActive("rotationOriginZ"))
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

		if(_gui->getOverlay()->checkValueForm("targetTransformationX", targetTransformation.x, {}))
		{
			targetTransformation.x /= multiplier;

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, targetTransformation);
		}
		if(_gui->getOverlay()->checkValueForm("targetTransformationY", targetTransformation.y, {}))
		{
			targetTransformation.y /= multiplier;

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, targetTransformation);
		}
		if(_gui->getOverlay()->checkValueForm("targetTransformationZ", targetTransformation.z, {}))
		{
			targetTransformation.z /= multiplier;

			_fe3d->animation3d_setTargetTransformation(_currentAnimationId, _currentFrameIndex, _currentPartId, targetTransformation);
		}
		if(_gui->getOverlay()->checkValueForm("speedX", speed.x, {}))
		{
			speed.x /= 1000.0f;

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, speed);
		}
		if(_gui->getOverlay()->checkValueForm("speedY", speed.y, {}))
		{
			speed.y /= 1000.0f;

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, speed);
		}
		if(_gui->getOverlay()->checkValueForm("speedZ", speed.z, {}))
		{
			speed.z /= 1000.0f;

			_fe3d->animation3d_setSpeed(_currentAnimationId, _currentFrameIndex, _currentPartId, speed);
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginX", rotationOrigin.x, {}))
		{
			rotationOrigin.x /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, rotationOrigin);
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginY", rotationOrigin.y, {}))
		{
			rotationOrigin.y /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, rotationOrigin);
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginZ", rotationOrigin.z, {}))
		{
			rotationOrigin.z /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
			_fe3d->animation3d_setRotationOrigin(_currentAnimationId, _currentFrameIndex, _currentPartId, rotationOrigin);
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
	}
}