//
// Created by juanan on 30/10/2026.
//

#include "igvExotraje.h"
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include<algorithm>

using namespace std;

/**
 * @brief constructor de la clase
 * @post todos los grados de libertad inicializados a 0.0f ("f" se pone para aclarar que es un float y el CLION no me grite, por que podría ser un double)
 */
igvExotraje::igvExotraje()
{
    rotBrazo1=0.0f;
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
    glRotatef(-90, 0, 1, 0);
    pintar_tubo(0.33, 0.09);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.20,0, 0);
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
    glScalef(0.25, 0.25, 0.25);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void igvExotraje::pintarTorreta(){
}

void igvExotraje::pintarLanzador(){
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
}


/** ---------------------- Funciones para aplicar los grados de libertad a cada parte ---------------------- */
void igvExotraje::mover(int parte, int sentido) //sentido tiene que ser "1" o "-1"
{
    float paso = 5.0f; // Grados por cada pulsación de tecla

    switch (parte)
    {
    case 1: // Brazo 1
        rotarBrazo1(sentido * paso);
        break;

        // Futuros grados de libertad:
        // case 2: rotarBrazo2(sentido * paso); break;
        // case 3: rotarTorreta(sentido * paso); break;

    default:
        break;
    }
}


void igvExotraje::rotarBrazo1(float ang)
{
    rotBrazo1 = max(-60.0f, min(60.0f,rotBrazo1+ang) );
}

/**
 * @brief funcion que dibuja el exotraje en escena
 */
void igvExotraje::visualizar(){
    glPushMatrix();

    //nivel 1 (cuerpo)
    pintarCuerpo();


    //nivel 2 (brazo1, ruedasx2, brazo-misiles,lanza cosas)

    pintarRueda();

    glPushMatrix();    //--------rama de brazo1->brazo2->torreta

        glTranslatef(-0.41,0.25,0);
        glRotatef(rotBrazo1, 1, 0, 0);
        pintarBrazo1();


        //nivel 3 (brazo2)
        glTranslatef(-0.20,-0.10,0);
        glRotatef(90,1,0,0);
        pintarBrazo2();

        //nivel 4 (torreta)

    glPopMatrix();//fin rama brazo

    glPopMatrix();
}


