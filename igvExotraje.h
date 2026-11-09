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
    int parte_seleccionada = 0; //0: ninguna, 1: Cuerpo, 2:brazo1, 3:brazo3, 4:Misiles, 5:Lanzador

    float mvCuerpo;
    float rotCuerpo;
    float rotBrazo1;
    float rotBrazo2;
    float rotLanzadorY;
    float rotBrazoMisilesY;

    float fase = 0.0f; ///< Acumulador de tiempo para animaciones sinusoidales en tiempo real
public:
    igvExotraje();
    ~igvExotraje() = default;

    // Métodos de selección por búfer de color
    void set_seleccionada(int parte){parte_seleccionada=parte;}
    int get_seleccionada()const{return parte_seleccionada;}
    void color(bool sel, int id);
    int parte_de_color(GLubyte pixel[3]);

    void arrastrar(int parte, int dx, int dy); ///< como el método mover pero por raton y no por teclado


    void animar(float dt); ///< para la animacion del modelo automatico

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
    void mover(int parte, int sentido, bool ejeY);

    void moverCuerpo(float num);
    void rotarCuerpo(float ang);
    void rotarBrazo1(float ang);
    void rotarBrazo2(float ang);
    void rotarLanzadorY(float ang);
    void rotarBrazoMisilesY(float ang);


    //metodo para visualizar todo el modelo
    void visualizar(bool sel);
};