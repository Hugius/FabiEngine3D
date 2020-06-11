#include <fstream>
#include <sstream>

#include "billboard_editor.hpp"

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::initializeGUI()
{
	// Private window instance of left viewport
	_window = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardManagement
	_window->addScreen("billboardManagement");
	_window->getScreen("billboardManagement")->addButton("addBillboard", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Add model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardManagement")->addButton("editBillboard", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardManagement")->addButton("deleteBillboard", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Delete model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingMain
	_window->addScreen("billboardEditingMain");
	_window->getScreen("billboardEditingMain")->addButton("mesh", vec2(0.0f, 0.7f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMain")->addButton("appearance", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Appearance", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMain")->addButton("animation", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Animation", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMain")->addButton("text", vec2(0.0f, -0.35f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Text", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMain")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - billboardEditingMesh
	_window->addScreen("billboardEditingMesh");
	_window->getScreen("billboardEditingMesh")->addButton("size", vec2(0.0f, 0.63f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Size", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMesh")->addButton("facingX", vec2(0.0f, 0.21), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Facing X: OFF", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMesh")->addButton("facingY", vec2(0.0f, -0.21), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Facing Y: OFF", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingMesh")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - billboardEditingAppearance
	_window->addScreen("billboardEditingAppearance");
	_window->getScreen("billboardEditingAppearance")->addButton("color", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Color", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAppearance")->addButton("texture", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Texture", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAppearance")->addButton("transparent", vec2(0.0f, -0.21), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "No-white: OFF", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAppearance")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - billboardEditingAnimation
	_window->addScreen("billboardEditingAnimation");
	_window->getScreen("billboardEditingAnimation")->addButton("rows", vec2(0.0f, 0.7f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Rows", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAnimation")->addButton("columns", vec2(0.0f, 0.35f), vec2(1.1f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Columns", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAnimation")->addButton("speed", vec2(0.0f, 0.0f), vec2(1.3f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Frame step", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAnimation")->addButton("animate", vec2(0.0f, -0.35f), vec2(1.7f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Animate", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingAnimation")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingText
	_window->addScreen("billboardEditingText");
	_window->getScreen("billboardEditingText")->addButton("color", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Color", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingText")->addButton("font", vec2(0.0f, 0.21), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Font", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingText")->addButton("content", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Content", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("billboardEditingText")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void BillboardEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, _defaultCameraPosition, -90.0f, 0.0f);
	_fe3d.camera_enableLookat(_billboardPosition);

	// Graphics
	_fe3d.gfx_enableAmbientLighting(0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableSceneReflections(0.0f, 0.25f);
	_fe3d.gfx_enableSpecularLighting(16.0f);
	_fe3d.gfx_enableShadows(vec3(25.0f), vec3(0.0f), 50.0f, 50.0f);
	
	// 3D Environment
	_fe3d.gameEntity_add("@grid", "Engine\\OBJs\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@grid", "Engine\\Textures\\metal.png");
	_fe3d.gameEntity_setUvRepeat("@grid", 25.0f);
	_fe3d.gameEntity_setSceneReflective("@grid", true);
	_fe3d.gameEntity_setSpecularLighted("@grid", true);
	_fe3d.gameEntity_add("@cube", "Engine\\OBJs\\cube.obj", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@cube", "Engine\\Textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@cube", true);
	string path = "Engine\\Textures\\";
	_fe3d.skyEntity_add("@sky", { path + "right.png", path + "left.png", path + "top.png", path + "bottom.png", path + "back.png", path + "front.png" });
	_fe3d.skyEntity_setRotationSpeed("@sky", 0.1f);
	_fe3d.skyEntity_select("@sky");

	// Other
	_gui->getGlobalScreen()->addTextfield("currentBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_isLoaded = true;

	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Create or overwrite billboards file
	std::ifstream file(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\billboards.fe3d");
	string line;

	// Read model data
	while (std::getline(file, line))
	{
		// Placeholder variables
		string name, diffusePath, fontPath, content;
		vec2 size;
		vec3 color;
		bool facingX, facingY, transparent, playing;
		int rows, columns, framestep;

		// For item extraction
		std::istringstream iss(line);

		// Extract from file
		iss >> size.x >> size.y >> color.r >> color.g >> color.b >> facingX >> facingY >> diffusePath >>
			transparent >> fontPath >> content >> playing >> rows >> columns >> framestep;

		// Run checks on string values
		diffusePath = (diffusePath == "-") ? "" : diffusePath;
		fontPath = (fontPath == "-") ? "" : fontPath;
		content = (content == "-") ? "" : content;

		// If billboard name not existing yet
		if (std::find(_billboardNames.begin(), _billboardNames.end(), name) == _billboardNames.end())
		{
			// Add billboard name
			_billboardNames.push_back(name);

			// Check if billboard has a diffuse map
			if (diffusePath != "")
			{
				// Animation aspects
				_fe3d.billboardEntity_setAnimationFramestep(name, framestep);
				_fe3d.billboardEntity_setAnimationRows(name, rows);
				_fe3d.billboardEntity_setAnimationColumns(name, columns);

				// Playing sprite animation
				if (playing)
				{
					_fe3d.billBoardEntity_playSpriteAnimation(name, -1);
				}
			}
			else if (content != "")
			{
				_fe3d.billBoardEntity_add(name, content, fontPath, color, _billboardPosition, vec3(0.0f), size, facingX, facingY);
			}
			else
			{
				_fe3d.billBoardEntity_add(name, color, _billboardPosition, vec3(0.0f), size, facingX, facingY);
			}
		}
	}

	// Close file
	file.close();

	// Logging
	_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" saved!");
}

void BillboardEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite billboards file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\billboards.fe3d");

		// Write billboard data into file
		for (auto& billboardName : _billboardNames)
		{
			file << billboardName
				<< " " << _fe3d.billboardEntity_getSize(billboardName).x << " " << _fe3d.billboardEntity_getSize(billboardName).y
				<< " " << _fe3d.billboardEntity_getColor(billboardName).r << " " << _fe3d.billboardEntity_getColor(billboardName).g
				<< " " << _fe3d.billboardEntity_getColor(billboardName).b << " " << _fe3d.billboardEntity_isFacingCameraX(billboardName)
				<< " " << _fe3d.billboardEntity_isFacingCameraY(billboardName) << " " << _fe3d.billboardEntity_getDiffuseMapPath(billboardName)
				<< " " << _fe3d.billboardEntity_isTransparent(billboardName) << " " << _fe3d.billboardEntity_getFontPath(billboardName)
				<< " " << _fe3d.billboardEntity_getTextContent(billboardName) << " " << _fe3d.billboardEntity_isAnimationPlaying(billboardName)
				<< " " << _fe3d.billboardEntity_getAnimationRows(billboardName) << " " << _fe3d.billboardEntity_getAnimationColumns(billboardName)
				<< " " << _fe3d.billboardEntity_getAnimationFramestep(billboardName);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" saved!");
	}
}

void BillboardEditor::unload()
{
	// Graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableSceneReflections();
	_fe3d.gfx_disableSpecularLighting();

	// 3D environment
	_fe3d.gameEntity_delete("@grid");
	_fe3d.gameEntity_delete("@cube");
	_fe3d.skyEntity_delete("@sky");

	// Delete models
	for (auto& billboardName : _billboardNames)
	{
		if (_fe3d.billboardEntity_isExisting(billboardName))
		{
			_fe3d.billboardEntity_delete(billboardName);
		}
	}
	_billboardNames.clear();

	// Delete model name textfield & scrolling list buttons
	_gui->getGlobalScreen()->deleteTextfield("currentBillboardName");

	// Other
	_isLoaded = false;
}
