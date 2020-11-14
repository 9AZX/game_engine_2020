#include "ElementPhysics.hpp"
#include "Bulletlink.hpp"

namespace engine {
	ElementPhysics::ElementPhysics(btVector3 size) {
		this->shape = new btBoxShape(size);
	}

	ElementPhysics::ElementPhysics(float size) {
		this->shape = new btSphereShape(size);
	}

	ElementPhysics::~ElementPhysics() {

	}

	void ElementPhysics::setInertia(NotGLM::Vector3 inertia)
	{
		this->localInertia = btVector3(inertia->x, inertia->y, inertia->z);

	}

	NotGLM::Vector3 ElementPhysics::getInertia()
	{
		float x = this->localInertia.getX();
		float y = this->localInertia.getY();
		float z = this->localInertia.getZ();
		return (NotGLM::vector3(x, y, z));
	}

	void ElementPhysics::setMasse(float masse)
	{
		this->mass = masse;
	}

	float ElementPhysics::getMasse()
	{
		return(this->mass);
	}

	void ElementPhysics::calcInertia()
	{
		this->shape->calculateLocalInertia(this->mass, this->localInertia);
	}

	void ElementPhysics::setupBody(engine::Bulletlink &physic)
	{
		this->ElementMotionState = new btDefaultMotionState(physic.PhysicsTransform);
		this->myBoxRigidBodyConstructionInfo = btRigidBody::btRigidBodyConstructionInfo(this->mass, this->ElementMotionState, this->shape, this->localInertia);
		this->body = new btRigidBody(this->myBoxRigidBodyConstructionInfo);
	}

	btRigidBody* ElementPhysics::getBody() {
		return(this->body);
	}
}