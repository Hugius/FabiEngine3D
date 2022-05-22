#pragma once

#include "mathematics.hpp"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class StartedAnimation3d final
{
public:
	void setPartIds(const vector<string> & value);
	void setPlayCount(int value);
	void setPaused(bool value);
	void setAutopaused(bool value);
	void setSpeedMultiplier(float value);
	void setFrameIndex(int value);
	void setTotalMovement(const string & partId, const fvec3 & value);
	void setTotalRotation(const string & partId, const fvec3 & value);
	void setTotalScaling(const string & partId, const fvec3 & value);
	void setTotalSpeed(const string & partId, const fvec3 & value);

	const vector<string> & getPartIds() const;

	const fvec3 & getTotalMovement(const string & partId) const;
	const fvec3 & getTotalRotation(const string & partId) const;
	const fvec3 & getTotalScaling(const string & partId) const;
	const fvec3 & getTotalSpeed(const string & partId) const;

	const float getSpeedMultiplier() const;

	const int getFrameIndex() const;
	const int getPlayCount() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

private:
	unordered_map<string, fvec3> _totalMovements = {};
	unordered_map<string, fvec3> _totalRotations = {};
	unordered_map<string, fvec3> _totalScalings = {};
	unordered_map<string, fvec3> _totalSpeeds = {};

	vector<string> _partIds = {};

	float _speedMultiplier = 1.0f;

	int _frameIndex = 0;
	int _playCount = 0;

	bool _isPaused = false;
	bool _isAutopaused = false;
};