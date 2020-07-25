#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardManagement
	_leftWindow->addScreen("billboardEditorMenu");
	_leftWindow->getScreen("billboardEditorMenu")->addButton("addBillboard", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Add board", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenu")->addButton("editBillboard", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit board", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenu")->addButton("deleteBillboard", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Delete board", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingMain
	_leftWindow->addScreen("billboardEditingMain");
	_leftWindow->getScreen("billboardEditingMain")->addButton("mesh", vec2(0.0f, 0.7f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMain")->addButton("appearance", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Appearance", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMain")->addButton("animation", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Animation", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMain")->addButton("text", vec2(0.0f, -0.35f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Text", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMain")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingMesh
	_leftWindow->addScreen("billboardEditingMesh");
	_leftWindow->getScreen("billboardEditingMesh")->addButton("size", vec2(0.0f, 0.63f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMesh")->addButton("facingX", vec2(0.0f, 0.21), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Facing X: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMesh")->addButton("facingY", vec2(0.0f, -0.21), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Facing Y: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingMesh")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAppearance
	_leftWindow->addScreen("billboardEditingAppearance");
	_leftWindow->getScreen("billboardEditingAppearance")->addButton("color", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAppearance")->addButton("texture", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAppearance")->addButton("isTransparent", vec2(0.0f, -0.21), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "No-white: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAppearance")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAnimation
	_leftWindow->addScreen("billboardEditingAnimation");
	_leftWindow->getScreen("billboardEditingAnimation")->addButton("rows", vec2(0.0f, 0.7f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Rows", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAnimation")->addButton("columns", vec2(0.0f, 0.35f), vec2(1.1f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Columns", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAnimation")->addButton("speed", vec2(0.0f, 0.0f), vec2(1.3f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Frame step", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAnimation")->addButton("animate", vec2(0.0f, -0.35f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Animate", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingAnimation")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingText
	_leftWindow->addScreen("billboardEditingText");
	_leftWindow->getScreen("billboardEditingText")->addButton("font", vec2(0.0f, 0.63f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Font", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingText")->addButton("color", vec2(0.0f, 0.21), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingText")->addButton("content", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Content", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("billboardEditingText")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void BillboardEditor::load()
{
	// Camera
	_fe3d.camera_setPosition(_defaultCameraPosition);
	_fe3d.camera_setYaw(-90.0f);
	_fe3d.camera_enableLookat(_billboardPosition);

	// Graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.75f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableShadows(vec3(25.0f), vec3(0.0f), 50.0f, 50.0f);
	
	// 3D Environment
	_fe3d.gameEntity_add("@@grid", "Engine\\OBJs\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "Engine\\Textures\\grass.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 25.0f);
	_fe3d.gameEntity_add("@@cube", "Engine\\OBJs\\cube.obj", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "Engine\\Textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Other
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
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
		iss >> name >> size.x >> size.y >> color.r >> color.g >> color.b >> facingX >> facingY >> diffusePath >>
			transparent >> fontPath >> content >> playing >> rows >> columns >> framestep;
		
		// Run checks on string values
		diffusePath = (diffusePath == "-") ? "" : diffusePath;
		fontPath = (fontPath == "-") ? "" : fontPath;
		content = (content == "-") ? "" : content;

		// Add billboard name
		_billboardNames.push_back(name);

		// Check if billboard has a diffuse map
		if (diffusePath != "")
		{
			_fe3d.billBoardEntity_add(name, diffusePath, _billboardPosition, vec3(0.0f), size, transparent, facingX, facingY, false, false);
			_fe3d.billboardEntity_setColor(name, color);

			// Playing sprite animation
			if (playing)
			{
				_fe3d.billboardEntity_setAnimationFramestep(name, framestep);
				_fe3d.billboardEntity_setAnimationRows(name, rows);
				_fe3d.billboardEntity_setAnimationColumns(name, columns);
				_fe3d.billBoardEntity_playSpriteAnimation(name, -1);
			}
		}
		else if (content != "")
		{
			_fe3d.billBoardEntity_add(name, content, fontPath, color, _billboardPosition, vec3(0.0f), size, facingX, facingY, false);
		}
		else
		{
			_fe3d.billBoardEntity_add(name, color, _billboardPosition, vec3(0.0f), size, facingX, facingY, false);
		}
	}

	// Close file
	file.close();

	// Logging
	_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" loaded!");
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
			// Convert string values
			string diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardName);
			string fontPath = _fe3d.billboardEntity_getFontPath(billboardName);
			string textContent = _fe3d.billboardEntity_getTextContent(billboardName);
			diffusePath = (diffusePath == "") ? "-" : diffusePath;
			fontPath = (fontPath == "") ? "-" : fontPath;
			textContent = (textContent == "") ? "-" : textContent;

			// Export data
			file << billboardName
				<< " " << _fe3d.billboardEntity_getSize(billboardName).x << " " << _fe3d.billboardEntity_getSize(billboardName).y
				<< " " << _fe3d.billboardEntity_getColor(billboardName).r << " " << _fe3d.billboardEntity_getColor(billboardName).g
				<< " " << _fe3d.billboardEntity_getColor(billboardName).b << " " << _fe3d.billboardEntity_isFacingCameraX(billboardName)
				<< " " << _fe3d.billboardEntity_isFacingCameraY(billboardName) << " " << diffusePath
				<< " " << _fe3d.billboardEntity_isTransparent(billboardName) << " " << fontPath << " " << textContent
				<< " " << _fe3d.billboardEntity_isAnimationPlaying(billboardName) << " " << _fe3d.billboardEntity_getAnimationRows(billboardName)
				<< " " << _fe3d.billboardEntity_getAnimationColumns(billboardName) << " " << _fe3d.billboardEntity_getAnimationFramestep(billboardName)
				<< std::endl;
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
	_fe3d.gfx_disableShadows();

	// 3D environment
	_fe3d.gameEntity_delete("@@grid");
	_fe3d.gameEntity_delete("@@cube");

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();
	_billboardNames.clear();

	// Delete billboard name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableLookat();

	// Other
	_billboardCreationEnabled = false;
	_billboardChoosingEnabled = false;
	_billboardEditingEnabled = false;
	_billboardRemovalEnabled = false;
	_isLoaded = false;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_currentBillboardID = "";
}
