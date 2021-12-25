#include "model_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void ModelEditor::_updateCamera()
{
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d.camera_getThirdPersonLookat();
		if(_fe3d.input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d.camera_setThirdPersonLookat(cameraLookat);

		_fe3d.image_setVisible("@@cursor", false);

		const auto distance = _fe3d.camera_getThirdPersonDistance();
		_fe3d.gfx_setShadowEyePosition(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d.gfx_setShadowCenterPosition(cameraLookat);
		_fe3d.gfx_setShadowSize(distance * 4.0f);
		_fe3d.gfx_setShadowReach(distance * 8.0f);
	}

	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getOverlay()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void ModelEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

		if(!_currentModelID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				for(const auto& partID : _fe3d.model_getPartIDs(_currentModelID))
				{
					if(_fe3d.model_isWireframed(_currentModelID, partID))
					{
						_fe3d.model_setWireframed(_currentModelID, partID, false);
					}
					else
					{
						_fe3d.model_setWireframed(_currentModelID, partID, true);
					}
				}
			}
		}
	}

	auto partID = (_hoveredPartID.empty() ? _currentPartID : _hoveredPartID);
	if(partID.empty())
	{
		_selectedPartHighlightDirection = 1; // Reset direction
	}
	else
	{
		const auto transparency = _fe3d.model_getTransparency(_currentModelID, partID);

		if(transparency == 0.0f)
		{
			_selectedPartHighlightDirection *= -1;
		}

		if(transparency == 1.0f)
		{
			_selectedPartHighlightDirection *= -1;
		}

		const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
		_fe3d.model_setTransparency(_currentModelID, partID, (transparency + speed));
	}
}

void ModelEditor::_updateModelCreating()
{
	if(_isCreatingModel)
	{
		string newModelID;

		if(_gui.getOverlay()->checkValueForm("modelCreate", newModelID, {}))
		{
			if(newModelID.find(' ') != string::npos)
			{
				Logger::throwWarning("Model ID cannot contain any spaces!");
				return;
			}

			if(newModelID.find('@') != string::npos)
			{
				Logger::throwWarning("Model ID cannot contain '@'!");
				return;
			}

			newModelID = ("@" + newModelID);

			if(find(_loadedModelIDs.begin(), _loadedModelIDs.end(), newModelID) != _loadedModelIDs.end())
			{
				Logger::throwWarning("Model with ID \"" + newModelID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateModelCreating");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\mesh\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				_isCreatingModel = false;
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "OBJ");
			if(filePath.empty())
			{
				_isCreatingModel = false;
				return;
			}

			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				_isCreatingModel = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearMeshCache(finalFilePath);
			_fe3d.model_create(newModelID, finalFilePath);

			if(_fe3d.model_isExisting(newModelID))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

				_currentModelID = newModelID;
				_loadedModelIDs.push_back(newModelID);

				_fe3d.text_setContent(_gui.getOverlay()->getTextField("modelID")->getEntityID(), "Model: " + newModelID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), true);
				_isCreatingModel = false;
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if(_isChoosingModel)
	{
		if(!_hoveredModelID.empty())
		{
			_fe3d.model_setVisible(_hoveredModelID, false);
		}

		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("modelList");

		if(!selectedButtonID.empty())
		{
			_hoveredModelID = ("@" + selectedButtonID);

			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentModelID = ("@" + selectedButtonID);
				_hoveredModelID = "";

				if(!_isDeletingModel)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("modelID")->getEntityID(), "Model: " + _currentModelID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), true);
				}

				_fe3d.model_setVisible(_currentModelID, true);
				_gui.getOverlay()->deleteChoiceForm("modelList");
				_isChoosingModel = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("modelList"))
		{
			_isChoosingModel = false;
			_isDeletingModel = false;
			_gui.getOverlay()->deleteChoiceForm("modelList");
		}
		else // Nothing hovered
		{
			_hoveredModelID = "";
		}

		if(!_hoveredModelID.empty())
		{
			_fe3d.model_setVisible(_hoveredModelID, true);
		}
	}
}

void ModelEditor::_updateModelDeleting()
{
	if(_isDeletingModel && !_currentModelID.empty())
	{
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d.model_delete(_currentModelID);
			_loadedModelIDs.erase(remove(_loadedModelIDs.begin(), _loadedModelIDs.end(), _currentModelID), _loadedModelIDs.end());
			_isDeletingModel = false;
			_currentModelID = "";
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d.model_setVisible(_currentModelID, false);
			_isDeletingModel = false;
			_currentModelID = "";
		}
	}
}

void ModelEditor::_updatePartChoosing()
{
	if(_isChoosingPart)
	{
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("partList");

		if(!selectedButtonID.empty())
		{
			_hoveredPartID = selectedButtonID;

			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentPartID = selectedButtonID;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen(_nextActiveScreenID);
				_fe3d.text_setContent(_gui.getOverlay()->getTextField("partID")->getEntityID(), ("Part: " + _currentPartID), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("partID")->getEntityID(), true);
				_gui.getOverlay()->deleteChoiceForm("partList");
				_hoveredPartID = "";
				_nextActiveScreenID = "";
				_isChoosingPart = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("partList"))
		{
			_isChoosingPart = false;
			_gui.getOverlay()->deleteChoiceForm("partList");
		}
		else
		{
			_hoveredPartID = "";
			for(const auto& partID : _fe3d.model_getPartIDs(_currentModelID))
			{
				_fe3d.model_setTransparency(_currentModelID, partID, 1.0f);
			}
		}
	}
}