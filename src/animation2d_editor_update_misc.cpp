#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	if(!_currentAnimationID.empty())
	{
		if(!isBillboardAnimationStarted(_currentAnimationID, PREVIEW_BILLBOARD_ID))
		{
			if(_isEditorLoaded)
			{
				_fe3d->billboard_setUvMultiplier(PREVIEW_BILLBOARD_ID, fvec2(1.0f));
				_fe3d->billboard_setUvOffset(PREVIEW_BILLBOARD_ID, fvec2(0.0f));
			}
		}
	}
}

void Animation2dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		string newAnimationID = "";

		if(_gui->getOverlay()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			if(newAnimationID.find(' ') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain any spaces!");
				return;
			}

			if(newAnimationID.find('@') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain '@'!");
				return;
			}

			auto animationIDs = getAnimationIDs();
			if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) != animationIDs.end())
			{
				Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
				return;
			}

			_animations.push_back(make_shared<Animation2d>(newAnimationID));

			_currentAnimationID = newAnimationID;

			_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");
			_fe3d->text_setContent(_gui->getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationID")->getEntityID(), true);
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
				_currentAnimationID = selectedButtonID;

				if(!_isDeletingAnimation)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");
					_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _getAnimation(_currentAnimationID)->getPreviewTexturePath());
					_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, true);
					_fe3d->text_setContent(_gui->getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("animationID")->getEntityID(), true);
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
	if(_isDeletingAnimation && !_currentAnimationID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			_deleteAnimation(_currentAnimationID);

			_currentAnimationID = "";
			_isDeletingAnimation = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentAnimationID = "";
			_isDeletingAnimation = false;
		}
	}
}