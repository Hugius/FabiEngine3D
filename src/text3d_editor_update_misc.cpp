#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void Text3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));
		const auto lookatOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(-GRID_Y_OFFSET, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void Text3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentTextId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->text3d_setWireframed(_currentTextId, !_fe3d->text3d_isWireframed(_currentTextId));
			}
		}
	}
}

void Text3dEditor::_updateTextCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createText") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newTextId = _gui->getOverlay()->getValueFormContent();

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

		if(find(_loadedText3dIds.begin(), _loadedText3dIds.end(), newTextId) != _loadedText3dIds.end())
		{
			Logger::throwWarning("Text already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\text3d\\font_map\\");

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

		_fe3d->text3d_create(newTextId, finalFilePath, false);

		if(_fe3d->text3d_isExisting(newTextId))
		{
			_currentTextId = newTextId;
			_loadedText3dIds.push_back(newTextId);
			sort(_loadedText3dIds.begin(), _loadedText3dIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			_gui->getOverlay()->getTextField("textId")->setTextContent("Text3D: " + newTextId.substr(1));
			_gui->getOverlay()->getTextField("textId")->setVisible(true);
		}
	}
}

void Text3dEditor::_updateTextChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editText") || (_gui->getOverlay()->getChoiceFormId() == "deleteText"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredTextId.empty())
			{
				_fe3d->text3d_setVisible(_hoveredTextId, false);

				_hoveredTextId = "";
			}
		}
		else
		{
			if(_hoveredTextId.empty())
			{
				_hoveredTextId = ("@" + selectedOptionId);

				_fe3d->text3d_setVisible(_hoveredTextId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentTextId = _hoveredTextId;
				_hoveredTextId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteText")
				{
					_gui->getOverlay()->openAnswerForm("deleteText", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("textId")->setTextContent("Text3D: " + _currentTextId.substr(1));
					_gui->getOverlay()->getTextField("textId")->setVisible(true);
				}

				_fe3d->text3d_setVisible(_currentTextId, true);
			}
		}
	}
}

void Text3dEditor::_updateTextDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteText") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->text3d_delete(_currentTextId);

			_loadedText3dIds.erase(remove(_loadedText3dIds.begin(), _loadedText3dIds.end(), _currentTextId), _loadedText3dIds.end());
			_currentTextId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->text3d_setVisible(_currentTextId, false);

			_currentTextId = "";
		}
	}
}