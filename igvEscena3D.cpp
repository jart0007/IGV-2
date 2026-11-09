#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <igvCilindro.h>

#include "igvEscena3D.h"

#include "igvLampara.h"
#include "igvMallaTriangulos.h"


// M�todos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D()
{
    // TODO: rtApaado B: Inseel crta �digo para crear un cilindro
    malla = new igvLampara(0.3,1,40,30);
    modelo = new igvExotraje();
}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D()
{
    if (malla != nullptr)
    {
        delete malla;
        malla = nullptr;
    }
    if (modelo != nullptr)
    {
        delete modelo;
        modelo = nullptr;
    }
}


// M�todos p�blicos

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{
    GLfloat rojo[] = {1, 0, 0, 1.0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar(bool sel)
{
    GLfloat color_malla[] = {0, 0.25, 0, 1.0};
    GLfloat luz0[4] = {5, 5, 5, 1};

    if (!sel)
    {
        glLightfv(GL_LIGHT0, GL_POSITION, luz0);
        glEnable(GL_LIGHT0);
        if (ejes) pintar_ejes();
    }

    // --- 1. MALLA PARAMÉTRICA (Transformaciones P1 en obj[0]) ---
    glPushMatrix();
    // Transformaciones P1 acumuladas para el modelo 1
    glTranslatef(obj[0].tx, obj[0].ty, obj[0].tz);
    glScalef(obj[0].s, obj[0].s, obj[0].s);
    glRotatef(obj[0].rx, 1, 0, 0);
    glRotatef(obj[0].ry, 0, 1, 0);
    glRotatef(obj[0].rz, 0, 0, 1);

    // Rotaciones teclado de la malla
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    if (sel)
    {
        glColor3ub(0, 0, 0); // Máscara de fondo en modo selección
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
    }
    glTranslatef(-1, 0, -1);
    malla->visualizar();
    glPopMatrix(); 


    // --- 2. MODELO ARTICULADO (Transformaciones P1 en obj[1]) ---
    glPushMatrix();
    // Transformaciones P1 acumuladas para el robot
    glTranslatef(obj[1].tx, obj[1].ty, obj[1].tz);
    glScalef(obj[1].s, obj[1].s, obj[1].s);
    glRotatef(obj[1].rx, 1, 0, 0);
    glRotatef(obj[1].ry, 0, 1, 0);
    glRotatef(obj[1].rz, 0, 0, 1);

    if (modelo) modelo->visualizar(sel);
    glPopMatrix();
}


/**
 * M�todo para la visualizaci�n del modelo sin luces (se utiliza durante la
 * selecci�n)
 */
void igvEscena3D::visualizarVB()
{
    visualizar(true);
}


/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes()
{
    return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes(bool _ejes)
{
    ejes = _ejes;
}

void igvEscena3D::mover(int parte, int sentido, bool ejeY)
{
    if (modelo != nullptr)
    {
        modelo->mover(parte, sentido, ejeY);
    }
}

void igvEscena3D::arrastrar(int parte, int dx, int dy)
{
    if (modelo != nullptr)
    {
        modelo->arrastrar(parte, dx, dy);
    }
}



void igvEscena3D::trasladar(float x, float y, float z)
{
    obj[seleccionado].tx+=x;
    obj[seleccionado].ty+=y;
    obj[seleccionado].tz+=z;
}



void igvEscena3D::rotar(float drx, float dry, float drz)
{
    obj[seleccionado].rx+=drx;
    obj[seleccionado].ry+=dry;
    obj[seleccionado].rz+=drz;
}



void igvEscena3D::escalar(float factor)
{
    obj[seleccionado].s+=factor;
}


void igvEscena3D::set_seleccionadoObjeto(const int seleccionado)
{
    this->seleccionado = seleccionado;
}
