#pragma once

#include "fe3d.hpp"
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
	void createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize, bool isCentered);
	void createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	void createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered);
	void createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered, bool isDynamic);
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
	void createChoiceForm(const string& ID, string title, Vec2 position, const vector<string>& buttonTitles);
	void deleteChoiceForm(const string& ID);
	void createAnswerForm(const string& ID, string title, Vec2 position);

	// Strings
	const string& checkChoiceForm(const string& ID);

	// Booleans
	const bool isFocused() const;
	const bool isScrollingListExisting(const string& ID) const;
	const bool isWriteFieldExisting(const string& ID) const;
	const bool isButtonExisting(const string& ID) const;
	const bool isRectangleExisting(const string& ID) const;
	const bool isTextFieldExisting(const string& ID) const;
	const bool checkValueForm(const string& ID, unsigned int& value, const vector<unsigned int>& forbiddenValues = {});
	const bool checkValueForm(const string& ID, int& value, const vector<int>& forbiddenValues = {});
	const bool checkValueForm(const string& ID, float& value, const vector<float>& forbiddenValues = {});
	const bool checkValueForm(const string& ID, double& value, const vector<double>& forbiddenValues = {});
	const bool checkValueForm(const string& ID, string& value, const vector<string>& forbiddenValues = {});
	const bool isValueFormConfirmed() const;
	const bool isValueFormCancelled() const;
	const bool isValueFormExisting(const string& ID) const;
	const bool isChoiceFormCancelled(const string& ID) const;
	const bool isChoiceFormExisting(const string& ID) const;
	const bool isAnswerFormConfirmed(const string& ID);
	const bool isAnswerFormDenied(const string& ID);
	const bool isAnswerFormExisting(const string& ID) const;

	// GUI elements
	const vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists() const;
	const vector<shared_ptr<EngineGuiWriteField>>& getWriteFields() const;
	const vector<shared_ptr<EngineGuiButton>>& getButtons() const;
	const vector<shared_ptr<EngineGuiRectangle>>& getRectangles() const;
	const vector<shared_ptr<EngineGuiTextField>>& getTextFields() const;
	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID) const;
	shared_ptr<EngineGuiWriteField> getWriteField(const string& ID) const;
	shared_ptr<EngineGuiButton> getButton(const string& ID) const;
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID) const;
	shared_ptr<EngineGuiTextField> getTextField(const string& ID) const;

private:
	// Voids
	void _createValueForm(const string& ID, string title, string valueString, Vec2 position, Vec2 size, Vec2 buttonsPosition, bool onlyNumbers, bool minusAllowed);
	void _updateValueFormDeleting();
	void _deleteAnswerForm(const string& ID);

	// Booleans
	const bool _checkValueForm(const string& ID, string& valueString, const vector<string>& forbiddenValueStrings);

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

	// Miscellaneous
	FabiEngine3D& _fe3d;
};