#pragma once
#include "bullet/btBulletDynamicsCommon.h"
#include "Engine/Maths/Matrix.hpp"
#include "Engine/Maths/Vector3.hpp"
#include "ElementPhysics.hpp"

namespace Engine
{
	class ElementPhysics;
	class Bulletlink
	{
	public:
		btDiscreteDynamicsWorld* PhysicsWorld;
		btBroadphaseInterface* PhysicsBroadphase;
		btCollisionDispatcher* PhysicsDispatcher;
		btDefaultCollisionConfiguration* PhysicsCollisionConfiguration;
		btSequentialImpulseConstraintSolver* PhysicsSICS;
		btTransform PhysicsTransform;
		btScalar matrix[16];

		Bulletlink();
		Bulletlink(Engine::Math::Vector3);
		~Bulletlink();
		void Stepsim(float);
		Engine::ElementPhysics CreateSquare(Engine::Math::Vector3 position, Engine::Math::Vector3 size);
		Engine::ElementPhysics CreateSphere(Engine::Math::Vector3 position, float size);
		void addBody(ElementPhysics &element);
		Engine::Math::Vector3 getPositionElement(ElementPhysics &element);

	};
}

