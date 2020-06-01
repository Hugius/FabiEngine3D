#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_scrollinglist.hpp"
#include "engine_gui_writefield.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_textfield.hpp"

class EngineGuiGlobalScreen final
{
public:
	EngineGuiGlobalScreen(FabiEngine3D& fe3d);

	void update();
	void setFocus(bool focused);

	bool isFocused();

	void addScrollingList(const string& ID, vec2 position, vec2 size, vec3 color, vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, vec2 charSize);
	void addWriteField(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor, 
		bool noNumbers = false, bool noCaps = false, bool noSpecials = false, bool noLetters = false);
	void addButton(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, string textContent, vec3 textColor, vec3 textHoverColor);
	void addRectangle(const string& ID, vec2 position, vec2 size, vec3 color);
	void addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor);

	bool checkScrollingList(const string& ID);
	bool checkWriteField(const string& ID);
	bool checkButton(const string& ID);
	bool checkRectangle(const string& ID);
	bool checkTextfield(const string& ID);

	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWriteField> getWriteField(const string& ID);
	shared_ptr<EngineGuiButton> getButton(const string& ID);
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield> getTextfield(const string& ID);

	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWriteField>>& getWriteFields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>& getTextfields();

	template <typename T> void addValueForm(const string& ID, string title, T value, vec2 position);
	template <typename T> bool checkValueForm(const string& ID, T& value);
	void addAnswerForm(const string& ID, string title, vec2 position);
	bool checkAnswerFormConfirmed(const string& ID);
	bool checkAnswerFormDeclined(const string& ID);
	void removeAnswerForm(const string& ID);

private:
	void _updateValueFilling();
	void _removeValueForm(string ID);

	FabiEngine3D& _fe3d;

	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;

	vector<string> _valueFormIDs;
	string _answerFormID = "";
	bool _isFocused = false;
	bool _exitValueFilling = false;
};