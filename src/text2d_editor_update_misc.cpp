#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentTextID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->text2d_isWireframed(_currentTextID))
				{
					_fe3d->text2d_setWireframed(_currentTextID, false);
				}
				else
				{
					_fe3d->text2d_setWireframed(_currentTextID, true);
				}
			}
		}
	}
}

void Text2dEditor::_updateTextCreating()
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
				Logger::throwError("Text2dEditor::_updateTextCreating");
			}

			_fe3d->text2d_create(newTextID, true);

			if(_fe3d->text2d_isExisting(newTextID))
			{
				_fe3d->text2d_setPosition(newTextID, Tools::convertPositionToViewport(fvec2(0.0f)));
				_fe3d->text2d_setSize(newTextID, Tools::convertSizeToViewport(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));

				_currentTextID = newTextID;
				_loadedTextIDs.push_back(newTextID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text: " + newTextID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				_isCreatingText = false;
			}
		}
	}
}

void Text2dEditor::_updateTextChoosing()
{
	if(_isChoosingText)
	{
		if(!_hoveredTextID.empty())
		{
			_fe3d->text2d_setVisible(_hoveredTextID, false);
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
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text: " + selectedButtonID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				}

				_fe3d->text2d_setVisible(_currentTextID, true);
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
			_fe3d->text2d_setVisible(_hoveredTextID, true);
		}
	}
}

void Text2dEditor::_updateTextDeleting()
{
	if(_isDeletingText && !_currentTextID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->text2d_delete(_currentTextID);

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