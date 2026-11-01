//
// Created by juanan on 30/10/2026.
//

#include "igvExotraje.h"
#include <cstdlib>
#include <stdio.h>
#include <math.h>

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

    glTranslatef(-0.41, 0.25, 0);
    //abajo estan las transformaciones para modelar el objeto, arriba, para moverlo junto a el padre
    //(todo: ¿por que aparece en el centro y no en el centro del padre como antes?, ¿es diferente a teoria TANTO?)


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

    glTranslatef(-0.61, 0.15, 0);
    glRotatef(90,1,0,0);
    //abajo estan las transformaciones para modelar el objeto, arriba, para moverlo junto a el padre

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

void igvExotraje::visualizar(){
    glPushMatrix();

    //nivel 1 (cuerpo)
    pintarCuerpo();


    //nivel 2 (brazo1, ruedasx2, brazo-misiles,lanza cosas)
    pintarBrazo1(); pintarRueda();


    //nivel 3 (brazo2)
    pintarBrazo2();

    //nivel 4 (torreta)

    glPopMatrix();
}
