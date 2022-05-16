#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	if(!_currentAnimation2dId.empty())
	{
		if(!_fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD3D_ID, _currentAnimation2dId))
		{
			_fe3d->quad3d_setUvMultiplier(PREVIEW_QUAD3D_ID, fvec2(1.0f));
			_fe3d->quad3d_setUvOffset(PREVIEW_QUAD3D_ID, fvec2(0.0f));
		}
	}
}

void Animation2dEditor::_updateAnimation2dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createAnimation2d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newAnimation2dId = _gui->getOverlay()->getValueFormContent();

		if(newAnimation2dId.empty())
		{
			Logger::throwWarning("Animation2D ID cannot be empty");

			return;
		}

		if(any_of(newAnimation2dId.begin(), newAnimation2dId.end(), isspace))
		{
			Logger::throwWarning("Animation2D ID cannot contain any spaces");

			return;
		}

		if(any_of(newAnimation2dId.begin(), newAnimation2dId.end(), isupper))
		{
			Logger::throwWarning("Animation2D ID cannot contain any capitals");

			return;
		}

		newAnimation2dId = ("@" + newAnimation2dId);

		if(find(_loadedAnimation2dIds.begin(), _loadedAnimation2dIds.end(), newAnimation2dId) != _loadedAnimation2dIds.end())
		{
			Logger::throwWarning("Animation2D already exists");

			return;
		}

		_fe3d->animation2d_create(newAnimation2dId);

		_currentAnimation2dId = newAnimation2dId;

		_loadedAnimation2dIds.push_back(newAnimation2dId);

		sort(_loadedAnimation2dIds.begin(), _loadedAnimation2dIds.end());

		_fe3d->quad3d_setVisible(PREVIEW_QUAD3D_ID, true);

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

		_gui->getOverlay()->getTextField(ANIMATION2D_TITLE_ID)->setTextContent("Animation2D: " + newAnimation2dId);
		_gui->getOverlay()->getTextField(ANIMATION2D_TITLE_ID)->setVisible(true);
	}
}

void Animation2dEditor::_updateAnimation2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAnimation2d") || (_gui->getOverlay()->getChoiceFormId() == "deleteAnimation2d"))
	{
		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentAnimation2dId = ("@" + _gui->getOverlay()->getChoiceFormOptionId());

			if(_gui->getOverlay()->getChoiceFormId() == "deleteAnimation2d")
			{
				_gui->getOverlay()->openAnswerForm("deleteAnimation2d", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
			}
			else
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

				_fe3d->quad3d_setVisible(PREVIEW_QUAD3D_ID, true);

				_gui->getOverlay()->getTextField(ANIMATION2D_TITLE_ID)->setTextContent("Animation2D: " + _currentAnimation2dId.substr(1));
				_gui->getOverlay()->getTextField(ANIMATION2D_TITLE_ID)->setVisible(true);
			}
		}
	}
}

void Animation2dEditor::_updateAnimation2dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAnimation2d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->animation2d_delete(_currentAnimation2dId);

			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD3D_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD3D_ID, false);

			_loadedAnimation2dIds.erase(remove(_loadedAnimation2dIds.begin(), _loadedAnimation2dIds.end(), _currentAnimation2dId), _loadedAnimation2dIds.end());

			_currentAnimation2dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAnimation2dId = "";
		}
	}
}

void Animation2dEditor::_updateImageChoosing()
{
	if((_gui->getOverlay()->getAnswerFormId() == "preview") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto decision = ((_gui->getOverlay()->getAnswerFormDecision() == "Quad2D") ? "quad2d" : "quad3d");
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\" + decision + "\\diffuse_map\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const auto finalFilePath = filePath.substr(rootPath.size());

		_fe3d->misc_clearImageCache(finalFilePath);

		_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD3D_ID, finalFilePath);

		_isPreviewTextureChosen = true;
	}
}