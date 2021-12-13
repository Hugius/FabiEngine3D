#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void BillboardEditor::_updateTexturingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "billboardEditorMenuTexturing")
	{
		// Temporary values
		auto textContent = _fe3d.billboard_getTextContent(_currentBillboardID);
		auto isTextual = _fe3d.billboard_isTextual(_currentBillboardID);
		auto hasDiffuseMap = _fe3d.billboard_hasDiffuseMap(_currentBillboardID);
		auto hasEmissionMap = _fe3d.billboard_hasEmissionMap(_currentBillboardID);
		auto textureRepeat = _fe3d.billboard_getTextureRepeat(_currentBillboardID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("font")->isHovered())
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\fonts\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "TTF");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set font
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearFontCache(finalFilePath);
			_fe3d.billboard_setFont(_currentBillboardID, finalFilePath);

			// Set default text
			if(textContent.empty())
			{
				_fe3d.billboard_setTextContent(_currentBillboardID, "text");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textContent")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textContent", "Text content", textContent, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\textures\\diffuse_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set diffuse map
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clear2dTextureCache(finalFilePath);
			_fe3d.billboard_setDiffuseMap(_currentBillboardID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("BillboardEditor::_updateTexturingMenu");
			}

			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\textures\\emission_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set emission map
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
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
			_gui.getGlobalScreen()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("textContent", textContent, {}))
		{
			_fe3d.billboard_setTextContent(_currentBillboardID, textContent);
		}
		if(_gui.getGlobalScreen()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d.billboard_setTextureRepeat(_currentBillboardID, textureRepeat);
		}

		// Update buttons hoverability
		screen->getButton("font")->setHoverable(!hasDiffuseMap || isTextual);
		screen->getButton("textContent")->setHoverable(isTextual);
		screen->getButton("diffuseMap")->setHoverable(!isTextual);
		screen->getButton("diffuseMap")->setHoverable(!isTextual);
		screen->getButton("clearMaps")->setHoverable((hasDiffuseMap && !isTextual) || hasEmissionMap);
		screen->getButton("textureRepeat")->setHoverable((hasDiffuseMap && !isTextual) || hasEmissionMap);
	}
}