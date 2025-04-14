#include "bullet.h"

void Bullet::MoveBullet()
{
	float x_delta = cos(this->Angle) * this->speedX;
	float y_delta = sin(this->Angle) * this->speedY;

	this->Position.x = this->Position.x + x_delta;
	this->Position.y = this->Position.y + y_delta;


	if (this->Position.x > this->WIDTH + OFFSET)
	{

		this->Position.x = 0 - OFFSET + 35;
	}
	else if (this->Position.x < -OFFSET)
	{
		this->Position.x = this->WIDTH + OFFSET - 35;
	}
	else if (this->Position.y > this->HEIGHT + OFFSET)
	{
		this->Position.y = 0 - OFFSET + 35;
	}
	else if (this->Position.y < -OFFSET)
	{
		this->Position.y = this->HEIGHT + OFFSET - 35;
	}
}

Bullet::Bullet(const int height, const int width, const int offset, const int radius, const double angle, float x, float y)
{
	this->HEIGHT = height;
	this->WIDTH = width;
	this->OFFSET = offset;

	this->Radius = radius;

	this->Angle = angle;

	this->Position = {x, y};

	this->speedX = -8;
	this->speedY = -8;

	this->Frame = 0;
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	this->MoveBullet();
	this->Frame++;
}

void Bullet::Draw()
{
	DrawCircle(this->Position.x, this->Position.y, this->Radius, RAYWHITE);
}

Vector2 Bullet::GetPosition()
{
	return {this->Position.x, this->Position.y};
}

double& Bullet::GetRadius()
{
	return this->Radius;
}

int Bullet::GetFrame()
{
	return this->Frame;
}

bool Bullet::DestroyOnColl(std::list<Meteor>& MetLst)
{
	for (auto it = MetLst.begin(); it != MetLst.end(); )
	{
		if (CheckCollisionCircles(this->Position, this->Radius, it->GetPosition(), it->GetRadius()) )
		{
			if (it->GetRadius() == 60)
			{
				MetLst.push_back( Meteor(this->HEIGHT, this->WIDTH, OFFSET, 20, it->GetPosition(), this->Angle + 1.5708) );
				MetLst.push_back( Meteor(this->HEIGHT, this->WIDTH, OFFSET, 20, it->GetPosition(), this->Angle - 1.5708) );
			}

			it = MetLst.erase(it);
			return true;
		}
		else
		{
			it++;
		}
	}

	return false;
}



