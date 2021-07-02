#pragma once

#include "fabi_engine_3d.hpp"

class EngineGuiTextfield final
{
public:
	EngineGuiTextfield(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, 
		string textContent, Vec3 textColor, bool isCentered = true, bool isDynamic = false);
	~EngineGuiTextfield();

	void setVisible(bool isVisible);

	const Vec2 getOriginalPosition();
	const Vec2 getOriginalSize();
	const Vec3 getOriginalColor();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

private:
	FabiEngine3D& _fe3d;

	const Vec3 _originalColor;
	const Vec2 _originalPosition;
	Vec2 _originalSize;

	const string _ID;
	const string _entityID;
	const string _parentID;
};