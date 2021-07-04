#include "environment_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void EnvironmentEditor::_updateWaterMenuMain()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuMain")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenu");
				_currentEnvironmentType = EnvironmentType::NONE;
			}
			else if (screen->getButton("add")->isHovered())
			{
				_isWaterCreationEnabled = true;
				_gui.getGlobalScreen()->addValueForm("newWaterName", "New Water Name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isWaterChoosingEnabled = true;
				_isWaterEditingEnabled = true;
				auto IDs = getLoadedWaterIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("waterList", "Select Water", Vec2(-0.4f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isWaterChoosingEnabled = true;
				_isWaterRemovalEnabled = true;
				auto IDs = getLoadedWaterIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("waterList", "Select Water", Vec2(-0.4f, 0.1f), IDs);
			}
		}
	}
}

void EnvironmentEditor::_updateWaterMenuChoice()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuChoice")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(), false);
				_fe3d.terrainEntity_select("");
				_fe3d.waterEntity_select("");
				_hoveredTerrainID = "";
				_currentWaterID = "";
				_isWaterEditingEnabled = false;
			}
			else if (screen->getButton("terrain")->isHovered())
			{
				_isTerrainChoosingEnabled = true;
				for (auto& name : _loadedTerrainIDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("terrainList", "Select Terrain", Vec2(-0.4f, 0.1f), _loadedTerrainIDs);
				for (auto& name : _loadedTerrainIDs) { name = "@" + name; }
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuOptions");
			}
		}

		// Screen hoverabilities
		screen->getButton("effects")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));

		// Update preview terrain choosing
		if (_isTerrainChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");

			// Hide last terrain
			if (_hoveredTerrainID != "")
			{
				_fe3d.terrainEntity_select("");
			}

			// Check if a terrain name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Only select the terrain if it has a heightmap
					if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
					{
						_fe3d.terrainEntity_select(_currentTerrainID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("terrainList");
					_isTerrainChoosingEnabled = false;
				}
				else
				{
					// Set new hovered terrain
					_hoveredTerrainID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
			{
				_isTerrainChoosingEnabled = false;
				_gui.getGlobalScreen()->removeChoiceForm("terrainList");
			}
			else // Nothing hovered
			{
				_hoveredTerrainID = "";
			}

			// Show hovered terrain
			if (_hoveredTerrainID != "")
			{
				// Only select the terrain if it has a heightmap
				if (_fe3d.terrainEntity_isExisting(_hoveredTerrainID))
				{
					_fe3d.terrainEntity_select(_hoveredTerrainID);
				}
			}
		}
	}
}

void EnvironmentEditor::_updateWaterMenuMesh()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "waterEditorMenuMesh")
	{
		// Temporary values
		Vec3 waterPosition = _fe3d.waterEntity_getPosition(_currentWaterID);
		float waterSize = _fe3d.waterEntity_getSize(_currentWaterID);

		// GUI management
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("positionX", "X", waterPosition.x, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionY", "Y", waterPosition.y, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionZ", "Z", waterPosition.z, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("size", "Size", waterSize, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}			
		}

		// Holding LMB
		if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("up")->isHovered())
			{
				_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition + Vec3(0.0f, 0.1f, 0.0f));
			}
			else if (screen->getButton("down")->isHovered())
			{
				_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition - Vec3(0.0f, 0.1f, 0.0f));
			}
		}

		// Update size changes
		if (_gui.getGlobalScreen()->checkValueForm("size", waterSize, { 0.0f }))
		{
			waterSize = std::max(0.0f, waterSize);
			_fe3d.waterEntity_setSize(_currentWaterID, waterSize);
		}

		// Update position changes
		if 
		(
			_gui.getGlobalScreen()->checkValueForm("positionX", waterPosition.x, { }) ||
			_gui.getGlobalScreen()->checkValueForm("positionY", waterPosition.y, { }) ||
			_gui.getGlobalScreen()->checkValueForm("positionZ", waterPosition.z, { })
		)
		{
			_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition);
		}

		// Button hoverabilities
		screen->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
		screen->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
	}
}