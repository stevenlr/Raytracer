#include <iostream>

#include <CImg.h>

#include "Raytracer.h"

using namespace std;
using namespace glm;
using namespace cimg_library;

int main(int argc, char *argv[]) {
	int width = 854;
	int height = 480;
	int x, y;

	CImg<float> image(width, height, 1, 3);
	CImgDisplay disp(image);

	Camera camera(vec3(0, -5, 0), vec3(0, 0, 0), vec3(0, 0, 1),
			70, width, height, 0.01f, 1000.0f);
	Scene scene;

	Object *sphere1 = new Sphere(1, Material(glm::vec3(1, 0, 0)));
	Object *sphere2 = new Sphere(1, Material(glm::vec3(0, 0, 1)));

	sphere1->transform.translate(1, 0, 0).scale(0.5);
	sphere2->transform.scale(0.5).translate(1, 0, 0);

	scene.addObject(sphere1);
	scene.addObject(sphere2);

	cimg_forXY(image, x, y) {
		Ray ray = camera.computeRay(x, y);
		glm::vec3 color = scene.launchRay(ray);

		image(x, y, 0) = color.r;
		image(x, y, 1) = color.g;
		image(x, y, 2) = color.b;

		if (x == 0 && y % 16 == 0) {
			disp.display(image);
		}
	}

	cout << "done" << endl;

	disp.display(image);
	cin.get();

	return 0;
}