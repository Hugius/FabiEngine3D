#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_updateMainAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			_fe3d->misc_disableAabbFrameRendering();
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("aabbCreate", "Create AABB", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = _fe3d->aabb_getChildIDs(_currentModelID, AabbParentEntityType::MODEL);
			for(auto& id : IDs)
			{
				id = id.substr(string(_currentModelID + "@").size());
			}
			sort(IDs.begin(), IDs.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Edit AABB", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = _fe3d->aabb_getChildIDs(_currentModelID, AabbParentEntityType::MODEL);
			for(auto& id : IDs)
			{
				id = id.substr(string(_currentModelID + "@").size());
			}
			sort(IDs.begin(), IDs.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Delete AABB", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingAabb = true;
			_isDeletingAabb = true;
		}
	}
}

void ModelEditor::_updateChoiceAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbChoice")
	{
		auto position = _fe3d->aabb_getPosition(_currentModelID + "@" + _currentAabbID);
		auto size = _fe3d->aabb_getSize(_currentModelID + "@" + _currentAabbID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible((_currentModelID + "@" + _currentAabbID), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbID")->getEntityID(), false);
			_currentAabbID = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->createValueForm("positionX", "X", (position.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionY", "Y", (position.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionZ", "Z", (position.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			position.x /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelID + "@" + _currentAabbID), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			position.y /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelID + "@" + _currentAabbID), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			position.z /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelID + "@" + _currentAabbID), position);
		}
		if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelID + "@" + _currentAabbID), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelID + "@" + _currentAabbID), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelID + "@" + _currentAabbID), size);
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if(_isCreatingAabb)
	{
		string newAabbID;

		if(_gui->getOverlay()->checkValueForm("aabbCreate", newAabbID, {}))
		{
			if(newAabbID.find(' ') != string::npos)
			{
				Logger::throwWarning("AABB id cannot contain any spaces!");
				return;
			}

			if(newAabbID.find('@') != string::npos)
			{
				Logger::throwWarning("AABB id cannot contain '@'!");
				return;
			}

			if(_fe3d->aabb_isExisting(_currentModelID + "@" + newAabbID))
			{
				Logger::throwWarning("AABB with id \"" + newAabbID + "\" already exists!");
				return;
			}

			_currentAabbID = newAabbID;

			_fe3d->aabb_create(_currentModelID + "@" + _currentAabbID, false);
			_fe3d->aabb_setFollowParentVisibility((_currentModelID + "@" + _currentAabbID), false);
			_fe3d->aabb_setParentEntityID((_currentModelID + "@" + _currentAabbID), _currentModelID);
			_fe3d->aabb_setParentEntityType((_currentModelID + "@" + _currentAabbID), AabbParentEntityType::MODEL);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");
			_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("aabbID")->getEntityID(), ("AABB: " + _currentAabbID), 0.025f);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbID")->getEntityID(), true);

			_isCreatingAabb = false;
		}
	}
}

void ModelEditor::_updateAabbChoosing()
{
	if(_isChoosingAabb)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("aabbList");

		if(!selectedButtonID.empty())
		{
			if(_hoveredAabbID.empty())
			{
				_hoveredAabbID = selectedButtonID;
				_fe3d->aabb_setVisible((_currentModelID + "@" + _hoveredAabbID), true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAabbID = selectedButtonID;
				_hoveredAabbID = "";

				if(!_isDeletingAabb)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("aabbID")->getEntityID(), ("AABB: " + _currentAabbID), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbID")->getEntityID(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("aabbList");
				_isChoosingAabb = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("aabbList"))
		{
			_gui->getOverlay()->deleteChoiceForm("aabbList");
			_isChoosingAabb = false;
			_isDeletingAabb = false;
		}
		else
		{
			if(!_hoveredAabbID.empty())
			{
				_fe3d->aabb_setVisible((_currentModelID + "@" + _hoveredAabbID), false);
				_hoveredAabbID = "";
			}
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if(_isDeletingAabb && !_currentAabbID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->aabb_delete(_currentModelID + "@" + _currentAabbID);
			_isDeletingAabb = false;
			_currentAabbID = "";
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingAabb = false;
			_currentAabbID = "";
		}
	}
}