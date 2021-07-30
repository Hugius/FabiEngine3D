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

	void addScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize);
	void addWritefield(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, 
		bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void addButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor);
	void addButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor);
	void addRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color);
	void addRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath);
	void addTextfield(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered = true);

	bool checkScrollingList(const string& ID);
	bool checkWritefield(const string& ID);
	bool checkButton(const string& ID);
	bool checkRectangle(const string& ID);
	bool checkTextfield(const string& ID);

	void deleteScrollingList(const string& ID);
	void deleteWritefield(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWritefield> getWritefield(const string& ID);
	shared_ptr<EngineGuiButton> getButton(const string& ID);
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield> getTextfield(const string& ID);

	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWritefield>>& getWritefields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>& getTextfields();

	// Value form
	void addValueForm(const string& ID, string title, unsigned int value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void addValueForm(const string& ID, string title, int value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void addValueForm(const string& ID, string title, float value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void addValueForm(const string& ID, string title, double value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void addValueForm(const string& ID, string title, string value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	bool checkValueForm(const string& ID, unsigned int& value, vector<unsigned int> forbiddenValues = {});
	bool checkValueForm(const string& ID, int& value, vector<int> forbiddenValues = {});
	bool checkValueForm(const string& ID, float& value, vector<float> forbiddenValues = {});
	bool checkValueForm(const string& ID, double& value, vector<double> forbiddenValues = {});
	bool checkValueForm(const string& ID, string& value, vector<string> forbiddenValues = {});
	bool isValueFormExisting(const string& ID);

	// Choice form
	void addChoiceForm(const string& ID, string title, Vec2 position, vector<string> buttonTitles);
	string getSelectedChoiceFormButtonID(const string& ID);
	bool isChoiceFormCancelled(const string& ID);
	void deleteChoiceForm(const string& ID);
	bool isChoiceFormExisting(const string& ID);

	// Answer form
	void addAnswerForm(const string& ID, string title, Vec2 position);
	bool isAnswerFormConfirmed(const string& ID);
	bool isAnswerFormDenied(const string& ID);
	bool isAnswerFormExisting(const string& ID);

private:
	void _updateValueFilling();
	void _createValueForm(const string& ID, string title, string valueString, Vec2 position, Vec2 size, bool onlyNumbers, Vec2 buttonsPosition);
	bool _checkValueForm(const string& ID, string& valueString, vector<string> forbiddenValueStrings);
	void _deleteValueForm(const string& ID);
	void _deleteAnswerForm(const string& ID);

	FabiEngine3D& _fe3d;

	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWritefield>> _writefields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;

	vector<string> _valueFormIDs;
	string _choiceFormID = "";
	string _answerFormID = "";

	bool _isFocused = false;
	bool _exitValueFilling = false;
};