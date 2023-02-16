# Reporte Raytracer | Josue Alexis Campos Negron

Para la realizacion del proyecto principalmente utilizamos el libro _Ray Tracing in One Weekend_ para poder entender mejor los conceptos de rayos y cuando estos golpean y rebotan entre los objetos. Sin embargo, dicho fuente de consulta unicamente trabaja con esferas por lo cual fue necesario la implementacion del triangulo en el plano y luego de la clase `primitive` la cual puede general cualquier poligono a base de triangulos. Para la implementacion de dichos elementos utilizamos los conceptos vistos para la clase `sphere` y conceptos matematicos para conocer cuando un rayo golpea al triangulo y por ende a nuestro ohjeto.

# Codigo

En el codigo tenemos multiples librerias para el funcionamiento del Raytracer. Las siguientes librerias nos ayudan en la informacion del rayo y el efecto de este en los objetos.
- hittable_list.h: Define la lista de objetos y la secuencia de los golpes de rato entre los objetos.
- hittanle.h: Realiza el reconocimiento del rayo si intersecta con el objeto.
- ray.h: Realiza todo el procedimiento respecto al rayo.
- rtweekend.h: Contiene funciones de utilidad para simplicidad de ciertas funciones.
- vec3.h: Define una clase el cual nos permite trabajar con puntos y operaciones de punto mas facilmente.

Luego, tenemos librerias que nos ayudan al diseño de nuestras figuras y simplifican el trabajo en codigo.
- camera.h: Define la camara y funciones de la misma para el cambio de perspectiva, posicion, zoom entre otras cosas.
- color.h: Realiza el procesamiento del colo de pixeles de manera mas simple e intuitiva.

Finalmente, tenemos las librerias que definen las figuras de la escena las cuales son:
- triangle.h: Define el triangulo un triangulo en el plano y la funcion de reconocimiento si un rayo lo golpea.
- sphere.h: Define la clase del objeto esfera el cual grafica la esfera junto con la funcion para reconocer si un rayo golpea la esfera.
- primitive.h: Grafica una figura con base a triangulos en el plano por lo cual recibe un conjunto de puntos y un vector de vertices que definen los triangulos de la figura.

# Archivo input txt
Nuestro programa tiene como input el archivo `info.txt` en el cual se presenta los datos necesarios para los objetos de la escena. Por otro lado tenemos como output el archivo `image.ppm` el cual es la imagen de nuestro escena. A continuacion presentamos las caracteristicas del archivo `info.txt`.

En la primera linea ingresaremos un numero entero $N$ el cual denota el numero de figuras primitivas que se van a presentar. Luego tenemos $N$ bloques de la siguiente forma:
- La primera linea $P, V$ y $M$ donde $P$ denota el numero de puntos de la figura, $V$ el numero de triangulos de la figura y $M$ el tipo de material de la figura. Tenemos $3$ tipos de material:
    1. Cristalino.
    2. Mate.
    3. Metalico.
- Ahora tenemos $P$ lineas con $d_1, d_2$ y $d_3$ separados por espacio los cuales son numeros de tipo `double` que definen un punto.
- Seguidamente tenemos $V$ lineas con enteros $c_1, c_2$ y $c_3$ separados por espacio los cuales representan los indices de los puntos que forman el triangulo.

En la siguiente lines tenemos un entero $m$ el cual denota el numero de esferas que se van a presentar en la escena. Despues tenemos $m$ lineas de la forma $p_1, p_2, p_3, r$ y $M$ separados por un espacio donde los $p_i$ son de tipo `double` y denotan el punto centro de la esfera, $r$ tambien es de tipo `double` y denota el radio de la esfera, finalmente tenemos a $M$ el caul es de tipo `int` y denota el tipo de material clasificado de la misma manera antes mencionada.

A continuacion presentamos un ejemplo del archivo txt en donde tenemos dos figuras primitivas, un cubo y una piramide y una esfera alineadas en el eje $X$.

```
2
8 12 3
1.0 0.0 1.0
-1.0 0.0 1.0
-1.0 0.0 -1.0
1.0 0.0 -1.0
1.0 2.0 1.0
-1.0 2.0 1.0
-1.0 2.0 -1.0
1.0 2.0 -1.0
3 2 0
3 0 1
6 2 3
6 3 7
7 3 1
7 1 5
6 7 5
6 5 4
6 0 4
6 2 0
5 1 0
5 0 4
5 6 2
4.0 0.0 1.0
2.0 0.0 1.0
2.0 0.0 -1.0
4.0 0.0 -1.0
3.0 2.0 0.0
0 1 2
2 3 0
0 1 4
1 2 4
2 3 4
3 0 4
1
-3.0 1.0 0.0 1.0 2
```

# Bibliografia
Utilizamos la siguiente colección de libros.

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects)

- [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)

- [Ray Tracing: The Rest of Your Life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)

También se hizo uso de la siguiente página web para conocer cuando un punto intersectaba con el plano.

[Point in Triangle](https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/point_in_triangle.html)