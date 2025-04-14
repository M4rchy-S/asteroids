#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <raylib.h>
#include <math.h>
#include <algorithm>
#include <list>

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#include "meteor.h"
#include "bullet.h"



//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
enum GameScreen { TITLE = 0, GAMEPLAY, LOST, WON };

const unsigned int SIDE_LEN = 10;
const double ROT_SPEED = 0.07f;
const double MOV_SPEED = -6;
const int OFFSET = 50;

//const double PI_SQ = 9.869604401089358;
//const double PI_SQ_NEG = -9.869604401089358;

//------------------------------------------------------------------------------------------
// Game Class
//------------------------------------------------------------------------------------------
class Asteroids {
public:
	Asteroids(const int height, const int width, GameScreen &screen);

	~Asteroids();

	void Update();

	void Draw();

	void ResetGame();

private:

	Vector2 RotatePoint(const Vector2 point, double angle);
	void MovePlayer(double speed_x, double speed_y);

	void LoseGame();

	void WinGame();

	int HEIGHT;
	int WIDTH;

	GameScreen* screen_ptr;

	double speedX;
	double speedY;

	Vector2 playerCenter;
	Vector2 playerA;
	Vector2 playerB;
	Vector2 playerC;

	double Angle;

	std::list<Meteor> MeteorList;
	std::list<Bullet> BulList;

	int remainRocks;

};

#endif