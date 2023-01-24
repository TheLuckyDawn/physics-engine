all: compile link

compile:
	g++ -c main.cpp engine/verlet.cpp engine/vector2.cpp engine/AABB.cpp engine/physicsObject.cpp engine/engine.cpp -I"C:\SFML-2.5.1\include" -DSFML_STATIC
	
link:
	g++ main.o verlet.o vector2.o AABB.o physicsObject.o engine.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	rm -f main *.o