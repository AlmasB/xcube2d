#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include <vector>
#include <memory>

#include "GameMath.h"

static const float DEFAULT_GRAVITY = -1.0f;

class PhysicsObject;

class PhysicsEngine {
	friend class XCube2Engine;
	friend class PhysicsObject;
	private:
		Vector2f gravity;
		PhysicsEngine();

		std::vector<std::shared_ptr<PhysicsObject>> objects;

	public:
		/**
		* Note that gravity is naturally a negative value
		* update interval in seconds
		*/
		void setGravity(float gravityValue, float worldUpdateInterval);
		void update();

		void registerObject(std::shared_ptr<PhysicsObject>);
};

class PhysicsObject {
	friend class PhysicsEngine;
	protected:
		Point2 center;
		float lX, lY, hlX, hlY;	// lengths and half lengths

		Vector2f force;

		void applyForce(const Vector2f &);
	public:
		PhysicsObject(const Point2 & center, float x, float y);

		Point2 getCenter() { return center; }
		float getLengthX() { return lX; }
		float getLengthY() { return lY; }
		float getHalfLengthX() { return hlX; }
		float getHalfLengthY() { return hlY; }

		bool isColliding(const PhysicsObject & other);
		/**
		* If we have different implementations of engines/gravity
		* this can be very useful
		*/
		virtual void applyGravity(const PhysicsEngine & engine);
		virtual void applyAntiGravity(const PhysicsEngine & engine);
};

#endif