#pragma once

#include "fe3d.hpp"
#include "engine_gui_scrolling_list.hpp"
#include "engine_gui_write_field.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiScreen final
{
public:
	// Constructors
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size);

	// VOID
	void update(bool hoverable);
	void show();
	void hide();
	void createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered);
	void createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	void createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered);
	void createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered);
	void createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered, bool isDynamic);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);

	// STRING
	const string& getID() const;
	const string& getParentID() const;

	// FVEC2
	const fvec2 convertPosition(fvec2 position) const;
	const fvec2 convertSize(fvec2 size) const;

	// BOOL
	const bool isScrollingListExisting(const string& ID) const;
	const bool isWriteFieldExisting(const string& ID) const;
	const bool isButtonExisting(const string& ID) const;
	const bool isRectangleExisting(const string& ID) const;
	const bool isTextFieldExisting(const string& ID) const;

	// Miscellaneous
	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID) const;
	shared_ptr<EngineGuiWriteField> getWriteField(const string& ID) const;
	shared_ptr<EngineGuiButton> getButton(const string& ID) const;
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID) const;
	shared_ptr<EngineGuiTextField> getTextField(const string& ID) const;
	const vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists() const;
	const vector<shared_ptr<EngineGuiWriteField>>& getWriteFields() const;
	const vector<shared_ptr<EngineGuiButton>>& getButtons() const;
	const vector<shared_ptr<EngineGuiRectangle>>& getRectangles() const;
	const vector<shared_ptr<EngineGuiTextField>>& getTextFields() const;

private:
	// FVEC4
	const fvec4 _convertDimensions(fvec2 position, fvec2 size) const;

	// FVEC2
	fvec2 _parentPosition;
	fvec2 _parentSize;

	// STRING
	const string _ID;
	const string _parentID;

	// BOOL
	bool _isActive = false;

	// Miscellaneous
	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextField>> _textFields;
	FabiEngine3D& _fe3d;
};