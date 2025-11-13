/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Fall
 * \par CS200 Computer Graphics I
 * \copyright DigiPen Institute of Technology
 */

#include "Samurai.h"
#include "Engine/Input.hpp"

Samurai::Samurai() : 
	GameObject({100,100})
{
	AddGOComponent(new CS230::Sprite("Assets/sprites/DemoSceneShowcase/Samurai.spt", this));
	AddGOComponent(new CS230::ShowCollision());
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}

void Samurai::Update([[maybe_unused]] double dt)
{
	GameObject::Update(dt);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
	{
		SetVelocity({ velocity.x, GetVelocity().y });
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left))
	{
		SetVelocity({ -velocity.x, GetVelocity().y });
	}
	else
	{
		SetVelocity({ 0, GetVelocity().y });
	}

	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up))
	{
		SetVelocity({ GetVelocity().x, velocity.y });
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Down))
	{
		SetVelocity({ GetVelocity().x, -velocity.y });
	}
	else
	{
		SetVelocity({ GetVelocity().x, 0 });
	}

}

void Samurai::Draw(Math::TransformationMatrix camera_matrix, unsigned int color, float depth)
{
	GameObject::Draw(camera_matrix * Math::ScaleMatrix(1.0), color, depth);
}
