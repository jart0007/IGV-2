#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

#include <iostream>

// Aplicaci�n del patr�n de dise�o Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// Constructor por defecto
igvInterfaz::igvInterfaz() = default;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * diseño Singleton
 * @return Una referencia al objeto �nico de la clase
 */
igvInterfaz& igvInterfaz::getInstancia()
{
    if (!_instancia)
    {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo()
{
    // inicia la c�mara
    _instancia->camara.set(IGV_PARALELA, {3.0, 2.0, 4}, {0, 0, 0}
                           , {0, 1.0, 0}, -1 * 1.5, 1 * 1.5, -1 * 1.5, 1 * 1.5
                           , -1 * 3, 200);


    //Camara de perspectiva de planta
    p0p = igvPunto3D(0, 5, 0);
    rp = igvPunto3D(0, 0, 0);
    Vp = igvPunto3D(0, 0, -1);

    _instancia->camaraPlanta.set(IGV_PARALELA, p0p, rp, Vp, -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);


}

/**
 * Inicializa todos los par�metros para crear una ventana de visualizaci�n
 * @param argc N�mero de par�metros por l�nea de comandos al ejecutar la
 *             aplicaci�n
 * @param argv Par�metros por l�nea de comandos al ejecutar la aplicaci�n
 * @param _ancho_ventana Ancho inicial de la ventana de visualizaci�n
 * @param _alto_ventana Alto inicial de la ventana de visualizaci�n
 * @param _pos_X Coordenada X de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _pos_Y Coordenada Y de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _titulo T�tulo de la ventana de visualizaci�n
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void igvInterfaz::configura_entorno(int argc, char** argv, int _ancho_ventana
                                    , int _alto_ventana, int _pos_X, int _pos_Y
                                    , std::string _titulo)
{
    // inicializaci�n de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicializaci�n de la ventana de visualizaci�n
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());

    //<>Inicializamos el menú
    inicializarMenu();

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminaci�n de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para c�lculo iluminaci�n

    crear_mundo(); // crea el mundo a visualizar en la ventana
}

/**
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion()
{
    glutMainLoop(); // inicia el bucle de visualizaci�n de GLUT
}

/**
 * M�todo para control de eventos del teclado
 * @param key C�digo de la tecla pulsada
 * @param x Coordenada X de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
/**
 * @brief Submenú de interacción y eventos del menú[cite: 37]
 */
void igvInterfaz::menuHandle(int valor)
{
    _instancia->menuSelection = valor;

    switch (valor)
    {
    case M_PLANO:
        _instancia->escena.getMalla()->setGouraud(false);
        break;
    case M_GOURAUD:
        _instancia->escena.getMalla()->setGouraud(true);
        break;

    // --- SELECCIÓN DE MODO DE INTERACCIÓNnnnnnnN ---[cite: 37]
    case M_TRANS_P1:
        _instancia->modoInteraccion = MODO_P1;
        std::cout << "[MODO] Transformaciones Práctica 1 (1: Malla, 2: Mecha)\n";
        break;
    case M_TECLADO:
        _instancia->modoInteraccion = MODO_TECLADO;
        std::cout << "[MODO] Articulaciones por Teclado\n";
        break;
    case M_RATON:
        _instancia->modoInteraccion = MODO_RATON;
        std::cout << "[MODO] Articulaciones por Ratón (Buffer de Color)\n";
        break;
    case M_CAMARA_MODO:
        _instancia->modoInteraccion = MODO_CAMARA;
        std::cout << "[MODO] Control de Cámara activado\n";
        break;

    // --- ANIMACIÓN ---[cite: 34]
    case M_ANIMAR_MODELO:
        _instancia->animar_modelo = !_instancia->animar_modelo;
        if (_instancia->animar_modelo || _instancia->orbitar_camara) {
            _instancia->t_prev = glutGet(GLUT_ELAPSED_TIME);
            glutIdleFunc(idleFunc);
        } else {
            glutIdleFunc(nullptr);
        }
        break;

    case M_ORBITAR_CAMARA:
        _instancia->orbitar_camara = !_instancia->orbitar_camara;
        if (_instancia->animar_modelo || _instancia->orbitar_camara) {
            _instancia->t_prev = glutGet(GLUT_ELAPSED_TIME);
            glutIdleFunc(idleFunc);
        } else {
            glutIdleFunc(nullptr);
        }
        break;

    // --- VISTAS ---[cite: 30]
    case M_PLANTA:
        _instancia->verPlanta = !_instancia->verPlanta;
        break;
    case M_REINICIAR_CAMARA:
        _instancia->crear_mundo();
        break;

    case M_AYUDA:
        std::cout << "\n=== CONTROLES SEGÚN EL MODO ACTIVO ===\n";
        std::cout << " Modo P1      : Teclas 1/2 eligen objeto. Flechas mueven, X/Y/Z rotan, S escala.\n";
        std::cout << " Modo Teclado : Teclas 1..5 eligen parte. Flechas mueven la articulación.\n";
        std::cout << " Modo Ratón   : Clic izq selecciona pieza (resalta amarillo), arrastrar mueve.\n";
        std::cout << " Modo Cámara  : Flechas orbitan / cabecean la cámara.\n";
        break;

    case M_SALIR:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void igvInterfaz::inicializarMenu()
{
    int sub1 = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Plano (GL_FLAT)", M_PLANO);
    glutAddMenuEntry("Interpolado (GL_SMOOTH)", M_GOURAUD);

    int sub2 = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Transformar modelos (P1)", M_TRANS_P1);
    glutAddMenuEntry("Articulaciones: teclado", M_TECLADO);
    glutAddMenuEntry("Articulaciones: raton", M_RATON);
    glutAddMenuEntry("Mover la camara", M_CAMARA_MODO);

    int sub3 = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Animar modelo", M_ANIMAR_MODELO);
    glutAddMenuEntry("Orbitar camara", M_ORBITAR_CAMARA);

    int sub4 = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Perspectiva / Paralela", M_PROYECCION);
    glutAddMenuEntry("Vista de planta", M_PLANTA);
    glutAddMenuEntry("Reiniciar camara", M_REINICIAR_CAMARA);

    glutCreateMenu(menuHandle);
    glutAddSubMenu("Sombreado", sub1);
    glutAddSubMenu("Interaccion", sub2);
    glutAddSubMenu("Animacion", sub3);
    glutAddSubMenu("Camara y vistas", sub4);
    glutAddMenuEntry("Ayuda (teclas)", M_AYUDA);
    glutAddMenuEntry("Salir", M_SALIR);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * @brief Teclado con diferenciación por modo de interacción[cite: 38]
 */
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e': case 'E':
        _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
        break;
    case 27:
        exit(0);
        break;

    default:
        if (_instancia->modoInteraccion == MODO_P1)
        {
            switch (key)
            {
            case '1': _instancia->escena.set_seleccionadoObjeto(0); std::cout << "[P1] Objeto 1: Malla\n"; break;
            case '2': _instancia->escena.set_seleccionadoObjeto(1); std::cout << "[P1] Objeto 2: Mecha\n"; break;
            case 'x': _instancia->escena.rotar(10, 0, 0); break;
            case 'X': _instancia->escena.rotar(-10, 0, 0); break;
            case 'y': _instancia->escena.rotar(0, 10, 0); break;
            case 'Y': _instancia->escena.rotar(0, -10, 0); break;
            case 'z': _instancia->escena.rotar(0, 0, 10); break;
            case 'Z': _instancia->escena.rotar(0, 0, -10); break;
            case 's': _instancia->escena.escalar(0.1f); break;
            case 'S': _instancia->escena.escalar(-0.1f); break;
            }
        }
        else if (_instancia->modoInteraccion == MODO_TECLADO || _instancia->modoInteraccion == MODO_RATON)
        {
            if (key >= '1' && key <= '5')
            {
                _instancia->parte = key - '0';
                _instancia->parte_seleccionada = _instancia->parte;
                _instancia->escena.set_seleccionada(_instancia->parte);
            }
        }
        break;
    }

    glutPostRedisplay();
}

/**
 * @brief Cursores especiales diferenciados por modo de interacción[cite: 38]
 */
void igvInterfaz::specialFunc(int key, int x, int y)
{
    switch (_instancia->modoInteraccion)
    {
    case MODO_P1:
        switch (key)
        {
        case GLUT_KEY_LEFT:  _instancia->escena.trasladar(-0.1f, 0, 0); break;
        case GLUT_KEY_RIGHT: _instancia->escena.trasladar(+0.1f, 0, 0); break;
        case GLUT_KEY_UP:    _instancia->escena.trasladar(0, 0, -0.1f); break;
        case GLUT_KEY_DOWN:  _instancia->escena.trasladar(0, 0, +0.1f); break;
        }
        break;

    case MODO_TECLADO:
        switch (key)
        {
        case GLUT_KEY_LEFT:  _instancia->escena.mover(_instancia->parte, -1, false); break;
        case GLUT_KEY_RIGHT: _instancia->escena.mover(_instancia->parte, +1, false); break;
        case GLUT_KEY_UP:    _instancia->escena.mover(_instancia->parte, +1, true); break;
        case GLUT_KEY_DOWN:  _instancia->escena.mover(_instancia->parte, -1, true); break;
        }
        break;

    case MODO_CAMARA:
        switch (key)
        {
        case GLUT_KEY_LEFT:  _instancia->camara.orbita(-5); break;
        case GLUT_KEY_RIGHT: _instancia->camara.orbita(+5); break;
        case GLUT_KEY_UP:    _instancia->camara.cabeceo(+5); break;
        case GLUT_KEY_DOWN:  _instancia->camara.cabeceo(-5); break;
        }
        break;

    case MODO_RATON:
        switch (key)
        {
        case GLUT_KEY_LEFT:  _instancia->escena.mover(_instancia->parte_seleccionada, -1, false); break;
        case GLUT_KEY_RIGHT: _instancia->escena.mover(_instancia->parte_seleccionada, +1, false); break;
        case GLUT_KEY_UP:    _instancia->escena.mover(_instancia->parte_seleccionada, +1, true); break;
        case GLUT_KEY_DOWN:  _instancia->escena.mover(_instancia->parte_seleccionada, -1, true); break;
        }
        break;
    }

    glutPostRedisplay();
}

void igvInterfaz::mouseFunc(GLint boton, GLint estado, GLint x, GLint y)
{
    if (boton == GLUT_LEFT_BUTTON)
    {
        // Ignorar clic si cae en la vista secundaria de planta (cuadrante superior derecho)[cite: 31]
        int vpMinX = _instancia->get_ancho_ventana() - _instancia->get_ancho_ventana() / 3;
        int vpMaxY = _instancia->get_alto_ventana() / 3;

        if (_instancia->verPlanta && x >= vpMinX && y <= vpMaxY)
        {
            return;
        }

        if (estado == GLUT_DOWN)
        {
            _instancia->boton_retenido = true;
            if (_instancia->modoInteraccion == MODO_RATON)
            {
                _instancia->modo = IGV_SELECCIONAR;
            }
        }
        if (estado == GLUT_UP)
        {
            _instancia->boton_retenido = false;
        }

        _instancia->cursorX = x;
        _instancia->cursorY = y;
        glutPostRedisplay();
    }
}

void igvInterfaz::motionFunc(GLint x, GLint y)
{
    if (_instancia->boton_retenido && _instancia->modoInteraccion == MODO_RATON)
    {
        if (_instancia->parte_seleccionada > 0)
        {
            int dx = x - _instancia->cursorX;
            int dy = _instancia->cursorY - y;

            _instancia->escena.arrastrar(_instancia->parte_seleccionada, dx, dy);

            _instancia->cursorX = x;
            _instancia->cursorY = y;
            glutPostRedisplay();
        }
    }
}

void igvInterfaz::displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_instancia->modo == IGV_SELECCIONAR)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_DITHER);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _instancia->camara.aplicar();
        _instancia->escena.visualizarVB();

        GLubyte pixel[3];
        glReadPixels(_instancia->cursorX, _instancia->alto_ventana - 1 - _instancia->cursorY,
                     1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        int parte = _instancia->escena.parte_de_color(pixel);
        _instancia->parte_seleccionada = parte;
        _instancia->parte = parte;
        _instancia->escena.set_seleccionada(parte);

        _instancia->modo = IGV_VISUALIZAR;
        glEnable(GL_LIGHTING);
        glEnable(GL_DITHER);

        glutPostRedisplay();
    }
    else
    {
        // 1. Viewport Principal
        glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());
        _instancia->camara.aplicar();
        _instancia->escena.visualizar(false);

        // 2. Viewport Planta (si está activo)
        if (_instancia->verPlanta)
        {
            int vpAncho = _instancia->get_ancho_ventana() / 3;
            int vpAlto = _instancia->get_alto_ventana() / 3;
            int vpX = _instancia->get_ancho_ventana() - vpAncho;
            int vpY = _instancia->get_alto_ventana() - vpAlto;

            glEnable(GL_SCISSOR_TEST);
            glScissor(vpX, vpY, vpAncho, vpAlto);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_SCISSOR_TEST);

            glViewport(vpX, vpY, vpAncho, vpAlto);
            _instancia->camaraPlanta.aplicar();
            _instancia->escena.visualizar(false);
        }

        glutSwapBuffers();
    }
}

void igvInterfaz::reshapeFunc(int w, int h)
{
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    _instancia->camara.aplicar();
}

void igvInterfaz::idleFunc()
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = (t - _instancia->t_prev) / 1000.0f;
    _instancia->t_prev = t;

    if (_instancia->animar_modelo)
    {
        _instancia->escena.animar(dt);
    }

    if (_instancia->orbitar_camara)
    {
        _instancia->camara.orbita(20.0f * dt);
    }

    glutPostRedisplay();
}

/**
 * M�todo para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks()
{
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialFunc);

    //Añadido para buffer de color
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutIdleFunc(idleFunc);
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana()
{
    return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana()
{
    return alto_ventana;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana(int _ancho_ventana)
{
    ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana(int _alto_ventana)
{
    alto_ventana = _alto_ventana;
}
