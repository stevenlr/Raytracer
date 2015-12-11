#include <iostream>

#include <CImg.h>

#include "Raytracer.h"

using namespace std;
using namespace glm;

int main(int argc, char *argv[]) {
	int width = 854;
	int height = 480;

	CImg<float> image(width, height, 1, 3);
	CImgDisplay disp(image);

	Camera camera(vec3(-5, 0, 0), vec3(0, 0, 0), vec3(0, 0, 1),
			70, width, height, 0.01f, 1000.0f);
	Scene scene;

	scene.addObject(new Sphere(vec3(0, 0, 0), 1, Material(glm::vec3(1, 0, 0))));

	CImg_forXY(image, x, y) {
		Ray ray = camera.computeRay(x, y);
		glm::vec3 color = scene.launchRay(ray);

		image(x, y, 0) = color.r;
		image(x, y, 0) = color.g;
		image(x, y, 0) = color.b;

		if (x == 0 && y % 16 == 0) {
			disp.display(image);
		}
	}

	disp.display(image);

	return 0;
}