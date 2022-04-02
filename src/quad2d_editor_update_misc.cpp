#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(!_currentQuadId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->quad2d_setWireframed(_currentQuadId, !_fe3d->quad2d_isWireframed(_currentQuadId));
			}
		}
	}
}

void Quad2dEditor::_updateQuadCreating()
{
	if(_isCreatingQuad)
	{
		string newQuadId;

		if(_gui->getOverlay()->checkValueForm("quadCreate", newQuadId, {_currentQuadId}))
		{
			if(newQuadId.empty())
			{
				Logger::throwWarning("Quad ID cannot be empty");
				return;
			}

			if(any_of(newQuadId.begin(), newQuadId.end(), isspace))
			{
				Logger::throwWarning("Quad ID cannot contain any spaces");
				return;
			}

			if(!all_of(newQuadId.begin(), newQuadId.end(), isalnum))
			{
				Logger::throwWarning("Quad ID cannot contain any specials");
				return;
			}

			if(any_of(newQuadId.begin(), newQuadId.end(), isupper))
			{
				Logger::throwWarning("Quad ID cannot contain any capitals");
				return;
			}

			newQuadId = ("@" + newQuadId);

			if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newQuadId) != _loadedEntityIds.end())
			{
				Logger::throwWarning("Quad already exists");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			_fe3d->quad2d_create(newQuadId, true);

			if(_fe3d->quad2d_isExisting(newQuadId))
			{
				_currentQuadId = newQuadId;
				_loadedEntityIds.push_back(newQuadId);
				sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

				_fe3d->quad2d_setPosition(newQuadId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
				_fe3d->quad2d_setSize(newQuadId, Tools::convertSizeRelativeToDisplay(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");
				_gui->getOverlay()->getTextField("quadId")->setTextContent("Quad2D: " + newQuadId.substr(1));
				_gui->getOverlay()->getTextField("quadId")->setVisible(true);
				_isCreatingQuad = false;
			}
		}
	}
}

void Quad2dEditor::_updateQuadChoosing()
{
	if(_isChoosingQuad)
	{
		auto selectedButtonId = _gui->getOverlay()->getSelectedChoiceFormOptionId("quadList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredQuadId.empty())
			{
				_hoveredQuadId = ("@" + selectedButtonId);
				_fe3d->quad2d_setVisible(_hoveredQuadId, false);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadId = _hoveredQuadId;
				_hoveredQuadId = "";

				if(!_isDeletingQuad)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("quadId")->setTextContent("Quad2D: " + _currentQuadId.substr(1));
					_gui->getOverlay()->getTextField("quadId")->setVisible(true);
				}

				_fe3d->quad2d_setVisible(_currentQuadId, true);
				_gui->getOverlay()->disableChoiceForm("quadList");
				_isChoosingQuad = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("quadList"))
		{
			_gui->getOverlay()->disableChoiceForm("quadList");
			_isChoosingQuad = false;
			_isDeletingQuad = false;
		}
		else
		{
			if(!_hoveredQuadId.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuadId, true);
				_hoveredQuadId = "";
			}
		}
	}
}

void Quad2dEditor::_updateQuadDeleting()
{
	if(_isDeletingQuad && !_currentQuadId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormActive("delete"))
		{
			_gui->getOverlay()->enableAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormAccepted("delete"))
		{
			_fe3d->quad2d_delete(_currentQuadId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentQuadId), _loadedEntityIds.end());
			_currentQuadId = "";
			_isDeletingQuad = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentQuadId = "";
			_isDeletingQuad = false;
		}
	}
}