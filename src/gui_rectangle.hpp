#pragma once

#include "engine_interface.hpp"

class GuiRectangle
{
public:
	GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered);
	GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered);
	~GuiRectangle();

	virtual void setVisible(bool isVisible);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	const fvec3& getInitialColor() const;

	const fvec2& getInitialPosition() const;
	const fvec2& getInitialSize() const;

protected:
	const string _ID;
	const string _entityID;
	const string _parentID;

	fvec3 _initialColor;

	fvec2 _initialPosition;
	fvec2 _initialSize;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};