#include "Bulletlink.hpp"

namespace engine {
	Bulletlink::Bulletlink() {
		PhysicsCollisionConfiguration = new btDefaultCollisionConfiguration();
		PhysicsDispatcher = new	btCollisionDispatcher(PhysicsCollisionConfiguration);
		PhysicsBroadphase = new btDbvtBroadphase();
		PhysicsSICS = new btSequentialImpulseConstraintSolver;
		PhysicsWorld = new btDiscreteDynamicsWorld(PhysicsDispatcher, PhysicsBroadphase, PhysicsSICS, PhysicsCollisionConfiguration);
		PhysicsWorld->setGravity(btVector3(0, -10, 0));
	};

	Bulletlink::Bulletlink(NotGLM::Vector3 vector) {
		PhysicsCollisionConfiguration = new btDefaultCollisionConfiguration();
		PhysicsDispatcher = new	btCollisionDispatcher(PhysicsCollisionConfiguration);
		PhysicsBroadphase = new btDbvtBroadphase();
		PhysicsSICS = new btSequentialImpulseConstraintSolver;
		PhysicsWorld = new btDiscreteDynamicsWorld(PhysicsDispatcher, PhysicsBroadphase, PhysicsSICS, PhysicsCollisionConfiguration);
		PhysicsWorld->setGravity(btVector3(vector->x, vector->y, vector->z));
	}

	Bulletlink::~Bulletlink() {
	}

	void Bulletlink::Stepsim(float sim = 0.001) {
		if (this->PhysicsWorld)
			this->PhysicsWorld->stepSimulation(sim);
	}

	ElementPhysics Bulletlink::CreateSquare(NotGLM::Vector3 position, NotGLM::Vector3 size) {
		btVector3 btsize(size->x, size->y, size->z);
		engine::ElementPhysics square(btsize);
		this->PhysicsTransform.setIdentity();
		this->PhysicsTransform.setOrigin(btVector3(position->x, position->y, position->z));
		return(square);
	}

	ElementPhysics Bulletlink::CreateSphere(NotGLM::Vector3 position, float size) {
		engine::ElementPhysics sphere(size);
		this->PhysicsTransform.setIdentity();
		this->PhysicsTransform.setOrigin(btVector3(position->x, position->y, position->z));
		return(sphere);
	}

	void Bulletlink::addBody(ElementPhysics &element) {
		this->PhysicsWorld->addRigidBody(element.getBody());
	}

	NotGLM::Vector3 Bulletlink::getPositionElement(ElementPhysics& element) {
		element.getBody()->getMotionState()->getWorldTransform(this->PhysicsTransform);
		float x = this->PhysicsTransform.getOrigin().getX();
		float y = this->PhysicsTransform.getOrigin().getY();
		float x = this->PhysicsTransform.getOrigin().getZ();
		return(NotGLM::Vector3(x, y, z))
	}
}
