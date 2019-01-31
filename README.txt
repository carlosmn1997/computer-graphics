El programa funciona en Windows 10 con el compilado MinGW en el estándar c++14.

Se compila con la siguiente instrucción (hace falta tener MinGW en las variables de entorno de windows):

g++ -std=c++14 render/tests/render_test.cpp render/Plane.h render/Sphere.h Vec.cpp Vec.h ReferenceSystem.h exception.h render/Render.h render/Light.h render/Object.h render/RandomNumber.h -o main

Y se ejecuta con:

./main <numPaths>

El programa genera el fichero salida.ppm con la imagen en LDR

