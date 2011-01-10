
CC=g++
flags=-O2 -msse3 -msse4.2 -I../mlib

all: rt2cpu

rt2cpu: all_obj.o bvh-aabb.o engine.o main.o primitives.o pr_plane.o pr_triangle.o scene.o smath.o boundingvolume.o camera.o lights.o material.o pr_mesh.o pr_sphere.o ray.o settings.o texture.o
	$(CC) $(flags) ../build/all_obj.o ../build/bvh-aabb.o ../build/engine.o ../build/main.o ../build/primitives.o ../build/pr_plane.o ../build/pr_triangle.o ../build/scene.o ../build/smath.o ../build/boundingvolume.o ../build/camera.o ../build/lights.o ../build/material.o ../build/pr_mesh.o ../build/pr_sphere.o ../build/ray.o ../build/settings.o ../build/texture.o -o ../build/rt2cpu -lgomp -lSDL -lmlib -L../build/

all_obj.o:
	$(CC) $(flags) -c all_obj.cpp          -o ../build/all_obj.o

bvh-aabb.o:
	$(CC) $(flags) -c bvh-aabb.cpp         -o ../build/bvh-aabb.o

engine.o:
	$(CC) $(flags) -c engine.cpp           -o ../build/engine.o

main.o:
	$(CC) $(flags) -c main.cpp             -o ../build/main.o

primitives.o:
	$(CC) $(flags) -c primitives.cpp       -o ../build/primitives.o

pr_plane.o:
	$(CC) $(flags) -c pr_plane.cpp         -o ../build/pr_plane.o

pr_triangle.o:
	$(CC) $(flags) -c pr_triangle.cpp      -o ../build/pr_triangle.o

scene.o:
	$(CC) $(flags) -c scene.cpp            -o ../build/scene.o

smath.o:
	$(CC) $(flags) -c smath.cpp            -o ../build/smath.o

boundingvolume.o:
	$(CC) $(flags) -c boundingvolume.cpp   -o ../build/boundingvolume.o

camera.o:
	$(CC) $(flags) -c camera.cpp           -o ../build/camera.o

lights.o:
	$(CC) $(flags) -c lights.cpp           -o ../build/lights.o

material.o:
	$(CC) $(flags) -c material.cpp         -o ../build/material.o

pr_mesh.o:
	$(CC) $(flags) -c pr_mesh.cpp          -o ../build/pr_mesh.o

pr_sphere.o:
	$(CC) $(flags) -c pr_sphere.cpp        -o ../build/pr_sphere.o

ray.o:
	$(CC) $(flags) -c ray.cpp              -o ../build/ray.o

settings.o:
	$(CC) $(flags) -c settings.cpp         -o ../build/settings.o

texture.o:
	$(CC) $(flags) -c texture.cpp          -o ../build/texture.o

clean:
	rm -rf ../build/*.o 

