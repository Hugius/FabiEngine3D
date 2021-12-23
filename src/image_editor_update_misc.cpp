#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void ImageEditor::_updateImageCreating()
{
	if(_isCreatingImage)
	{
		// Temporary values
		string newImageID;

		// Check if user filled in a new ID
		if(_gui.getOverlay()->checkValueForm("imageCreate", newImageID, {_currentImageID}))
		{
			// Spaces not allowed
			if(newImageID.find(' ') != string::npos)
			{
				Logger::throwWarning("Image ID cannot contain any spaces!");
				return;
			}

			// @ sign not allowed
			if(newImageID.find('@') != string::npos)
			{
				Logger::throwWarning("Image ID cannot contain '@'!");
				return;
			}

			// Add @ sign to new ID
			newImageID = ("@" + newImageID);

			// Check if image already exists
			if(find(_loadedImageIDs.begin(), _loadedImageIDs.end(), newImageID) != _loadedImageIDs.end())
			{
				Logger::throwWarning("Image with ID \"" + newImageID.substr(1) + "\" already exists!");
				return;
			}

			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("ImageEditor::_updateImageCreating");
			}

			// Create image
			_fe3d.image_create(newImageID, true);

			// Check if image creation went well
			if(_fe3d.image_isExisting(newImageID))
			{
				// Go to next screen
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuChoice");

				// Select image
				_currentImageID = newImageID;
				_loadedImageIDs.push_back(newImageID);

				// Miscellaneous
				_fe3d.image_setVisible(newImageID, false);
				_fe3d.text_setContent(_gui.getOverlay()->getTextField("imageID")->getEntityID(), "Image: " + newImageID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("imageID")->getEntityID(), true);
				_isCreatingImage = false;
			}
		}
	}
}

void ImageEditor::_updateImageChoosing()
{
	if(_isChoosingImage)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("imageList");

		// Check if image ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select image
				_currentImageID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingImage)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuChoice");
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("imageID")->getEntityID(), "Image: " + selectedButtonID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("imageID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getOverlay()->deleteChoiceForm("imageList");
				_isChoosingImage = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("imageList")) // Cancelled choosing
		{
			_isChoosingImage = false;
			_isDeletingImage = false;
			_gui.getOverlay()->deleteChoiceForm("imageList");
		}
	}
}

void ImageEditor::_updateImageDeleting()
{
	if(_isDeletingImage && !_currentImageID.empty())
	{
		// Add answer form
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuMain");

			// Delete image
			if(_fe3d.image_isExisting(_currentImageID))
			{
				_fe3d.image_delete(_currentImageID);
			}

			// Miscellaneous
			_loadedImageIDs.erase(remove(_loadedImageIDs.begin(), _loadedImageIDs.end(), _currentImageID), _loadedImageIDs.end());
			_currentImageID = "";
			_isDeletingImage = false;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isChoosingImage = true;
			_currentImageID = "";
		}
	}
}