#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "objekti.h"



/* Deklaracija callback funkcija*/
static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);




int main(int argc, char **argv){



	/* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    /* Ambijentalno osvetljenje scene. */
    GLfloat model_ambient[] = { 0.3, 0.3, 0.3, 1 };
   
    /* inicijalizacija */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("moving-target");


 
    /*pozivanje callback funkcija*/
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

	
    /* obavlja se OpenGL inicijalizacija */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.4, 0.5, 0.6, 0);
       glEnable (GL_LINE_SMOOTH);

	    /*Ukljucivanje svetla, i osvetljavanje scene*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);



   /* ulazak u petlju*/
    glutMainLoop();

    return 0;
}

/*funkcija za iscrtavanje koordinatnog sistema*/
void draw_axes(float len) {
   
     glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();

	glEnable(GL_LIGHTING);

    
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
          exit(0);
          break;
    }
}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);

	/*podesavanje projekcije*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 3, 60);
}




void on_display() {
    

    GLfloat light_position[] = { 0, 1, 1, 0};

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    GLfloat light_diffuse[] = { 0.8,0.8,0.8};

    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 0 };

    GLfloat ambient_coeffs[] = { 0, 0.9, 0.9, 1 };

    GLfloat diffuse_coeffs[] = { 0.0, 0.2, 0.8, 1 };

    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    GLfloat shininess = 20;

	/*brisanje predhodnog sadrzaja prozora*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*podesavanje tacke pogleda*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
     gluLookAt(
            10/5, 20/5, 30/5,
            0, 0, 0,
            0, 1, 0
        );

glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess); 

    glShadeModel(GL_SMOOTH);



    //draw_axes(4);
     
    draw_duck();
    glLineWidth(2);
   
  
    glutFullScreen();
    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}


