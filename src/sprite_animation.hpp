#pragma once

class SpriteAnimation final
{
public:
	// VOIDS
	void startSpriteAnimation(int loops);
	void pauseSpriteAnimation();
	void resumeSpriteAnimation();
	void stopSpriteAnimation();
	void setSpriteAnimationRowIndex(unsigned int value);
	void setSpriteAnimationColumnIndex(unsigned int value);
	void setTotalSpriteAnimationRowCount(unsigned int value);
	void setTotalSpriteAnimationColumnCount(unsigned int value);
	void setSpriteAnimationFramestep(unsigned int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();

	// INT
	const int getMaxLoops() const;

	// UNSIGNED INT
	const unsigned int getPassedFrames() const;
	const unsigned int getFramestep() const;
	const unsigned int getRowCount() const;
	const unsigned int getColumnCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;
	const unsigned int getLoops() const;

	// BOOL
	const bool isSpriteAnimationStarted() const;
	const bool isSpriteAnimationPaused() const;

private:
	// INT
	int _maxLoops = 0;

	// UNSIGNED INT
	unsigned int _framestep = 0;
	unsigned int _passedFrames = 0;
	unsigned int _rowCount = 0;
	unsigned int _columnCount = 0;
	unsigned int _rowIndex = 0;
	unsigned int _columnIndex = 0;
	unsigned int _loops = 0;

	// BOOL
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused = false;
};