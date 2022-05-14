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
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(0.0f, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
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
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_fe3d->model_setVisible(GRID_ID, !_fe3d->model_isVisible(GRID_ID));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible(BOX_ID, !_fe3d->model_isVisible(BOX_ID));
		}

		if(!_currentText3dId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->text3d_setWireframed(_currentText3dId, !_fe3d->text3d_isWireframed(_currentText3dId));
			}
		}
	}
}

void Text3dEditor::_updateText3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createText3d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newText3dId = _gui->getOverlay()->getValueFormContent();

		if(newText3dId.empty())
		{
			Logger::throwWarning("Text3D ID cannot be empty");

			return;
		}

		if(any_of(newText3dId.begin(), newText3dId.end(), isspace))
		{
			Logger::throwWarning("Text3D ID cannot contain any spaces");

			return;
		}

		if(any_of(newText3dId.begin(), newText3dId.end(), isupper))
		{
			Logger::throwWarning("Text3D ID cannot contain any capitals");

			return;
		}

		newText3dId = ("@" + newText3dId);

		if(find(_loadedText3dIds.begin(), _loadedText3dIds.end(), newText3dId) != _loadedText3dIds.end())
		{
			Logger::throwWarning("Text3D already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\text3d\\font_map\\");

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

		_fe3d->text3d_create(newText3dId, finalFilePath, false);

		if(_fe3d->text3d_isExisting(newText3dId))
		{
			_currentText3dId = newText3dId;
			_loadedText3dIds.push_back(newText3dId);
			sort(_loadedText3dIds.begin(), _loadedText3dIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			_gui->getOverlay()->getTextField("text3dId")->setTextContent("Text3D: " + newText3dId.substr(1));
			_gui->getOverlay()->getTextField("text3dId")->setVisible(true);
		}
	}
}

void Text3dEditor::_updateText3dChoosing()
{
	if(!_hoveredText3dId.empty())
	{
		_fe3d->text3d_setVisible(_hoveredText3dId, false);

		_hoveredText3dId = "";
	}

	if((_gui->getOverlay()->getChoiceFormId() == "editText3d") || (_gui->getOverlay()->getChoiceFormId() == "deleteText3d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredText3dId.empty())
			{
				_hoveredText3dId = ("@" + selectedOptionId);

				_fe3d->text3d_setVisible(_hoveredText3dId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentText3dId = _hoveredText3dId;
				_hoveredText3dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteText3d")
				{
					_gui->getOverlay()->openAnswerForm("deleteText3d", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("text3dId")->setTextContent("Text3D: " + _currentText3dId.substr(1));
					_gui->getOverlay()->getTextField("text3dId")->setVisible(true);
				}
			}
		}
	}
}

void Text3dEditor::_updateText3dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteText3d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->text3d_delete(_currentText3dId);

			_loadedText3dIds.erase(remove(_loadedText3dIds.begin(), _loadedText3dIds.end(), _currentText3dId), _loadedText3dIds.end());
			_currentText3dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->text3d_setVisible(_currentText3dId, false);

			_currentText3dId = "";
		}
	}
}