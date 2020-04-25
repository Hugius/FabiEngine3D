#include "world_editor.hpp"
#include "input_handler.hpp"
#include "configuration.hpp"
#include "shader_bus.hpp"

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
			_modelAmounts[_modelIndex]++;
			auto * newModel = models[_modelIndex];
			//_game.addGameEntity
			//(
			//	_getSelectedID(), newModel->getModelName(),
			//	_game.getEntity("previewEntity")->getTranslation(), _game.getEntity("previewEntity")->getRotation(),
			//	_game.getEntity("previewEntity")->getScaling(),
			//	newModel->isTransparent(), newModel->isFaceCulled(),
			//	newModel->isLightMapped(), newModel->isSkyReflective(), newModel->isSpecular()
			//);
		}

		// Update preview entity
		if (_game.isExisting("previewEntity"))
		{
			_game.getEntity("previewEntity")->setTranslation(terrainPoint);
		}
		else // Create new preview entity
		{
			GameEntity * model = models[_modelIndex];
			//_game.addGameEntity
			//(
			//	"previewEntity", model->getModelName(),
			//	vec3(0.0f), model->getRotation(), model->getScaling(),
			//	model->isTransparent(), model->isFaceCulled(),
			//	model->isLightMapped(), model->isSkyReflective(), model->isSpecular()
			//);
		}
	}
	else
	{
		// Delete example entity if existing
		if (_game.isExisting("previewEntity"))
		{
			_game.deleteEntity("previewEntity");
		}

		// Changing transformation type to translation
		if (input.getKeyPressed(Input::KEY_T))
		{
			_transformationType = TransformationType::T;
		}
		
		// Changing transformation type to rotation
		if (input.getKeyPressed(Input::KEY_R))
		{
			_transformationType = TransformationType::R;
		}

		// Changing transformation type to scaling
		if (input.getKeyPressed(Input::KEY_L))
		{
			_transformationType = TransformationType::S;
		}

		// Changing direction type to X
		if (input.getKeyPressed(Input::KEY_X))
		{
			_directionType = DirectionType::X;
		}

		// Changing direction type to Y
		if (input.getKeyPressed(Input::KEY_Y))
		{
			_directionType = DirectionType::Y;
		}

		// Changing direction type to Z
		if (input.getKeyPressed(Input::KEY_Z))
		{
			_directionType = DirectionType::Z;
		}

		// Resetting rotation
		if (input.getKeyDown(Input::KEY_V))
		{
			_game.getEntity(_getSelectedID())->setRotation(vec3(0.0f));
		}

		// Rotate or scale placed model
		if (_game.isExisting(_getSelectedID()))
		{
			// Mouse position
			static ivec2 oldMousePos;
			int xDifference = (mousePos.x - oldMousePos.x);
			int yDifference = (mousePos.y - oldMousePos.y);

			// Rotating the model
			if (input.getMouseDown(Input::MOUSE_BUTTON_RIGHT))
			{
				// Translation
				if (_transformationType == TransformationType::T)
				{
					if (_directionType == DirectionType::X)
					{
						_game.getEntity(_getSelectedID())->translate(vec3(float(xDifference) / 50.0f, 0.0f, 0.0f), delta);
					}
					else if (_directionType == DirectionType::Y)
					{
						_game.getEntity(_getSelectedID())->translate(vec3(0.0f, -(float(yDifference) / 75.0f), 0.0f), delta);
					}
					else if (_directionType == DirectionType::Z)
					{
						_game.getEntity(_getSelectedID())->translate(vec3(0.0f, 0.0f, float(xDifference) / 50.0f), delta);
					}
				}

				// Rotation
				if (_transformationType == TransformationType::R)
				{
					if (_directionType == DirectionType::X)
					{
						_game.getEntity(_getSelectedID())->rotate(vec3(float(xDifference) / 10.0f, 0.0f, 0.0f), delta);
					}
					else if (_directionType == DirectionType::Y)
					{
						_game.getEntity(_getSelectedID())->rotate(vec3(0.0f, float(xDifference) / 10.0f, 0.0f), delta);
					}
					else if (_directionType == DirectionType::Z)
					{
						_game.getEntity(_getSelectedID())->rotate(vec3(0.0f, 0.0f, float(xDifference) / 10.0f), delta);
					}
				}
				
				// Scaling
				if (_transformationType == TransformationType::S)
				{
					if (_directionType == DirectionType::X)
					{
						_game.getEntity(_getSelectedID())->scale(vec3(float(xDifference) / 100.0f, 0.0f, 0.0f), delta);
					}
					else if (_directionType == DirectionType::Y)
					{
						_game.getEntity(_getSelectedID())->scale(vec3(0.0f, float(yDifference) / 100.0f, 0.0f), delta);
					}
					else if (_directionType == DirectionType::Z)
					{
						_game.getEntity(_getSelectedID())->scale(vec3(0.0f, 0.0f, float(xDifference) / 100.0f), delta);
					}
				}

				// Center camera
				camera.disableFirstPersonView();
				camera.center();
			}
			oldMousePos = mousePos;

			// Scaling the model
			_game.getEntity(_getSelectedID())->scale(vec3(input.getMouseWheelY() / 50.0f), delta);
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
		if (_modelIndex > 0)  // Limit
		{
			if (input.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
			{
				if (_modelIndex > 4) // Limit
				{
					_modelIndex -= 5;
				}
			}
			else // Normal speed
			{
				_modelIndex--;
			}

			// Remove preview entity
			if (_game.isExisting("previewEntity"))
			{
				_game.deleteEntity("previewEntity");
			}
		}
	}

	// Next model
	if (input.getKeyPressed(Input::KEY_E))
	{
		// Change model index
		if (_modelIndex < _modelAmounts.size() - 1)  // Limit
		{
			if (input.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
			{
				if (_modelIndex < (_modelAmounts.size() - 5))  // Limit
				{
					_modelIndex += 5;
				}
			}
			else // Normal speed
			{
				_modelIndex++;
			}

			// Remove preview entity
			if (_game.isExisting("previewEntity"))
			{
				_game.deleteEntity("previewEntity");
			}
		}
	}

	// Remove last entity
	if (input.getKeyPressed(Input::KEY_DELETE))
	{
		if (_game.isExisting(_getSelectedID())) // Check if exists
		{
			_game.deleteEntity(_getSelectedID()); // Delete
			_modelAmounts[_modelIndex]--;
		}
	}

	// Update GUI text
	/*text.addTextEntity("modelName", "Model: " + models[_modelIndex]->getModelName(), "font", vec3(1.0f), vec2(-0.75f, 0.95f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	if (_directionType == DirectionType::X)
	{
		text.addTextEntity("dirType", "Direction: X", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (_directionType == DirectionType::Y)
	{
		text.addTextEntity("dirType", "Direction: Y", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (_directionType == DirectionType::Z)
	{
		text.addTextEntity("dirType", "Direction: Z", "font", vec3(1.0f), vec2(-0.75f, 0.7f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (_transformationType == TransformationType::T)
	{
		text.addTextEntity("transType", "Transformation: T", "font", vec3(1.0f), vec2(-0.75f, 0.825f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (_transformationType == TransformationType::R)
	{
		text.addTextEntity("transType", "Transformation: R", "font", vec3(1.0f), vec2(-0.75f, 0.825f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	}
	if (_transformationType == TransformationType::S)
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
	}*/
	
	// Controls display
	if (input.getKeyDown(Input::KEY_C))
	{
		//text.addTextEntity("move", "Move: WASD", "font", vec3(0.0f), vec2(-0.75f, 0.45f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("ascend", "Ascend: SPACE", "font", vec3(0.0f), vec2(-0.75f, 0.325f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("descend", "Descend: LCTRL", "font", vec3(0.0f), vec2(-0.75f, 0.2f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("switchMode", "Switch mode: MMB", "font", vec3(0.0f), vec2(-0.75f, 0.075f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("place", "Place: LMB", "font", vec3(0.0f), vec2(-0.75f, -0.05f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("transform", "Transform: RMB", "font", vec3(0.0f), vec2(-0.75f, -0.175), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("changeDir", "Change dir: X Y Z", "font", vec3(0.0f), vec2(-0.75f, -0.3f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("changeTrans", "Change trans: T R L", "font", vec3(0.0f), vec2(-0.75f, -0.425f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("resetRot", "Reset rotation: V", "font", vec3(0.0f), vec2(-0.75f, -0.55f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
		//text.addTextEntity("export", "Export: O", "font", vec3(0.0f), vec2(-0.75f, -0.675f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
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