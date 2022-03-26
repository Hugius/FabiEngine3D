#pragma once

#include "engine_interface.hpp"

class GuiQuadField
{
public:
	GuiQuadField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered);
	GuiQuadField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered);
	~GuiQuadField();

	virtual void setVisible(bool isVisible);

	const string& getId() const;
	const string& getEntityId() const;
	const string& getParentId() const;

	const fvec3& getColor() const;

	const fvec2& getPosition() const;
	const fvec2& getSize() const;

protected:
	const string _id;
	const string _parentId;
	const string _entityId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};