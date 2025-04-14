#include "asteroids.h"

Asteroids::Asteroids(const int height, const int width, GameScreen &screen)
{
	this->HEIGHT = height;
	this->WIDTH = width;

	this->screen_ptr = &screen;

	this->ResetGame();


}

Asteroids::~Asteroids()
{
	this->screen_ptr = nullptr;
}

void Asteroids::Update()
{
	//	Player input
	//	-------------------------------------------------------
	

	if (IsKeyDown(KEY_LEFT))
	{
		double newAngle = this->Angle - ROT_SPEED;

#ifdef DEBUG
		std::cout << "Angle: " << this->Angle * 180 / PI << " Grad\n";
		std::cout << "Angle: " << this->Angle  << " RAD\n";
#endif

		this->playerA = this->RotatePoint(this->playerA, newAngle - this->Angle  );
		this->playerB = this->RotatePoint(this->playerB, newAngle - this->Angle  );
		this->playerC = this->RotatePoint(this->playerC, newAngle - this->Angle  );

		this->Angle = newAngle;
		
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		double newAngle = this->Angle + ROT_SPEED;
#ifdef DEBUG
		std::cout << "Angle: " << this->Angle * 180 / PI << " Grad\n";
		std::cout << "Angle: " << this->Angle << " RAD\n";
#endif

		this->playerA = this->RotatePoint(this->playerA, newAngle - this->Angle);
		this->playerB = this->RotatePoint(this->playerB, newAngle - this->Angle);
		this->playerC = this->RotatePoint(this->playerC, newAngle - this->Angle);

		this->Angle = newAngle;
		
	}

	if (IsKeyDown(KEY_UP))
	{

		this->speedX -= 0.125;
		this->speedY -= 0.125;
		
		this->speedX = std::max(MOV_SPEED, this->speedX);
		this->speedY = std::max(MOV_SPEED, this->speedY);
	
		this->MovePlayer(this->speedX, this->speedY);

	}
	else if (this->speedX < 0 || this->speedY < 0)
	{
		if (this->speedX < 0)
			this->speedX += 0.075;
		if (this->speedY < 0)
			this->speedY += 0.075;
		
		this->MovePlayer(this->speedX, this->speedY);
	}

	if (IsKeyReleased(KEY_SPACE))
	{

		this->BulList.push_back( Bullet(this->HEIGHT, this->WIDTH, OFFSET, 3, this->Angle, this->playerA.x, this->playerA.y) );


	}


	//	Game Logic
	//	-------------------------------------------------------
	for (auto &meteor : MeteorList)
	{
		meteor.Update();

		if (CheckCollisionPointCircle(this->playerA, meteor.GetPosition(), meteor.GetRadius() ) || 
			CheckCollisionPointCircle(this->playerB, meteor.GetPosition(), meteor.GetRadius() ) ||
			CheckCollisionPointCircle(this->playerC, meteor.GetPosition(), meteor.GetRadius())	||
			CheckCollisionPointCircle(this->playerCenter, meteor.GetPosition(), meteor.GetRadius() ) )
		{
			this->LoseGame();
		}

	}

	for (auto it = this->BulList.begin(); it != this->BulList.end(); )
	{
		it->Update();
		if (it->DestroyOnColl(this->MeteorList) )
		{
			it = BulList.erase(it);
			this->remainRocks--;
			if (this->remainRocks == 0)
			{
				WinGame();
				break;
			}
			continue;
		}

		if (it->GetFrame() > 60)
		{
			it = BulList.erase(it);
		}
		else
		{
			it++;
		}

	}

}

void Asteroids::Draw()
{

	DrawTriangle(playerA, playerB, playerC, RED );

	for (auto& meteor : this->MeteorList)
	{
		meteor.Draw();
	}

	for (auto& bullet : this->BulList)
	{
		bullet.Draw();
	}

}

Vector2 Asteroids::RotatePoint(const Vector2 point, const double angle)
{
	Vector2 ret_point = { 0, 0 };

	ret_point.x = this->playerCenter.x + (point.x - this->playerCenter.x) * cos(angle) - (point.y - this->playerCenter.y) * sin(angle);
	ret_point.y = this->playerCenter.y + (point.x - this->playerCenter.x) * sin(angle) + (point.y - this->playerCenter.y) * cos(angle);

	return ret_point;
}

void Asteroids::MovePlayer(double speed_x, double speed_y)
{
#ifdef DEBUG
	std::cout << "PlayerCenter: [" << this->playerCenter.x << ", " << this->playerCenter.y << "]\n";
#endif

	float x_delta = cos(this->Angle) * speed_x;
	float y_delta = sin(this->Angle) * speed_y;

	this->playerCenter.x = this->playerCenter.x + x_delta;
	this->playerCenter.y = this->playerCenter.y + y_delta;

	this->playerA.x = this->playerA.x + x_delta;
	this->playerA.y = this->playerA.y + y_delta;

	this->playerB.x = this->playerB.x + x_delta;
	this->playerB.y = this->playerB.y + y_delta;

	this->playerC.x = this->playerC.x + x_delta;
	this->playerC.y = this->playerC.y + y_delta;

	
	if (this->playerA.x > this->WIDTH + OFFSET || this->playerB.x > this->WIDTH + OFFSET || this->playerC.x > this->WIDTH + OFFSET)
	{

		this->playerA.x = -(this->playerCenter.x - this->playerA.x) - + 0 - OFFSET + 35;
		this->playerB.x = -(this->playerCenter.x - this->playerB.x) + 0 - OFFSET + 35;
		this->playerC.x = -(this->playerCenter.x - this->playerC.x) + 0 - OFFSET + 35;
		this->playerCenter.x = 0 - OFFSET + 35;
	}
	else if (this->playerA.x < -OFFSET || this->playerB.x < -OFFSET || this->playerC.x < -OFFSET)
	{
		this->playerA.x = this->WIDTH + OFFSET - 35 - (this->playerCenter.x - this->playerA.x);
		this->playerB.x = this->WIDTH + OFFSET - 35 - (this->playerCenter.x - this->playerB.x);
		this->playerC.x = this->WIDTH + OFFSET - 35 - (this->playerCenter.x - this->playerC.x);
		this->playerCenter.x = this->WIDTH + OFFSET - 35;
	}
	else if (this->playerA.y > this->HEIGHT + OFFSET || this->playerB.y > this->HEIGHT + OFFSET || this->playerC.y > this->HEIGHT + OFFSET)
	{
		this->playerA.y = -(this->playerCenter.y - this->playerA.y) + 0 - OFFSET + 35;
		this->playerB.y = -(this->playerCenter.y - this->playerB.y) + 0 - OFFSET + 35;
		this->playerC.y = -(this->playerCenter.y - this->playerC.y) + 0 - OFFSET + 35;
		this->playerCenter.y = 0 - OFFSET + 35;
	}
	else if (this->playerA.y < -OFFSET || this->playerB.y < -OFFSET || this->playerC.y < -OFFSET)
	{
		this->playerA.y = this->HEIGHT + OFFSET - 35 - (this->playerCenter.y - this->playerA.y);
		this->playerB.y = this->HEIGHT + OFFSET - 35 - (this->playerCenter.y - this->playerB.y);
		this->playerC.y = this->HEIGHT + OFFSET - 35 - (this->playerCenter.y - this->playerC.y);
		this->playerCenter.y = this->HEIGHT + OFFSET - 35;
	}


}

void Asteroids::LoseGame()
{
	*this->screen_ptr = GameScreen::LOST;
}

void Asteroids::WinGame()
{
	*this->screen_ptr = GameScreen::WON;
}

void Asteroids::ResetGame()
{
	if(*this->screen_ptr != GameScreen::TITLE)
		*this->screen_ptr = GameScreen::GAMEPLAY;

	this->playerCenter = { this->WIDTH / 2.0f , this->HEIGHT / 2.0f };
	this->playerA = { this->playerCenter.x, this->playerCenter.y - SIDE_LEN - SIDE_LEN };
	this->playerB = { this->playerCenter.x - SIDE_LEN, this->playerCenter.y + SIDE_LEN };
	this->playerC = { this->playerCenter.x + SIDE_LEN, this->playerCenter.y + SIDE_LEN };


	this->Angle = 1.5708;
	this->speedX = 0;
	this->speedY = 0;

	this->MeteorList.clear();

	this->remainRocks = 8;

	for (int i = 0; i < this->remainRocks / 2; i++)
		this->MeteorList.push_back(Meteor(this->HEIGHT, this->WIDTH, OFFSET, 20));

	for (int i = 0; i < this->remainRocks / 2; i++)
		this->MeteorList.push_back(Meteor(this->HEIGHT, this->WIDTH, OFFSET, 60));

	this->BulList.clear();

	this->remainRocks += 8;

	

}




