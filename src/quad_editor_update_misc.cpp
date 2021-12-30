#include "quad_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void QuadEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		if(!_currentQuadID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.quad_isWireframed(_currentQuadID))
				{
					_fe3d.quad_setWireframed(_currentQuadID, false);
				}
				else
				{
					_fe3d.quad_setWireframed(_currentQuadID, true);
				}
			}
		}
	}
}

void QuadEditor::_updateQuadCreating()
{
	if(_isCreatingQuad)
	{
		string newQuadID;

		if(_gui.getOverlay()->checkValueForm("quadCreate", newQuadID, {_currentQuadID}))
		{
			if(newQuadID.find(' ') != string::npos)
			{
				Logger::throwWarning("Quad ID cannot contain any spaces!");
				return;
			}

			if(newQuadID.find('@') != string::npos)
			{
				Logger::throwWarning("Quad ID cannot contain '@'!");
				return;
			}

			newQuadID = ("@" + newQuadID);

			if(find(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), newQuadID) != _loadedQuadIDs.end())
			{
				Logger::throwWarning("Quad with ID \"" + newQuadID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("QuadEditor::_updateQuadCreating");
			}

			_fe3d.quad_create(newQuadID, true);

			if(_fe3d.quad_isExisting(newQuadID))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("quadEditorMenuChoice");

				_currentQuadID = newQuadID;
				_loadedQuadIDs.push_back(newQuadID);

				_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

				_fe3d.quad_setVisible(newQuadID, false);
				_fe3d.text_setContent(_gui.getOverlay()->getTextField("quadID")->getEntityID(), "Quad: " + newQuadID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("quadID")->getEntityID(), true);
				_isCreatingQuad = false;
			}
		}
	}
}

void QuadEditor::_updateQuadChoosing()
{
	if(_isChoosingQuad)
	{
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("quadList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadID = ("@" + selectedButtonID);

				if(!_isDeletingQuad)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("quadEditorMenuChoice");

					_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _fe3d.quad_getDiffuseMapPath(_currentQuadID));
					_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

					_fe3d.text_setContent(_gui.getOverlay()->getTextField("quadID")->getEntityID(), "Quad: " + selectedButtonID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("quadID")->getEntityID(), true);
				}

				_gui.getOverlay()->deleteChoiceForm("quadList");
				_isChoosingQuad = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("quadList"))
		{
			_isChoosingQuad = false;
			_isDeletingQuad = false;
			_gui.getOverlay()->deleteChoiceForm("quadList");
		}
	}
}

void QuadEditor::_updateQuadDeleting()
{
	if(_isDeletingQuad && !_currentQuadID.empty())
	{
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("quadEditorMenuMain");

			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			_fe3d.quad_delete(_currentQuadID);
			_currentQuadID = "";

			_loadedQuadIDs.erase(remove(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), _currentQuadID), _loadedQuadIDs.end());
			_isDeletingQuad = false;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isChoosingQuad = true;
			_currentQuadID = "";
		}
	}
}