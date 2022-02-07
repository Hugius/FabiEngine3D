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
		if(_fe3d->input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible("@@cursor", false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->gfx_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->gfx_setShadowLookatOffset(cameraLookat);
		_fe3d->gfx_setShadowSize(distance * 2.0f);
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

void Text3dEditor::_updateText3dCreating()
{
	if(_isCreatingText3d)
	{
		string newTextId;

		if(_gui->getOverlay()->checkValueForm("text3dCreate", newTextId, {_currentTextId}))
		{
			if(any_of(newTextId.begin(), newTextId.end(), isspace))
			{
				Logger::throwWarning("Text ID cannot contain any spaces");
				return;
			}

			if(!all_of(newTextId.begin(), newTextId.end(), isalnum))
			{
				Logger::throwWarning("Text ID cannot contain any specials");
				return;
			}

			if(any_of(newTextId.begin(), newTextId.end(), isupper))
			{
				Logger::throwWarning("Text ID cannot contain any capitals");
				return;
			}

			newTextId = ("@" + newTextId);

			if(find(_loadedTextIds.begin(), _loadedTextIds.end(), newTextId) != _loadedTextIds.end())
			{
				Logger::throwWarning("Text already exists");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\text3d\\font_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				_isCreatingText3d = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				_isCreatingText3d = false;
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) && filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				_isCreatingText3d = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->text3d_create(newTextId, finalFilePath, false);

			if(_fe3d->text3d_isExisting(newTextId))
			{
				_currentTextId = newTextId;
				_loadedTextIds.push_back(newTextId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
				_gui->getOverlay()->getTextField("textId")->changeTextContent("Text3D: " + newTextId.substr(1));
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
				_isCreatingText3d = false;
			}
		}
	}
}

void Text3dEditor::_updateText3dChoosing()
{
	if(_isChoosingText3d)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("text3dList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredTextId.empty())
			{
				_hoveredTextId = ("@" + selectedButtonId);
				_fe3d->text3d_setVisible(_hoveredTextId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTextId = _hoveredTextId;
				_hoveredTextId = "";

				if(!_isDeletingText3d)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("textId")->changeTextContent("Text3D: " + _currentTextId.substr(1));
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
				}

				_fe3d->text3d_setVisible(_currentTextId, true);
				_gui->getOverlay()->deleteChoiceForm("text3dList");
				_isChoosingText3d = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("text3dList"))
		{
			_gui->getOverlay()->deleteChoiceForm("text3dList");
			_isChoosingText3d = false;
			_isDeletingText3d = false;
		}
		else
		{
			if(!_hoveredTextId.empty())
			{
				_fe3d->text3d_setVisible(_hoveredTextId, false);
				_hoveredTextId = "";
			}
		}
	}
}

void Text3dEditor::_updateText3dDeleting()
{
	if(_isDeletingText3d && !_currentTextId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->text3d_delete(_currentTextId);

			_loadedTextIds.erase(remove(_loadedTextIds.begin(), _loadedTextIds.end(), _currentTextId), _loadedTextIds.end());
			_currentTextId = "";
			_isDeletingText3d = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->text3d_setVisible(_currentTextId, false);

			_currentTextId = "";
			_isDeletingText3d = false;
		}
	}
}