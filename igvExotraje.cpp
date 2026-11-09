//
// Created by juanan on 30/10/2026.
//

#include "igvExotraje.h"
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include<algorithm>

using namespace std;

/*
 * Para guardar los colores "falsos" para la seleccion usamos una
 * matriz global del tipo "GLubyte[]"
 */
const GLubyte COLOR_SEL[6][3] = {
    {0, 0, 0},       // 0: Ninguna parte / Fondo
    {255, 0, 0},     // 1: Cuerpo (Rojo)
    {0, 255, 0},     // 2: Brazo 1 (Verde)
    {0, 0, 255},     // 3: Brazo 2 (Azul)
    {255, 255, 0},   // 4: Brazo Misiles (Amarillo)
    {255, 0, 255}    // 5: Lanzador (Magenta)
};

/**
 * @brief constructor de la clase
 * @post todos los grados de libertad inicializados a 0.0f ("f" se pone para aclarar que es un float y el CLION no me grite, por que podría ser un double)
 */
igvExotraje::igvExotraje()
{
    rotBrazo1 = 0.0f;
    rotBrazo2 = 0.0f;
    mvCuerpo = 0.0f;
    rotCuerpo = 0.0f;
    rotLanzadorY = 0.0f;
    rotBrazoMisilesY = 0.0f;
}

/**
 * @brief funcion para hacer un tubo básico (sin tapa)
 * @param largo largo del tubo
 * @param ancho ancho del tubo
 * @post creacion del tubo en el centro mirando hacia el usuario con base en el plano XY y altura en el Z positivo
 */
void igvExotraje::pintar_tubo(float largo, float ancho)
{
    GLUquadricObj* tubo;

    tubo = gluNewQuadric();
    gluQuadricDrawStyle(tubo, GLU_FILL);

    glPushMatrix();
    gluCylinder(tubo, ancho, ancho, largo, 20, 20);
    glPopMatrix();

    /*
    glPushMatrix();
    gluDisk(tubo, 0, ancho, 20, 1);
    glPopMatrix();
    */

    gluDeleteQuadric(tubo);
}


/** ---------------------- Funciones para dibujar las partes del exotraje en la escena ---------------------- */

void igvExotraje::pintarCuerpo(){

    //TODO preguntar si es asi

    //cuerpo
    glPushMatrix();
    glScalef(0.5, 1, 0.75);
    glutSolidCube(1);
    glPopMatrix();

    //hombro derecho, arriba de este iría el lanzadorrr
    glPushMatrix();
    glTranslatef(-0.33, 0.25, 0);
    glScalef(0.16, 0.20, 0.20);
    glutSolidCube(1);
    glPopMatrix();

    //Cara
    glPushMatrix();
    glTranslatef(0, 0.25, 0.375);
    glutSolidSphere(0.15,20,20);
    glPopMatrix();

    //antenas
    glPushMatrix();
    glTranslatef(0.12,0.5,-0.1);
    glRotatef(-90,1,0,0);
    pintar_tubo(0.5,0.005);
    glPopMatrix();
}

void igvExotraje::pintarBrazo1(){

    glPushMatrix();
    /*
    glTranslatef(-0.41, 0.25, 0);
    */
    //(todo: ¿por que aparece en el centro y no en el centro del padre como antes?, ¿es diferente a teoria TANTO?) -> por que esta mal..


    //TODO qué se pone aquí #asustado (pegar a juan)

    //tubo que rota arriba y abajo el brazo
    glPushMatrix();
    pintar_tubo(0.33, 0.09);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0, 0.20);
    glScalef(0.20, 0.20, 0.20);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

//Lo que hay debajo del brazo 1
void igvExotraje::pintarBrazo2(){
    glPushMatrix();

    glPushMatrix();
    pintar_tubo(0.4, 0.09);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0.5);
    glScalef(0.25, 0.40, 0.25);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void igvExotraje::pintarTorreta(){
    glPushMatrix();

    glPushMatrix();
    pintar_tubo(0.40, 0.05);
    glPopMatrix();

    glPopMatrix();



    // todo shawty like a melody in my head that I can't get out got me singing like nanananana everyday is like an iPad stuck on replay (ay)

}

void igvExotraje::pintarLanzador(){
    glPushMatrix();

        glPushMatrix();
        glutSolidSphere(0.07,20,20);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.03,0.03);
        glRotatef(-45,1,0,0);
        pintar_tubo(0.15,0.04);
        glPopMatrix();

    glPopMatrix();
}

void igvExotraje::pintarRueda(){
    glPushMatrix();
    //pintar_tubo(0.5, 0.1);
    glTranslatef(0,-0.4,0);

    glScalef(0.7,1.5,1.5);
    glutSolidSphere(0.25,20,20);
    glPopMatrix();
}

void igvExotraje::pintarBrazoLanzaMisiles(){
    glPushMatrix();

        glPushMatrix();
        glScalef(0.3,0.5,0.4);
        glutSolidCube(1);
        glPopMatrix();

        //tendrá 6 misiles
        // misiles izq
        glPushMatrix();
        glTranslatef(-0.08,0.15,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.08,-0.15,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

        //misiles der
        glPushMatrix();
        glTranslatef(0.08,0.15,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.08,-0.15,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

        //misiles del medio
        glPushMatrix();
        glTranslatef(0.08,0,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.08,0,0.20);
        glutSolidSphere(0.05,20,20);
        glPopMatrix();

    glPopMatrix();

}


/** ---------------------- Funciones para aplicar los grados de libertad a cada parte ---------------------- */

/**
 *@brief Selecciona para cada parte un color dependiendo si esta seleccionado o no
 */
void igvExotraje::color(bool sel, int id)
{
    if (sel)
    {
        glColor3ubv(COLOR_SEL[id]);
    }
    else
    {
        // Reseteamos EMISSION a 0 para no heredar la luz propia de la lámpara
        GLfloat sin_emision[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, sin_emision);

        if (id == parte_seleccionada)
        {
            GLfloat amarillo[] = {1.0f, 1.0f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
        }
        else
        {
            GLfloat color_original[] = {0.4f, 0.4f, 0.4f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_original);
        }
    }
}

int igvExotraje::parte_de_color(GLubyte pixel[3])
{
    for (int i = 1; i<=5; ++i)
    {
        if (pixel[0] == COLOR_SEL[i][0] &&
            pixel[1] == COLOR_SEL[i][1] &&
            pixel[2] == COLOR_SEL[i][2])
        {
            return i; //click en objeto
        }
    }
    return 0; //has hecho click en el vacio, espabila
}

void igvExotraje::arrastrar(int parte, int dx, int dy)
{
    float sensRot = 0.5f; //grados por pixel
    float sensTras = 0.05f;

    switch (parte)
    {
    case 1: //cuerpo
        rotarCuerpo(dx * sensRot);
        moverCuerpo(dy * sensTras);
        break;
    case 2: //Brazo 1
        rotarBrazo1(dy * sensRot);
        break;
    case 3: //Brazo 2
        rotarBrazo2(dy * sensRot);
        break;
    case 4: //Brazo misiles
        rotarBrazoMisilesY(dy*sensRot);
        break;
    case 5: //Lanzador
        rotarLanzadorY(dy*sensRot);
        break;
    }
}

/**
 * @param sentido tiene que ser -1 o 1, define el sentido positivo o negativo de la accion
 * @param ejeY booleano que nos dice si queremos movernos por el ejeY (como subir o bajar) o el ejeX(ir a der-izq o hacer un cabeceo:= util para el lanza estratagemas y el cuerpo)
 */
void igvExotraje::mover(int parte, int sentido, bool ejeY)
{
    float paso = 0.5f; //para traslaciones
    float grado = 5.0;// Grados por cada pulsación de tecla (para rotaciones)

    switch (parte)
    {
    case 1: // cuerpo
        if (!(ejeY)){
            rotarCuerpo(sentido*grado);
        }else{
            moverCuerpo(paso*sentido);
        }
        break;

    case 2: // Brazo 1
        rotarBrazo1(sentido * grado);
        break;
    case 3: //brazo 2
        rotarBrazo2(sentido * grado);
        break;

    //Brazo lanzamisiles
    case 4:
        rotarBrazoMisilesY(sentido * grado);
        break;

    case 5: //lanza cosas
        rotarLanzadorY(sentido * grado);
        break;

    default:
        break;
    }
}


void igvExotraje::moverCuerpo(float num)
{
    mvCuerpo += num;
}

void igvExotraje::rotarCuerpo(float ang)
{
    if (ang+rotCuerpo==360) rotCuerpo = 0;
    else rotCuerpo+=ang;
}

void igvExotraje::rotarBrazo1(float ang)
{
    rotBrazo1 = max(-60.0f, min(60.0f,rotBrazo1+ang) );
}

void igvExotraje::rotarBrazo2(float ang)
{
    rotBrazo2 = max(-30.0f,min(30.0f,rotBrazo2+ang) );
}

void igvExotraje::rotarBrazoMisilesY(float ang)
{
    rotBrazoMisilesY = max(-70.0f,min(20.f,rotBrazoMisilesY+ang));
}


void igvExotraje::rotarLanzadorY(float ang) {
    rotLanzadorY = max(-35.0f,min(0.5f ,rotLanzadorY+ang) );

}

/**
 * @brief Actualiza los grados de libertad en función del tiempo transcurrido (dt)
 * @param dt Tiempo en segundos desde el último fotograma
 */
void igvExotraje::animar(float dt)
{
    fase += dt;

    // Movimientos del cuerpo (Avance y Giro)
    mvCuerpo  = 1.5f * sin(0.35f * fase);
    rotCuerpo = 60.0f * sin(0.6f * fase);

    // Animación de articulaciones respetando sus límites
    rotBrazo1        = max(-60.0f, min(60.0f, 40.0f * sin(0.9f * fase)));
    rotBrazo2        = max(-30.0f, min(30.0f, 25.0f * sin(1.3f * fase)));
    rotBrazoMisilesY = max(-70.0f, min(20.0f, -25.0f + 45.0f * sin(1.1f * fase)));
    rotLanzadorY     = max(-35.0f, min(0.5f, -17.25f + 17.25f * sin(1.8f * fase)));
}

/**
 * @brief funcion que dibuja el exotraje en escena
 */
void igvExotraje::visualizar(bool sel){
    glPushMatrix();

    //nivel 1 (cuerpo)
    glTranslated(0,0,mvCuerpo);
    glRotatef(rotCuerpo,0,1,0);

    color(sel,1);
    pintarCuerpo();
    //nivel 2 (brazo1, ruedasx2, brazo-misiles,lanza cosas)
    pintarRueda();

    glPushMatrix();    //--------rama de brazo1->brazo2->torreta


        glTranslatef(-0.41,0.25,0);
        glRotatef(-rotBrazo1, 1, 0, 0);
        glRotatef(-90, 0, 1, 0); //Esto invierte los ejes X y Z

        color(sel,2);
        pintarBrazo1();

        glRotatef(90, 0, 1, 0); //Deshacemos la inversión



        //nivel 3 (brazo2)
        glTranslatef(-0.20,0,0);
        glRotatef(90,1,0,0);
        glRotatef(rotBrazo2,0,0,1); //grado de libertad

        color(sel,3);
        pintarBrazo2();

        glRotatef(-90,1,0,0); //Deshacemos la inversion del eje

        //nivel 4 (torreta)
        glTranslatef(0,-0.43,0.20);
        pintarTorreta();

    glPopMatrix();//fin rama brazo


    glPushMatrix(); //brazo lanza-misiles (para que no afecte al lanzador)
        glTranslatef(0.4, 0.2, 0);
        glRotatef(rotBrazoMisilesY, 1, 0, 0);

        color(sel,4);
        pintarBrazoLanzaMisiles();
    glPopMatrix();

    glTranslatef(-0.34,0.35,0);

    color(sel,5);
    glRotatef(rotLanzadorY, 1, 0, 0);
    pintarLanzador();


    // RESTAURAR MATERIAL NEUTRO AL SALIR PARA NO CONTAMINAR OTROS OBJETOS DE LA ESCENA <-- arreglo para que no se pinte la lampara sin quererlo
    if (!sel)
    {
        GLfloat neutro[] = {0.4f, 0.4f, 0.4f, 1.0f};
        GLfloat sin_emision[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, neutro);
        glMaterialfv(GL_FRONT, GL_EMISSION, sin_emision);
    }
    
    glPopMatrix();
}