#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "texture_buffer.hpp"

#include <array>

using std::array;

class ReflectionEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTarget();
	void capture();
	void setCaptured();
	void setPosition(const fvec3 & value);
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setCubeMap(shared_ptr<TextureBuffer> value);
	void setExceptionEntityId(const string & id);

	const shared_ptr<TextureBuffer> getCubeTextureBuffer() const;

	const string & getExceptionEntityId() const;

	const fvec3 & getPosition() const;

	const bool mustCapture() const;

private:
	shared_ptr<TextureBuffer> _cubeTextureBuffer = nullptr;

	string _exceptionEntityId = "";

	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	float _positionTargetSpeed = 0.0f;

	bool _mustCapture = false;
	bool _isCaptured = false;
};