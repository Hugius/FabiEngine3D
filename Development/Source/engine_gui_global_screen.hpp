#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_scrolling_list.hpp"
#include "engine_gui_write_field.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiGlobalScreen final
{
public:
	EngineGuiGlobalScreen(FabiEngine3D& fe3d);

	// Voids
	void update();
	void setFocus(bool focused);
	void createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize);
	void createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor);
	void createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath);
	void createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered = true);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);
	void createValueForm(const string& ID, string title, unsigned int value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void createValueForm(const string& ID, string title, int value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void createValueForm(const string& ID, string title, float value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void createValueForm(const string& ID, string title, double value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void createValueForm(const string& ID, string title, string value, Vec2 position, Vec2 size, Vec2 buttonsPosition);
	void createChoiceForm(const string& ID, string title, Vec2 position, vector<string> buttonTitles);
	void deleteChoiceForm(const string& ID);
	void createAnswerForm(const string& ID, string title, Vec2 position);

	// Strings
	const string checkChoiceForm(const string& ID);

	// Booleans
	bool isFocused();
	bool isScrollingListExisting(const string& ID);
	bool isWriteFieldExisting(const string& ID);
	bool isButtonExisting(const string& ID);
	bool isRectangleExisting(const string& ID);
	bool isTextFieldExisting(const string& ID);
	bool checkValueForm(const string& ID, unsigned int& value, vector<unsigned int> forbiddenValues = {});
	bool checkValueForm(const string& ID, int& value, vector<int> forbiddenValues = {});
	bool checkValueForm(const string& ID, float& value, vector<float> forbiddenValues = {});
	bool checkValueForm(const string& ID, double& value, vector<double> forbiddenValues = {});
	bool checkValueForm(const string& ID, string& value, vector<string> forbiddenValues = {});
	bool isValueFormConfirmed();
	bool isValueFormCancelled();
	bool isValueFormExisting(const string& ID);
	bool isChoiceFormCancelled(const string& ID);
	bool isChoiceFormExisting(const string& ID);
	bool isAnswerFormConfirmed(const string& ID);
	bool isAnswerFormDenied(const string& ID);
	bool isAnswerFormExisting(const string& ID);

	// GUI elements
	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWriteField> getWriteField(const string& ID);
	shared_ptr<EngineGuiButton> getButton(const string& ID);
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID);
	shared_ptr<EngineGuiTextField> getTextField(const string& ID);
	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWriteField>>& getWriteFields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextField>>& getTextFields();

private:
	// Voids
	void _createValueForm(const string& ID, string title, string valueString, Vec2 position, Vec2 size, Vec2 buttonsPosition, bool onlyNumbers, bool minusAllowed);
	void _updateValueFormDeleting();
	void _deleteAnswerForm(const string& ID);
	bool _checkValueForm(const string& ID, string& valueString, vector<string> forbiddenValueStrings);

	// Instances
	FabiEngine3D& _fe3d;

	// GUI elements
	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextField>> _textFields;

	// Strings
	vector<string> _valueFormIDs;
	string _choiceFormID = "";
	string _answerFormID = "";

	// Booleans
	bool _isFocused = false;
	bool _mustDeleteValueForms = false;
};