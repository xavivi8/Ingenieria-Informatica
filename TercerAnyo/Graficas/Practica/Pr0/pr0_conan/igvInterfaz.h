#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>

/**
 * Clase para encapsular la configuraci�n y la interfaz de la aplicaci�n
 */
class igvInterfaz
{  private:
		// Atributos
      int ancho_ventana = 0; ///< Ancho inicial de la ventana de visualizaci�n
      int alto_ventana = 0;  ///< Alto inicial de la ventana de visualizaci�n
	  bool ejes = true;
      // Aplicaci�n del patr�n Singleton
      static igvInterfaz* _instancia;   ///< Puntero al objeto �nico de la clase
      /// Constructor por defecto
      igvInterfaz() = default;

   public:
      // Aplicaci�n del patr�n Singleton
      static igvInterfaz& getInstancia ();

      /// Destructor
      ~igvInterfaz() = default;

		// Metodos est�ticos
		// callbacks de eventos
      static void keyboardFunc(unsigned char key, int x, int y); // m�todo para control de eventos del teclado
      static void reshapeFunc(int w, int h); // m�todo que define la camara de visi�n y el viewport
      // se llama autom�ticamente cuando se cambia el tama�o de la ventana
      static void displayFunc(); // m�todo para visualizar la escena


		// Metodos
		// inicializa todos los par�metros para crear una ventana de visualizaci�n
      void configura_entorno(int argc, char **argv // parametros del main
         , int _ancho_ventana, int _alto_ventana // ancho y alto de la ventana de visualizaci�n
         , int _pos_X, int _pos_Y // posicion inicial de la ventana de visualizaci�n
         , std::string _titulo // t�tulo de la ventan de visualizaci�n
      );
      void inicializa_callbacks(); // inicializa todos los callbacks

      void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

      // m�todos get_ y set_ de acceso a los atributos
      int get_ancho_ventana();
      int get_alto_ventana();
      bool get_ejes();
      void set_ancho_ventana(int _ancho_ventana);
      void set_alto_ventana(int _alto_ventana);
      void set_ejes(bool _ejes);
};

#endif   // __IGVINTERFAZ
