#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(!_currentQuadId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->quad2d_setWireframed(_currentQuadId, !_fe3d->quad2d_isWireframed(_currentQuadId));
			}
		}
	}
}

void Quad2dEditor::_updateQuadCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createQuad") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newQuadId = _gui->getOverlay()->getValueFormContent();

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
		}
	}
}

void Quad2dEditor::_updateQuadChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editQuad") || (_gui->getOverlay()->getChoiceFormId() == "deleteQuad"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredQuadId.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuadId, true);

				_hoveredQuadId = "";
			}
		}
		else
		{
			if(_hoveredQuadId.empty())
			{
				_hoveredQuadId = ("@" + selectedOptionId);

				_fe3d->quad2d_setVisible(_hoveredQuadId, false);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentQuadId = _hoveredQuadId;
				_hoveredQuadId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteQuad")
				{
					_gui->getOverlay()->openAnswerForm("deleteQuad", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("quadId")->setTextContent("Quad2D: " + _currentQuadId.substr(1));
					_gui->getOverlay()->getTextField("quadId")->setVisible(true);
				}

				_fe3d->quad2d_setVisible(_currentQuadId, true);
			}
		}
	}
}

void Quad2dEditor::_updateQuadDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteQuad") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad2d_delete(_currentQuadId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentQuadId), _loadedEntityIds.end());
			_currentQuadId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentQuadId = "";
		}
	}
}