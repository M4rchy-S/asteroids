#include "meteor.h"

void Meteor::MoveRock()
{
	float x_delta = cos(this->Angle) * this->speedX;
	float y_delta = sin(this->Angle) * this->speedY;

	this->Position.x = this->Position.x + x_delta;
	this->Position.y = this->Position.y + y_delta;


	if (this->Position.x > this->WIDTH + OFFSET)
	{

		this->Position.x = 0 - OFFSET + 35;
	}
	else if (this->Position.x < -OFFSET )
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

Meteor::Meteor(const int height, const int width, const int offset, const int radius)
{
	this->HEIGHT = height;
	this->WIDTH = width;
	this->OFFSET = offset;

	this->Radius = radius;

	this->Angle = GetRandomValue(0, int(PI * PI + 0.2));

	while (true)
	{
		this->Position = {
		static_cast<float>(GetRandomValue(0, this->WIDTH)),
		static_cast<float>(GetRandomValue(0, this->HEIGHT))
		};

		double distance = sqrt( pow(this->WIDTH / 2 - this->Position.x, 2) + pow(this->HEIGHT / 2 - this->Position.y, 2) );

		if (distance < 225)
			continue;

		break;

	}

	

	this->speedX = static_cast<float>(GetRandomValue(-2, -5));
	this->speedY = static_cast<float>(GetRandomValue(-2, -5));

}

Meteor::Meteor(const int height, const int width, const int offset, const int radius, Vector2 Position, double angle)
{
	this->HEIGHT = height;
	this->WIDTH = width;
	this->OFFSET = offset;

	this->Radius = radius;

	this->Angle = angle;

	this->Position = {
		Position.x,
		Position.y
	};

	this->speedX = static_cast<float>(GetRandomValue(-2, -5));
	this->speedY = static_cast<float>(GetRandomValue(-2, -5));


}

Meteor::~Meteor()
{

}

void Meteor::Update()
{
	this->MoveRock();
}

void Meteor::Draw()
{
	DrawCircle(this->Position.x, this->Position.y, this->Radius, RAYWHITE);
}

Vector2 Meteor::GetPosition()
{
	return {this->Position.x, this->Position.y} ;
}

double &Meteor::GetRadius()
{
	return this->Radius;
}

double Meteor::GetAngle()
{
	return this->Angle;
}
