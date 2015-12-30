#include <iostream>

#include <CImg.h>

#include "Raytracer.h"

using namespace std;
using namespace glm;
using namespace cimg_library;

int main(int argc, char *argv[]) {
	int width = 120;
	int height = 120;
	int x, y;

	CImg<float> image(width, height, 1, 3);
	image.fill(0);
	CImgDisplay disp(image);

	Camera camera(vec3(0, -5, 0), vec3(0, 0, 0), vec3(0, 0, 1),
			70, width, height, 0.01f, 1000.0f);
	Scene scene;
	MeshModel model1("models/ship.obj");

    scene.setBackgroundColor(vec3(0.5f));
    scene.setAmbientColor(vec3(0.05f));

	Object *sphere1 = new Sphere(0.5f, Material(glm::vec3(0.9, 0.3, 0.1)));
	Object *sphere2 = new Sphere(0.5f, Material(glm::vec3(0.8, 0.8, 0.2)));
	Object *plane = new Plane(vec3(0, 0, 1), Material(glm::vec3(0.7f, 0.7f, 0.7f)));
	Object *mesh1 = new Mesh(model1, Material(glm::vec3(0.7f, 0.7f, 0.9f)));

    sphere1->transform.translate(0, -0.5f, 0).scale(1, 1, 3);
    sphere2->transform.translate(1, -0.5, 0).scale(3, 1, 1);
	plane->transform.translate(0, 0, -1);
	mesh1->transform.translate(1, -0.5, 0).rotate(.2f, .2f, .1f);

	//scene.addObject(sphere1);
	//scene.addObject(sphere2);
	scene.addObject(plane);
	scene.addObject(mesh1);

    Light *sun = new DirectionalLight(glm::normalize(vec3(-1, 0, -1)), glm::vec3(1, 0.98, 0.95));
    Light *point= new PointLight(vec3(-1, -1.5f, 0), vec3(0, 0.5f, 0.6f), vec3(0, 0, 1));

    scene.addLight(sun);
    scene.addLight(point);

    int ssNbRays = 1;
    float ssOffsets[4][2] = {{0, 0}, {0.5, 0}, {0, 0.5}, {0.5, 0.5}};

	cimg_forXY(image, x, y) {
        glm::vec3 color(0);

        for (int i = 0; i < ssNbRays; ++i) {
		    Ray ray = camera.computeRay(x + ssOffsets[i][0], y + ssOffsets[i][1]);
		    color += scene.getShadeFromRay(ray);
        }

        color /= ssNbRays;
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
