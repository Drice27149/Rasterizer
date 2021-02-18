#include "Renderer.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

Matrix getModelTransformation(){
	Matrix result(4, 4);
	float d[] = {
		1.0, 0, 0, 0,
		0, 1.0, 0, 0,
		0, 0, 1.0, 0,
		0, 0, 0, 1,0
	};	
	result.init(d);
	return result;
}

// e: eye position
// g: gaze direction
// t: up direction
Matrix getCameraTransformation(Vector e, Vector g, Vector t){
	Matrix translation(4, 4);
	Matrix rotation(4, 4);
	
	float td[] = {
		0, 0, 0, -e[0],
		0, 0, 0, -e[1],
		0, 0, 0, -e[2],
		0, 0, 0, 1
	};
	translation.init(td);
	
	Vector w = Vector::crossProduct(g, t);
	float rd[] = {
		w[0], w[1], w[2], 0,
		t[0], t[1], t[2], 0,
		-g[0], -g[1], -g[2], 0,
		0, 0, 0, 1
	};
	rotation.init(rd);
	
	return rotation * translation;
}	

// p: perspective transform
// orth: orth projection 
// orth = scale * translate, translate first, then scale

Matrix getProjectionTransformation(float n, float f, float l, float r, float t, float b){
	Matrix p(4, 4); 
	Matrix translate(4, 4);
	Matrix scale(4, 4);
	
	float pd[] = {
		n, 0, 0, 0, 
		0, n, 0, 0, 
		0, 0, n+f, -f*n, 
		0, 0, 1.0, 0
	};
	p.init(pd);
	
	float td[] = {
		1.0, 0, 0, -(r+l)*0.5,
		0, 1.0, 0, -(t+b)*0.5, 
		0, 0, 1.0, -(n+f)*0.5,
		0, 0, 0, 1.0
	};
	translate.init(td);
	
	float sd[] = {
		2.0/(r-l), 0, 0, 0,
		0, 2.0/(t-b), 0, 0,
		0, 0, 2.0/(n-f), 0,
		0, 0, 0, 1.0
	};
	scale.init(sd);
	
	return scale * translate * p;
}

Matrix getViewportTransformation(float width, float height){
	Matrix vp(4, 4);
	float vpd[] = {
		width*0.5, 0, (width-1.0)*0.5, 
		height*0.5, 0, (height-1.0)*0.5, 
		0, 0, 1.0
	};
	vp.init(vpd);
	return vp;
}

void Renderer::render(Scene* scene){
	
}