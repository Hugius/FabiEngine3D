#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void BillboardEditor::_updateTexturingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "billboardEditorMenuTexturing")
	{
		auto textContent = _fe3d.billboard_getTextContent(_currentBillboardID);
		auto isTextual = _fe3d.billboard_isTextual(_currentBillboardID);
		auto hasDiffuseMap = _fe3d.billboard_hasDiffuseMap(_currentBillboardID);
		auto hasEmissionMap = _fe3d.billboard_hasEmissionMap(_currentBillboardID);
		auto textureRepeat = _fe3d.billboard_getTextureRepeat(_currentBillboardID);

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("font")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\font_map\\");

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
			_fe3d.billboard_setFont(_currentBillboardID, finalFilePath);

			if(textContent.empty())
			{
				_fe3d.billboard_setTextContent(_currentBillboardID, "text");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textContent")->isHovered())
		{
			_gui.getOverlay()->createValueForm("textContent", "Text content", textContent, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\diffuse_map\\");

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
			_fe3d.misc_clear2dTextureCache(finalFilePath);
			_fe3d.billboard_setDiffuseMap(_currentBillboardID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\emission_map\\");

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
			_fe3d.misc_clear2dTextureCache(finalFilePath);
			_fe3d.billboard_setEmissionMap(_currentBillboardID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.billboard_setDiffuseMap(_currentBillboardID, "");
			_fe3d.billboard_setEmissionMap(_currentBillboardID, "");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui.getOverlay()->checkValueForm("textContent", textContent, {}))
		{
			_fe3d.billboard_setTextContent(_currentBillboardID, textContent);
		}
		if(_gui.getOverlay()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d.billboard_setTextureRepeat(_currentBillboardID, textureRepeat);
		}

		screen->getButton("font")->setHoverable(!hasDiffuseMap || isTextual);
		screen->getButton("textContent")->setHoverable(isTextual);
		screen->getButton("diffuseMap")->setHoverable(!isTextual);
		screen->getButton("diffuseMap")->setHoverable(!isTextual);
		screen->getButton("clearMaps")->setHoverable((hasDiffuseMap && !isTextual) || hasEmissionMap);
		screen->getButton("textureRepeat")->setHoverable((hasDiffuseMap && !isTextual) || hasEmissionMap);
	}
}