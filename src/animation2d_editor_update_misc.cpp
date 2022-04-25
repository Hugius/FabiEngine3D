#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

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
	if((_gui->getOverlay()->getValueFormId() == "createAnimation") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newAnimationId = _gui->getOverlay()->getValueFormContent();

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
	}
}

void Animation2dEditor::_updateAnimationChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAnimation") || (_gui->getOverlay()->getChoiceFormId() == "deleteAnimation"))
	{
		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentAnimationId = ("@" + _gui->getOverlay()->getChoiceFormOptionId());

			if(_gui->getOverlay()->getChoiceFormId() == "deleteAnimation")
			{
				_gui->getOverlay()->openAnswerForm("deleteAnimation", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
			}
			else
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

				_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, true);

				_gui->getOverlay()->getTextField("animationId")->setTextContent("Animation: " + _currentAnimationId.substr(1));
				_gui->getOverlay()->getTextField("animationId")->setVisible(true);
			}
		}
	}
}

void Animation2dEditor::_updateAnimationDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAnimation") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

			_fe3d->animation2d_delete(_currentAnimationId);

			_loadedAnimationIds.erase(remove(_loadedAnimationIds.begin(), _loadedAnimationIds.end(), _currentAnimationId), _loadedAnimationIds.end());
			_currentAnimationId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAnimationId = "";
		}
	}
}

void Animation2dEditor::_updateImageChoosing()
{
	if(_gui->getOverlay()->getAnswerFormId() == "preview" && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto decision = ((_gui->getOverlay()->getAnswerFormDecision() == "Quad2D") ? "quad2d" : "quad3d");
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\" + decision + "\\diffuse_map\\");

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

		const string finalFilePath = filePath.substr(rootPath.size());
		_fe3d->misc_clearImageCache(finalFilePath);
		_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, finalFilePath);
		_isPreviewTextureChosen = true;
	}
}