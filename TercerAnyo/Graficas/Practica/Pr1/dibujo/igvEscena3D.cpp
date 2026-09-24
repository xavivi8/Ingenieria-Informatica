#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{  GLfloat rojo[] = { 1, 0, 0, 1.0 };
   GLfloat verde[] = { 0, 1, 0, 1.0 };
   GLfloat azul[] = { 0, 0, 1, 1.0 };

   glMaterialfv ( GL_FRONT, GL_EMISSION, rojo );
   glBegin ( GL_LINES );
   glVertex3f ( 1000, 0, 0 );
   glVertex3f ( -1000, 0, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, verde );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 1000, 0 );
   glVertex3f ( 0, -1000, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, azul );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 0, 1000 );
   glVertex3f ( 0, 0, -1000 );
   glEnd ();
}

/**
 * M�todo para pintar un tubo utilizando cu�dricas GLU
 */
void igvEscena3D::pintar_tubo()
{  GLUquadricObj *tubo;
   GLfloat color_tubo[] = { 0, 0, 0.5 };

   glMaterialfv ( GL_FRONT, GL_EMISSION, color_tubo );

   tubo = gluNewQuadric ();
   gluQuadricDrawStyle ( tubo, GLU_FILL );

   glPushMatrix ();
   glTranslatef ( 0, 0, -0.5 );
   gluCylinder ( tubo, 0.25, 0.25, 1, 20, 20 );
   glPopMatrix ();

   gluDeleteQuadric ( tubo );
}

// M�todos p�blicos

/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar(void)
{  // crear luces
   GLfloat luz0[] = { 10, 8, 9, 1 }; // luz puntual
   glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
   glEnable ( GL_LIGHT0 );

   // crear el modelo
   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   { pintar_ejes (); }

   // se pintan los objetos de la escena
   GLfloat color_cubo[] = { 0, 0.25, 0 };
   glMaterialfv ( GL_FRONT, GL_EMISSION, color_cubo );

/**
 * Medusa
 */
glPushMatrix ();

/* =====================================================
 * CUERPO / CAMPANA
 * ===================================================== */

// Campana principal: esfera achatada
glPushMatrix ();
    glScalef ( 1.5, 1.5, 0.7 );
    glutSolidSphere ( 1, 30, 30 );
glPopMatrix ();


// Borde de la campana
glPushMatrix ();
    glTranslatef ( 0, 0, -0.45 );
    glScalef ( 1.0, 1.0, 0.6 );
    glutSolidTorus ( 0.10, 1.10, 20, 30 );
glPopMatrix ();


// Parte central inferior
glPushMatrix ();
    glTranslatef ( 0, 0, -0.45 );
    glutSolidSphere ( 0.40, 20, 20 );
glPopMatrix ();


/* =====================================================
 * TENTÁCULO 1
 * ===================================================== */

glPushMatrix ();

    glTranslatef ( 0.65, 0, -0.55 );

    // Primer segmento
    glRotatef ( 15, 0, 1, 0 );

    GLUquadricObj *tentaculo1;
    tentaculo1 = gluNewQuadric ();
    gluQuadricDrawStyle ( tentaculo1, GLU_FILL );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo1, 0.10, 0.08, 0.7, 15, 15 );
    glPopMatrix ();

    // Nos desplazamos hasta la articulación
    glTranslatef ( 0, 0, -0.7 );

    glutSolidSphere ( 0.11, 15, 15 );

    // Segundo segmento
    glRotatef ( -25, 0, 1, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo1, 0.08, 0.06, 0.65, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.65 );

    glutSolidSphere ( 0.09, 15, 15 );

    // Tercer segmento
    glRotatef ( 30, 1, 0, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo1, 0.06, 0.025, 0.55, 15, 15 );
    glPopMatrix ();

    gluDeleteQuadric ( tentaculo1 );

glPopMatrix ();


/* =====================================================
 * TENTÁCULO 2
 * ===================================================== */

glPushMatrix ();

    glTranslatef ( -0.65, 0, -0.55 );
    glRotatef ( -15, 0, 1, 0 );

    GLUquadricObj *tentaculo2;
    tentaculo2 = gluNewQuadric ();
    gluQuadricDrawStyle ( tentaculo2, GLU_FILL );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo2, 0.10, 0.08, 0.7, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.7 );

    glutSolidSphere ( 0.11, 15, 15 );

    glRotatef ( 25, 0, 1, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo2, 0.08, 0.06, 0.65, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.65 );

    glutSolidSphere ( 0.09, 15, 15 );

    glRotatef ( -30, 1, 0, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo2, 0.06, 0.025, 0.55, 15, 15 );
    glPopMatrix ();

    gluDeleteQuadric ( tentaculo2 );

glPopMatrix ();


/* =====================================================
 * TENTÁCULO 3
 * ===================================================== */

glPushMatrix ();

    glTranslatef ( 0, 0.65, -0.55 );
    glRotatef ( 15, 1, 0, 0 );

    GLUquadricObj *tentaculo3;
    tentaculo3 = gluNewQuadric ();
    gluQuadricDrawStyle ( tentaculo3, GLU_FILL );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo3, 0.10, 0.08, 0.7, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.7 );

    glutSolidSphere ( 0.11, 15, 15 );

    glRotatef ( -25, 1, 0, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo3, 0.08, 0.06, 0.65, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.65 );

    glutSolidSphere ( 0.09, 15, 15 );

    glRotatef ( 30, 0, 1, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo3, 0.06, 0.025, 0.55, 15, 15 );
    glPopMatrix ();

    gluDeleteQuadric ( tentaculo3 );

glPopMatrix ();


/* =====================================================
 * TENTÁCULO 4
 * ===================================================== */

glPushMatrix ();

    glTranslatef ( 0, -0.65, -0.55 );
    glRotatef ( -15, 1, 0, 0 );

    GLUquadricObj *tentaculo4;
    tentaculo4 = gluNewQuadric ();
    gluQuadricDrawStyle ( tentaculo4, GLU_FILL );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo4, 0.10, 0.08, 0.7, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.7 );

    glutSolidSphere ( 0.11, 15, 15 );

    glRotatef ( 25, 1, 0, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo4, 0.08, 0.06, 0.65, 15, 15 );
    glPopMatrix ();

    glTranslatef ( 0, 0, -0.65 );

    glutSolidSphere ( 0.09, 15, 15 );

    glRotatef ( -30, 0, 1, 0 );

    glPushMatrix ();
        glRotatef ( 180, 1, 0, 0 );
        gluCylinder ( tentaculo4, 0.06, 0.025, 0.55, 15, 15 );
    glPopMatrix ();

    gluDeleteQuadric ( tentaculo4 );

glPopMatrix ();


/* =====================================================
 * 4 TENTÁCULOS PEQUEÑOS CENTRALES
 * ===================================================== */

GLUquadricObj *tentaculoCentral;
tentaculoCentral = gluNewQuadric ();
gluQuadricDrawStyle ( tentaculoCentral, GLU_FILL );

for ( int i = 0; i < 4; i++ )
{
    glPushMatrix ();

        glRotatef ( i * 90, 0, 0, 1 );
        glTranslatef ( 0.30, 0, -0.55 );

        glRotatef ( 180, 1, 0, 0 );

        gluCylinder (
            tentaculoCentral,
            0.07,
            0.025,
            1.1,
            15,
            15
        );

        glTranslatef ( 0, 0, 1.1 );

        glutSolidSphere ( 0.05, 10, 10 );

    glPopMatrix ();
}

gluDeleteQuadric ( tentaculoCentral );


glPopMatrix ();


   glPopMatrix (); // restaura la matriz de modelado
}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}