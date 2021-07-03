#include "animation_editor.hpp"

void AnimationEditor::_updateFrameScreen()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "animationEditorMenuFrame")
		{
			// Temporary values
			auto currentAnimation = _getAnimation(_currentAnimationID);
			auto& transformation = currentAnimation->frames[_currentFrameIndex].targetTransformations[_currentPartID];
			auto& rotationOrigin = currentAnimation->frames[_currentFrameIndex].rotationOrigins[_currentPartID];
			auto& speed = currentAnimation->frames[_currentFrameIndex].speeds[_currentPartID];
			auto& speedType = currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartID];
			auto& transType = currentAnimation->frames[_currentFrameIndex].transformationTypes[_currentPartID];

			// Translation in small units, scaling in %, rotation in whole degrees
			float multiplier = (transType == TransformationType::TRANSLATION) ? 1000.0f :
				(transType == TransformationType::SCALING) ? 100.0f : 1.0f;

			// Rotation origin is only available if transformation type is rotation
			screen->getButton("rotationOrigin")->setHoverable(transType == TransformationType::ROTATION);

			// Speed is only available if speed type is not instantly
			screen->getButton("speed")->setHoverable(speedType != AnimationSpeedType::INSTANTLY);

			// Update screen logic
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_currentPartID = "";
					_fe3d.modelEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
				}
				else if (screen->getButton("transformation")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xTransformation", "X", transformation.x * multiplier, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("yTransformation", "Y", transformation.y * multiplier, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("zTransformation", "Z", transformation.z * multiplier, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("rotationOrigin")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xRotationOrigin", "X", rotationOrigin.x * 1000.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("yRotationOrigin", "Y", rotationOrigin.y * 1000.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("zRotationOrigin", "Z", rotationOrigin.z * 1000.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xTransformationSpeed", "X", speed.x * 1000.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("yTransformationSpeed", "Y", speed.y * 1000.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("zTransformationSpeed", "Z", speed.z * 1000.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("speedType")->isHovered())
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
				else if (screen->getButton("transType")->isHovered())
				{
					// Change transformation type
					if (transType == TransformationType::TRANSLATION)
					{
						transType = TransformationType::ROTATION;
					}
					else if (transType == TransformationType::ROTATION)
					{
						transType = TransformationType::SCALING;
					}
					else if (transType == TransformationType::SCALING)
					{
						transType = TransformationType::TRANSLATION;
					}
				}
				else if (screen->getButton("part")->isHovered())
				{
					// Choosing part of preview model
					auto modelParts = currentAnimation->partIDs;
					modelParts.erase(modelParts.begin());
					_gui.getGlobalScreen()->addChoiceForm("parts", "Select part", Vec2(-0.4f, 0.1f), modelParts);
				}
			}

			// Emphasize selected model part
			if (!_currentPartID.empty())
			{
				_fe3d.modelEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
				_fe3d.modelEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor * _partColorStrength, _currentPartID);
			}

			// Update color strength
			_partColorIncreasing = (_partColorStrength >= 1.0f) ? false : (_partColorStrength <= 0.0f) ? true : _partColorIncreasing;
			_partColorStrength += ((_partColorIncreasing ? 1.0f : -1.0f) * _colorChangingSpeed);

			// Update X transformation change
			if (_gui.getGlobalScreen()->checkValueForm("xTransformation", transformation.x, { }))
			{
				transformation.x /= multiplier;
			}

			// Update Y transformation change
			if (_gui.getGlobalScreen()->checkValueForm("yTransformation", transformation.y, { }))
			{
				transformation.y /= multiplier;
			}

			// Update Z transformation change
			if (_gui.getGlobalScreen()->checkValueForm("zTransformation", transformation.z, { }))
			{
				transformation.z /= multiplier;
			}

			// Update X rotation origin change
			if (_gui.getGlobalScreen()->checkValueForm("xRotationOrigin", rotationOrigin.x, { }))
			{
				rotationOrigin.x /= 1000.0f;
			}

			// Update Y rotation origin change
			if (_gui.getGlobalScreen()->checkValueForm("yRotationOrigin", rotationOrigin.y, { }))
			{
				rotationOrigin.y /= 1000.0f;
			}

			// Update Z rotation origin change
			if (_gui.getGlobalScreen()->checkValueForm("zRotationOrigin", rotationOrigin.z, { }))
			{
				rotationOrigin.z /= 1000.0f;
			}

			// Update X speed change
			if (_gui.getGlobalScreen()->checkValueForm("xTransformationSpeed", speed.x, { }))
			{
				speed.x /= 1000.0f;
			}

			// Update Y speed change
			if (_gui.getGlobalScreen()->checkValueForm("yTransformationSpeed", speed.y, { }))
			{
				speed.y /= 1000.0f;
			}

			// Update Z speed change
			if (_gui.getGlobalScreen()->checkValueForm("zTransformationSpeed", speed.z, { }))
			{
				speed.z /= 1000.0f;
			}

			// Button text contents
			if (speedType == AnimationSpeedType::LINEAR)
			{
				screen->getButton("speedType")->changeTextContent("Speed: linear");
			}
			else if (speedType == AnimationSpeedType::EXPONENTIAL)
			{
				screen->getButton("speedType")->changeTextContent("Speed: exponent");
			}
			else
			{
				screen->getButton("speedType")->changeTextContent("Speed: instant");
			}
			if (transType == TransformationType::TRANSLATION)
			{
				screen->getButton("transType")->changeTextContent("Type: translate");
			}
			else if (transType == TransformationType::ROTATION)
			{
				screen->getButton("transType")->changeTextContent("Type: rotate");
			}
			else
			{
				screen->getButton("transType")->changeTextContent("Type: scale");
			}

			// Check if a animation partID is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("parts");
			if (selectedButtonID != "")
			{
				// Check if LMB pressed
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Check if selected part exists on preview model
					if (_fe3d.modelEntity_hasPart(currentAnimation->previewModelID, selectedButtonID))
					{
						_currentPartID = selectedButtonID;
						_gui.getGlobalScreen()->removeChoiceForm("parts");
					}
					else
					{
						_fe3d.logger_throwWarning("Part does not exist on current preview model!");
					}
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("parts")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->removeChoiceForm("parts");
			}
		}
	}
}