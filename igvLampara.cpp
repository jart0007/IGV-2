//
// Created by juanan on 25/10/2026.
//

#include "igvLampara.h"

#include <math.h>


/**
 * Constructor por defecto
 */
igvLampara::igvLampara() : igvMallaTriangulos()
{
    usarnormales = false;
}


/**
El Bucle Anidado (La altura / Extrusión):
El cálculo de y: A diferencia del toroide, aquí no hay ángulo $v$ porque la pared del cilindro es
completamente vertical y recta. En su lugar, el bucle j divide la altura total a en trozos iguales según
divV y calcula la altura física y en la que toca dibujar la siguiente rebanada.

El truco de optimización (Bucle i): Para dibujar las siguientes alturas, el programa no vuelve a calcular
senos ni cosenos. Como el cilindro tiene exactamente el mismo grosor de principio a fin, el código
busca la coordenada que calculó en el anillo base (base0) y copia exactamente la $X$ y la $Z$ en la nueva
posición de memoria (baseJ), asignándole únicamente la nueva altura y.

Las Normales calcadas: De la misma forma, como la pared no se curva hacia adentro ni hacia afuera, la
dirección perpendicular de la pared en la base es idéntica a la dirección perpendicular en la parte más alta.
Por tanto, simplemente copia las normales de la base.


-------------------------------
Tendrías que modificar el bucle anidado (el que calcula la altura) introduciendo una interpolación
lineal para el radio.
 - Calcular la reducción del radio: A medida que la altura y aumenta desde $0$ hasta $a$, el radio debe
   disminuir desde $r$ hasta $0$. La fórmula matemática para el radio actual a cualquier altura y es: float radio_actual = r * (1.0f - (y / a));

 - Recalcular X y Z: Como en el primer bucle guardaste los cosenos y senos puros (cx y sx) dentro del
   array de normales de la base, puedes reutilizarlos multiplicándolos por tu nuevo radio_actual.
**/

igvLampara::igvLampara(float r, float a, int divU, int divV){

    //Inicialización de parámetros
    if (divU < 3) divU = 3;
    if (divV < 1) divV = 1;

    num_vertices   = divU * (divV + 1);
    vertices       = new float[num_vertices * 3];
    normales       = new float[num_vertices * 3];

    num_triangulos = divU * divV * 2;
    triangulos     = new unsigned int[num_triangulos * 3];

    for (int j=0; j<=divV; j++) {
        float v = (float)j/(float)divV; //proporcion de altura de 0.0 a 1.0. 1/5 = 0.algo 5/5 = 1 --> Valor entre 0 y 1
        float y = v*a; //Altura en la que estamos en el eje Y

        //cálculo del radio segun la altura (variable)
        float r_nuevo = 0;

        //Si v está por debajo del 20% de la altura total de la lampara se dibuja la base
        //3.5 y 2.5 son pendientes de inclinación
        if (v <= 0.15f) {
            // 1. Base ancha que se estrecha
            r_nuevo = r * (0.5 - 2.33f * v);
        }
        else if (v < 0.70f) {
            // 2. Mástil fino
            r_nuevo = 0.15f * r;
        }
        else {
            // 3. Pantalla RECTA/PLANA:
            // Al fijar un radio constante (ej. 0.5f), la pantalla sube completamente vertical
            r_nuevo = 0.5f * r;
        }

        for (int i=0; i < divU; ++i) {
            float alpha = (i/(float)divU) * 2.0*(float)M_PI; // convertir el angulo. 2*Pi es el circulo completo
            float cx = cos(alpha);
            float sx = sin(alpha);

            int k = (j * divU + i) * 3;

            vertices[k+0] = r_nuevo * cx;
            vertices[k+1] = y;
            vertices[k+2] = r_nuevo * sx;

            normales[k + 0] = cx;
            normales[k + 1] = 0.0f;
            normales[k + 2] = sx;
        }
    }

    //triangulacion
    int t = 0;
    for (int j = 0; j < divV; ++j) {
        for (int i=0; i < divU; ++i)
        {
            unsigned int a_idx =  j      * divU + i;
            unsigned int b_idx =  j      * divU + ((i + 1) % divU);
            unsigned int c_idx = (j + 1) * divU + ((i + 1) % divU);
            unsigned int d_idx = (j + 1) * divU + i;

            // Triángulo 1: (a, d, b)
            triangulos[t++] = a_idx;
            triangulos[t++] = d_idx;
            triangulos[t++] = b_idx;

            // Triángulo 2: (b, d, c)
            triangulos[t++] = b_idx;
            triangulos[t++] = d_idx;
            triangulos[t++] = c_idx;
        }
    }
}

igvLampara::~igvLampara() {};