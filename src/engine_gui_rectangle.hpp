#pragma once

#include "fe3d.hpp"

class EngineGuiRectangle
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered);
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered);
	~EngineGuiRectangle();

	// Voids
	virtual void setVisible(bool isVisible);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	// Strings
	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	// Vectors
	const Vec2 getInitialPosition() const;
	const Vec2 getInitialSize() const;
	const Vec3 getInitialColor() const;

protected:
	// Strings
	const string _ID;
	const string _entityID;
	const string _parentID;

	// Vectors
	Vec2 _initialPosition;
	Vec2 _initialSize;
	Vec3 _initialColor;

	// Miscellaneous
	FabiEngine3D& _fe3d;
};