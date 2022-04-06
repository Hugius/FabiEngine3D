#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
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
			if(newTextId.empty())
			{
				Logger::throwWarning("Text ID cannot be empty");
				return;
			}

			if(any_of(newTextId.begin(), newTextId.end(), isspace))
			{
				Logger::throwWarning("Text ID cannot contain any spaces");
				return;
			}

			if(any_of(newTextId.begin(), newTextId.end(), isupper))
			{
				Logger::throwWarning("Text ID cannot contain any capitals");
				return;
			}

			newTextId = ("@" + newTextId);

			if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newTextId) != _loadedEntityIds.end())
			{
				Logger::throwWarning("Text already exists");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\text2d\\font_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				_isCreatingText = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				_isCreatingText = false;
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				_isCreatingText = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->text2d_create(newTextId, finalFilePath, true);

			if(_fe3d->text2d_isExisting(newTextId))
			{
				_currentTextId = newTextId;
				_loadedEntityIds.push_back(newTextId);
				sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

				_fe3d->text2d_setPosition(newTextId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
				_fe3d->text2d_setSize(newTextId, Tools::convertSizeRelativeToDisplay(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");
				_gui->getOverlay()->getTextField("textId")->setTextContent("Text: " + newTextId.substr(1));
				_gui->getOverlay()->getTextField("textId")->setVisible(true);
				_isCreatingText = false;
			}
		}
	}
}

void Text2dEditor::_updateTextChoosing()
{
	if(_isChoosingText)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredTextId.empty())
			{
				_hoveredTextId = ("@" + selectedOptionId);
				_fe3d->text2d_setVisible(_hoveredTextId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTextId = _hoveredTextId;
				_hoveredTextId = "";

				if(_isDeletingText)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("textId")->setTextContent("Text: " + _currentTextId.substr(1));
					_gui->getOverlay()->getTextField("textId")->setVisible(true);
				}

				_fe3d->text2d_setVisible(_currentTextId, true);

				_isChoosingText = false;
			}
		}
		//else if(_gui->getOverlay()->isChoiceFormCancelled())
		{

			_isChoosingText = false;
			_isDeletingText = false;
		}
		//else
		//{
		//	if(!_hoveredTextId.empty())
		//	{
		//		_fe3d->text2d_setVisible(_hoveredTextId, false);
		//		_hoveredTextId = "";
		//	}
		//}
	}
}

void Text2dEditor::_updateTextDeleting()
{
	if(_isDeletingText && !_isChoosingText)
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->text2d_delete(_currentTextId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentTextId), _loadedEntityIds.end());
			_currentTextId = "";
			_isDeletingText = false;


		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentTextId = "";
			_isDeletingText = false;


		}
	}
}