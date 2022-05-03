#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(!_currentText2dId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->text2d_setWireframed(_currentText2dId, !_fe3d->text2d_isWireframed(_currentText2dId));
			}
		}
	}
}

void Text2dEditor::_updateText2dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createText2d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newText2dId = _gui->getOverlay()->getValueFormContent();

		if(newText2dId.empty())
		{
			Logger::throwWarning("Text2D ID cannot be empty");

			return;
		}

		if(any_of(newText2dId.begin(), newText2dId.end(), isspace))
		{
			Logger::throwWarning("Text2D ID cannot contain any spaces");

			return;
		}

		if(any_of(newText2dId.begin(), newText2dId.end(), isupper))
		{
			Logger::throwWarning("Text2D ID cannot contain any capitals");

			return;
		}

		newText2dId = ("@" + newText2dId);

		if(find(_loadedText2dIds.begin(), _loadedText2dIds.end(), newText2dId) != _loadedText2dIds.end())
		{
			Logger::throwWarning("Text2D already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\text2d\\font_map\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");
		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const string finalFilePath = filePath.substr(rootPath.size());
		_fe3d->misc_clearImageCache(finalFilePath);

		_fe3d->text2d_create(newText2dId, finalFilePath, true);

		if(_fe3d->text2d_isExisting(newText2dId))
		{
			_currentText2dId = newText2dId;
			_loadedText2dIds.push_back(newText2dId);
			sort(_loadedText2dIds.begin(), _loadedText2dIds.end());

			_fe3d->text2d_setPosition(newText2dId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->text2d_setSize(newText2dId, Tools::convertSizeRelativeToDisplay(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");
			_gui->getOverlay()->getTextField("text2dId")->setTextContent("Text2D: " + newText2dId.substr(1));
			_gui->getOverlay()->getTextField("text2dId")->setVisible(true);
		}
	}
}

void Text2dEditor::_updateText2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editText2d") || (_gui->getOverlay()->getChoiceFormId() == "deleteText2d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredText2dId.empty())
			{
				_fe3d->text2d_setVisible(_hoveredText2dId, false);

				_hoveredText2dId = "";
			}
		}
		else
		{
			if(_hoveredText2dId.empty())
			{
				_hoveredText2dId = ("@" + selectedOptionId);

				_fe3d->text2d_setVisible(_hoveredText2dId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentText2dId = _hoveredText2dId;
				_hoveredText2dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteText2d")
				{
					_gui->getOverlay()->openAnswerForm("deleteText2d", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("text2dId")->setTextContent("Text2D: " + _currentText2dId.substr(1));
					_gui->getOverlay()->getTextField("text2dId")->setVisible(true);
				}

				_fe3d->text2d_setVisible(_currentText2dId, true);
			}
		}
	}
}

void Text2dEditor::_updateText2dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteText2d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->text2d_delete(_currentText2dId);

			_loadedText2dIds.erase(remove(_loadedText2dIds.begin(), _loadedText2dIds.end(), _currentText2dId), _loadedText2dIds.end());
			_currentText2dId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentText2dId = "";
		}
	}
}