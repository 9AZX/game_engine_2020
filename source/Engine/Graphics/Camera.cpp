#include "Engine/Graphics/Camera.hpp"

Engine::Math::Matrix4 ourLookAt(Engine::Math::Vector3 eye, Engine::Math::Vector3 center, Engine::Math::Vector3 up)
{
    auto normalize = [](Engine::Math::Vector3 v)
    {
        float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
        return Engine::Math::Vector3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
    };

    auto cross = [](Engine::Math::Vector3 v, Engine::Math::Vector3 v2)
    {
        return Engine::Math::Vector3((v.y * v2.z) - (v.z * v2.y),
            (v.z * v2.x) - (v.x * v2.z),
            (v.x * v2.y) - (v.y * v2.x));
    };

    Engine::Math::Vector3 f = normalize(center - eye);

    Engine::Math::Vector3 s(normalize(cross(f, up)));
    Engine::Math::Vector3 u(cross(s, f));

    Engine::Math::Matrix4 Result = Engine::Math::Matrix4(1.0);
    Result.matrixData[0] = s.x;
    Result.matrixData[4] = s.y;
    Result.matrixData[8] = s.z;
    Result.matrixData[1] = u.x;
    Result.matrixData[5] = u.y;
    Result.matrixData[9] = u.z;
    Result.matrixData[2] = -f.x;
    Result.matrixData[6] = -f.y;
    Result.matrixData[10] = -f.z;
    Result.matrixData[12] = -s.dot(eye);
    Result.matrixData[13] = -u.dot(eye);
    Result.matrixData[14] = f.dot(eye);
    return Result;
}

Engine::Math::Matrix4 ourPerspective(float fovy, float aspect, float zNear, float zFar)
{
    auto tanD = tan(fovy / 2.0);
    Engine::Math::Matrix4 Result = Engine::Math::Matrix4(0.0);
    Result.matrixData[0] = 1.0 / (aspect * tanD);
    Result.matrixData[5] = 1.0 / (tanD);
    Result.matrixData[10] = zFar / (zNear - zFar);
    Result.matrixData[11] = -1.0;
    Result.matrixData[14] = -(zFar * zNear) / (zFar - zNear);
    return Result;
}

void Camera::init(float FOV, float width, float height, float nearplane, float farPlane) {

	cameraPos = Engine::Math::Vector3(0.0f, 0.0f, 4.0f);
	Engine::Math::Vector3 cameraFront = Engine::Math::Vector3(0.0f, 0.0f, 0.0f);
	Engine::Math::Vector3 cameraUp = Engine::Math::Vector3(0.0f, 1.0f, 0.0f);

	viewMatrix = Engine::Math::Matrix4(1.0f);
	projectionMatrix = Engine::Math::Matrix4(1.0f);

	projectionMatrix = ourPerspective(FOV, width / height, nearplane, farPlane);
	viewMatrix = ourLookAt(cameraPos, cameraFront, cameraUp);

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