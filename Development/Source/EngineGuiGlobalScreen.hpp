#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiWritefield.hpp"

class EngineGuiGlobalScreen final
{
public:
	EngineGuiGlobalScreen(FabiEngine3D& fe3d);

	void update(float delta);

	void addWritefield(const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor);
	void addButton(const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor);
	void addRectangle(const string& ID, vec2 position, vec2 size, vec3 color);
	void addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor);

	void deleteWritefield(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	shared_ptr<EngineGuiWritefield> getWritefield(const string& ID);
	shared_ptr<EngineGuiButton> getButton(const string& ID);
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield> getTextfield(const string& ID);

	vector<shared_ptr<EngineGuiWritefield>>& getWritefields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>& getTextfields();

	const string& getHoveredItemID();

private:
	FabiEngine3D& _fe3d;

	string _hoveredItemID = "";

	vector<shared_ptr<EngineGuiWritefield>> _writefields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;
};