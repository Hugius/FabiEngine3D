#pragma once

#include "fabi_engine_3d.hpp"

class EngineGuiRectangle
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered = true);
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered = true);
	~EngineGuiRectangle();

	virtual void setVisible(bool isVisible);
	void updateOriginalPosition();
	void updateOriginalSize();
	void updateOriginalColor();

	const Vec2 getOriginalPosition();
	const Vec2 getOriginalSize();
	const Vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

protected:
	FabiEngine3D& _fe3d;

	Vec2 _originalPosition;
	Vec2 _originalSize;
	Vec3 _originalColor;

	const string _ID;
	const string _entityID;
	const string _parentID;
};