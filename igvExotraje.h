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
    float rotBrazo1;
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

    //funciones de grados de libertad
    void mover(int parte, int sentido);

    void rotarBrazo1(float ang);



    //metodo para visualizar todo el modelo
    void visualizar();
};