
CC=g++

flags=-O3 -msse3 -msse4.2 -g -I../mlib

all: rt2cpu

rt2cpu: ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o 
	$(CC) $(flags) ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o -lgomp -lSDL -lmlib -L../build/


../build/all_obj.o: all_obj.cpp all_obj.hpp
	$(CC) $(flags) -c all_obj.cpp -o ../build/all_obj.o

../build/boundingvolume.o: boundingvolume.cpp boundingvolume.hpp
	$(CC) $(flags) -c boundingvolume.cpp -o ../build/boundingvolume.o

../build/bvh-aabb.o: bvh-aabb.cpp bvh-aabb.hpp
	$(CC) $(flags) -c bvh-aabb.cpp -o ../build/bvh-aabb.o

../build/camera.o: camera.cpp camera.hpp
	$(CC) $(flags) -c camera.cpp -o ../build/camera.o

../build/engine.o: engine.cpp engine.hpp
	$(CC) $(flags) -c engine.cpp -o ../build/engine.o

../build/lights.o: lights.cpp lights.hpp
	$(CC) $(flags) -c lights.cpp -o ../build/lights.o

../build/main.o: main.cpp 
	$(CC) $(flags) -c main.cpp -o ../build/main.o

../build/material.o: material.cpp material.hpp
	$(CC) $(flags) -c material.cpp -o ../build/material.o

../build/primitives.o: primitives.cpp primitives.hpp
	$(CC) $(flags) -c primitives.cpp -o ../build/primitives.o

../build/pr_mesh.o: pr_mesh.cpp pr_mesh.hpp
	$(CC) $(flags) -c pr_mesh.cpp -o ../build/pr_mesh.o

../build/pr_plane.o: pr_plane.cpp pr_plane.hpp
	$(CC) $(flags) -c pr_plane.cpp -o ../build/pr_plane.o

../build/pr_sphere.o: pr_sphere.cpp pr_sphere.hpp
	$(CC) $(flags) -c pr_sphere.cpp -o ../build/pr_sphere.o

../build/pr_triangle.o: pr_triangle.cpp pr_triangle.hpp
	$(CC) $(flags) -c pr_triangle.cpp -o ../build/pr_triangle.o

../build/ray.o: ray.cpp ray.hpp
	$(CC) $(flags) -c ray.cpp -o ../build/ray.o

../build/scene.o: scene.cpp scene.hpp
	$(CC) $(flags) -c scene.cpp -o ../build/scene.o

../build/settings.o: settings.cpp settings.hpp
	$(CC) $(flags) -c settings.cpp -o ../build/settings.o

../build/smath.o: smath.cpp smath.hpp
	$(CC) $(flags) -c smath.cpp -o ../build/smath.o

../build/texture.o: texture.cpp texture.hpp
	$(CC) $(flags) -c texture.cpp -o ../build/texture.o


clean:
	rm -rf ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o 
