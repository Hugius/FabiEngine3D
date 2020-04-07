#pragma once

class Collision
{
public:
	Collision(bool x, bool y, bool z);

	void operator+=(const Collision& c);

	void setX(bool val);
	void setY(bool val);
	void setZ(bool val);

	inline bool xCollided() const;
	inline bool yCollided() const;
	inline bool zCollided() const;

private:
	int p_x;
	int p_y;
	int p_z;
};