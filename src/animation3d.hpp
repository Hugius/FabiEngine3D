#pragma once

#include "animation3d_frame.hpp"

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Animation3d final
{
public:
	Animation3d(const string & id);

	void createPart(const string & partId);
	void deletePart(const string & partId);
	void deleteParts();
	void createFrame(int index);
	void deleteFrame(int index);
	void deleteFrames();
	void setTargetTransformation(int frameIndex, const string & partId, const fvec3 & value);
	void setRotationOrigin(int frameIndex, const string & partId, const fvec3 & value);
	void setSpeed(int frameIndex, const string & partId, const fvec3 & value);
	void setSpeedType(int frameIndex, const string & partId, SpeedType value);
	void setTransformationType(int frameIndex, const string & partId, TransformationType value);

	const vector<string> & getPartIds() const;

	const string & getId() const;

	const fvec3 & getTargetTransformation(int frameIndex, const string & partId) const;
	const fvec3 & getRotationOrigin(int frameIndex, const string & partId) const;
	const fvec3 & getSpeed(int frameIndex, const string & partId) const;

	const int getFrameCount() const;

	const SpeedType & getSpeedType(int frameIndex, const string & partId) const;
	const TransformationType & getTransformationType(int frameIndex, const string & partId) const;

private:
	const string _id;

	vector<string> _partIds = {};
	vector<unique_ptr<Animation3dFrame>> _frames = {};
};