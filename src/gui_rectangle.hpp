#pragma once

#include "engine_interface.hpp"

class GuiRectangle
{
public:
	GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered);
	GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered);
	~GuiRectangle();

	virtual void setVisible(bool isVisible);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	const string& getId() const;
	const string& getEntityId() const;
	const string& getParentId() const;

	const fvec3& getInitialColor() const;

	const fvec2& getInitialPosition() const;
	const fvec2& getInitialSize() const;

protected:
	const string _id;
	const string _entityId;
	const string _parentId;

	fvec3 _initialColor;

	fvec2 _initialPosition;
	fvec2 _initialSize;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};