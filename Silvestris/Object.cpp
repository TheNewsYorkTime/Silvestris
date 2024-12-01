#include "Object.h"

//Broken
Object::Object(glm::vec3 vertices[], glm::vec4 color, int numVerts) {
	this->vertices.push_back({ vertices[numVerts - 1], color });
	this->vertices.push_back({ vertices[0], color });
	this->vertices.push_back({ vertices[1], color });

	for(int i = 3; i < numVerts; i += 3) {
		this->vertices.push_back({ vertices[numVerts - i], color });
		this->vertices.push_back({ vertices[i], color });
		this->vertices.push_back({ vertices[ i < numVerts ? i + 1 : 0 ], color });
	}

	this->color = color;
}

ash::vec2 <float> Object::getBoundingBox()
{
	return ash::vec2 <float>();
}

ash::vec2 <float> Object::getPosition()
{
	return ash::vec2 <float>();
}
/*
Circle::Circle(Vertex center, ash::Vec <float> radius) {
}

 */