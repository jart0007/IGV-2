#ifndef __IGVESCENA3D
#define __IGVESCENA3D
#include "igvExotraje.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

struct Transformaciones
{
    float tx = 0, ty = 0, tz = 0; ///< traslacion acumulada
    float rx=0, ry=0, rz = 0; ///< ángulos acumulados (en grados)
    float s=1; ///< escala acumulada
};


#include "igvMallaTriangulos.h"

/**
 * Los objetos de esta clase representan escenas 3D para su visualizaci�n
 */
class igvEscena3D
{
public:
    const int Objeto1 = 1; ///< Identificador interno del objeto 1
    const int Objeto2 = 2; ///< Identificador interno del objeto 2
    const int Objeto3 = 3; ///< Identificador interno del objeto 3

private:
    // Atributos
    bool ejes = true; ///< Indica si hay que dibujar los _ejes coordenados o no

    Transformaciones obj[3];
    int seleccionado = 0;

    // TODO: Apartado A: A�adir aqu� los atributos con los �ngulos de rotaci�n en X, Y y Z.
    double rotX=0, rotY=0, rotZ=0;
    igvMallaTriangulos* malla = nullptr; ///< Malla de tri�ngulos asociada a la escena

    //añadir el atributo para el modelo articulado
    igvExotraje* modelo = nullptr;
public:
        // Constructores por defecto y destructor
    igvEscena3D();
    ~igvEscena3D();

    // M�todos
    void trasladar(float x, float y, float z);
    void rotar(float drx, float dry, float drz);
    void escalar(float factor);

    // m�todo con las llamadas OpenGL para visualizar la escena
    void visualizar(bool sel = false);
    void visualizarVB();

    //métodos para el buffer de color
    int parte_de_color(GLubyte pixel[3]){return modelo ? modelo->parte_de_color(pixel) : 0;} //if inline
    void set_seleccionada(int parte){ if (modelo) modelo->set_seleccionada(parte);}
    bool get_ejes();

    void set_seleccionadoObjeto(int seleccionado);

    void animar(float dt) { if (modelo) modelo->animar(dt); }

    void set_ejes(bool _ejes);

    igvMallaTriangulos* getMalla() const
    {
        return malla;
    }

    void mover(int parte, int num, bool ejeY);
    void arrastrar(int parte, int dx, int dy);

    // Apartado A: métodos para incrementar los ángulos
    void incrX() {
        rotX += 10;
    }

    void incrY() {
        rotY += 10;
    }

    void incrZ() {
        rotZ += 10;
    }

    void decrX() {
        rotX -= 10;
    }

    void decrY() {
        rotY -= 10;
    }

    void decrZ() {
        rotZ -= 10;
    }

private:
    void pintar_ejes();

    void renderObjeto1();
    void renderObjeto2();
    void renderObjeto3();
};

#endif   // __IGVESCENA3D
