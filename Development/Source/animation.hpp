#pragma once

#include "animation_frame.hpp"

#include <vector>

using std::vector;

class Animation final
{
public:
	Animation(const string& ID);

	// Voids
	void addFrame(const AnimationFrame& value);
	void setFrame(unsigned int index, const AnimationFrame& value);
	void setFrames(const vector<AnimationFrame>& value);
	void addPart(const string& partID, Vec3 totalMovement, Vec3 totalRotation, Vec3 totalScaling);
	void setPreviewModelID(const string& value);
	void setOldPreviewModelID(const string& value);
	void setAnimatedModelID(const string& value);
	void setTotalMovement(const string& partID, Vec3 value);
	void setTotalRotation(const string& partID, Vec3 value);
	void setTotalScaling(const string& partID, Vec3 value);
	void setInitialSize(Vec3 value);
	void setSpeedMultiplier(float value);
	void setTimesToPlay(int value);
	void setFadeFramestep(int value);
	void setFadeFrameIndex(int value);
	void setFrameIndex(unsigned int value);
	void setPaused(bool value);
	void setAutoPaused(bool value);

	// Instances
	const vector<AnimationFrame>& getFrames() const;

	// Strings
	const string& getID() const;
	const vector<string>& getPartIDs() const;
	const string& getPreviewModelID() const;
	const string& getOldPreviewModelID() const;
	const string& getAnimatedModelID() const;

	// Vectors
	const map<string, Vec3>& getTotalMovements() const;
	const map<string, Vec3>& getTotalRotations() const;
	const map<string, Vec3>& getTotalScalings() const;
	const Vec3 getInitialSize() const;

	// Floats
	const float getSpeedMultiplier() const;

	// Integers
	const int getTimesToPlay() const;
	const int getFadeFramestep() const;
	const int getFadeFrameIndex() const;
	const unsigned int getFrameIndex() const;

	// Booleans
	const bool isPaused() const;
	const bool isAutoPaused() const;

private:
	// Instances
	vector<AnimationFrame> _frames;

	// Strings
	const string _ID;
	vector<string> _partIDs;
	string _previewModelID = "";
	string _oldPreviewModelID = "";
	string _animatedModelID = "";

	// Vectors
	map<string, Vec3> _totalMovements;
	map<string, Vec3> _totalRotations;
	map<string, Vec3> _totalScalings;
	Vec3 _initialSize = Vec3(0.0f);

	// Floats
	float _speedMultiplier = 1.0f;

	// Integers
	int _timesToPlay = 0;
	int _fadeFramestep = -1;
	int _fadeFrameIndex = -1;
	unsigned int _frameIndex = 0;

	// Booleans
	bool _isPaused = false;
	bool _isAutoPaused = false;
};