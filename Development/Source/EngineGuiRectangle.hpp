#pragma once

#include "FabiEngine3D.hpp"

class EngineGuiRectangle final
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color);
	~EngineGuiRectangle();

	void show();
	void hide();

	vec2 getOriginalPosition();
	vec2 getOriginalSize();
	vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

private:
	FabiEngine3D& _fe3d;

	const vec2 _originalPosition;
	const vec2 _originalSize;
	const vec3 _originalColor;

	const string _ID;
	const string _entityID;
	const string _parentID;
};