#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

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
	_leftWindow->addScreen("billboardEditorMenuMain");
	_leftWindow->getScreen("billboardEditorMenuMain")->addButton("addBillboard", vec2(0.0f, 0.63f), vec2(GW("Add board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add board", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMain")->addButton("editBillboard", vec2(0.0f, 0.21), vec2(GW("Edit board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit board", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMain")->addButton("deleteBillboard", vec2(0.0f, -0.21), vec2(GW("Delete board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete board", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingMain
	_leftWindow->addScreen("billboardEditorMenuChoice");
	_leftWindow->getScreen("billboardEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.7f), vec2(GW("Mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuChoice")->addButton("appearance", vec2(0.0f, 0.35f), vec2(GW("Appearance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Appearance", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuChoice")->addButton("animation", vec2(0.0f, 0.0f), vec2(GW("Animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animation", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuChoice")->addButton("text", vec2(0.0f, -0.35f), vec2(GW("Text"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Text", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuChoice")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingMesh
	_leftWindow->addScreen("billboardEditorMenuMesh");
	_leftWindow->getScreen("billboardEditorMenuMesh")->addButton("size", vec2(0.0f, 0.63f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingX", vec2(0.0f, 0.21), vec2(GW("Facing X: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing X: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingY", vec2(0.0f, -0.21), vec2(GW("Facing Y: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing Y: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuMesh")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAppearance
	_leftWindow->addScreen("billboardEditorMenuAppearance");
	_leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("color", vec2(0.0f, 0.63f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("texture", vec2(0.0f, 0.21), vec2(GW("Texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("isTransparent", vec2(0.0f, -0.21), vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAnimation
	_leftWindow->addScreen("billboardEditorMenuAnimation");
	_leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("rows", vec2(0.0f, 0.7f), vec2(GW("Rows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rows", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("columns", vec2(0.0f, 0.35f), vec2(GW("Columns"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Columns", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("speed", vec2(0.0f, 0.0f), vec2(GW("Frame step"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Frame step", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("animate", vec2(0.0f, -0.35f), vec2(GW("Animate"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animate", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingText
	_leftWindow->addScreen("billboardEditorMenuText");
	_leftWindow->getScreen("billboardEditorMenuText")->addButton("font", vec2(0.0f, 0.63f), vec2(GW("Font"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Font", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuText")->addButton("color", vec2(0.0f, 0.21), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuText")->addButton("content", vec2(0.0f, -0.21), vec2(GW("Content"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Content", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("billboardEditorMenuText")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void BillboardEditor::load()
{
	// Camera
	_fe3d.camera_load(_fe3d.camera_getFOV(), 0.1f, 10000.0f, _defaultCameraPosition, -90.0f);
	_fe3d.camera_enableLookat(_billboardPosition);

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.75f);
	_fe3d.gfx_enableShadows(vec3(10.0f, 10.0f, 10.0f), vec3(0.0f), 25.0f, 50.0f, false);
	
	// 3D Environment
	_fe3d.skyEntity_select("@@editorSky");
	_fe3d.gameEntity_add("@@grid", "engine\\models\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "engine\\textures\\grass.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 25.0f);
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Load billboards from file
	_loadBillboards();

	// Other
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("billboardEditor");
	_isLoaded = true;
}

void BillboardEditor::_loadBillboards()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Create or overwrite billboards file
	std::ifstream file(_fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\billboards.fe3d");
	string line;

	// Read model data
	while (std::getline(file, line))
	{
		// Placeholder variables
		string name, diffusePath, fontPath, textContent;
		vec2 size;
		vec3 color;
		bool facingX, facingY, transparent, playing;
		int rows, columns, framestep;

		// For file extraction
		std::istringstream iss(line);

		// Extract from file
		iss >>
			name >>
			size.x >>
			size.y >>
			color.r >>
			color.g >>
			color.b >>
			facingX >>
			facingY >>
			diffusePath >>
			transparent >>
			fontPath >>
			textContent >>
			playing >>
			rows >>
			columns >>
			framestep;

		// Perform empty string & space conversions
		diffusePath = (diffusePath == "?") ? "" : diffusePath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;
		std::replace(diffusePath.begin(), diffusePath.end(), '?', ' ');
		std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
		std::replace(textContent.begin(), textContent.end(), '?', ' ');

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
		else if (textContent != "")
		{
			_fe3d.billBoardEntity_add(name, textContent, fontPath, color, _billboardPosition, vec3(0.0f), size, facingX, facingY, false);
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
		file.open(_fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\billboards.fe3d");

		// Write billboard data into file
		for (auto& billboardName : _billboardNames)
		{
			// Perform empty string & space conversions
			string diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardName);
			string fontPath = _fe3d.billboardEntity_getFontPath(billboardName);
			string textContent = _fe3d.billboardEntity_getTextContent(billboardName);
			diffusePath = (diffusePath == "") ? "?" : diffusePath;
			fontPath = (fontPath == "") ? "?" : fontPath;
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(diffusePath.begin(), diffusePath.end(), '?', ' ');
			std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
			std::replace(textContent.begin(), textContent.end(), '?', ' ');

			// Export data
			file << billboardName << " " <<
				_fe3d.billboardEntity_getSize(billboardName).x << " " <<
				_fe3d.billboardEntity_getSize(billboardName).y << " " <<
				_fe3d.billboardEntity_getColor(billboardName).r << " " <<
				_fe3d.billboardEntity_getColor(billboardName).g << " " <<
				_fe3d.billboardEntity_getColor(billboardName).b << " " <<
				_fe3d.billboardEntity_isFacingCameraX(billboardName) << " " <<
				_fe3d.billboardEntity_isFacingCameraY(billboardName) << " " <<
				diffusePath << " " <<
				_fe3d.billboardEntity_isTransparent(billboardName) << " " <<
				fontPath << " " <<
				textContent << " " << 
				_fe3d.billboardEntity_isAnimationPlaying(billboardName) << " " << 
				_fe3d.billboardEntity_getAnimationRows(billboardName) << " " <<
				_fe3d.billboardEntity_getAnimationColumns(billboardName) << " " << 
				_fe3d.billboardEntity_getAnimationFramestep(billboardName) << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" saved!");
	}
}

void BillboardEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableShadows();

	// 3D environment
	_fe3d.gameEntity_delete("@@grid");
	_fe3d.gameEntity_delete("@@cube");

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Delete billboard name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Reset variables
	_billboardCreationEnabled = false;
	_billboardChoosingEnabled = false;
	_billboardEditingEnabled = false;
	_billboardRemovalEnabled = false;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_billboardNames.clear();

	// Miscellaneous
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
	_isLoaded = false;
}
