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
	void updateOriginalPosition();
	void updateOriginalSize();
	void updateOriginalColor();

	// Strings
	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	// Vectors
	const Vec2 getOriginalPosition() const;
	const Vec2 getOriginalSize() const;
	const Vec3 getOriginalColor() const;

protected:
	// Strings
	const string _ID;
	const string _entityID;
	const string _parentID;

	// Vectors
	Vec2 _originalPosition;
	Vec2 _originalSize;
	Vec3 _originalColor;

	// Miscellaneous
	FabiEngine3D& _fe3d;
};