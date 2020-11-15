#include "Engine/Graphics/Camera.hpp"

void Camera::init(float FOV, float width, float height, float nearplane, float farPlane) {

	cameraPos = Engine::Math::Vector3(0.0f, 0.0f, 4.0f);
	Engine::Math::Vector3 cameraFront = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
	Engine::Math::Vector3 cameraUp = Engine::Math::Vector3(0.0f, 1.0f, 0.0f);

	viewMatrix = Engine::Math::Matrix4(1.0f);
	projectionMatrix = Engine::Math::Matrix4(1.0f);

	projectionMatrix = glm::perspective(FOV, width / height, nearplane, farPlane);
	viewMatrix = glm::lookAt(cameraPos, cameraFront, cameraUp);

}

Engine::Math::Matrix4 Camera::getViewMatrix() {

	return viewMatrix;

}
Engine::Math::Matrix4 Camera::getprojectionMatrix() {

	return projectionMatrix;
}

void Camera::setCameraPosition(Engine::Math::Vector3 position) {

	cameraPos = position;
}