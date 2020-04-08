#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiButton.hpp"

class EngineGuiScreen
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size);

	const string& getID();
	const string& getParentID();

	void addButton(const string& ID, vec2 position, vec2 size);

	vector<EngineGuiButton>& getButtons();

private:
	FabiEngine3D& FE3D;

	const string _ID;
	const string _parentID;

	vector<EngineGuiButton> _buttons;
};