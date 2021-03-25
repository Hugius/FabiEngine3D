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
			auto& transformation = currentAnimation->frames[_currentFrameIndex].targetTransformations[_currentPartName];
			auto& rotationOrigin = currentAnimation->frames[_currentFrameIndex].rotationOrigins[_currentPartName];
			auto& speed = currentAnimation->frames[_currentFrameIndex].speeds[_currentPartName];
			auto& speedType = currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName];
			auto& transType = currentAnimation->frames[_currentFrameIndex].transformationTypes[_currentPartName];

			// Translation in small units, scaling in %, rotation in whole degrees
			float multiplier = (transType == TransformationType::TRANSLATION) ? 1000.0f :
				(transType == TransformationType::SCALING) ? 100.0f : 1.0f;

			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_currentPartName = "";
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
					_gui.getGlobalScreen()->addValueForm("transformationSpeed", "Transformation speed", speed * 1000.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("speedType")->isHovered())
				{
					// Change speed type
					if (speedType == AnimationSpeedType::LINEAR)
					{
						speedType = AnimationSpeedType::EXPONENTIAL;
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
					auto modelParts = currentAnimation->partNames;
					modelParts.erase(modelParts.begin());
					_gui.getGlobalScreen()->addChoiceForm("parts", "Select part", Vec2(-0.4f, 0.1f), modelParts);
				}
			}

			// Emphasize selected model part
			if (!_currentPartName.empty())
			{
				_fe3d.modelEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
				_fe3d.modelEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor * _partColorStrength, _currentPartName);
			}

			// Update color strength
			_partColorIncreasing = (_partColorStrength >= 1.0f) ? false : (_partColorStrength <= 0.0f) ? true : _partColorIncreasing;
			_partColorStrength += ((_partColorIncreasing ? 1.0f : -1.0f) * _colorChangingSpeed);

			// Update transformation X change
			if (_gui.getGlobalScreen()->checkValueForm("xTransformation", transformation.x, { }))
			{
				transformation.x /= multiplier;
			}

			// Update transformation Y change
			if (_gui.getGlobalScreen()->checkValueForm("yTransformation", transformation.y, { }))
			{
				transformation.y /= multiplier;
			}

			// Update transformation Z change
			if (_gui.getGlobalScreen()->checkValueForm("zTransformation", transformation.z, { }))
			{
				transformation.z /= multiplier;
			}

			// Update rotation origin X change
			if (_gui.getGlobalScreen()->checkValueForm("xRotationOrigin", rotationOrigin.x, { }))
			{
				rotationOrigin.x /= 1000.0f;
			}

			// Update rotation origin Y change
			if (_gui.getGlobalScreen()->checkValueForm("yRotationOrigin", rotationOrigin.y, { }))
			{
				rotationOrigin.y /= 1000.0f;
			}

			// Update rotation origin Z change
			if (_gui.getGlobalScreen()->checkValueForm("zRotationOrigin", rotationOrigin.z, { }))
			{
				rotationOrigin.z /= 1000.0f;
			}

			// Update speed change
			if (_gui.getGlobalScreen()->checkValueForm("transformationSpeed", speed, { }))
			{
				speed /= 1000.0f;
			}

			// Showing speed type
			string newTextContent = (currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] == AnimationSpeedType::LINEAR) ?
				"Speed: linear" : "Speed: exponential";
			_fe3d.textEntity_setTextContent(screen->getButton("speedType")->getTextfield()->getEntityID(), newTextContent);

			// Showing transformation type
			newTextContent = transType == TransformationType::TRANSLATION ? "Type: translation" :
				transType == TransformationType::ROTATION ? "Type: rotation" : "Type: scaling";
			_fe3d.textEntity_setTextContent(screen->getButton("transType")->getTextfield()->getEntityID(), newTextContent);

			// Check if a animation partname is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("parts");
			if (selectedButtonID != "")
			{
				// Check if LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Check if selected part exists on preview model
					if (_fe3d.modelEntity_hasPart(currentAnimation->previewModelID, selectedButtonID))
					{
						_currentPartName = selectedButtonID;
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