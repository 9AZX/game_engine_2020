#pragma once
#include "bullet/btBulletDynamicsCommon.h"
#include "Engine/Maths/Matrix.hpp"
#include "Engine/Maths/Vector3.hpp"

namespace engine {
	class Bulletlink;
	class ElementPhysics
	{
		btRigidBody* body;
		btCollisionShape* shape;
		btVector3 localInertia;
		btScalar mass;
		btDefaultMotionState* ElementMotionState;

	public:
		ElementPhysics(btVector3);
		ElementPhysics(float);
		~ElementPhysics();
		void setInertia(Engine::Math::Vector3);
		void setMasse(float);
		Engine::Math::Vector3 getInertia();
		float getMasse();
		void calcInertia();
		void setupBody(engine::Bulletlink &physic);
		btRigidBody* getBody();
	};
}

