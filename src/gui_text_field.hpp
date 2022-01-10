#pragma once

#include "engine_interface.hpp"

class GuiTextField final
{
public:
	GuiTextField(EngineInterface& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size,
				 string textContent, fvec3 color, bool isCentered);
	~GuiTextField();

	void setVisible(bool isVisible);
	void changeTextContent(const string& content);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	const fvec3 getInitialColor() const;

	const fvec2 getInitialPosition() const;
	const fvec2 getInitialSize() const;

private:
	const string _ID;
	const string _entityID;
	const string _parentID;

	fvec3 _initialColor;

	fvec2 _initialPosition;
	fvec2 _initialSize;

	EngineInterface& _fe3d;
};