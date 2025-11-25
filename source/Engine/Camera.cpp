/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/
#include "Camera.h"
#include "Engine.hpp"
#include "Matrix.hpp"

CS230::Camera::Camera(Math::rect _player_zone) :  position(Math::vec2{0.0,0.0}), offset(0.0,0.0), rotation(0.0), scale(Math::vec2{1.0,1.0}), player_zone(_player_zone)  {}

bool& CS230::Camera::SetFirstPersonView()
{
    return first_person_view;
}

bool& CS230::Camera::SetAnchoring()
{
    return anchoring;
}

void CS230::Camera::SetPosition(Math::vec2 new_position){
    position = new_position;
    is_position_outdated = true;
}

void CS230::Camera::SetRotation(double new_rotation)
{
    if(first_person_view)
    {
        rotation = new_rotation;
        is_rotation_outdated = true;
    }
}

void CS230::Camera::SetScale(Math::vec2 new_scale)
{
    if(first_person_view)
    {
        scale = new_scale;
        is_scale_outdated = true;
    }
}

void CS230::Camera::SetPositionOffset(Math::vec2 new_offset)
{
	offset = new_offset;
	is_position_outdated = true;
}

const Math::vec2& CS230::Camera::GetPosition() const { return position; }

void CS230::Camera::SetLimit(Math::irect new_limit){
    limit = new_limit;
}

void CS230::Camera::Update(const Math::vec2& player_position){
    if(anchoring)
    {
        SetPosition(player_position);
        return;
    }

    if (player_position.x > player_zone.Right() + position.x) {
        position.x = player_position.x - player_zone.Right();
        is_position_outdated = true;
    }
    if (player_position.x - position.x < player_zone.Left()) {
        position.x = player_position.x - player_zone.Left();
        is_position_outdated = true;
    }

    if (player_position.y > player_zone.Top() + position.y) {
        position.y = player_position.y - player_zone.Top();
        is_position_outdated = true;
    }
    if (player_position.y - position.y < player_zone.Bottom()) {
        position.y = player_position.y - player_zone.Bottom();
        is_position_outdated = true;
    }


    if (position.x < limit.Left()) {
        position.x = limit.Left();
        is_position_outdated = true;
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
        is_position_outdated = true;
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
        is_position_outdated = true;
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
        is_position_outdated = true;
    }
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    if(first_person_view){
        if(is_position_outdated || is_rotation_outdated || is_scale_outdated){
            camera_matrix = Math::TranslationMatrix(position - offset) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
            view_matrix = camera_matrix;
            std::swap(view_matrix[0][1], view_matrix[1][0]);
            view_matrix[0][2] = -(camera_matrix[0][0] * camera_matrix[0][2] + camera_matrix[1][0] * camera_matrix[1][2]);
            view_matrix[1][2] = -(camera_matrix[0][1] * camera_matrix[0][2] + camera_matrix[1][1] * camera_matrix[1][2]);
            is_position_outdated = false;
            is_rotation_outdated = false;
            is_scale_outdated = false;
            
        }
    }
    else
    {
        if(is_position_outdated){
            camera_matrix = Math::TranslationMatrix(position - offset) ;
            view_matrix = camera_matrix;
            view_matrix[0][2] = -(camera_matrix[0][0] * camera_matrix[0][2] + camera_matrix[1][0] * camera_matrix[1][2]);
            view_matrix[1][2] = -(camera_matrix[0][1] * camera_matrix[0][2] + camera_matrix[1][1] * camera_matrix[1][2]);
            is_position_outdated = false;
        }
    }
    return view_matrix;
}

