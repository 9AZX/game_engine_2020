#pragma once
#include "../../../source/bullet3-master/src/btBulletDynamicsCommon.h"
#include "../not_glm/not_glm_matrix.hpp"
#include "../not_glm/not_glm_vector.hpp"
#include "ElementPhysics.hpp"


namespace engine
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
		Bulletlink(NotGLM::Vector3);
		~Bulletlink();
		void Stepsim(float);
		engine::ElementPhysics CreateSquare(NotGLM::Vector3 position, NotGLM::Vector3 size);
		engine::ElementPhysics CreateSphere(NotGLM::Vector3 position, float size);
		void addBody(ElementPhysics &element);
		NotGLM::Vector3 getPositionElement(ElementPhysics &element);

	};
}

