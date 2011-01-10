
CC=g++

flags=-O2 -msse3 -msse4.2 -I../mlib

all: rt2cpu

rt2cpu: ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o 
	$(CC) $(flags) ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o -lgomp -lSDL -lmlib -L../build/


../build/all_obj.o:
	$(CC) $(flags) -c all_obj.cpp -o ../build/all_obj.o

../build/boundingvolume.o:
	$(CC) $(flags) -c boundingvolume.cpp -o ../build/boundingvolume.o

../build/bvh-aabb.o:
	$(CC) $(flags) -c bvh-aabb.cpp -o ../build/bvh-aabb.o

../build/camera.o:
	$(CC) $(flags) -c camera.cpp -o ../build/camera.o

../build/engine.o:
	$(CC) $(flags) -c engine.cpp -o ../build/engine.o

../build/lights.o:
	$(CC) $(flags) -c lights.cpp -o ../build/lights.o

../build/main.o:
	$(CC) $(flags) -c main.cpp -o ../build/main.o

../build/material.o:
	$(CC) $(flags) -c material.cpp -o ../build/material.o

../build/primitives.o:
	$(CC) $(flags) -c primitives.cpp -o ../build/primitives.o

../build/pr_mesh.o:
	$(CC) $(flags) -c pr_mesh.cpp -o ../build/pr_mesh.o

../build/pr_plane.o:
	$(CC) $(flags) -c pr_plane.cpp -o ../build/pr_plane.o

../build/pr_sphere.o:
	$(CC) $(flags) -c pr_sphere.cpp -o ../build/pr_sphere.o

../build/pr_triangle.o:
	$(CC) $(flags) -c pr_triangle.cpp -o ../build/pr_triangle.o

../build/ray.o:
	$(CC) $(flags) -c ray.cpp -o ../build/ray.o

../build/scene.o:
	$(CC) $(flags) -c scene.cpp -o ../build/scene.o

../build/settings.o:
	$(CC) $(flags) -c settings.cpp -o ../build/settings.o

../build/smath.o:
	$(CC) $(flags) -c smath.cpp -o ../build/smath.o

../build/texture.o:
	$(CC) $(flags) -c texture.cpp -o ../build/texture.o


clean:
	rm -rf ../build/all_obj.o ../build/boundingvolume.o ../build/bvh-aabb.o ../build/camera.o ../build/engine.o ../build/lights.o ../build/main.o ../build/material.o ../build/primitives.o ../build/pr_mesh.o ../build/pr_plane.o ../build/pr_sphere.o ../build/pr_triangle.o ../build/ray.o ../build/scene.o ../build/settings.o ../build/smath.o ../build/texture.o 
