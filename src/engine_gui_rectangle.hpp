#pragma once

#include "fe3d.hpp"

class EngineGuiRectangle
{
public:
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered);
	EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered);
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
	const fvec2 getInitialPosition() const;
	const fvec2 getInitialSize() const;
	const fvec3 getInitialColor() const;

protected:
	// Strings
	const string _ID;
	const string _entityID;
	const string _parentID;

	// Vectors
	fvec2 _initialPosition;
	fvec2 _initialSize;
	fvec3 _initialColor;

	// Miscellaneous
	FabiEngine3D& _fe3d;
};