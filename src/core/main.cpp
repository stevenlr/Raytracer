#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

#include <CImg.h>

#include "Raytracer.h"

using namespace std;
using namespace glm;
using namespace cimg_library;

int main(int argc, char *argv[])
{
	const int width = 800;
	const int height = 600;
	const int nbIter = 2000;
	const int ssNbRays = 4;

	CImg<float> image(width, height, 1, 3);
	CImg<float> finalImage(width, height, 1, 3);
	CImgDisplay disp(image);

	Camera camera(vec3(0, -5, 0), vec3(0, 0, 0), vec3(0, 0, 1),
	              70, width, height, 0.01f, 1000.0f);
	Scene scene;
	MeshModel model1("models/asteroid.obj");

	scene.setAmbientColor(glm::pow(vec3(0.05f, 0.05f, 0.1f) * 0.0f, glm::vec3(1.f)));

	Object *sphere1 = new Sphere(0.5f, Material(glm::vec3(1)));
	Object *sphere2 = new Sphere(0.25f, Material(glm::vec3(1), 1, 0));
	Object *ceiling = new Disc(vec3(0, 0, -1), 4, Material(glm::pow(glm::vec3(0.7f), vec3(1.f))));
	Object *lightCeiling = new Disc(vec3(0, 0, -1), 0.75f, Material(glm::pow(glm::vec3(0.7f), vec3(1.f)), 0, 1, 10));

	Object *wallBack = new Disc(vec3(0, -1, 0), 4, Material(glm::pow(glm::vec3(0.7f), vec3(1.f))));
	Object *floor = new Plane(vec3(0, 0, 1), Material(glm::pow(glm::vec3(0.7f), vec3(1.f)), 1, 0.5));
	Object *wallLeft = new Disc(vec3(1, 0, 0), 4, Material(glm::pow(glm::vec3(1, 0.2f, 0.2f), vec3(1.f))));
	Object *wallRight = new Disc(vec3(-1, 0, 0), 4, Material(glm::pow(glm::vec3(0.5f, 0.5f, 1), vec3(1.f))));
	Object *mesh = new Mesh(model1, Material(glm::vec3(0.7f, 0.7f, 0.9f)));

	sphere1->transform.translate(-1, -0.5, 0).scale(1, 1, 3);
	sphere2->transform.translate(1, -2, -0.75);
	floor->transform.translate(0, 0, -1);
	wallBack->transform.translate(0, 2, 0);
	wallLeft->transform.translate(-2, 0, 0);
	wallRight->transform.translate(2, 0, 0);
	mesh->transform.translate(-1, 1, -0.75);
	ceiling->transform.translate(0, 0, 2);
	lightCeiling->transform.translate(0, 0, 1.99f);

	scene.addObject(sphere1);
	scene.addObject(sphere2);
	scene.addObject(floor);
	scene.addObject(wallBack);
	scene.addObject(wallLeft);
	scene.addObject(wallRight);
	scene.addObject(ceiling);
	scene.addObject(lightCeiling);
	//scene.addObject(mesh);

	Light *sun = new DirectionalLight(glm::normalize(vec3(-1, 0.3f, -1)), glm::pow(glm::vec3(1, 0.98, 0.95), glm::vec3(1.f)));
	Light *point = new PointLight(vec3(-1, -1.5f, 0), vec3(0, 0.5f, 0.6f), vec3(0, 0, 1));

	//scene.addLight(sun);
	//scene.addLight(point);

	const int nbThreads = thread::hardware_concurrency();
	int nextRow = 0;
	mutex nextRowMutex;
	vector<thread> threads(nbThreads);
	const float ssOffsets[4][2] = {{0, 0}, {0.5, 0}, {0, 0.5}, {0.5, 0.5}};

	auto raytracingFunc = [&] () {
		int y = 0;

		while (true) {
			nextRowMutex.lock();
			y = nextRow++;
			nextRowMutex.unlock();

			if (y >= height) {
				return;
			}

			for (int x = 0; x < width; ++x) {
				glm::vec3 color(0);

				for (int i = 0; i < ssNbRays; ++i) {
					Ray ray = camera.computeRay(x + ssOffsets[i][0], y + ssOffsets[i][1]);
					color += scene.doPathTracing(ray);
				}

				color /= ssNbRays;

				image(x, y, 0) = color.r;
				image(x, y, 1) = color.g;
				image(x, y, 2) = color.b;
			}
		}
	};

	cout << "Using " << nbThreads << " threads" << endl;
	auto start = chrono::high_resolution_clock::now();

	const int nbIterEfective = nbIter / ssNbRays;

	for (int i = 0; i < nbIterEfective; ++i) {
		nextRow = 0;

		for (thread &t : threads) {
			new(&t) thread(raytracingFunc);
		}

		for (thread &t : threads) {
			t.join();
		}

		cout << i << endl;

		cimg_forXY(finalImage, x, y) {
			finalImage(x, y, 0) = (finalImage(x, y, 0) * i + image(x, y, 0)) / (i + 1.0f);
			finalImage(x, y, 1) = (finalImage(x, y, 1) * i + image(x, y, 1)) / (i + 1.0f);
			finalImage(x, y, 2) = (finalImage(x, y, 2) * i + image(x, y, 2)) / (i + 1.0f);
		}

		disp.display(finalImage);
	}

	vec3 color;

	cimg_forXY(finalImage, x, y) {
		color.r = finalImage(x, y, 0);
		color.g = finalImage(x, y, 1);
		color.b = finalImage(x, y, 2);

		color = glm::pow(color, vec3(0.45f));
		color = glm::clamp(color, vec3(0), vec3(1));

		finalImage(x, y, 0) = color.r;
		finalImage(x, y, 1) = color.g;
		finalImage(x, y, 2) = color.b;
	}

	auto ellapsed = chrono::high_resolution_clock::now() - start;
	cout << "done in " << chrono::duration_cast<std::chrono::seconds>(ellapsed).count() << "s";
	cout << " (" << chrono::duration_cast<std::chrono::milliseconds>(ellapsed).count() << "ms)" << endl << endl;

	disp.close();
	finalImage.display();

	return 0;
}
