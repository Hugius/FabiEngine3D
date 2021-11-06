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
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size);

	// Voids
	void update(bool hoverable);
	void show();
	void hide();
	void createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize);
	void createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor);
	void createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered = true);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered = true);
	void createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered = true, bool isDynamic = false);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);

	// Strings
	const string& getID() const;
	const string& getParentID() const;

	// Vectors
	const Vec2 convertPosition(Vec2 position) const;
	const Vec2 convertSize(Vec2 size) const;

	// Booleans
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
	// Vectors
	const Vec4 _convertDimensions(Vec2 position, Vec2 size) const;

	// Vectors
	Vec2 _parentPosition;
	Vec2 _parentSize;

	// Strings
	const string _ID;
	const string _parentID;

	// Booleans
	bool _isActive = false;

	// Miscellaneous
	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextField>> _textFields;
	FabiEngine3D& _fe3d;
};