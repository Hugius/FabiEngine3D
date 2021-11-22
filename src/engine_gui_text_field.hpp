#pragma once

#include "fe3d.hpp"

class EngineGuiTextField final
{
public:
	EngineGuiTextField(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size,
					   string textContent, fvec3 color, bool isCentered, bool isDynamic);
	~EngineGuiTextField();

	// VOID
	void setVisible(bool isVisible);
	void changeTextContent(const string& content);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	// STRING
	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	// FVEC3
	const fvec3 getInitialColor() const;

	// FVEC2
	const fvec2 getInitialPosition() const;
	const fvec2 getInitialSize() const;

private:
	// STRING
	const string _ID;
	const string _entityID;
	const string _parentID;

	// FVEC3
	fvec3 _initialColor;

	// FVEC2
	fvec2 _initialPosition;
	fvec2 _initialSize;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
};