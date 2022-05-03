#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createQuad2d", "Create Quad2D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto quad2dIds = _loadedQuad2dIds;

			for(auto & quad2dId : quad2dIds)
			{
				quad2dId = quad2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editQuad2d", "Edit Quad2D", fvec2(-0.5f, 0.1f), quad2dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto quad2dIds = _loadedQuad2dIds;

			for(auto & quad2dId : quad2dIds)
			{
				quad2dId = quad2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteQuad2d", "Delete Quad2D", fvec2(-0.5f, 0.1f), quad2dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveQuad2dsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Quad2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuChoice")
	{
		const auto color = _fe3d->quad2d_getColor(_currentQuad2dId);
		const auto opacity = _fe3d->quad2d_getOpacity(_currentQuad2dId);
		const auto textureRepeat = _fe3d->quad2d_getTextureRepeat(_currentQuad2dId);
		const auto isHorizontallyFlipped = _fe3d->quad2d_isHorizontallyFlipped(_currentQuad2dId);
		const auto isVerticallyFlipped = _fe3d->quad2d_isVerticallyFlipped(_currentQuad2dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad2d_setVisible(_currentQuad2dId, false);
			_gui->getOverlay()->getTextField("quad2dId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuMain");
			_currentQuad2dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\quad2d\\diffuse_map\\");

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
			_fe3d->quad2d_setDiffuseMap(_currentQuad2dId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isHorizontallyFlipped")->isHovered())
		{
			_fe3d->quad2d_setHorizontallyFlipped(_currentQuad2dId, !isHorizontallyFlipped);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isVerticallyFlipped")->isHovered())
		{
			_fe3d->quad2d_setVerticallyFlipped(_currentQuad2dId, !isVerticallyFlipped);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3((content / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3(color.r, (content / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3(color.r, color.g, (content / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad2d_setOpacity(_currentQuad2dId, (content / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad2d_setTextureRepeat(_currentQuad2dId, content);
		}

		screen->getButton("isHorizontallyFlipped")->setTextContent(isHorizontallyFlipped ? "Flipped X: ON" : "Flipped X: OFF");
		screen->getButton("isVerticallyFlipped")->setTextContent(isVerticallyFlipped ? "Flipped Y: ON" : "Flipped Y: OFF");
	}
}