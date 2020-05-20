#include "world_editor.hpp"

void WorldEditor::_upateWaterManagement()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _window->getScreen("waterManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_window->setActiveScreen("waterMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_window->setActiveScreen("waterOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("worldManagement");
				_currentWorldPart = WorldPart::NONE;
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// Update sub-menus
		_updateTPSCamera();
		_updateWaterMesh();
		_updateWaterOptions();
	}
}

void WorldEditor::_updateWaterMesh()
{
	if (_window->getActiveScreen()->getID() == "waterMesh")
	{
		auto screen = _window->getScreen("waterMesh");
		string dudvmapPath = "User\\Assets\\Textures\\DudvMaps\\";
		string normalmapPath = "User\\Assets\\Textures\\NormalMaps\\";

		// GUI management
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getScrollingList("buttonList")->getButton("dudvmap")->isHovered())
				{
					string fileName = _fe3d.misc_getWinExplorerFilename(dudvmapPath, "PNG");
					_waterDudvmapPath = (fileName == "") ? _waterDudvmapPath : (dudvmapPath + fileName);
				}
				else if (screen->getScrollingList("buttonList")->getButton("normalmap")->isHovered())
				{
					string fileName = _fe3d.misc_getWinExplorerFilename(normalmapPath, "PNG");
					_waterNormalmapPath = (fileName == "") ? _waterNormalmapPath : (normalmapPath + fileName);
				}
				else if (screen->getScrollingList("buttonList")->getButton("size")->isHovered())
				{
					_addValueForm("size", "Size", _waterSize);
				}
				else if (screen->getScrollingList("buttonList")->getButton("repeat")->isHovered())
				{
					_addValueForm("repeat", "Repeat", _waterRepeat);
				}
				else if (screen->getScrollingList("buttonList")->getButton("height")->isHovered())
				{
					_addValueForm("height", "Height", _waterHeight);
				}
				else if (screen->getButton("load")->isHovered())
				{
					// Remove existing terrain
					if (_fe3d.waterEntity_isExisting("@water"))
					{
						_fe3d.waterEntity_delete("@water");
					}

					// Add new terrain
					_fe3d.waterEntity_add("@water", _waterDudvmapPath, _waterNormalmapPath, vec3(0.0f, _waterHeight, 0.0f), _waterSize, _waterRepeat, 0.0f, _waterWavesEnabled, _waterRipplingEnabled, _waterColor, _waterShininess);
					_fe3d.waterEntity_select("@water");

					// Camera
					_waterCameraHeight = _waterHeight + (_waterSize / 16.0f);
					_waterCameraDistance = _waterSize / 2.0f;
					_cameraHeight = _waterCameraHeight;
					_cameraDistance = _waterCameraDistance;
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("waterManagement");
				}
			}
			else // Holding LMB
			{
				if (screen->getScrollingList("buttonList")->getButton("up")->isHovered())
				{
					_waterHeight += 0.01f * _delta;
					_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
				}
				else if (screen->getScrollingList("buttonList")->getButton("down")->isHovered())
				{
					_waterHeight -= 0.01f * _delta;
					_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
				}
			}
		}

		// Check if value confirmed
		_checkValueForm("size", _waterSize);
		_checkValueForm("repeat", _waterRepeat);
		_checkValueForm("height", _waterHeight);

		// Filling statuses
		bool loadedDudvmap = _waterDudvmapPath != "";
		bool loadedNormalmap = _waterNormalmapPath != "";
		bool loadedSize = _waterSize != 0.0f;
		bool loadedRepeat = _waterRepeat != 0.0f;
		bool loadedHeight = _waterHeight != 0.0f;

		// Button hoverability
		screen->getScrollingList("buttonList")->getButton("normalmap")->setHoverable(loadedDudvmap);
		screen->getScrollingList("buttonList")->getButton("size")->setHoverable(loadedNormalmap);
		screen->getScrollingList("buttonList")->getButton("repeat")->setHoverable(loadedSize);
		screen->getScrollingList("buttonList")->getButton("height")->setHoverable(loadedRepeat);
		screen->getScrollingList("buttonList")->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getScrollingList("buttonList")->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("load")->setHoverable(loadedDudvmap && loadedNormalmap && loadedSize && loadedRepeat && loadedHeight);
	}
}

void WorldEditor::_updateWaterOptions()
{
	if (_window->getActiveScreen()->getID() == "waterOptions")
	{
		auto screen = _window->getScreen("waterOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("speed")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
		}
	}
}