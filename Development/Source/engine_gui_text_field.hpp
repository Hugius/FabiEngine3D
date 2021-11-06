#pragma once

#include "fe3d.hpp"

class EngineGuiTextField final
{
public:
	EngineGuiTextField(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size,
					   string textContent, Vec3 color, bool isCentered = true, bool isDynamic = false);
	~EngineGuiTextField();

	// Voids
	void setVisible(bool isVisible);
	void changeTextContent(const string& content);
	void updateOriginalPosition();
	void updateOriginalSize();
	void updateOriginalColor();

	// Strings
	const string& getID();
	const string& getEntityID();
	const string& getParentID();

	// Vectors
	const Vec2 getOriginalPosition();
	const Vec2 getOriginalSize();
	const Vec3 getOriginalColor();

private:
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