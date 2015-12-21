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

    scene.setBackgroundColor(vec3(0, 0, 0));

	Object *sphere1 = new Sphere(1, Material(glm::vec3(1, 0, 0)));
	Object *sphere2 = new Sphere(0.5f, Material(glm::vec3(1, 1, 0)));
	Object *plane = new Plane(vec3(1, 0, 0.01), Material(glm::vec3(0.7f, 0.7f, 0.7f)));

	sphere2->transform.translate(1, 0, 0);
	plane->transform.translate(-0.7f, 0, 0);

	scene.addObject(sphere1);
	scene.addObject(sphere2);
	scene.addObject(plane);

    Light *sun = new DirectionalLight(glm::normalize(vec3(-1, 1, -1)), glm::vec3(0.9, 0.5, 0.3) * 0.5f);
    Light *point= new PointLight(vec3(0, -1, -1.5), vec3(0.2, 0.5, 0.9), vec3(0, 0, 1));

    scene.addLight(sun);
    scene.addLight(point);

	cimg_forXY(image, x, y) {
		Ray ray = camera.computeRay(x, y);
		glm::vec3 color = scene.getShadeFromRay(ray);

        color = glm::pow(color, vec3(0.45));
        color = glm::clamp(color, vec3(0), vec3(1));

		image(x, y, 0) = color.r;
		image(x, y, 1) = color.g;
		image(x, y, 2) = color.b;

		if (x == 0 && y % 16 == 0) {
			disp.display(image);
		}
	}

	cout << "done" << endl;

	disp.close();
	image.display();

	return 0;
}
