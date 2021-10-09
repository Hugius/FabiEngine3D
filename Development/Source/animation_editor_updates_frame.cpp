#include "animation_editor.hpp"
#include "logger.hpp"

void AnimationEditor::_updateFrameMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "animationEditorMenuFrame")
	{
		// Temporary values
		auto animation = _getAnimation(_currentAnimationID);
		auto frame = animation->getFrames()[_currentFrameIndex];
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
		screen->getButton("speed")->setHoverable(speedType != AnimationSpeedType::INSTANTLY);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			// Reset color inversion
			for (const auto& partID : _fe3d.modelEntity_getPartIDs(animation->getPreviewModelID()))
			{
				_fe3d.modelEntity_setColorInversion(animation->getPreviewModelID(), partID, 0.0f);
			}

			// Miscellaneous
			_currentPartID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("transformationX", "X", transformation.x * multiplier, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationY", "Y", transformation.y * multiplier, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationZ", "Z", transformation.z * multiplier, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rotationOriginX", "X", rotationOrigin.x * 1000.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("rotationOriginY", "Y", rotationOrigin.y * 1000.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("rotationOriginZ", "Z", rotationOrigin.z * 1000.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("transformationSpeedX", "X", speed.x * 1000.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationSpeedY", "Y", speed.y * 1000.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationSpeedZ", "Z", speed.z * 1000.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			// Change speed type
			if (speedType == AnimationSpeedType::LINEAR)
			{
				speedType = AnimationSpeedType::EXPONENTIAL;
			}
			else if (speedType == AnimationSpeedType::EXPONENTIAL)
			{
				speedType = AnimationSpeedType::INSTANTLY;
			}
			else
			{
				speedType = AnimationSpeedType::LINEAR;
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transType")->isHovered())
		{
			// Change transformation type
			if (transformationType == TransformationType::MOVEMENT)
			{
				transformationType = TransformationType::ROTATION;
			}
			else if (transformationType == TransformationType::ROTATION)
			{
				transformationType = TransformationType::SCALING;
			}
			else if (transformationType == TransformationType::SCALING)
			{
				transformationType = TransformationType::MOVEMENT;
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			// Choosing part of preview model
			auto modelParts = animation->getPartIDs();
			modelParts.erase(modelParts.begin());
			_gui.getGlobalScreen()->createChoiceForm("parts", "Select Part", Vec2(-0.5f, 0.1f), modelParts);
		}

		// Update rotation origin visualization
		if (_gui.getGlobalScreen()->isValueFormExisting("rotationOriginX") &&
			_gui.getGlobalScreen()->isValueFormExisting("rotationOriginY") &&
			_gui.getGlobalScreen()->isValueFormExisting("rotationOriginZ"))
		{
			if (_currentPartID.empty()) // Base rotation
			{
				_fe3d.modelEntity_rotateBase(animation->getPreviewModelID(), frame.getSpeeds().at(_currentPartID));
			}
			else // Part rotation
			{
				_fe3d.modelEntity_rotatePart(animation->getPreviewModelID(), _currentPartID, frame.getSpeeds().at(_currentPartID));
			}
			_mustUpdateCurrentFramePreview = false;
		}
		else
		{
			_mustUpdateCurrentFramePreview = true;
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("transformationX", transformation.x, {}))
		{
			transformation.x /= multiplier;
		}
		if (_gui.getGlobalScreen()->checkValueForm("transformationY", transformation.y, {}))
		{
			transformation.y /= multiplier;
		}
		if (_gui.getGlobalScreen()->checkValueForm("transformationZ", transformation.z, {}))
		{
			transformation.z /= multiplier;
		}
		if (_gui.getGlobalScreen()->checkValueForm("rotationOriginX", rotationOrigin.x, {}))
		{
			rotationOrigin.x /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if (_gui.getGlobalScreen()->checkValueForm("rotationOriginY", rotationOrigin.y, {}))
		{
			rotationOrigin.y /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if (_gui.getGlobalScreen()->checkValueForm("rotationOriginZ", rotationOrigin.z, {}))
		{
			rotationOrigin.z /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if (_gui.getGlobalScreen()->checkValueForm("transformationSpeedX", speed.x, {}))
		{
			speed.x /= 1000.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("transformationSpeedY", speed.y, {}))
		{
			speed.y /= 1000.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("transformationSpeedZ", speed.z, {}))
		{
			speed.z /= 1000.0f;
		}

		// Update button text contents
		if (speedType == AnimationSpeedType::LINEAR)
		{
			screen->getButton("speedType")->changeTextContent("Speed: LINEAR");
		}
		else if (speedType == AnimationSpeedType::EXPONENTIAL)
		{
			screen->getButton("speedType")->changeTextContent("Speed: EXPONENT");
		}
		else
		{
			screen->getButton("speedType")->changeTextContent("Speed: INSTANT");
		}
		if (transformationType == TransformationType::MOVEMENT)
		{
			screen->getButton("transType")->changeTextContent("Type: MOVE");
		}
		else if (transformationType == TransformationType::ROTATION)
		{
			screen->getButton("transType")->changeTextContent("Type: ROTATE");
		}
		else
		{
			screen->getButton("transType")->changeTextContent("Type: SCALE");
		}

		// Update frame values
		frame.setTargetTransformation(_currentPartID, transformation);
		frame.setRotationOrigin(_currentPartID, rotationOrigin);
		frame.setSpeed(_currentPartID, speed);
		frame.setSpeedType(_currentPartID, speedType);
		frame.setTransformationType(_currentPartID, transformationType);

		// Update frame
		animation->setFrame(_currentFrameIndex, frame);

		// Check if an animation part ID is clicked
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("parts");
		if (!selectedButtonID.empty())
		{
			// Check if LMB pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Check if selected part exists on preview model
				if (_fe3d.modelEntity_hasPart(animation->getPreviewModelID(), selectedButtonID))
				{
					_currentPartID = selectedButtonID;
					_hoveredPartID = "";
					_gui.getGlobalScreen()->deleteChoiceForm("parts");
				}
				else
				{
					Logger::throwWarning("Part does not exist on current preview model!");
				}
			}
			else
			{
				// Check if new part hovered
				if (_hoveredPartID != selectedButtonID)
				{
					// Reset color inversion
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(animation->getPreviewModelID()))
					{
						_fe3d.modelEntity_setColorInversion(animation->getPreviewModelID(), partID, 0.0f);
					}
				}

				// Set hovered ID
				_hoveredPartID = selectedButtonID;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("parts")) // Cancelled choosing
		{
			// Reset color inversion
			for (const auto& partID : _fe3d.modelEntity_getPartIDs(animation->getPreviewModelID()))
			{
				_fe3d.modelEntity_setColorInversion(animation->getPreviewModelID(), partID, 0.0f);
			}

			// Miscellaneous
			_gui.getGlobalScreen()->deleteChoiceForm("parts");
			_hoveredPartID = "";
		}
		else
		{
			// Check if a part was hovered
			if (!_hoveredPartID.empty())
			{
				// Reset color inversion
				for (const auto& partID : _fe3d.modelEntity_getPartIDs(animation->getPreviewModelID()))
				{
					_fe3d.modelEntity_setColorInversion(animation->getPreviewModelID(), partID, 0.0f);
				}
			}

			// Reset hovered ID
			_hoveredPartID = "";
		}
	}
}