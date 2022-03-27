#pragma once

#include "engine_interface.hpp"

class GuiQuadField final
{
public:
	GuiQuadField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered);
	~GuiQuadField();

	void setVisible(bool value);
	void setColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setSize(const fvec2 & value);
	void setOpacity(float value);
	void setMinPosition(const fvec2 & value);
	void setMaxPosition(const fvec2 & value);
	void setDiffuseMap(const string & value);

	const string & getId() const;
	const string & getParentId() const;
	const string & getDiffuseMapPath() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool isVisible() const;
	const bool isCentered() const;

protected:
	const string _id;
	const string _parentId;
	const string _entityId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};