#include "text_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TextEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentTextID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->text_isWireframed(_currentTextID))
				{
					_fe3d->text_setWireframed(_currentTextID, false);
				}
				else
				{
					_fe3d->text_setWireframed(_currentTextID, true);
				}
			}
		}
	}
}

void TextEditor::_updateTextCreating()
{
	if(_isCreatingText)
	{
		string newTextID;

		if(_gui->getOverlay()->checkValueForm("textCreate", newTextID, {_currentTextID}))
		{
			if(newTextID.find(' ') != string::npos)
			{
				Logger::throwWarning("Text ID cannot contain any spaces!");
				return;
			}

			if(newTextID.find('@') != string::npos)
			{
				Logger::throwWarning("Text ID cannot contain '@'!");
				return;
			}

			newTextID = ("@" + newTextID);

			if(find(_loadedTextIDs.begin(), _loadedTextIDs.end(), newTextID) != _loadedTextIDs.end())
			{
				Logger::throwWarning("Text with ID \"" + newTextID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("TextEditor::_updateTextCreating");
			}

			_fe3d->text_create(newTextID, true);

			if(_fe3d->text_isExisting(newTextID))
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("textEditorMenuChoice");

				_currentTextID = newTextID;
				_loadedTextIDs.push_back(newTextID);

				_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

				_fe3d->text_setVisible(newTextID, false);
				_fe3d->text_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text: " + newTextID.substr(1), 0.025f);
				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				_isCreatingText = false;
			}
		}
	}
}

void TextEditor::_updateTextChoosing()
{
	if(_isChoosingText)
	{
		if(!_hoveredTextID.empty())
		{
			_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, false);
		}

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("textList");

		if(!selectedButtonID.empty())
		{
			_hoveredTextID = ("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTextID = ("@" + selectedButtonID);
				_hoveredTextID = "";

				if(!_isDeletingText)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("textEditorMenuChoice");

					_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _fe3d->text_getFontMapPath(_currentTextID));
					_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

					_fe3d->text_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text: " + selectedButtonID.substr(1), 0.025f);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("textList");
				_isChoosingText = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("textList"))
		{
			_gui->getOverlay()->deleteChoiceForm("textList");
			_isChoosingText = false;
			_isDeletingText = false;
		}
		else
		{
			_hoveredTextID = "";
		}

		if(!_hoveredTextID.empty())
		{
			_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _fe3d->text_getFontMapPath(_hoveredTextID));
			_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, true);
		}
	}
}

void TextEditor::_updateTextDeleting()
{
	if(_isDeletingText && !_currentTextID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			_fe3d->text_delete(_currentTextID);

			_loadedTextIDs.erase(remove(_loadedTextIDs.begin(), _loadedTextIDs.end(), _currentTextID), _loadedTextIDs.end());
			_currentTextID = "";
			_isDeletingText = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentTextID = "";
			_isDeletingText = false;
		}
	}
}