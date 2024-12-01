#pragma once
#include "core.h"

enum  ObjectType  {
	OBJECT_SQUARE,
	OBJECT_ELLIPSE,
	OBJECT_POLYGON
} ;

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	Vertex* adjacent;
};

class Object {

public:
	Object(glm::vec3 vertices[], glm::vec4 color, int numVerts);
	std::vector <Vertex> vertices;
private:
	ObjectType type;
	glm::vec4 color;
	ash::vec2 <float> position;
	ash::vec2 <float> boundingBoxSize;

	ash::vec2 <float> getBoundingBox();
	ash::vec2 <float> getPosition();

};

class Circle : Object {

	Circle(Vertex center, ash::vec2 <float> radius);

	ObjectType type = OBJECT_ELLIPSE;
	ash::vec2 <float> radius;

	ash::vec2 <float> foci;

};