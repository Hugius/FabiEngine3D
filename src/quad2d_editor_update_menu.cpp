#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("quadCreate", "Create Quad2D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
			_isCreatingQuad = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("quadList", "Edit Quad2D", fvec2(-0.5f, 0.1f), ids);
			_isChoosingQuad = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("quadList", "Delete Quad2D", fvec2(-0.5f, 0.1f), ids);
			_isChoosingQuad = true;
			_isDeletingQuad = true;
		}

		if(_gui->getOverlay()->isAnswerFormAccepted())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveEntitiesToFile();
			unload();

			_gui->getOverlay()->closeAnswerForm();
		}
		if(_gui->getOverlay()->isAnswerFormDenied())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();

			_gui->getOverlay()->closeAnswerForm();
		}
	}
}

void Quad2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuChoice")
	{
		auto color = _fe3d->quad2d_getColor(_currentQuadId);
		auto opacity = _fe3d->quad2d_getOpacity(_currentQuadId);
		auto textureRepeat = _fe3d->quad2d_getTextureRepeat(_currentQuadId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad2d_setVisible(_currentQuadId, false);
			_gui->getOverlay()->getTextField("quadId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuMain");
			_currentQuadId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\quad2d\\diffuse_map\\");

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
			_fe3d->quad2d_setDiffuseMap(_currentQuadId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			//_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			//_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->quad2d_setColor(_currentQuadId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->quad2d_setColor(_currentQuadId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->quad2d_setColor(_currentQuadId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("opacity", opacity, {}))
		{
			opacity /= 100.0f;
			_fe3d->quad2d_setOpacity(_currentQuadId, opacity);
		}
		//if(_gui->getOverlay()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d->quad2d_setTextureRepeat(_currentQuadId, textureRepeat);
		}
	}
}