# SteffanM Physics in Bootstrap Documentation

My current implementation of custom physics in bootstrap operates on only two primary shapes: Spheres and Planes.

The code has been designed to be easily extendable via adding new shape classes, inheriting from the PhysicsObject class and creating a constructor that inherits from Physics object with an argument of the type as defined in the Enumerator in the PhysicsObject.h file. 

E.g. Constructor for a plane class:

	Plane::Plane() : PhysicsObject(ShapeType::PLANE)
	{
		// Constructor code goes here;
	}

To calculate collisions between different shapes in the scene, our PhysicsScene class contains an array of collision functions. When two objects collide, their shape types are checked, and the appropriate Shape to Shape collision function is called.

This document is intended to detail the physics object classes, properties, and how they interact together.

---
## Shapes


### Plane
A plane is an incredibly basic, simple shape. It is an infinite shape, extending forever.

It can be defined concisely using a vector2 normal and a distance to origin. Using these two properties, you can calculate an infinite plane that exists in a space and collisions with the plane in that space.

### Sphere
A sphere, or in 2D - a circle, is the next most simple shape with which you can calculate physics collisions.

It can be defined concisely using a position in space and a radius. With these two properties alone, you can calculate a sphere that exists in a space and collisions with the sphere in that space.

---

## Collision Types


| Collision Type | How it is calculated |
| ------ | ------ |
| Plane to Plane | Not Yet Implemented (Planes are rarely dynamic objects, and rarely move as a result of physics) |
| Sphere to Sphere | If the distance between the center points of two spheres is less than the value of their radii added together, then the spheres have collided. |
| Plane to Sphere | The dot product of plane's normal and the sphere's position == distance from sphere to origin, projected along the plane's normal. If this distance is less than the radius of the sphere, then there is a collision.  |
