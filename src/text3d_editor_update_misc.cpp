#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void Text3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyDown(InputType::KEY_SPACEBAR))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyDown(InputType::KEY_SHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->graphics_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->graphics_setShadowLookatOffset(cameraLookat);
		_fe3d->graphics_setShadowSize(distance * 2.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
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
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentTextId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
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
			_loadedEntityIds.push_back(newTextId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

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

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentTextId), _loadedEntityIds.end());
			_currentTextId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->text3d_setVisible(_currentTextId, false);

			_currentTextId = "";
		}
	}
}