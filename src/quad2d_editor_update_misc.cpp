#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentQuadID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->quad2d_isWireframed(_currentQuadID))
				{
					_fe3d->quad2d_setWireframed(_currentQuadID, false);
				}
				else
				{
					_fe3d->quad2d_setWireframed(_currentQuadID, true);
				}
			}
		}
	}
}

void Quad2dEditor::_updateQuadCreating()
{
	if(_isCreatingQuad)
	{
		string newQuadID;

		if(_gui->getOverlay()->checkValueForm("quadCreate", newQuadID, {_currentQuadID}))
		{
			if(newQuadID.find(' ') != string::npos)
			{
				Logger::throwWarning("quad id cannot contain any spaces!");
				return;
			}

			if(newQuadID.find('@') != string::npos)
			{
				Logger::throwWarning("quad id cannot contain '@'!");
				return;
			}

			newQuadID = ("@" + newQuadID);

			if(find(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), newQuadID) != _loadedQuadIDs.end())
			{
				Logger::throwWarning("quad with id \"" + newQuadID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("Quad2dEditor::_updateQuadCreating");
			}

			_fe3d->quad2d_create(newQuadID, true);

			if(_fe3d->quad2d_isExisting(newQuadID))
			{
				_fe3d->quad2d_setPosition(newQuadID, Tools::convertPositionToViewport(fvec2(0.0f)));
				_fe3d->quad2d_setSize(newQuadID, Tools::convertSizeToViewport(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));

				_currentQuadID = newQuadID;
				_loadedQuadIDs.push_back(newQuadID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityId(), "Quad2D: " + newQuadID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityId(), true);
				_isCreatingQuad = false;
			}
		}
	}
}

void Quad2dEditor::_updateQuadChoosing()
{
	if(_isChoosingQuad)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("quadList");

		if(!selectedButtonID.empty())
		{
			if(_hoveredQuadID.empty())
			{
				_hoveredQuadID = ("@" + selectedButtonID);
				_fe3d->quad2d_setVisible(_hoveredQuadID, false);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadID = ("@" + selectedButtonID);
				_hoveredQuadID = "";

				if(!_isDeletingQuad)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityId(), "Quad2D: " + selectedButtonID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityId(), true);
				}

				_fe3d->quad2d_setVisible(_currentQuadID, true);
				_gui->getOverlay()->deleteChoiceForm("quadList");
				_isChoosingQuad = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("quadList"))
		{
			_gui->getOverlay()->deleteChoiceForm("quadList");
			_isChoosingQuad = false;
			_isDeletingQuad = false;
		}
		else
		{
			if(!_hoveredQuadID.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuadID, true);
				_hoveredQuadID = "";
			}
		}
	}
}

void Quad2dEditor::_updateQuadDeleting()
{
	if(_isDeletingQuad && !_currentQuadID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad2d_delete(_currentQuadID);

			_loadedQuadIDs.erase(remove(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), _currentQuadID), _loadedQuadIDs.end());
			_currentQuadID = "";
			_isDeletingQuad = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentQuadID = "";
			_isDeletingQuad = false;
		}
	}
}