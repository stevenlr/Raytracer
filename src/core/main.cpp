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

int main(int argc, char *argv[]) {
	int width = 854;
	int height = 480;
	int x, y;

	CImg<float> image(width, height, 1, 3);
	CImgDisplay disp(image);

	Camera camera(vec3(0, -5, 0), vec3(0, 0, 0), vec3(0, 0, 1),
			70, width, height, 0.01f, 1000.0f);
	Scene scene;

    scene.setBackgroundColor(vec3(0.5f));
    scene.setAmbientColor(vec3(0.05f));

	Object *sphere1 = new Sphere(0.5f, Material(glm::vec3(0.9, 0.3, 0.1)));
	Object *sphere2 = new Sphere(0.5f, Material(glm::vec3(0.8, 0.8, 0.2)));
	Object *plane = new Plane(vec3(0, 0, 1), Material(glm::vec3(0.7f, 0.7f, 0.7f)));

    sphere1->transform.translate(0, -0.5f, 0).scale(1, 1, 3);
    sphere2->transform.translate(1, -0.5, 0).scale(3, 1, 1);
	plane->transform.translate(0, 0, -1);

	scene.addObject(sphere1);
	scene.addObject(sphere2);
	scene.addObject(plane);

    Light *sun = new DirectionalLight(glm::normalize(vec3(-1, 0, -1)), glm::vec3(1, 0.98, 0.95));
    Light *point= new PointLight(vec3(-1, -1.5f, 0), vec3(0, 0.5f, 0.6f), vec3(0, 0, 1));

    scene.addLight(sun);
    scene.addLight(point);

    int ssNbRays = 4;
    float ssOffsets[4][2] = {{0, 0}, {0.5, 0}, {0, 0.5}, {0.5, 0.5}};

    int nbThreads = thread::hardware_concurrency();
    int nextRow = 0;
    mutex nextRowMutex;
    vector<thread> threads(nbThreads);

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
        }
    };

    cout << "Using " << nbThreads << " threads" << endl;
    auto start = chrono::high_resolution_clock::now();

    for (thread &t : threads) {
        new(&t) thread(raytracingFunc);
    }

    for (thread &t : threads) {
        t.join();
    }

    auto ellapsed = chrono::high_resolution_clock::now() - start;
	cout << "done in " << chrono::duration_cast<std::chrono::seconds>(ellapsed).count() << "s";
    cout << " (" << chrono::duration_cast<std::chrono::milliseconds>(ellapsed).count() << "ms)" << endl << endl;

	disp.close();
	image.display();

	return 0;
}
