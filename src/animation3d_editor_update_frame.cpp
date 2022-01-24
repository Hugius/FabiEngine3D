#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateFrameMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation3dEditorMenuFrame")
	{
		auto currentAnimation = _getAnimation(_currentAnimationID);
		auto frame = currentAnimation->getFrames()[_currentFrameIndex];
		auto transformation = frame.getTargetTransformations().at(_currentPartID);
		auto rotationOrigin = frame.getRotationOrigins().at(_currentPartID);
		auto speed = frame.getSpeeds().at(_currentPartID);
		auto speedType = frame.getSpeedTypes().at(_currentPartID);
		auto transformationType = frame.getTransformationTypes().at(_currentPartID);
		auto multiplier = (transformationType == TransformationType::MOVEMENT) ? 1000.0f : (transformationType == TransformationType::SCALING) ? 100.0f : 1.0f;

		screen->getButton("rotationOrigin")->setHoverable(transformationType == TransformationType::ROTATION);
		screen->getButton("speed")->setHoverable(speedType != Animation3dSpeedType::INSTANTLY);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentPartID.empty())
			{
				_fe3d->model_setOpacity(currentAnimation->getPreviewModelID(), _currentPartID, _originalPartOpacity);
				_currentPartID = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartID.empty())
			{
				auto modelParts = currentAnimation->getPartIDs();
				modelParts.erase(modelParts.begin());
				_gui->getOverlay()->createChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), modelParts);
			}
			else
			{
				_fe3d->model_setOpacity(currentAnimation->getPreviewModelID(), _currentPartID, _originalPartOpacity);
				_currentPartID = "";
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui->getOverlay()->createValueForm("transformationX", "X", transformation.x * multiplier, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("transformationY", "Y", transformation.y * multiplier, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("transformationZ", "Z", transformation.z * multiplier, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->createValueForm("transformationSpeedX", "X", speed.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("transformationSpeedY", "Y", speed.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("transformationSpeedZ", "Z", speed.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			if(speedType == Animation3dSpeedType::LINEAR)
			{
				speedType = Animation3dSpeedType::EXPONENTIAL;
			}
			else if(speedType == Animation3dSpeedType::EXPONENTIAL)
			{
				speedType = Animation3dSpeedType::INSTANTLY;
			}
			else
			{
				speedType = Animation3dSpeedType::LINEAR;
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui->getOverlay()->createValueForm("rotationOriginX", "X", rotationOrigin.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("rotationOriginY", "Y", rotationOrigin.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("rotationOriginZ", "Z", rotationOrigin.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->isValueFormExisting("rotationOriginX") &&
		   _gui->getOverlay()->isValueFormExisting("rotationOriginY") &&
		   _gui->getOverlay()->isValueFormExisting("rotationOriginZ"))
		{
			if(_currentPartID.empty())
			{
				_fe3d->model_rotateBase(currentAnimation->getPreviewModelID(), frame.getSpeeds().at(_currentPartID));
			}
			else
			{
				_fe3d->model_rotatePart(currentAnimation->getPreviewModelID(), _currentPartID, frame.getSpeeds().at(_currentPartID));
			}
			_mustUpdateCurrentFramePreview = false;
		}
		else
		{
			_mustUpdateCurrentFramePreview = true;
		}

		if(_gui->getOverlay()->checkValueForm("transformationX", transformation.x, {}))
		{
			transformation.x /= multiplier;
		}
		if(_gui->getOverlay()->checkValueForm("transformationY", transformation.y, {}))
		{
			transformation.y /= multiplier;
		}
		if(_gui->getOverlay()->checkValueForm("transformationZ", transformation.z, {}))
		{
			transformation.z /= multiplier;
		}
		if(_gui->getOverlay()->checkValueForm("transformationSpeedX", speed.x, {}))
		{
			speed.x /= 1000.0f;
		}
		if(_gui->getOverlay()->checkValueForm("transformationSpeedY", speed.y, {}))
		{
			speed.y /= 1000.0f;
		}
		if(_gui->getOverlay()->checkValueForm("transformationSpeedZ", speed.z, {}))
		{
			speed.z /= 1000.0f;
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginX", rotationOrigin.x, {}))
		{
			rotationOrigin.x /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginY", rotationOrigin.y, {}))
		{
			rotationOrigin.y /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui->getOverlay()->checkValueForm("rotationOriginZ", rotationOrigin.z, {}))
		{
			rotationOrigin.z /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}

		screen->getButton("part")->changeTextContent(_currentPartID.empty() ? "Select Part" : "Unselect Part");
		switch(transformationType)
		{
			case TransformationType::MOVEMENT:
			{
				screen->getButton("transformationType")->changeTextContent("Type: MOVE");
				break;
			}
			case TransformationType::ROTATION:
			{
				screen->getButton("transformationType")->changeTextContent("Type: ROTATE");
				break;
			}
			case TransformationType::SCALING:
			{
				screen->getButton("transformationType")->changeTextContent("Type: SCALE");
				break;
			}
		}
		switch(speedType)
		{
			case Animation3dSpeedType::LINEAR:
			{
				screen->getButton("speedType")->changeTextContent("Type: LINEAR");
				break;
			}
			case Animation3dSpeedType::EXPONENTIAL:
			{
				screen->getButton("speedType")->changeTextContent("Type: EXPONENT");
				break;
			}
			case Animation3dSpeedType::INSTANTLY:
			{
				screen->getButton("speedType")->changeTextContent("Type: INSTANT");
				break;
			}
		}

		frame.setTargetTransformation(_currentPartID, transformation);
		frame.setTransformationType(_currentPartID, transformationType);
		frame.setSpeed(_currentPartID, speed);
		frame.setSpeedType(_currentPartID, speedType);
		frame.setRotationOrigin(_currentPartID, rotationOrigin);

		currentAnimation->setFrame(_currentFrameIndex, frame);

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("partList");

		if(!selectedButtonID.empty())
		{
			if(_hoveredPartID.empty())
			{
				_hoveredPartID = selectedButtonID;
				_originalPartOpacity = _fe3d->model_getOpacity(currentAnimation->getPreviewModelID(), _hoveredPartID);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentPartID = selectedButtonID;
				_hoveredPartID = "";
				_gui->getOverlay()->deleteChoiceForm("partList");
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("partList"))
		{
			_gui->getOverlay()->deleteChoiceForm("partList");
		}
		else
		{
			if(!_hoveredPartID.empty())
			{
				_fe3d->model_setOpacity(currentAnimation->getPreviewModelID(), _hoveredPartID, _originalPartOpacity);
				_hoveredPartID = "";
			}
		}
	}
}