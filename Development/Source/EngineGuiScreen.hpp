#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiWritefield.hpp"

class EngineGuiScreen final
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size);

	void update(float delta, bool hoverable);
	void show();
	void hide();

	const string& getID();
	const string& getParentID();

	void addWritefield(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor);
	void addButton(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, string textContent, vec3 textColor, vec3 textHoverColor);
	void addRectangle(const string& ID, vec2 position, vec2 size, vec3 color);
	void addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor);

	void deleteWritefield(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	shared_ptr<EngineGuiWritefield> getWritefield(const string& ID);
	shared_ptr<EngineGuiButton>     getButton(const string& ID);
	shared_ptr<EngineGuiRectangle>  getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield>  getTextfield(const string& ID);

	vector<shared_ptr<EngineGuiWritefield>>& getWritefields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>& getTextfields();

	const string& getHoveredItemID();

private:
	FabiEngine3D& _fe3d;

	string _hoveredItemID = "";

	vec2 _parentPosition;
	vec2 _parentSize;

	const string _ID;
	const string _parentID;

	bool _enabled = false;

	vector<shared_ptr<EngineGuiWritefield>> _writefields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;

	vec4 _convertDimensions(vec2 position, vec2 size);
};