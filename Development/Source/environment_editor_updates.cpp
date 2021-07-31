#include "environment_editor.hpp"

void EnvironmentEditor::update()
{
	if (_isEditorLoaded)
	{
		// Update main menu
		if (_isInMainMenu)
		{
			// Temporary values
			auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

			// Select the default sky
			_fe3d.skyEntity_select("@@engineBackground");

			// No terrain
			_fe3d.terrainEntity_select("");

			// No water
			_fe3d.waterEntity_select("");

			// GUI management
			if (screen->getID() == "environmentEditorMenuMain")
			{
				// Check if input received
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
						unload();
					}
					else if (screen->getButton("sky")->isHovered())
					{
						if (loadSkyEntitiesFromFile())
						{
							// Go to sky menu
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuSky");
							_currentEnvironmentType = EnvironmentType::SKY;
							_isInMainMenu = false;
						}
					}
					else if (screen->getButton("terrain")->isHovered())
					{
						if (loadTerrainEntitiesFromFile())
						{
							// Camera
							_fe3d.camera_reset();
							_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
							_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
							_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH, INITIAL_CAMERA_DISTANCE);

							// 3D environment
							_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj", 
								Vec3(0.0f, -TERRAIN_Y_OFFSET, 0.0f), Vec3(0.0f), Vec3(1.0f));
							_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
							_fe3d.modelEntity_setFaceCulled("@@cube", true);
							_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj", 
								Vec3(0.0f, -TERRAIN_Y_OFFSET, 0.0f), Vec3(0.0f), Vec3(TERRAIN_GRID_SIZE, 1.0f, TERRAIN_GRID_SIZE));
							_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
							_fe3d.modelEntity_setUvRepeat("@@grid", 10.0f);
							_fe3d.modelEntity_setTransparent("@@grid", true);

							// Go to terrain menu
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuTerrain");
							_currentEnvironmentType = EnvironmentType::TERRAIN;
							_isInMainMenu = false;
						}
					}
					else if (screen->getButton("water")->isHovered())
					{
						if (loadWaterEntitiesFromFile())
						{
							// Go to water menu
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuWater");
							_currentEnvironmentType = EnvironmentType::WATER;
							_isInMainMenu = false;
						}
					}
				}

				// Check if user wants to save changes
				if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
				{
					saveSkyEntitiesToFile();
					saveTerrainEntitiesToFile();
					saveWaterEntitiesToFile();
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
					unload();
				}
				else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
				{

				}
			}
		}
		else
		{
			// Update editors
			_updateSkyEditor();
			_updateTerrainEditor();
			_updateWaterEditor();
		}

		// Update miscellaneous
		_updateMiscellaneous();
	}
}