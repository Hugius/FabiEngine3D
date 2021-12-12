#include "mesh_animation_editor.hpp"
#include "logger.hpp"

void MeshAnimationEditor::_updateFrameMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "meshAnimationEditorMenuFrame")
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
		screen->getButton("speed")->setHoverable(speedType != MeshAnimationSpeedType::INSTANTLY);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			// Reset wireframe color
			for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
			{
				_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
			}

			// Miscellaneous
			_currentPartID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("meshAnimationEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			// Choosing part of preview model
			auto modelParts = currentAnimation->getPartIDs();
			modelParts.erase(modelParts.begin());
			_gui.getGlobalScreen()->createChoiceForm("parts", "Select Part", fvec2(-0.5f, 0.1f), modelParts);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transformation")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("transformationX", "X", transformation.x * multiplier, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationY", "Y", transformation.y * multiplier, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationZ", "Z", transformation.z * multiplier, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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
			_gui.getGlobalScreen()->createValueForm("transformationSpeedX", "X", speed.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationSpeedY", "Y", speed.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("transformationSpeedZ", "Z", speed.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speedType")->isHovered())
		{
			// Change speed type
			if(speedType == MeshAnimationSpeedType::LINEAR)
			{
				speedType = MeshAnimationSpeedType::EXPONENTIAL;
			}
			else if(speedType == MeshAnimationSpeedType::EXPONENTIAL)
			{
				speedType = MeshAnimationSpeedType::INSTANTLY;
			}
			else
			{
				speedType = MeshAnimationSpeedType::LINEAR;
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrigin")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rotationOriginX", "X", rotationOrigin.x * 1000.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("rotationOriginY", "Y", rotationOrigin.y * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("rotationOriginZ", "Z", rotationOrigin.z * 1000.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update rotation origin visualization
		if(_gui.getGlobalScreen()->isValueFormExisting("rotationOriginX") &&
		   _gui.getGlobalScreen()->isValueFormExisting("rotationOriginY") &&
		   _gui.getGlobalScreen()->isValueFormExisting("rotationOriginZ"))
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
		if(_gui.getGlobalScreen()->checkValueForm("transformationX", transformation.x, {}))
		{
			transformation.x /= multiplier;
		}
		if(_gui.getGlobalScreen()->checkValueForm("transformationY", transformation.y, {}))
		{
			transformation.y /= multiplier;
		}
		if(_gui.getGlobalScreen()->checkValueForm("transformationZ", transformation.z, {}))
		{
			transformation.z /= multiplier;
		}
		if(_gui.getGlobalScreen()->checkValueForm("transformationSpeedX", speed.x, {}))
		{
			speed.x /= 1000.0f;
		}
		if(_gui.getGlobalScreen()->checkValueForm("transformationSpeedY", speed.y, {}))
		{
			speed.y /= 1000.0f;
		}
		if(_gui.getGlobalScreen()->checkValueForm("transformationSpeedZ", speed.z, {}))
		{
			speed.z /= 1000.0f;
		}
		if(_gui.getGlobalScreen()->checkValueForm("rotationOriginX", rotationOrigin.x, {}))
		{
			rotationOrigin.x /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui.getGlobalScreen()->checkValueForm("rotationOriginY", rotationOrigin.y, {}))
		{
			rotationOrigin.y /= 1000.0f;
			_mustUpdateCurrentFramePreview = true;
		}
		if(_gui.getGlobalScreen()->checkValueForm("rotationOriginZ", rotationOrigin.z, {}))
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
		if(speedType == MeshAnimationSpeedType::LINEAR)
		{
			screen->getButton("speedType")->changeTextContent("Type: LINEAR");
		}
		else if(speedType == MeshAnimationSpeedType::EXPONENTIAL)
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

		// Check if an animation part ID is clicked
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("parts");
		if(!selectedButtonID.empty())
		{
			// Check if LMB pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Check if selected part exists on preview model
				if(_fe3d.model_hasPart(currentAnimation->getPreviewModelID(), selectedButtonID))
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
				if(_hoveredPartID != selectedButtonID)
				{
					// Reset wireframe color
					for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
					{
						_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
					}
				}

				// Set hovered ID
				_hoveredPartID = selectedButtonID;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("parts")) // Cancelled choosing
		{
			// Reset wireframe color
			for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
			{
				_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
			}

			// Miscellaneous
			_gui.getGlobalScreen()->deleteChoiceForm("parts");
			_hoveredPartID = "";
		}
		else
		{
			// Check if a part was hovered
			if(!_hoveredPartID.empty())
			{
				// Reset wireframe color
				for(const auto& partID : _fe3d.model_getPartIDs(currentAnimation->getPreviewModelID()))
				{
					_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, 0.0f);
				}
			}

			// Reset hovered ID
			_hoveredPartID = "";
		}
	}
}