#include "PhysicsEngine.h"

PhysicsObject::PhysicsObject(const Point3f & center, float x, float y, float z)
: center(center), lX(x), lY(y), lZ(z), hlX(x / 2.0f), hlY(y / 2.0f), hlZ(z / 2.0f), force(0.0f, 0.0f, 0.0f) {}

bool PhysicsObject::isColliding(const PhysicsObject & other) {
	if (center.y + hlY < other.center.y - other.hlY ||
		center.y - hlY > other.center.y + other.hlY)
		return false;

	Rectf r1 = { center.x - hlX, center.z - hlZ, lX, lZ };
	Rectf r2 = { other.center.x - other.hlX, other.center.z - other.hlZ, other.lX, other.lZ };

	return r1.intersects(r2);
}

void PhysicsObject::applyForce(const Vector3f & v) {
	force = v;
}

void PhysicsObject::applyGravity(const PhysicsEngine & engine) {
	center += engine.gravity;
}

void PhysicsObject::applyAntiGravity(const PhysicsEngine & engine) {
	center -= engine.gravity;
}

/* PHYSICS ENGINE */

PhysicsEngine::PhysicsEngine() : gravity(Vector3f(0, DEFAULT_GRAVITY, 0)) {}

void PhysicsEngine::setGravity(float val, float interval) {
	gravity = Vector3f(0, val * interval, 0);
}

void PhysicsEngine::registerObject(std::shared_ptr<PhysicsObject> obj) {
	objects.push_back(obj);
}

void PhysicsEngine::update() {
	/*for (auto obj : objects) {
		bool g = isOnPlatform(obj);

		obj->center.x += obj->force.x * 0.016;
		obj->center.y += obj->force.y * 0.016 - (g ? 9.8 * 0.016 : 0);
		obj->center.z += obj->force.z * 0.016;
	}*/

	for (int i = 0; i < objects.size(); ++i) {
		bool isOnPlatform = false;
		std::shared_ptr<PhysicsObject> obj = objects[i];

		if (obj->getCenter().y - obj->getHalfLengthY() > 0) {
			for (int j = 0; j < objects.size(); ++j) {
				if (i == j) continue;

				std::shared_ptr<PhysicsObject> other = objects[j];

				if (obj->isColliding(*other)) {
					//if (obj->center.y - obj->getHalfLengthY() >= other->center.y + other->getHalfLengthY()) {
					
					Rectangle2f rect = { other->getCenter().x - other->getHalfLengthX(), other->getCenter().z - other->getHalfLengthZ(), other->getLengthX(), other->getLengthZ() };
					if (rect.contains(Point2(obj->getCenter().x, obj->getCenter().z))) {
						isOnPlatform = true;
						break;
					}
				}
			}
		}
		else {
			isOnPlatform = true;
		}

		obj->center.x += obj->force.x * 0.016;
		obj->center.y += obj->force.y * 0.016 - (!isOnPlatform ? 9.8 * 0.016 : 0);
		obj->center.z += obj->force.z * 0.016;

		bool collision = false;

		for (int j = 0; j < objects.size(); ++j) {
			if (i == j) continue;

			std::shared_ptr<PhysicsObject> other = objects[j];

			if (obj->isColliding(*other)) {
				//if (isBetween(obj->getCenter().y, other->getCenter().y - other->getHalfLengthY(), other->getCenter().y + other->getHalfLengthY())) {
					
					other->applyForce(obj->force * 0.5f);
					//obj->applyForce(Vector3f(0, 0, 0));
					collision = true;
					//break;	// we shouldnt break and check other object collisions
				//}
			}
		}

		if (collision) obj->applyForce(Vector3f(0, 0, 0));

		if (obj->force.x != 0)
			obj->force.x -= obj->force.x * 0.016;

		if (obj->force.y != 0)
			obj->force.y -= obj->force.y * 0.016;

		if (obj->force.z != 0)
			obj->force.z -= obj->force.z * 0.016;

		if (abs(obj->force.x) < 0.1)
			obj->force.x = 0;
		if (abs(obj->force.y) < 0.1)
			obj->force.y = 0;
		if (abs(obj->force.z) < 0.1)
			obj->force.z = 0;
	}
}

bool PhysicsEngine::isOnPlatform(std::shared_ptr<PhysicsObject> obj) {
	if (obj->center.y - obj->getHalfLengthY() > 0) {

	}

	return true;
}