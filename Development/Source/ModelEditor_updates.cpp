#include <GLM/glm.hpp>

using glm::ivec2;

#include <WE3D/ModelEditor.hpp>
#include <WE3D/TextureLoader.hpp>
#include <WE3D/InputHandler.hpp>

void ModelEditor::update(ivec2 mousePos, InputHandler& inputHandler, float delta)
{
	// Previous model
	if (inputHandler.getKeyPressed(Input::KEY_Q))
	{
		if (p_modelIndex > 0)  // Limit
		{
			if (inputHandler.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
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
		}
	}

	// Next model
	if (inputHandler.getKeyPressed(Input::KEY_E))
	{
		// Change model index
		if (p_modelIndex < p_modelNames.size() - 1)  // Limit
		{
			if (inputHandler.getKeyDown(Input::KEY_LSHIFT)) // Faster swapping
			{
				if (p_modelIndex < (p_modelNames.size() - 5))  // Limit
				{
					p_modelIndex += 5;
				}
			}
			else // Normal speed
			{
				p_modelIndex++;
			}
		}
	}

	// Lightmapping button
	if (inputHandler.getKeyPressed(Input::KEY_L))
	{
		getSelectedModel()->setLightMapped(!getSelectedModel()->isLightMapped());
		auto parts = p_objLoader.loadOBJ(getSelectedModel()->getModelName());
		for (auto & part : parts)
		{
			getSelectedModel()->addLightmap(p_texLoader.getTexture("../Game/Textures/LightMaps/" + part.textureName, false, false));
		}
	}

	// Transparency button
	if (inputHandler.getKeyPressed(Input::KEY_T))
	{
		getSelectedModel()->setTransparent(!getSelectedModel()->isTransparent());
	}

	// Face culling button
	if (inputHandler.getKeyPressed(Input::KEY_F))
	{
		getSelectedModel()->setFaceCulled(!getSelectedModel()->isFaceCulled());
	}

	// Reflection button
	if (inputHandler.getKeyPressed(Input::KEY_R))
	{
		getSelectedModel()->setSkyReflective(!getSelectedModel()->isSkyReflective());
		auto parts = p_objLoader.loadOBJ(getSelectedModel()->getModelName());
		for (auto & part : parts)
		{
			getSelectedModel()->addReflectionMap(p_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + part.textureName, false, false));
		}
	}

	// Specular button
	if (inputHandler.getKeyPressed(Input::KEY_S))
	{
		getSelectedModel()->setSpecular(!getSelectedModel()->isSpecular());
	}

	// Chaning rotation direction
	if (inputHandler.getKeyPressed(Input::KEY_D))
	{
		if (p_rotationType == RotationType::X)
		{
			p_rotationType = RotationType::Y;
		}
		else if (p_rotationType == RotationType::Y)
		{
			p_rotationType = RotationType::Z;
		}
		else if (p_rotationType == RotationType::Z)
		{
			p_rotationType = RotationType::X;
		}
	}

	// Mouse position
	static ivec2 oldMousePos;
	int xDifference = (mousePos.x - oldMousePos.x);
	int yDifference = (mousePos.y - oldMousePos.y);

	// Moving the model
	if (inputHandler.getMouseDown(Input::MOUSE_BUTTON_LEFT))
	{
		getSelectedModel()->translate(vec3(float(xDifference) / 35.0f, float(-yDifference) / 35.0f, 0.0f), delta);
	}

	// Rotating the model
	if (inputHandler.getMouseDown(Input::MOUSE_BUTTON_RIGHT))
	{
		if (p_rotationType == RotationType::X)
		{
			getSelectedModel()->rotate(vec3(float(yDifference) / 2.0f, 0.0f, 0.0f), delta);
		}
		else if (p_rotationType == RotationType::Y)
		{
			getSelectedModel()->rotate(vec3(0.0f, float(xDifference) / 2.0f, 0.0f), delta);
		}
		else if (p_rotationType == RotationType::Z)
		{
			getSelectedModel()->rotate(vec3(0.0f, 0.0f, float(xDifference) / 2.0f), delta);
		}
	}
	oldMousePos = mousePos;

	// Scaling the model
	getSelectedModel()->scale(vec3(inputHandler.getMouseWheelY() / 15.0f), delta);

	// Update model matrix
	getSelectedModel()->updateModelMatrix();

	// Saving
	if (inputHandler.getKeyPressed(Input::KEY_O))
	{
		p_saveModelData();
	}
}