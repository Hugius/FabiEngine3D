#include "sprite_animation_editor.hpp"
#include "logger.hpp"

void SpriteAnimationEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool SpriteAnimationEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string> SpriteAnimationEditor::getAllAnimationIDs()
{
	vector<string> result;

	// Find all IDs
	for(const auto& animation : _animations)
	{
		result.push_back(animation->getID());
	}

	// Sort alphabetically
	sort(result.begin(), result.end());

	return result;
}

void SpriteAnimationEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("SpriteAnimationEditor::_deleteAnimation");
}

shared_ptr<SpriteAnimation> SpriteAnimationEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("SpriteAnimationEditor::_getAnimation");
}

const bool SpriteAnimationEditor::isAnimationExisting(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

const bool SpriteAnimationEditor::isAnimationStarted(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation does not exist
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, billboardID)) != _startedAnimations.end();
	}

	return false;
}

const bool SpriteAnimationEditor::isAnimationPlaying(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}

const bool SpriteAnimationEditor::isAnimationPaused(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}

void SpriteAnimationEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		// Check if user filled in a new ID
		string newAnimationID = "";
		if(_gui.getGlobalScreen()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			// @ sign not allowed
			if(newAnimationID.find('@') == string::npos)
			{
				// Spaces not allowed
				if(newAnimationID.find(' ') == string::npos)
				{
					// Check if animation already exists
					auto animationIDs = getAllAnimationIDs();
					if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) == animationIDs.end())
					{
						// Go to next screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuChoice");

						// Create animation
						_animations.push_back(make_shared<SpriteAnimation>(newAnimationID));

						// Select animation
						_currentAnimationID = newAnimationID;

						// Miscellaneous
						_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
						_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);
						_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
						_isCreatingAnimation = false;
					}
					else
					{
						Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Animation ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Animation ID cannot contain '@'!");
			}
		}
	}
}

void SpriteAnimationEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");

		// Check if a animation ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select animation
				_currentAnimationID = selectedButtonID;

				// Go to next screen
				if(!_isDeletingAnimation)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _getAnimation(_currentAnimationID)->getPreviewTexturePath());
				_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
		{
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
			_gui.getGlobalScreen()->deleteChoiceForm("animationList");
		}
	}
}

void SpriteAnimationEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && _currentAnimationID != "")
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuMain");

			// Delete animation
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);
			_deleteAnimation(_currentAnimationID);
			_currentAnimationID = "";

			// Miscellaneous
			_isDeletingAnimation = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}