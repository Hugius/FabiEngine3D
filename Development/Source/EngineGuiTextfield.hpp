#pragma once

#include "FabiEngine3D.hpp"

class EngineGuiTextfield final
{
public:
	EngineGuiTextfield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor);
	~EngineGuiTextfield();

	vec3 getOriginalColor();
	vec2 getOriginalPosition();
	vec2 getOriginalSize();

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