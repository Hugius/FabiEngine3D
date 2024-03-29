#pragma once

#include "mathematics.hpp"
#include "texture_buffer.hpp"

#include <array>
#include <string>

using std::string;
using std::array;

class Captor final
{
public:
	Captor(const string & id);

	void capture();
	void updateTarget();
	void setReflectionsCaptured();
	void setRefractionsCaptured();
	void setPosition(const fvec3 & value);
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setReflectionCubeMap(shared_ptr<TextureBuffer> value);
	void setRefractionCubeMap(shared_ptr<TextureBuffer> value);
	void setExceptionId(const string & value);
	void setReflectionQuality(int value);
	void setRefractionQuality(int value);

	const shared_ptr<TextureBuffer> getReflectionTextureBuffer() const;
	const shared_ptr<TextureBuffer> getRefractionTextureBuffer() const;

	const string & getId() const;
	const string & getExceptionId() const;

	const fvec3 & getPosition() const;

	const int getReflectionQuality() const;
	const int getRefractionQuality() const;

	const bool mustCaptureReflections() const;
	const bool mustCaptureRefractions() const;

private:
	const string _id;

	shared_ptr<TextureBuffer> _reflectionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _refractionTextureBuffer = nullptr;

	string _exceptionId = "";

	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	float _positionTargetSpeed = 0.0f;

	int _reflectionQuality = 128;
	int _refractionQuality = 128;

	bool _mustCaptureReflections = false;
	bool _mustCaptureRefractions = false;
};