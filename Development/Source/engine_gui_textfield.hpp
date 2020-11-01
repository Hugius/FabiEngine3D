#pragma once

#include "fabi_engine_3d.hpp"

class EngineGuiTextfield final
{
public:
	EngineGuiTextfield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, 
		string textContent, vec3 textColor, bool isCentered = true);
	~EngineGuiTextfield();

	void show();
	void hide();

	const vec2 getOriginalPosition();
	const vec2 getOriginalSize();
	const vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

private:
	FabiEngine3D& _fe3d;

	const vec3 _originalColor;
	const vec2 _originalPosition;
	const vec2 _originalSize;

	const string _ID;
	const string _entityID;
	const string _parentID;
};