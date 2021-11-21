#pragma once

#include "fe3d.hpp"

class EngineGuiTextField final
{
public:
	EngineGuiTextField(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size,
					   string textContent, fvec3 color, bool isCentered, bool isDynamic);
	~EngineGuiTextField();

	// Voids
	void setVisible(bool isVisible);
	void changeTextContent(const string& content);
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

private:
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