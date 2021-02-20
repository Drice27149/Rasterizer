#include <cmath>
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
		1.0, 0, 0, -e[0],
		0, 1.0, 0, -e[1],
		0, 0, 1.0, -e[2],
		0, 0, 0, 1
	};
	translation.init(td);
	
	Vector w = Vector::crossProduct(g, t);
	float rd[] = {
		w[0], w[1], w[2], 0,
		t[0], t[1], t[2], 0,
		-g[0], -g[1], -g[2], 0,
		0, 0, 0, 1.0
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
		width*0.5, 0, 0, width*0.5, 
		0, height*0.5, 0, height*0.5, 
		0, 0, 1.0, 0,
		0, 0, 0, 1.0
	};
	vp.init(vpd);
	return vp;
}

float min(float u, float v){ return u>v?v:u; }

float max(float u, float v){ return u>v?u:v; }

float min(float u, float v, float w){ return min(min(u,v),w); } 

float max(float u, float v, float w){ return max(max(u,v),w); }

int isInsideTriangle(Vector* v, Vector u){
	int positive = 0, negative = 0;
	for(int i = 0; i < 3; i++){
		Vector last = v[(i-1+3)%3];
		Vector a = v[i] - last;
		Vector b = u - last;
		if(a[0]*b[1] - b[0]*a[1] >= 0.0) positive++;
		else negative++;
	}
	return positive==3 || negative==3;
}

// vs: screen space coordinate
// vw: world space coordinate, before camera transformation
void Renderer::renderTriangle(Vector* vs, Vector* vw){
	float maxX = max(vs[0][0], vs[1][0], vs[2][0]);
	float minX = min(vs[0][0], vs[1][0], vs[2][0]);
	float maxY = max(vs[0][1], vs[1][1], vs[2][1]);
	float minY = min(vs[0][1], vs[1][1], vs[2][1]);
	
	if(minX < 0) minX = 0;
	if(maxX >= width) maxX = width - 1.0;
	if(minY < 0) minY = 0;
	if(maxY >= height) maxY = height - 1.0;
	
	for(int x = minX+0.5; x <= maxX; x++){
		for(int y = minY+0.5; y <= maxY; y++){
			float xf = (float)x + 0.5;
			float yf = (float)y + 0.5;
			Vector u(xf, yf, 0.0f);
			if(isInsideTriangle(vs, u)){
				// missing: depth test
				frameBuffer[y * width + x] = Vector(1.0, 1.0, 1.0); 
			}
		}
	}
}

void Renderer::render(Scene* scene){
	frameBuffer.clear();
	depthBuffer.clear();
	float inf = 1e9 + 7;
	for(int i = 0; i < scene->width*scene->height; i++){
		frameBuffer.push_back(Vector(0.0, 0.0, 0.0));
		depthBuffer.push_back(inf);
	}
	width = scene->width;
	height = scene->height;
	
	// tan(fov * 0.5) = t / n
	// aspect = r / t
	float t = tan(fov / 180.0 * 3.1415926 * 0.5) * std::abs(near);
	float r = aspect * t;
	
	gDirection.normalize();
	uDirection.normalize();
	
	Matrix M_cam = getCameraTransformation(origin, gDirection, uDirection);
	Matrix M_p = getProjectionTransformation(near, far, -r, r, -t, t);
	Matrix M_vp = getViewportTransformation(width, height);
	Matrix M = M_vp * M_p * M_cam;
	
	for(Object* object: scene->objects){
		for(Triangle& triangle: object->triangles){
			Vector vs[3];
			for(int i = 0; i < 3; i++){ 
				Vector tv(4);
				float td[] = {triangle.vertex[i][0], triangle.vertex[i][1], triangle.vertex[i][2], 1.0f};
				tv.init(td);
				vs[i] = M * tv;
				for(int j = 0; j < 3; j++) vs[i][j] /= vs[i][3];
				vs[i].reduce(3);
			}
			Renderer::renderTriangle(vs, triangle.vertex);
		}
	}
}

void Renderer::writeImage(const char* filename){
	auto fp = freopen(filename, "w", stdout);
	printf("P3\n%d %d\n255\n", width, height);
	for(int x = 0; x < height; x++){
		for(int y = 0; y < width; y++){
			Vector& u = frameBuffer[x * width + y];
			printf("%.0f %.0f %.0f\n", u[0]*255.0, u[1]*255.0, u[2]*255.0);
		}
	}
	fclose(fp);
}







