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
		auto textContent = _fe3d.billboardEntity_getTextContent(_currentBillboardID);
		auto isText = _fe3d.billboardEntity_isText(_currentBillboardID);
		auto hasDiffuseMap = _fe3d.billboardEntity_hasDiffuseMap(_currentBillboardID);
		auto hasEmissionMap = _fe3d.billboardEntity_hasEmissionMap(_currentBillboardID);
		auto textureRepeat = _fe3d.billboardEntity_getTextureRepeat(_currentBillboardID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("font")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\fonts\\");

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
			_fe3d.billboardEntity_setFont(_currentBillboardID, finalFilePath);

			// Set default text
			if(textContent.empty())
			{
				_fe3d.billboardEntity_setTextContent(_currentBillboardID, "text");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textContent")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textContent", "Text content", textContent, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\diffuse_maps\\");

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
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\emission_maps\\");

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
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.billboardEntity_setEmissionMap(_currentBillboardID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, "");
			_fe3d.billboardEntity_setEmissionMap(_currentBillboardID, "");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("textContent", textContent, {}))
		{
			_fe3d.billboardEntity_setTextContent(_currentBillboardID, textContent);
		}
		if(_gui.getGlobalScreen()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d.billboardEntity_setTextureRepeat(_currentBillboardID, textureRepeat);
		}

		// Update buttons hoverability
		screen->getButton("font")->setHoverable(!hasDiffuseMap || isText);
		screen->getButton("textContent")->setHoverable(isText);
		screen->getButton("diffuseMap")->setHoverable(!isText);
		screen->getButton("diffuseMap")->setHoverable(!isText);
		screen->getButton("clearMaps")->setHoverable((hasDiffuseMap && !isText) || hasEmissionMap);
		screen->getButton("textureRepeat")->setHoverable((hasDiffuseMap && !isText) || hasEmissionMap);
	}
}