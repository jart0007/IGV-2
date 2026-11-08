//
// Created by juanan and danoi and dani on 30/10/2026.
//

#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#ifndef PR2A_MECAHELLDVERS_H
#define PR2A_MECAHELLDVERS_H

#endif //PR2A_MECAHELLDVERS_H

class igvExotraje{
private:
    float mvCuerpo;
    float rotCuerpo;
    float rotBrazo1;
    float rotBrazo2;
    float rotLanzadorY;
    float rotBrazoMisilesY;
public:
    igvExotraje();
    ~igvExotraje() = default;

    //funciones para pintar el exotraje
    void pintar_tubo(float largo, float ancho);
    void pintarCuerpo();
    void pintarBrazo1();
    void pintarBrazo2();
    void pintarTorreta();
    void pintarLanzador();
    void pintarRueda();
    void pintarBrazoLanzaMisiles();
    void arrastrar(int parte, int dx, int dy);

    //funciones de grados de libertad
    void mover(int parte, int sentido, bool ejeY);

    void moverCuerpo(float num);
    void rotarCuerpo(float ang);
    void rotarBrazo1(float ang);
    void rotarBrazo2(float ang);
    void rotarLanzadorY(float ang);
    void rotarBrazoMisilesY(float ang);


    //metodo para visualizar todo el modelo
    void visualizar();
};