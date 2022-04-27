#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(!_currentQuad2dId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->quad2d_setWireframed(_currentQuad2dId, !_fe3d->quad2d_isWireframed(_currentQuad2dId));
			}
		}
	}
}

void Quad2dEditor::_updateQuadCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createQuad") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newQuad2dId = _gui->getOverlay()->getValueFormContent();

		if(newQuad2dId.empty())
		{
			Logger::throwWarning("Quad ID cannot be empty");

			return;
		}

		if(any_of(newQuad2dId.begin(), newQuad2dId.end(), isspace))
		{
			Logger::throwWarning("Quad ID cannot contain any spaces");

			return;
		}

		if(any_of(newQuad2dId.begin(), newQuad2dId.end(), isupper))
		{
			Logger::throwWarning("Quad ID cannot contain any capitals");

			return;
		}

		newQuad2dId = ("@" + newQuad2dId);

		if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newQuad2dId) != _loadedEntityIds.end())
		{
			Logger::throwWarning("Quad already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		_fe3d->quad2d_create(newQuad2dId, true);

		if(_fe3d->quad2d_isExisting(newQuad2dId))
		{
			_currentQuad2dId = newQuad2dId;
			_loadedEntityIds.push_back(newQuad2dId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_fe3d->quad2d_setPosition(newQuad2dId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->quad2d_setSize(newQuad2dId, Tools::convertSizeRelativeToDisplay(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");
			_gui->getOverlay()->getTextField("quad2dId")->setTextContent("Quad2D: " + newQuad2dId.substr(1));
			_gui->getOverlay()->getTextField("quad2dId")->setVisible(true);
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
			if(!_hoveredQuad2dId.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuad2dId, true);

				_hoveredQuad2dId = "";
			}
		}
		else
		{
			if(_hoveredQuad2dId.empty())
			{
				_hoveredQuad2dId = ("@" + selectedOptionId);

				_fe3d->quad2d_setVisible(_hoveredQuad2dId, false);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentQuad2dId = _hoveredQuad2dId;
				_hoveredQuad2dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteQuad")
				{
					_gui->getOverlay()->openAnswerForm("deleteQuad", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("quad2dId")->setTextContent("Quad2D: " + _currentQuad2dId.substr(1));
					_gui->getOverlay()->getTextField("quad2dId")->setVisible(true);
				}

				_fe3d->quad2d_setVisible(_currentQuad2dId, true);
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
			_fe3d->quad2d_delete(_currentQuad2dId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentQuad2dId), _loadedEntityIds.end());
			_currentQuad2dId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentQuad2dId = "";
		}
	}
}