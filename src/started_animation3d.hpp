#pragma once

#include "mathematics.hpp"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class StartedAnimation3d final
{
public:
	void setPartIds(const vector<string>& value);
	void setPlayCount(int value);
	void setPaused(bool value);
	void setAutopaused(bool value);
	void setSpeedMultiplier(float value);
	void setFrameIndex(unsigned int value);
	void setTotalMovement(const string& partId, const fvec3& value);
	void setTotalRotation(const string& partId, const fvec3& value);
	void setTotalScaling(const string& partId, const fvec3& value);
	void setTotalSpeed(const string& partId, const fvec3& value);

	const vector<string>& getPartIds() const;

	const fvec3& getTotalMovement(const string& partId) const;
	const fvec3& getTotalRotation(const string& partId) const;
	const fvec3& getTotalScaling(const string& partId) const;
	const fvec3& getTotalSpeed(const string& partId) const;

	const int getPlayCount() const;

	const float getSpeedMultiplier() const;

	const unsigned int getFrameIndex() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

private:
	vector<string> _partIds;

	unordered_map<string, fvec3> _totalMovements;
	unordered_map<string, fvec3> _totalRotations;
	unordered_map<string, fvec3> _totalScalings;
	unordered_map<string, fvec3> _totalSpeeds;

	int _playCount = 0;

	float _speedMultiplier = 1.0f;

	unsigned int _frameIndex = 0;

	bool _isPaused = false;
	bool _isAutopaused = false;
};