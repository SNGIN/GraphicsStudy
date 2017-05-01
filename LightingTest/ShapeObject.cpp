#include "ShapeObject.h"


ShapeObject::ShapeObject()
{
}


ShapeObject::~ShapeObject()
{
}

void ShapeObject::MaterialSet(Material* mat){
	m_Material = mat;
}