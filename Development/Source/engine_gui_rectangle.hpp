#pragma once

#include "fabi_engine_3d.hpp"

class EngineGuiRectangle
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered = true);
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& textureName, bool isCentered = true);
	~EngineGuiRectangle();

	virtual void show();
	virtual void hide();

	const Vec2 getOriginalPosition();
	const Vec2 getOriginalSize();
	const Vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

protected:
	FabiEngine3D& _fe3d;

	const Vec2 _originalPosition;
	const Vec2 _originalSize;
	const Vec3 _originalColor;

	const string _ID;
	const string _entityID;
	const string _parentID;
};