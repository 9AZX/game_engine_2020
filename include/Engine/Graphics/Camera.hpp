#pragma once

#include "Engine/Maths/Vector3.hpp"
#include "Engine/Maths/Matrix4.hpp"

class Camera
{
public:

	void init(float FOV, float width, float height, float nearplane, float farPlane);
	void setCameraPosition(Engine::Math::Vector3 position);
	Engine::Math::Matrix4 getViewMatrix();
	Engine::Math::Matrix4 getprojectionMatrix();

private:

	Engine::Math::Matrix4 projectionMatrix;
	Engine::Math::Matrix4 viewMatrix;
	Engine::Math::Vector3 cameraPos;

};