#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_write_field.hpp"
#include "gui_button.hpp"
#include "gui_rectangle.hpp"
#include "gui_text_field.hpp"

class GuiOverlay final
{
public:
	GuiOverlay(shared_ptr<EngineInterface> fe3d);

	void update();
	void setFocused(bool value);
	void createScrollingList(const string& ID, fvec2 position, fvec2 size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, fvec2 charSize, bool isCentered);
	void createWriteField(const string& ID, fvec2 position, fvec2 size, const fvec3& color, const fvec3& hoverColor, const fvec3& textColor, const fvec3& textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, const fvec3& color, const fvec3& hoverColor, string textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, const fvec3& hoverColor, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, const fvec3& color, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered);
	void createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, const fvec3& textColor, bool isCentered);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);
	void createValueForm(const string& ID, string title, unsigned int value, fvec2 position, fvec2 size, fvec2 buttonsPosition);
	void createValueForm(const string& ID, string title, int value, fvec2 position, fvec2 size, fvec2 buttonsPosition);
	void createValueForm(const string& ID, string title, float value, fvec2 position, fvec2 size, fvec2 buttonsPosition);
	void createValueForm(const string& ID, string title, double value, fvec2 position, fvec2 size, fvec2 buttonsPosition);
	void createValueForm(const string& ID, string title, string value, fvec2 position, fvec2 size, fvec2 buttonsPosition);
	void createChoiceForm(const string& ID, string title, fvec2 position, const vector<string>& buttonTitles);
	void deleteChoiceForm(const string& ID);
	void createAnswerForm(const string& ID, string title, fvec2 position);

	const string checkChoiceForm(const string& ID);

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

	const vector<shared_ptr<GuiScrollingList>>& getScrollingLists() const;
	const vector<shared_ptr<GuiWriteField>>& getWriteFields() const;
	const vector<shared_ptr<GuiButton>>& getButtons() const;
	const vector<shared_ptr<GuiRectangle>>& getRectangles() const;
	const vector<shared_ptr<GuiTextField>>& getTextFields() const;
	shared_ptr<GuiScrollingList> getScrollingList(const string& ID) const;
	shared_ptr<GuiWriteField> getWriteField(const string& ID) const;
	shared_ptr<GuiButton> getButton(const string& ID) const;
	shared_ptr<GuiRectangle> getRectangle(const string& ID) const;
	shared_ptr<GuiTextField> getTextField(const string& ID) const;

private:
	void _createValueForm(const string& ID, string title, string valueString, fvec2 position, fvec2 size, fvec2 buttonsPosition, bool onlyNumbers, bool minusAllowed);
	void _updateValueFormDeleting();
	void _deleteAnswerForm(const string& ID);

	const bool _checkValueForm(const string& ID, string& valueString, const vector<string>& forbiddenValueStrings);

	vector<shared_ptr<GuiScrollingList>> _scrollingLists;
	vector<shared_ptr<GuiWriteField>> _writeFields;
	vector<shared_ptr<GuiButton>> _buttons;
	vector<shared_ptr<GuiRectangle>> _rectangles;
	vector<shared_ptr<GuiTextField>> _textFields;

	vector<string> _valueFormIDs;
	string _choiceFormID = "";
	string _answerFormID = "";

	bool _isFocused = false;
	bool _mustDeleteValueForms = false;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};