#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_write_field.hpp"
#include "gui_button.hpp"
#include "gui_rectangle.hpp"
#include "gui_text_field.hpp"

class GuiScreen final
{
public:
	GuiScreen(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size);

	void update(bool hoverable);
	void show();
	void hide();
	void createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered);
	void createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered);
	void createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);

	const string& getID() const;
	const string& getParentID() const;

	const fvec2 convertPosition(fvec2 position) const;
	const fvec2 convertSize(fvec2 size) const;

	const bool isScrollingListExisting(const string& ID) const;
	const bool isWriteFieldExisting(const string& ID) const;
	const bool isButtonExisting(const string& ID) const;
	const bool isRectangleExisting(const string& ID) const;
	const bool isTextFieldExisting(const string& ID) const;

	shared_ptr<GuiScrollingList> getScrollingList(const string& ID) const;
	shared_ptr<GuiWriteField> getWriteField(const string& ID) const;
	shared_ptr<GuiButton> getButton(const string& ID) const;
	shared_ptr<GuiRectangle> getRectangle(const string& ID) const;
	shared_ptr<GuiTextField> getTextField(const string& ID) const;
	const vector<shared_ptr<GuiScrollingList>>& getScrollingLists() const;
	const vector<shared_ptr<GuiWriteField>>& getWriteFields() const;
	const vector<shared_ptr<GuiButton>>& getButtons() const;
	const vector<shared_ptr<GuiRectangle>>& getRectangles() const;
	const vector<shared_ptr<GuiTextField>>& getTextFields() const;

private:
	const fvec4 _convertDimensions(fvec2 position, fvec2 size) const;

	fvec2 _parentPosition;
	fvec2 _parentSize;

	const string _ID;
	const string _parentID;

	bool _isActive = false;

	vector<shared_ptr<GuiScrollingList>> _scrollingLists;
	vector<shared_ptr<GuiWriteField>> _writeFields;
	vector<shared_ptr<GuiButton>> _buttons;
	vector<shared_ptr<GuiRectangle>> _rectangles;
	vector<shared_ptr<GuiTextField>> _textFields;
	shared_ptr<EngineInterface> _fe3d;
};