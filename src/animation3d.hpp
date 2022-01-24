#pragma once

#include "animation3d_frame.hpp"

#include <vector>

using std::vector;

class Animation3d final
{
public:
	Animation3d(const string& id);

	void addFrame(const Animation3dFrame& value);
	void setFrame(unsigned int index, const Animation3dFrame& value);
	void setFrames(const vector<Animation3dFrame>& value);
	void addPart(const string& partId, const fvec3& totalMovement, const fvec3& totalRotation, const fvec3& totalScaling);
	void setPreviewModelId(const string& value);
	void setTotalMovement(const string& partId, const fvec3& value);
	void setTotalRotation(const string& partId, const fvec3& value);
	void setTotalScaling(const string& partId, const fvec3& value);
	void setInitialSize(const fvec3& value);
	void setSpeed(float value);
	void setPlayCount(int value);
	void setFrameIndex(unsigned int value);
	void setPaused(bool value);
	void setAutopaused(bool value);

	const string& getId() const;
	const vector<string>& getPartIds() const;
	const string& getPreviewModelId() const;

	const map<string, fvec3>& getTotalMovements() const;
	const map<string, fvec3>& getTotalRotations() const;
	const map<string, fvec3>& getTotalScalings() const;
	const fvec3& getInitialSize() const;

	const float getSpeed() const;

	const int getPlayCount() const;

	const unsigned int getFrameIndex() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

	const vector<Animation3dFrame>& getFrames() const;

private:
	const string _id;
	vector<string> _partIds;
	string _previewModelId = "";

	map<string, fvec3> _totalMovements;
	map<string, fvec3> _totalRotations;
	map<string, fvec3> _totalScalings;
	fvec3 _initialSize = fvec3(0.0f);

	float _speed = 1.0f;

	int _playCount = 0;

	unsigned int _frameIndex = 0;

	bool _isPaused = false;
	bool _isAutopaused = false;

	vector<Animation3dFrame> _frames;
};