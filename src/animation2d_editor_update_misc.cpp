#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	if(!_currentAnimationId.empty())
	{
		if(!isQuad3dAnimationStarted(_currentAnimationId, PREVIEW_QUAD_ID))
		{
			if(_isEditorLoaded)
			{
				_fe3d->quad3d_setUvMultiplier(PREVIEW_QUAD_ID, fvec2(1.0f));
				_fe3d->quad3d_setUvOffset(PREVIEW_QUAD_ID, fvec2(0.0f));
			}
		}
	}
}

void Animation2dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		string newAnimationId = "";

		if(_gui->getOverlay()->checkValueForm("animationCreate", newAnimationId, {_currentAnimationId}))
		{
			if(newAnimationId.find(' ') != string::npos)
			{
				Logger::throwWarning("Animation id cannot contain any spaces!");
				return;
			}

			if(newAnimationId.find('@') != string::npos)
			{
				Logger::throwWarning("Animation id cannot contain '@'!");
				return;
			}

			auto animationIds = getAnimationIds();
			if(find(animationIds.begin(), animationIds.end(), newAnimationId) != animationIds.end())
			{
				Logger::throwWarning("Animation id \"" + newAnimationId + "\" already exists!");
				return;
			}

			_animations.push_back(make_shared<Animation2d>(newAnimationId));

			_currentAnimationId = newAnimationId;

			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, true);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");
			_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationId")->getEntityId(), "Animation: " + newAnimationId, 0.025f);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), true);
			_isCreatingAnimation = false;
		}
	}
}

void Animation2dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("animationList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAnimationId = selectedButtonID;

				if(!_isDeletingAnimation)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

					_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, _getAnimation(_currentAnimationId)->getPreviewTexturePath());
					_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, true);

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationId")->getEntityId(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
		{
			_gui->getOverlay()->deleteChoiceForm("animationList");
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
		}
	}
}

void Animation2dEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && !_currentAnimationId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

			_deleteAnimation(_currentAnimationId);

			_currentAnimationId = "";
			_isDeletingAnimation = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentAnimationId = "";
			_isDeletingAnimation = false;
		}
	}
}