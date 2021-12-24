#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateFrameMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "animation3dEditorMenuFrame")
	{
		// Temporary values
		auto currentAnimation = _getAnimation(_currentAnimationID);
		auto frame = currentAnimation->getFrames()[_currentFrameIndex];
		auto transformation = frame.getTargetTransformations().at(_currentPartID);
		auto rotationOrigin = frame.getRotationOrigins().at(_currentPartID);
		auto speed = frame.getSpeeds().at(_currentPartID);
		auto speedType = frame.getSpeedTypes().at(_currentPartID);
		auto transformationType = frame.getTransformationTypes().at(_currentPartID);

		// Movement in small units, rotation in whole degrees, scaling in %
		float multiplier = (transformationType == TransformationType::MOVEMENT) ? 1000.0f :
			(transformationType == TransformationType::SCALING) ? 100.0f : 1.0f;

		// Rotation origin is only available if transformation type is rotation
		screen->getButton("rotationOrigin")->setHoverable(transformationType == TransformationType::ROTATION);

		// Speed is only available if speed type is not instantly
		screen->getButton("speed")->setHoverable(speedType != Animation3dSpeedType::INSTANTLY);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused())) // Back button
		{
			// Reset wireframe
			for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
			{
				_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
				_fe3d.model_setWireframed(currentAnimation->getPreviewModelID(), partID, false);
			}

			// Miscellaneous
			_currentPartID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			// Choosing part of preview model
			auto modelParts = currentAnimation->getPartIDs();
			modelParts.erase(modelParts.begin());
			_gui.getOverlay()->createChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), modelParts);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui.getOverlay()->createValueForm("transformationX", "X", transformation.x * multiplier, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("transformationY", "Y", transformation.y * multiplier, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("transformationZ", "Z", transformation.z * multiplier, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformationType")->isHovered())
		{
			// Change transformation type
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
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getOverlay()->createValueForm("transformationSpeedX", "X", speed.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("transformationSpeedY", "Y", speed.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("transformationSpeedZ", "Z", speed.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			// Change speed type
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
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui.getOverlay()->createValueForm("rotationOriginX", "X", rotationOrigin.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("rotationOriginY", "Y", rotationOrigin.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("rotationOriginZ", "Z", rotationOrigin.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update rotation origin visualization
		if(_gui.getOverlay()->isValueFormExisting("rotationOriginX") &&
		   _gui.getOverlay()->isValueFormExisting("rotationOriginY") &&
		   _gui.getOverlay()->isValueFormExisting("rotationOriginZ"))
		{
			if(_currentPartID.empty()) // Base rotation
			{
				_fe3d.model_rotateBase(currentAnimation->getPreviewModelID(), frame.getSpeeds().at(_currentPartID));
			}
			else // Part rotation
			{
				_fe3d.model_rotatePart(currentAnimation->getPreviewModelID(), _currentPartID, frame.getSpeeds().at(_currentPartID));
			}
			_mustUpdateCurrentFramePreview = false;
		}
		else
		{
			_mustUpdateCurrentFramePreview = true;
		}

		// Update value forms
		if(_gui.getOverlay()->checkValueForm("transformationX", transformation.x, {}))
		{
			transformation.x /= multiplier;
		}
		if(_gui.getOverlay()->checkValueForm("transformationY", transformation.y, {}))
		{
			transformation.y /= multiplier;
		}
		if(_gui.getOverlay()->checkValueForm("transformationZ", transformation.z, {}))
		{
			transformation.z /= multiplier;
		}
		if(_gui.getOverlay()->checkValueForm("transformationSpeedX", speed.x, {}))
		{
			speed.x /= 1000.0f;
		}
		if(_gui.getOverlay()->checkValueForm("transformationSpeedY", speed.y, {}))
		{
			speed.y /= 1000.0f;
		}
		if(_gui.getOverlay()->checkValueForm("transformationSpeedZ", speed.z, {}))
		{
			speed.z /= 1000.0f;
		}
		if(_gui.getOverlay()->checkValueForm("rotationOriginX", rotationOrigin.x, {}))
		{
			rotationOrigin.x /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui.getOverlay()->checkValueForm("rotationOriginY", rotationOrigin.y, {}))
		{
			rotationOrigin.y /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui.getOverlay()->checkValueForm("rotationOriginZ", rotationOrigin.z, {}))
		{
			rotationOrigin.z /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}

		// Update button text contents
		if(transformationType == TransformationType::MOVEMENT)
		{
			screen->getButton("transformationType")->changeTextContent("Type: MOVE");
		}
		else if(transformationType == TransformationType::ROTATION)
		{
			screen->getButton("transformationType")->changeTextContent("Type: ROTATE");
		}
		else
		{
			screen->getButton("transformationType")->changeTextContent("Type: SCALE");
		}
		if(speedType == Animation3dSpeedType::LINEAR)
		{
			screen->getButton("speedType")->changeTextContent("Type: LINEAR");
		}
		else if(speedType == Animation3dSpeedType::EXPONENTIAL)
		{
			screen->getButton("speedType")->changeTextContent("Type: EXPONENT");
		}
		else
		{
			screen->getButton("speedType")->changeTextContent("Type: INSTANT");
		}

		// Update frame values
		frame.setTargetTransformation(_currentPartID, transformation);
		frame.setTransformationType(_currentPartID, transformationType);
		frame.setSpeed(_currentPartID, speed);
		frame.setSpeedType(_currentPartID, speedType);
		frame.setRotationOrigin(_currentPartID, rotationOrigin);

		// Update frame
		currentAnimation->setFrame(_currentFrameIndex, frame);

		// Get selected button ID
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("partList");

		// Check if part ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentPartID = selectedButtonID;
				_hoveredPartID = "";
				_gui.getOverlay()->deleteChoiceForm("partList");
			}
			else
			{
				_hoveredPartID = selectedButtonID;
				_fe3d.model_setWireframed(currentAnimation->getPreviewModelID(), _hoveredPartID, true);
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("partList"))
		{
			_gui.getOverlay()->deleteChoiceForm("partList");
		}
		else
		{
			// Check if part was hovered
			if(!_hoveredPartID.empty())
			{
				// Reset wireframe
				for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
				{
					_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
					_fe3d.model_setWireframed(currentAnimation->getPreviewModelID(), partID, false);
				}
			}

			// Miscellaneous
			_hoveredPartID = "";
		}
	}
}