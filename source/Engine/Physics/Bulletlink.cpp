#include "Engine/Physics/Bulletlink.hpp"

namespace Engine {
	Bulletlink::Bulletlink() {
		PhysicsCollisionConfiguration = new btDefaultCollisionConfiguration();
		PhysicsDispatcher = new	btCollisionDispatcher(PhysicsCollisionConfiguration);
		PhysicsBroadphase = new btDbvtBroadphase();
		PhysicsSICS = new btSequentialImpulseConstraintSolver;
		PhysicsWorld = new btDiscreteDynamicsWorld(PhysicsDispatcher, PhysicsBroadphase, PhysicsSICS, PhysicsCollisionConfiguration);
		PhysicsWorld->setGravity(btVector3(0, -10, 0));
	};

	Bulletlink::Bulletlink(Engine::Math::Vector3 vector) {
		PhysicsCollisionConfiguration = new btDefaultCollisionConfiguration();
		PhysicsDispatcher = new	btCollisionDispatcher(PhysicsCollisionConfiguration);
		PhysicsBroadphase = new btDbvtBroadphase();
		PhysicsSICS = new btSequentialImpulseConstraintSolver;
		PhysicsWorld = new btDiscreteDynamicsWorld(PhysicsDispatcher, PhysicsBroadphase, PhysicsSICS, PhysicsCollisionConfiguration);
		PhysicsWorld->setGravity(btVector3(vector.x, vector.y, vector.z));
	}

	Bulletlink::~Bulletlink() {
	}

	void Bulletlink::Stepsim(float sim = 0.001) {
		if (this->PhysicsWorld)
			this->PhysicsWorld->stepSimulation(sim);
	}

	ElementPhysics Bulletlink::CreateSquare(Engine::Math::Vector3 position, Engine::Math::Vector3 size) {
		btVector3 btsize(size.x, size.y, size.z);
		Engine::ElementPhysics square(btsize);
		this->PhysicsTransform.setIdentity();
		this->PhysicsTransform.setOrigin(btVector3(position.x, position.y, position.z));
		return(square);
	}

	ElementPhysics Bulletlink::CreateSphere(Engine::Math::Vector3 position, float size) {
		Engine::ElementPhysics sphere(size);
		this->PhysicsTransform.setIdentity();
		this->PhysicsTransform.setOrigin(btVector3(position.x, position.y, position.z));
		return(sphere);
	}

	void Bulletlink::addBody(ElementPhysics &element) {
		this->PhysicsWorld->addRigidBody(element.getBody());
	}

	Engine::Math::Vector3 Bulletlink::getPositionElement(ElementPhysics& element) {
		element.getBody()->getMotionState()->getWorldTransform(this->PhysicsTransform);
		float x = this->PhysicsTransform.getOrigin().getX();
		float y = this->PhysicsTransform.getOrigin().getY();
		float z = this->PhysicsTransform.getOrigin().getZ();
		return(Engine::Math::Vector3(x, y, z));
	}
}
