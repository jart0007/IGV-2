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
public:
    void pintarCuerpo();
    void pintarBrazo1();
    void pintarBrazo2();
    void pintarTorreta();
    void pintarLanzador();
    void pintarRueda();///< x2
    void pintarBrazoLanzaMisiles();

    //metodo para visualizar todo el modelo
    void visualizar();
};