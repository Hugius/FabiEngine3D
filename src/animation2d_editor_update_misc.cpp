#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	if(!_currentAnimationId.empty())
	{
		if(!_fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD_ID, _currentAnimationId))
		{
			_fe3d->quad3d_setUvMultiplier(PREVIEW_QUAD_ID, fvec2(1.0f));
			_fe3d->quad3d_setUvOffset(PREVIEW_QUAD_ID, fvec2(0.0f));
		}
	}
}

void Animation2dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		string newAnimationId = "";

		if(_gui->getOverlay()->getValueFormId() == "animationCreate")
		{
			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				if(newAnimationId.empty())
				{
					Logger::throwWarning("Animation ID cannot be empty");
					return;
				}

				if(any_of(newAnimationId.begin(), newAnimationId.end(), isspace))
				{
					Logger::throwWarning("Animation ID cannot contain any spaces");
					return;
				}

				if(any_of(newAnimationId.begin(), newAnimationId.end(), isupper))
				{
					Logger::throwWarning("Animation ID cannot contain any capitals");
					return;
				}

				newAnimationId = ("@" + newAnimationId);

				if(find(_loadedAnimationIds.begin(), _loadedAnimationIds.end(), newAnimationId) != _loadedAnimationIds.end())
				{
					Logger::throwWarning("Animation already exists");
					return;
				}

				_currentAnimationId = newAnimationId;
				_loadedAnimationIds.push_back(newAnimationId);
				sort(_loadedAnimationIds.begin(), _loadedAnimationIds.end());

				_fe3d->animation2d_create(newAnimationId);

				_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, true);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");
				_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + newAnimationId);
				_gui->getOverlay()->getTextField("animationId")->setVisible(true);



				_isCreatingAnimation = false;
			}
		}
	}
}

void Animation2dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAnimationId = ("@" + selectedOptionId);

				if(_isDeletingAnimation)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

					_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, true);

					_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + _currentAnimationId.substr(1));
					_gui->getOverlay()->getTextField("animationId")->setVisible(true);
				}

				_isChoosingAnimation = false;


			}
		}
		//else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;


		}
	}
}

void Animation2dEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && !_isChoosingAnimation)
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

			_fe3d->animation2d_delete(_currentAnimationId);

			_loadedAnimationIds.erase(remove(_loadedAnimationIds.begin(), _loadedAnimationIds.end(), _currentAnimationId), _loadedAnimationIds.end());
			_currentAnimationId = "";
			_isDeletingAnimation = false;


		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAnimationId = "";
			_isDeletingAnimation = false;


		}
	}
}