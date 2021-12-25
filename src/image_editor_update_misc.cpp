#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void ImageEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		if(!_currentImageID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.image_isWireframed(_currentImageID))
				{
					_fe3d.image_setWireframed(_currentImageID, false);
				}
				else
				{
					_fe3d.image_setWireframed(_currentImageID, true);
				}
			}
		}
	}
}

void ImageEditor::_updateImageCreating()
{
	if(_isCreatingImage)
	{
		string newImageID;

		if(_gui.getOverlay()->checkValueForm("imageCreate", newImageID, {_currentImageID}))
		{
			if(newImageID.find(' ') != string::npos)
			{
				Logger::throwWarning("Image ID cannot contain any spaces!");
				return;
			}

			if(newImageID.find('@') != string::npos)
			{
				Logger::throwWarning("Image ID cannot contain '@'!");
				return;
			}

			newImageID = ("@" + newImageID);

			if(find(_loadedImageIDs.begin(), _loadedImageIDs.end(), newImageID) != _loadedImageIDs.end())
			{
				Logger::throwWarning("Image with ID \"" + newImageID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("ImageEditor::_updateImageCreating");
			}

			_fe3d.image_create(newImageID, true);

			if(_fe3d.image_isExisting(newImageID))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuChoice");

				_currentImageID = newImageID;
				_loadedImageIDs.push_back(newImageID);

				_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

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
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("imageList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentImageID = ("@" + selectedButtonID);

				if(!_isDeletingImage)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuChoice");

					_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _fe3d.image_getDiffuseMapPath(_currentImageID));
					_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

					_fe3d.text_setContent(_gui.getOverlay()->getTextField("imageID")->getEntityID(), "Image: " + selectedButtonID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("imageID")->getEntityID(), true);
				}

				_gui.getOverlay()->deleteChoiceForm("imageList");
				_isChoosingImage = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("imageList"))
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
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("imageEditorMenuMain");

			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			_fe3d.image_delete(_currentImageID);
			_currentImageID = "";

			_loadedImageIDs.erase(remove(_loadedImageIDs.begin(), _loadedImageIDs.end(), _currentImageID), _loadedImageIDs.end());
			_isDeletingImage = false;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isChoosingImage = true;
			_currentImageID = "";
		}
	}
}