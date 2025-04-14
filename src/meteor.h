#ifndef METEOR_H
#define METEOR_H

#include "raylib.h"
#include "math.h"

class Meteor
{
private:
	int HEIGHT;
	int WIDTH;
	int OFFSET;

	Vector2 Position;

	double Radius; // 10 or 5
	double Angle;  // 0 - PI^2

	double speedX; // 2 - 6
	double speedY; // 2 - 6

	void MoveRock();

public:
	Meteor(const int height, const int width, const int offset, const int radius);
	
	Meteor(const int height, const int width, const int offset, const int radius, Vector2 Position, double angle);

	~Meteor();

	void Update();

	void Draw();

	Vector2 GetPosition();
	
	double &GetRadius();

	double GetAngle();

};



#endif