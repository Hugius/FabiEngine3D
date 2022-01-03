#include "quad_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void QuadEditor::_updateMainMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "quadEditorMenuMain")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getOverlay()->createValueForm("quadCreate", "Create Quad", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingQuad = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("quadList", "Edit Quad", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingQuad = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("quadList", "Delete Quad", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingQuad = true;
			_isDeletingQuad = true;
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void QuadEditor::_updateChoiceMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "quadEditorMenuChoice")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setWireframed(PREVIEW_BILLBOARD_ID, false);
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			_currentQuadID = "";
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("quadID")->getEntityID(), false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("quadEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("QuadEditor::_updateChoiceMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\quad\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d.misc_clearImageCache(finalFilePath);
			_fe3d.quad_setDiffuseMap(_currentQuadID, finalFilePath);
		}
	}
}