#pragma once
#include "../../../source/bullet3-master/src/btBulletDynamicsCommon.h"
#include "../not_glm/not_glm_matrix.hpp"
#include "../not_glm/not_glm_vector.hpp"

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
		void setInertia(NotGLM::vector3);
		void setMasse(float);
		NotGLM::Vector3 getInertia();
		float getMasse();
		void calcInertia();
		void setupBody(engine::Bulletlink &physic);
		btRigidBody* getBody();
	};
}

