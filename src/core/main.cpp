#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <functional>
#include <random>

#include <CImg.h>

#include "Raytracer.h"

using namespace std;
using namespace glm;
using namespace cimg_library;

int main(int argc, char *argv[]) {
	int width = 400;
	int height = 300;
	int x, y;

	CImg<float> image(width, height, 1, 3);
    CImg<float> finalImage(width, height, 1, 3);
	CImgDisplay disp(image);

	Camera camera(vec3(0, -5, 0), vec3(0, 0, 0), vec3(0, 0, 1),
			70, width, height, 0.01f, 1000.0f);
	Scene scene;

    scene.setAmbientColor(vec3(0.05f, 0.05f, 0.1f));

	Object *sphere1 = new Sphere(0.5f, Material(glm::vec3(1)));
	Object *sphere2 = new Sphere(0.25f, Material(glm::vec3(1)));

	Object *wallBack = new Disc(vec3(0, -1, 0), 4, Material(glm::vec3(0.7f)));
    Object *floor = new Plane(vec3(0, 0, 1), Material(glm::vec3(0.7f)));
    Object *wallLeft = new Disc(vec3(1, 0, 0), 4, Material(glm::pow(glm::vec3(1, 0.5f, 0.5f), vec3(2.2))));
    Object *wallRight = new Disc(vec3(-1, 0, 0), 4, Material(glm::pow(glm::vec3(0.5f, 0.5f, 1), vec3(2.2))));

    sphere1->transform.translate(-1, -0.5, 0).scale(1, 1, 3);
    sphere2->transform.translate(1, -2, -0.75);
	floor->transform.translate(0, 0, -1);
    wallBack->transform.translate(0, 2, 0);
    wallLeft->transform.translate(-2, 0, 0);
    wallRight->transform.translate(2, 0, 0);

	scene.addObject(sphere1);
	scene.addObject(sphere2);
	scene.addObject(floor);
    scene.addObject(wallBack);
    scene.addObject(wallLeft);
    scene.addObject(wallRight);

    Light *sun = new DirectionalLight(glm::normalize(vec3(-1, 0.3f, -1)), glm::vec3(1, 0.98, 0.95));
    Light *point = new PointLight(vec3(-1, -1.5f, 0), vec3(0, 0.5f, 0.6f), vec3(0, 0, 1));

    scene.addLight(sun);
    //scene.addLight(point);

    int nbThreads = thread::hardware_concurrency();
    int nextRow = 0;
    mutex nextRowMutex;
    vector<thread> threads(nbThreads);

    auto raytracingFunc = [&] () {
        int y = 0;
        default_random_engine generator;
        normal_distribution<float> rand(0, 0.05f);
        auto jitterDice = bind(rand, generator);

        while (true) {
            nextRowMutex.lock();
            y = nextRow++;
            nextRowMutex.unlock();

            if (y >= height) {
                return;
            }

            for (int x = 0; x < width; ++x) {
                glm::vec3 color(0);

		        Ray ray = camera.computeRay(x + jitterDice(), y + jitterDice());
		        color = scene.doPathTracing(ray);

		        image(x, y, 0) = color.r;
		        image(x, y, 1) = color.g;
		        image(x, y, 2) = color.b;
            }
        }
    };

    cout << "Using " << nbThreads << " threads" << endl;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
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

        color = glm::pow(color, vec3(0.45));
        //color = glm::clamp(color, vec3(0), vec3(1));

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
