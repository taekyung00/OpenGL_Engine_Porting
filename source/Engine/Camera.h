/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once

#include "Component.h"
#include "Matrix.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"

namespace CS230
{
	class Camera : public Component
	{
	public:
		Camera(Math::rect player_zone);
		bool&			  SetFirstPersonView();
		bool&			  SetAnchoring();
		void			  SetPosition(Math::vec2 new_position);
		void			  SetRotation(double new_rotation);
		void			  SetScale(Math::vec2 new_scale);
		const Math::vec2& GetPosition() const;
		void			  SetLimit(Math::irect new_limit);
		using Component::Update; // say i'll use this version too, so don't hide anymore
		void					   Update(const Math::vec2& player_position);
		Math::TransformationMatrix GetMatrix();

	private:
		Math::irect				   limit;
		bool					   first_person_view{ true };
		bool					   anchoring{ true };
		Math::vec2				   position;
		bool					   is_position_outdated{ true };
		double					   rotation;
		bool					   is_rotation_outdated{ true };
		Math::vec2				   scale;
		bool					   is_scale_outdated{ true };
		Math::rect				   player_zone;
		Math::TransformationMatrix camera_matrix{};
		Math::TransformationMatrix view_matrix{};
	};
}
