El programa funciona en Windows 10 con el compilado MinGW en el estándar c++14.

Se compila con la siguiente instrucción (hace falta tener MinGW en las variables de entorno de windows):

g++ -std=c++14 render/tests/render_test.cpp render/Plane.h render/Sphere.h Vec.cpp Vec.h ReferenceSystem.h exception.h render/Render.h render/Light.h render/Object.h render/RandomNumber.h -o main

También se ha probado en Linux con la siguiente instrucción con el compilador g++ en su versión g++ (Ubuntu 7.3.0-16ubuntu3) 7.3.0:

g++ -std=c++14 render/tests/render_test.cpp render/Plane.h render/Sphere.h Vec.cpp Vec.h ReferenceSystem.h exception.h render/Render.h render/Light.h render/Object.h render/RandomNumber.h -o main -fpermissive

Y se ejecuta con:

./main <numPaths> <height> <width> <nombreSalida>.ppm

El programa genera el fichero ldr_<NombreSalida>.ppm con la imagen en LDR y
<nombreSalida>.ppm


