#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "math.h"
#include "meteor.h"

#include <list>

class Bullet 
{
private:
	int HEIGHT;
	int WIDTH;
	int OFFSET;

	Vector2 Position;

	double Radius; // 10 or 5
	double Angle;  // 0 - PI^2

	double speedX;  
	double speedY; 

	void MoveBullet();

	unsigned int Frame;

public:
	Bullet(const int height, const int width, const int offset, const int radius, const double angle, float x, float y);
	~Bullet();

	void Update();

	void Draw();

	Vector2 GetPosition();
	
	double& GetRadius();

	int GetFrame();

	bool DestroyOnColl(std::list<Meteor> &MetLst);

};


#endif 
