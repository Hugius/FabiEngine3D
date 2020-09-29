#pragma once

#include "fabi_engine_3d.hpp"

class EngineGuiRectangle
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, bool centered = true);
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, const string& textureName, bool centered = true);
	~EngineGuiRectangle();

	virtual void show();
	virtual void hide();

	const vec2 getOriginalPosition();
	const vec2 getOriginalSize();
	const vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

protected:
	FabiEngine3D& _fe3d;

	const vec2 _originalPosition;
	const vec2 _originalSize;
	const vec3 _originalColor;

	const string _ID;
	const string _entityID;
	const string _parentID;
};