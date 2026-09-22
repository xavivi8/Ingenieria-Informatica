#include <cstdlib>

#include "igvInterfaz.h"

// Aplicaci�n del patr�n Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * dise�o Singleton
 * @return Una referencia al objeto �nico de la clase
 */
igvInterfaz& igvInterfaz::getInstancia ()
{  if ( !_instancia )
   {  _instancia = new igvInterfaz;
   }

   return *_instancia;
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
void igvInterfaz::configura_entorno ( int argc, char** argv
   , int _ancho_ventana, int _alto_ventana
   , int _pos_X, int _pos_Y
   , std::string _titulo )
{  // inicializaci�n de los atributos de la interfaz
   ancho_ventana = _ancho_ventana;
   alto_ventana = _alto_ventana;

   // inicializaci�n de la ventana de visualizaci�n
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(_ancho_ventana,_alto_ventana);
   glutInitWindowPosition(_pos_X,_pos_Y);
   glutCreateWindow(_titulo.c_str());

   glEnable(GL_DEPTH_TEST); // activa el ocultamiento de caras por Z-buffer
   glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana
}

/**
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion()
{  glutMainLoop(); // inicia el bucle de visualizaci�n de GLUT
}

/**
 * M�todo para control de eventos del teclado
 * @param key C�digo de la tecla pulsada
 * @param x Coordenada X de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post El atributo que indica si se tienen que pintar los ejes o no puede
 *       cambiar
 */
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y)
{  switch (key)
   {  case 27: // tecla de escape para SALIR
         exit(1);
         break;
   case 'e':
      _instancia->set_ejes(!_instancia->get_ejes());
      break;
   }
   glutPostRedisplay(); // renueva el contenido de la ventana de visi�n
}

/**
 * M�todo que define la c�mara de visi�n y el viewport. Se llama autom�ticamente
 * cuando se cambia el tama�o de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 */
void igvInterfaz::reshapeFunc(int w, int h)
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
   glViewport(0,0,(GLsizei) w,(GLsizei) h);

   // guardamos valores nuevos de la ventana de visualizaci�n
   _instancia->set_ancho_ventana ( w );
   _instancia->set_alto_ventana ( h );

   // establece el tipo de proyecci�n a utilizar
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-1,1,-1,1,-1,200);

   // se define la camara de vision
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/**
 * M�todo para visualizar la escena
 */
void igvInterfaz::displayFunc()
{  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el Z-buffer
   glPushMatrix(); // guarda la matriz de modelado

   // TODO: Apartado A: pintar los ejes
   if (_instancia->get_ejes()) {
      glBegin(GL_LINES);
         glColor3f(0,0,1);
         glVertex3f(0,0,0);
         glVertex3f(0,0,100);

         glColor3f(0,1,0);
         glVertex3f(0,0,0);
         glVertex3f(0,100,0);

         glColor3f(1,0,0);
         glVertex3f(0,0,0);
         glVertex3f(100,0,0);
      glEnd();
   }
   // TODO: Apartado B: visualizar primitiva cubo en modo alambre
   glColor3f(1,0,1);
   glutWireCube(1.0);
   // TODO: Apartado C: cara superior con tri�ngulos
   glBegin(GL_TRIANGLES);
      glColor3f(0,1,0);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(-0.5,0.5,0.5);
      glVertex3f(0,0.5,0);

      glColor3f(1,0,0);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(0,0.5,0);

      glColor3f(0,0,1);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(0,0.5,0);

      glColor3f(1,1,0);
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(-0.5,0.5,0.5);
      glVertex3f(0,0.5,0);
   glEnd();

  glPopMatrix (); // restaura la matriz de modelado
  glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

/**
 * M�todo para inicializar los callbacks
 */
void igvInterfaz::inicializa_callbacks()
{  glutKeyboardFunc(keyboardFunc);
   glutReshapeFunc(reshapeFunc);
   glutDisplayFunc(displayFunc);
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

bool igvInterfaz::get_ejes() {
   return ejes;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}

void igvInterfaz::set_ejes ( bool _ejes ) {
   ejes = _ejes;
}
