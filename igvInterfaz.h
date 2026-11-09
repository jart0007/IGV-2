#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>

#include "igvEscena3D.h"
#include "igvCamara.h"

enum modoInterfaz
{
    IGV_VISUALIZAR, ///< se visualiza de forma normal la escena, con el robot la lampara y esas cosas
    IGV_SELECCIONAR ///< modo seleccion por color (cuando se hace click en la escena)
};


enum Vista
{
    PLANTA ///< Vista de planta (cámara en el eje Y)
    , ALZADO ///< Vista de alzado (cámara en el eje Z)
    , PERFIL ///< Vista de perfil (cámara en el eje X)
    , OTRA ///< Otro tipo de vista
};

enum ModoInteraccion
{
    MODO_P1,      ///< Transformaciones P1 (trasladar/rotar/escalar objeto entero)[cite: 30, 38]
    MODO_TECLADO, ///< Articulaciones por teclado (1..5 + cursores)[cite: 37, 38]
    MODO_RATON,   ///< Selección por color y arrastre con ratón[cite: 37, 38]
    MODO_CAMARA   ///< Control manual de la cámara[cite: 37, 38]
};

/**
 * Los objetos de esta clase encapsulan la interfaz y el estado de la aplicación
 */
class igvInterfaz
{
private:
    // Atributos modelo articulado
    int parte=1;
    ModoInteraccion modoInteraccion = MODO_TECLADO; ///< Modo por defecto[cite: 37]
    bool verPlanta = true;                          ///< Controla la vista secundaria de planta[cite: 37]
    int tipo = 1;

    //atributos seleccion por color
    modoInterfaz modo = IGV_VISUALIZAR;
    int cursorX = 0; /**< Coordenada X. pixel de la pantalla sobre el que esta situado
                           el raton para pulsar o arrastrar */
    int cursorY = 0; ///< ^|\/|^ lo mismo pero en Y
    int parte_seleccionada =-1; ///< Identificador de objeto seleccionado
    bool boton_retenido = false; ///< Indica si el boton esta pulsado (true) o soltado

    bool animar_modelo = false;  ///< Controla si la animación del mecha está activa
    bool orbitar_camara = false; ///< Controla si la órbita automática de la cámara está activa[cite: 34, 35]
    int t_prev = 0;              ///< Guarda el tiempo de GLUT del fotograma anterior en ms

    int ancho_ventana = 0; ///< Ancho de la ventana de visualización
    int alto_ventana = 0; ///< Alto de la ventana de visualización

    igvEscena3D escena; ///< Escena que se visualiza en la ventana definida por igvInterfaz
    igvCamara camara; ///< Cámara que se utiliza para visualizar la escena
    igvCamara camaraPlanta;

    igvPunto3D p0 = {0, 0, 0} ///< Posición de la cámara
    , r = {0, 0, 0} ///< Punto de referencia para las vistas
    , V = {0, 0, 0} ///< Vector que indica la vertical en la vista
    ;

    igvPunto3D p0p = {0, 0, 0} ///< Posición de la cámara
    , rp = {0, 0, 0} ///< Punto de referencia para las vistas
    , Vp = {0, 0, 0} ///< Vector que indica la vertical en la vista
    ;

    int menuSelection = 0; ///< elegir entre plano "GL_FALT" o interpolado "GL_SMOOTH/Gouraud"

    typedef enum
    {
        M_PLANO, M_GOURAUD,
        M_TRANS_P1, M_TECLADO, M_RATON, M_CAMARA_MODO,
        M_ANIMAR_MODELO, M_ORBITAR_CAMARA,
        M_PROYECCION, M_PLANTA, M_REINICIAR_CAMARA,
        M_AYUDA, M_SALIR
    } OpcionesMenu;



    // Aplicación del patrón de diseño Singleton
    static igvInterfaz* _instancia; ///< Dirección de memoria del objeto único de la clase
    /// Constructor por defecto
    igvInterfaz();

public:
    // Aplicación del patrón de diseño Singleton
    static igvInterfaz& getInstancia();
    // Constructores por defecto y destructor

    /// Destructor
    ~igvInterfaz() = default;

    // Métodos estáticos
    // callbacks de eventos
    // callbacks de eventos
    static void specialFunc(int key, int x, int y);
    static void keyboardFunc(unsigned char key, int x, int y); // método para control de eventos del teclado
    static void reshapeFunc(int w, int h); // método que define la camara de vision y el viewport
    // se llama automáticamente cuando se cambia el tamaño de la ventana
    static void displayFunc(); // método para visualizar la escena
    static void mouseFunc(GLint boton, GLint estado, GLint x, GLint y);
    static void motionFunc(GLint x, GLint y);
    static void idleFunc(); //Callback para animacion continua

    void inicializarMenu();
    static void menuHandle(int valor);


    // Metodos
    // crea el mundo que se visualiza en la ventana
    void crear_mundo();

    // inicializa todos los parámetros para crear una ventana de visualización
    void configura_entorno(int argc, char** argv // parámetros del main
                           , int _ancho_ventana, int _alto_ventana // ancho y alto de la ventana de visualización
                           , int _pos_X, int _pos_Y // posición inicial de la ventana de visualización
                           , std::string _titulo // título de la ventana de visualización
    );
    void inicializa_callbacks(); // inicializa todos los callbacks

    void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

    // métodos get_ y set_ de acceso a los atributos
    int get_ancho_ventana();

    int get_alto_ventana();

    void set_ancho_ventana(int _ancho_ventana);

    void set_alto_ventana(int _alto_ventana);


};

#endif   // __IGVINTERFAZ
