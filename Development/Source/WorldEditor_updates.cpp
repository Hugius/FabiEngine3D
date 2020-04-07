#include <WE3D/WorldEditor.hpp>
#include <WE3D/InputHandler.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>

void WorldEditor::update
(
	ivec2 mousePos, vec3 terrainPoint,
	bool placementMode, vector<GameEntity*> & models,
	CameraManager& camera, TextEntityManager& text, InputHandler& input, float delta
)
{
	if (placementMode)
	{
		// Place new entity
		if (input.getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			p_modelAmounts[p_modelIndex]++;
			auto * newModel = models[p_modelIndex];
			p_game.addGameEntity
			(
				p_getSelectedID(), newModel->getModelName(),
				p_game.getEntity("previewEntity")->getTranslation(), p_game.getEntity("previewEntity")->getRotation(),
				p_game.getEntity("previewEntity")->getScaling(),
				newModel->isTransparent(), newModel->isFaceCulled(),
				newModel->isLightMapped(), newModel->isSkyReflective(), newModel->isSpecular()
			);
		}

		// Update preview entity
		if (p_game.isExisting("previewEntity"))
		{
			p_game.getEntity("previewEntity")->setTranslation(terrainPoint);
		}
		else // Create new preview entity
		{
			GameEntity * model = models[p_modelIndex];
			p_game.addGameEntity
			(
				"previewEntity", model->getModelName(),
				vec3(0.0f), model->getRotation(), model->getScaling(),
				model->isTransparent(), model->isFaceCulled(),
				model->isLightMapped(), model->isSkyReflective(), model->isSpecular()
			);
		}
	}
	else
	{
		// Delete example entity if existing
		if (p_game.isExisting("previewEntity"))
		{
			p_game.deleteEntity("previewEntity");
		}

		// Changing transformation type to translation
		if (input.getKeyPressed(Input::KEY_T))
		{
			p_transformationType = TransformationType::T;
		}
		
		// Changing transformation type to rotation
		if (input.getKeyPressed(Input::KEY_R))
		{
			p_transformationType = TransformationType::R;
		}

		// Changing transformation type to scaling
		if (input.getKeyPressed(Input::KEY_L))
		{
			p_transformationType = TransformationType::S;
		}

		// Changing direction type to X
		if (input.getKeyPressed(Input::KEY_X))
		{
			p_directionType = DirectionType::X;
		}

		// Changing direction type to Y
		if (input.getKeyPressed(Input::KEY_Y))
		{
			p_directionType = DirectionType::Y;
		}

		// Changing direction type to Z
		if (input.getKeyPressed(Input::KEY_Z))
		{
			p_directionType = DirectionType::Z;
		}

		// Resetting rotation
		if (input.getKeyDown(Input::KEY_V))
		{
			p_game.getEntity(p_getSelectedID())->setRotation(vec3(0.0f));
		}

		// Rotate or scale placed model
		if (p_game.isExisting(p_getSelectedID()))
		{
			// Mouse position
			static ivec2 oldMousePos;
			int xDifference = (mousePos.x - oldMousePos.x);
			int yDifference = (mousePos.y - oldMousePos.y);

			// Rotating the model
			if (input.getMouseDown(Input::MOUSE_BUTTON_RIGHT))
			{
				// Translation
				if (p_transformationType == TransformationType::T)
				{
					if (p_directionType == DirectionType::X)
					{
						p_game.getEntity(p_getSelectedID())->translate(vec3(float(xDifference) / 50.0f, 0.0f, 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Y)
					{
						p_game.getEntity(p_getSelectedID())->translate(vec3(0.0f, -(float(yDifference) / 75.0f), 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Z)
					{
						p_game.getEntity(p_getSelectedID())->translate(vec3(0.0f, 0.0f, float(xDifference) / 50.0f), delta);
					}
				}

				// Rotation
				if (p_transformationType == TransformationType::R)
				{
					if (p_directionType == DirectionType::X)
					{
						p_game.getEntity(p_getSelectedID())->rotate(vec3(float(xDifference) / 10.0f, 0.0f, 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Y)
					{
						p_game.getEntity(p_getSelectedID())->rotate(vec3(0.0f, float(xDifference) / 10.0f, 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Z)
					{
						p_game.getEntity(p_getSelectedID())->rotate(vec3(0.0f, 0.0f, float(xDifference) / 10.0f), delta);
					}
				}
				
				// Scaling
				if (p_transformationType == TransformationType::S)
				{
					if (p_directionType == DirectionType::X)
					{
						p_game.getEntity(p_getSelectedID())->scale(vec3(float(xDifference) / 100.0f, 0.0f, 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Y)
					{
						p_game.getEntity(p_getSelectedID())->scale(vec3(0.0f, float(yDifference) / 100.0f, 0.0f), delta);
					}
					else if (p_directionType == DirectionType::Z)
					{
						p_game.getEntity(p_getSelectedID())->scale(vec3(0.0f, 0.0f, float(xDifference) / 100.0f), delta);
					}
				}

				// Center camera
				camera.disableFirstPersonView();
				camera.center();
			}
			oldMousePos = mousePos;

			// Scaling the model
			p_game.getEntity(p_getSelectedID())->scale(vec3(input.getMouseWheelY() / 50.0f), delta);
		}

		// World save button
		if (input.getKeyPressed(Input::KEY_O))
		{
			Logger::getInst().throwInfo("Enter a name for this world:");
			string worldName;
			std::cin >> worldName;
			exportWorld(worldName);
		}
	}

	// Previous model
	if (input.getKeyPressed(Input::KEY_Q))
	{
		if (p_modelIndex > 0)  // Limit
		{
			if (input.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
			{
				if (p_modelIndex > 4) // Limit
				{
					p_modelIndex -= 5;
				}
			}
			else // Normal speed
			{
				p_modelIndex--;
			}

			// Remove preview entity
			if (p_game.isExisting("previewEntity"))
			{
				p_game.deleteEntity("previewEntity");
			}
		}
	}

	// Next model
	if (input.getKeyPressed(Input::KEY_E))
	{
		// Change model index
		if (p_modelIndex < p_modelAmounts.size() - 1)  // Limit
		{
			if (input.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
			{
				if (p_modelIndex < (p_modelAmounts.size() - 5))  // Limit
				{
					p_modelIndex += 5;
				}
			}
			else // Normal speed
			{
				p_modelIndex++;
			}

			// Remove preview entity
			if (p_game.isExisting("previewEntity"))
			{
				p_game.deleteEntity("previewEntity");
			}
		}
	}

	// Remove last entity
	if (input.getKeyPressed(Input::KEY_DELETE))
	{
		if (p_game.isExisting(p_getSelectedID())) // Check if exists
		{
			p_game.deleteEntity(p_getSelectedID()); // Delete
			p_modelAmounts[p_modelIndex]--;
		}
	}

	// Update GUI text
	text.addTextEntity("modelName", "Model: " + models[p_modelIndex]->getModelName(), "font", vec3(1.0f), vec2(-0.75f, 0.95f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	if (p_directionType == DirectionType::X)
	{
		text.addTextEntity("dirType", "Direction: X", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (p_directionType == DirectionType::Y)
	{
		text.addTextEntity("dirType", "Direction: Y", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (p_directionType == DirectionType::Z)
	{
		text.addTextEntity("dirType", "Direction: Z", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (p_transformationType == TransformationType::T)
	{
		text.addTextEntity("transType", "Transformation: T", "font", vec3(1.0f), vec2(-0.75f, 0.825f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (p_transformationType == TransformationType::R)
	{
		text.addTextEntity("transType", "Transformation: R", "font", vec3(1.0f), vec2(-0.75f, 0.825f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (p_transformationType == TransformationType::S)
	{
		text.addTextEntity("transType", "Transformation: S", "font", vec3(1.0f), vec2(-0.75f, 0.825f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (placementMode)
	{
		text.addTextEntity("mode", "Mode: placing", "font", vec3(1.0f), vec2(-0.75f, 0.575f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (!placementMode)
	{
		text.addTextEntity("mode", "Mode: editing", "font", vec3(1.0f), vec2(-0.75f, 0.575f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	
	// Controls display
	if (input.getKeyDown(Input::KEY_C))
	{
		text.addTextEntity("move", "Move: WASD", "font", vec3(0.0f), vec2(-0.75f, 0.45f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("ascend", "Ascend: SPACE", "font", vec3(0.0f), vec2(-0.75f, 0.325f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("descend", "Descend: LCTRL", "font", vec3(0.0f), vec2(-0.75f, 0.2f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("switchMode", "Switch mode: MMB", "font", vec3(0.0f), vec2(-0.75f, 0.075f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("place", "Place: LMB", "font", vec3(0.0f), vec2(-0.75f, -0.05f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("transform", "Transform: RMB", "font", vec3(0.0f), vec2(-0.75f, -0.175), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("changeDir", "Change dir: X Y Z", "font", vec3(0.0f), vec2(-0.75f, -0.3f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("changeTrans", "Change trans: T R L", "font", vec3(0.0f), vec2(-0.75f, -0.425f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("resetRot", "Reset rotation: V", "font", vec3(0.0f), vec2(-0.75f, -0.55f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		text.addTextEntity("export", "Export: O", "font", vec3(0.0f), vec2(-0.75f, -0.675f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	else
	{
		if (text.isExisting("move"))       
		{ 
			text.deleteEntity("move");        
		}
		if (text.isExisting("ascend"))     
		{ 
			text.deleteEntity("ascend");	
		}
		if (text.isExisting("descend"))  
		{ 
			text.deleteEntity("descend");	   
		}
		if (text.isExisting("switchMode"))
		{ 
			text.deleteEntity("switchMode");  
		}
		if (text.isExisting("place"))      
		{ 
			text.deleteEntity("place");		
		}
		if (text.isExisting("transform"))  
		{ 
			text.deleteEntity("transform");	
		}
		if (text.isExisting("changeDir"))  
		{ 
			text.deleteEntity("changeDir");	
		}
		if (text.isExisting("changeTrans"))
		{ 
			text.deleteEntity("changeTrans");
		}
		if (text.isExisting("resetRot"))   
		{ 
			text.deleteEntity("resetRot");   
		}
		if (text.isExisting("export"))     
		{ 
			text.deleteEntity("export");		
		}
	}
}