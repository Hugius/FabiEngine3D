#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentTextId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->text2d_setWireframed(_currentTextId, !_fe3d->text2d_isWireframed(_currentTextId));
			}
		}
	}
}

void Text2dEditor::_updateTextCreating()
{
	if(_isCreatingText)
	{
		string newTextId;

		if(_gui->getOverlay()->checkValueForm("textCreate", newTextId, {_currentTextId}))
		{
			if(newTextId.find(' ') != string::npos)
			{
				Logger::throwWarning("Text id cannot contain any spaces!");
				return;
			}

			if(newTextId.find('@') != string::npos)
			{
				Logger::throwWarning("Text id cannot contain '@'!");
				return;
			}

			newTextId = ("@" + newTextId);

			if(find(_loadedTextIds.begin(), _loadedTextIds.end(), newTextId) != _loadedTextIds.end())
			{
				Logger::throwWarning("Text with id \"" + newTextId.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectId.empty())
			{
				Logger::throwError("Text2dEditor::_updateTextCreating");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\image\\entity\\text2d\\font_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				_isCreatingText = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				_isCreatingText = false;
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) && filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				_isCreatingText = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->text2d_create(newTextId, finalFilePath, true);

			if(_fe3d->text2d_isExisting(newTextId))
			{
				_fe3d->text2d_setPosition(newTextId, Tools::convertPositionToViewport(fvec2(0.0f)));
				_fe3d->text2d_setSize(newTextId, Tools::convertSizeToViewport(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));

				_currentTextId = newTextId;
				_loadedTextIds.push_back(newTextId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textId")->getEntityId(), "Text: " + newTextId.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
				_isCreatingText = false;
			}
		}
	}
}

void Text2dEditor::_updateTextChoosing()
{
	if(_isChoosingText)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("textList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredTextId.empty())
			{
				_hoveredTextId = ("@" + selectedButtonId);
				_fe3d->text2d_setVisible(_hoveredTextId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTextId = _hoveredTextId;
				_hoveredTextId = "";

				if(!_isDeletingText)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textId")->getEntityId(), "Text: " + selectedButtonId.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
				}

				_fe3d->text2d_setVisible(_currentTextId, true);
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
			if(!_hoveredTextId.empty())
			{
				_fe3d->text2d_setVisible(_hoveredTextId, false);
				_hoveredTextId = "";
			}
		}
	}
}

void Text2dEditor::_updateTextDeleting()
{
	if(_isDeletingText && !_currentTextId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->text2d_delete(_currentTextId);

			_loadedTextIds.erase(remove(_loadedTextIds.begin(), _loadedTextIds.end(), _currentTextId), _loadedTextIds.end());
			_currentTextId = "";
			_isDeletingText = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentTextId = "";
			_isDeletingText = false;
		}
	}
}