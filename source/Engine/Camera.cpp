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

CS230::Camera::Camera(Math::rect _player_zone, size_t camera_amount) {
    cameras.resize(camera_amount);
    for(CameraSettings& cam : cameras){
        cam.player_zone = _player_zone;
        cam.position = Math::vec2{0.0,0.0};
        cam.offset = Math::vec2{0.0,0.0};
        cam.rotation = 0.0;
        cam.scale = Math::vec2{1.0,1.0};
    }
}

bool& CS230::Camera::SetFirstPersonView(size_t camera_index)
{
    return cameras[camera_index].first_person_view;
}

bool& CS230::Camera::SetAnchoring(size_t camera_index)
{
    return cameras[camera_index].anchoring;
}

void CS230::Camera::SetPosition(Math::vec2 new_position, size_t camera_index){
    cameras[camera_index].position = new_position;
    cameras[camera_index].is_position_outdated = true;
}

void CS230::Camera::SetRotation(double new_rotation, size_t camera_index)
{
    if(cameras[camera_index].first_person_view)
    {
        cameras[camera_index].rotation = new_rotation;
        cameras[camera_index].is_rotation_outdated = true;
    }
}

void CS230::Camera::SetScale(Math::vec2 new_scale, size_t camera_index)
{
    if(cameras[camera_index].first_person_view)
    {
        cameras[camera_index].scale = new_scale;
        cameras[camera_index].is_scale_outdated = true;
    }
}

void CS230::Camera::SetPositionOffset(Math::vec2 new_offset, size_t camera_index)
{
	cameras[camera_index].offset = new_offset;
	cameras[camera_index].is_position_outdated = true;
}

const Math::vec2& CS230::Camera::GetPosition(size_t camera_index) const { return cameras[camera_index].position; }

void CS230::Camera::SetLimit(Math::irect new_limit, size_t camera_index){
    cameras[camera_index].limit = new_limit;
}

void CS230::Camera::Update(const Math::vec2& player_position, size_t camera_index){
    if(cameras[camera_index].anchoring)
    {
        SetPosition(player_position, camera_index);
        return;
    }

    if (player_position.x > cameras[camera_index].player_zone.Right() + cameras[camera_index].position.x) {
        cameras[camera_index].position.x = player_position.x - cameras[camera_index].player_zone.Right();
        cameras[camera_index].is_position_outdated = true;
    }
    if (player_position.x - cameras[camera_index].position.x < cameras[camera_index].player_zone.Left()) {
        cameras[camera_index].position.x = player_position.x - cameras[camera_index].player_zone.Left();
        cameras[camera_index].is_position_outdated = true;
    }

    if (player_position.y > cameras[camera_index].player_zone.Top() + cameras[camera_index].position.y) {
        cameras[camera_index].position.y = player_position.y - cameras[camera_index].player_zone.Top();
        cameras[camera_index].is_position_outdated = true;
    }
    if (player_position.y - cameras[camera_index].position.y < cameras[camera_index].player_zone.Bottom()) {
        cameras[camera_index].position.y = player_position.y - cameras[camera_index].player_zone.Bottom();
        cameras[camera_index].is_position_outdated = true;
    }


    if (cameras[camera_index].position.x < cameras[camera_index].limit.Left()) {
        cameras[camera_index].position.x = cameras[camera_index].limit.Left();
        cameras[camera_index].is_position_outdated = true;
    }
    if (cameras[camera_index].position.x > cameras[camera_index].limit.Right()) {
        cameras[camera_index].position.x = cameras[camera_index].limit.Right();
        cameras[camera_index].is_position_outdated = true;
    }
    if (cameras[camera_index].position.y < cameras[camera_index].limit.Bottom()) {
        cameras[camera_index].position.y = cameras[camera_index].limit.Bottom();
        cameras[camera_index].is_position_outdated = true;
    }
    if (cameras[camera_index].position.y > cameras[camera_index].limit.Top()) {
        cameras[camera_index].position.y = cameras[camera_index].limit.Top();
        cameras[camera_index].is_position_outdated = true;
    }
}

Math::TransformationMatrix CS230::Camera::GetMatrix(size_t camera_index) {
    if(cameras[camera_index].first_person_view){
        if(cameras[camera_index].is_position_outdated || cameras[camera_index].is_rotation_outdated || cameras[camera_index].is_scale_outdated){
            cameras[camera_index].camera_matrix = Math::TranslationMatrix(cameras[camera_index].position - cameras[camera_index].offset) * Math::RotationMatrix(cameras[camera_index].rotation) * Math::ScaleMatrix(cameras[camera_index].scale);
            cameras[camera_index].view_matrix = cameras[camera_index].camera_matrix;
            std::swap(cameras[camera_index].view_matrix[0][1], cameras[camera_index].view_matrix[1][0]);
            cameras[camera_index].view_matrix[0][2] = -(cameras[camera_index].camera_matrix[0][0] * cameras[camera_index].camera_matrix[0][2] + cameras[camera_index].camera_matrix[1][0] * cameras[camera_index].camera_matrix[1][2]);
            cameras[camera_index].view_matrix[1][2] = -(cameras[camera_index].camera_matrix[0][1] * cameras[camera_index].camera_matrix[0][2] + cameras[camera_index].camera_matrix[1][1] * cameras[camera_index].camera_matrix[1][2]);
            cameras[camera_index].is_position_outdated = false;   
            cameras[camera_index].is_rotation_outdated = false;
            cameras[camera_index].is_scale_outdated = false;
            
        }   
    }
    else
    {
        if(cameras[camera_index].is_position_outdated){
            cameras[camera_index].camera_matrix = Math::TranslationMatrix(cameras[camera_index].position - cameras[camera_index].offset) ;
            cameras[camera_index].view_matrix = cameras[camera_index].camera_matrix;
            cameras[camera_index].view_matrix[0][2] = -(cameras[camera_index].camera_matrix[0][0] * cameras[camera_index].camera_matrix[0][2] + cameras[camera_index].camera_matrix[1][0] * cameras[camera_index].camera_matrix[1][2]);
            cameras[camera_index].view_matrix[1][2] = -(cameras[camera_index].camera_matrix[0][1] * cameras[camera_index].camera_matrix[0][2] + cameras[camera_index].camera_matrix[1][1] * cameras[camera_index].camera_matrix[1][2]);
            cameras[camera_index].is_position_outdated = false;
        }
    }
    return cameras[camera_index].view_matrix;
}

