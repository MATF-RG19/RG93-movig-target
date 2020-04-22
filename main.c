#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "objekti.h"


#define TIMER_INTERVAL 20
#define TIMER_ID 0

static void on_timer(int id);
 animation_parameter = 0;
 animation_ongoing = 0;


/* Deklaracija callback funkcija*/
static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);



int main(int argc, char **argv){



	
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


       
    glShadeModel(GL_SMOOTH);
        //animation_parameter=0;






  /* prilagodjavanje svetlosti i postavljanje parametara , uzeto sa casa i podesavano prema potrebama*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
    GLfloat shininess = 20; 


     GLfloat pozicija_svetla[] = { 5, 6, 12, 1 };
    GLfloat ambijent_svetla[] = { 0.1, 0, 0, 1 };
    GLfloat difuznost_svetla[] = { 0.5,0.25,0.1, 1 };
    GLfloat spekularnost_svetla[] = { 1, 1, 1, 1 };




    // postavlja se svetlo
    glLightfv(GL_LIGHT0, GL_POSITION, pozicija_svetla);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambijent_svetla);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuznost_svetla);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spekularnost_svetla);


  
   glMaterialf(GL_FRONT, GL_SHININESS, shininess);  



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
        /*
         *      Omoguceno  pokretanje, zaustavljanje i restartovanje animacije 
         
         */
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        case 's':
        case 'S':
            animation_ongoing = 0;
            break;
        case 'r':
        case 'R':
            animation_parameter = 0;
            glutPostRedisplay();
            break;
        
        case 27:
          exit(0);
          break;
    }
}


void on_timer(int id) {
    if (id == TIMER_ID) {
       

        animation_parameter += 1;

       
    }

    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);

	/*podesavanje projekcije*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 50);
}




void on_display() {
    

   
    

	/*brisanje predhodnog sadrzaja prozora*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*podesavanje tacke pogleda*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
     gluLookAt(
            0, 1, 9,
            0, 0.7, 0,
            0, 3, 0
        );



    //draw_axes(4);
  
 
   /*Iscrtavanje veceg boroja pilica pozivanjem funkcija, iscrtavanje i ostalih objekata, pod, tezga police*/
    glPushMatrix();
     glShadeModel(GL_SMOOTH);
     
      glEnable(GL_LIGHTING);
      glTranslatef(0,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
    
     
     glPushMatrix();
       glShadeModel(GL_SMOOTH);
     glEnable(GL_LIGHTING);
    glTranslatef(0.4,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
     
      glPushMatrix();
        glShadeModel(GL_SMOOTH);
       glEnable(GL_LIGHTING);
    glTranslatef(0.8,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
  
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glTranslatef(-0.4,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();

    glPushMatrix();
    glEnable(GL_LIGHTING);
    glTranslatef(-0.8,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();


    glPushMatrix();
    glEnable(GL_LIGHTING);
    glTranslatef(-1.6,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();

      glPushMatrix();
     
    glEnable(GL_LIGHTING);
    glTranslatef(1.6,0.6,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
    
  
     glPushMatrix();
     
     glEnable(GL_LIGHTING);
     glTranslatef(0,1.3,0);
    glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
   

   
   

  glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(0.4,1.3,0);
    glScalef(0.3,0.3,0.3);
   glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();

   glPushMatrix();
     glEnable(GL_LIGHTING);
     glTranslatef(-0.4,1.3,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

   glPushMatrix();
      glEnable(GL_LIGHTING);
     glTranslatef(-0.8,1.3,0);
     glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

    glPushMatrix();
      glEnable(GL_LIGHTING);
     glTranslatef(-1.6,1.3,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();
  
    glPushMatrix();
      glEnable(GL_LIGHTING);
     glTranslatef(1.6,1.3,0);
     glScalef(0.3,0.3,0.3);
      glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

   glPushMatrix();
      glEnable(GL_LIGHTING);
     glTranslatef(+0.8,1.3,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


  
   

   glPushMatrix();
     glEnable(GL_LIGHTING);
     glTranslatef(0,2,0);
    glScalef(0.3,0.3,0.3);
    glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();
   

  glPushMatrix();
      glEnable(GL_LIGHTING);
     glTranslatef(0.4,2,0);
    glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
    draw_duck();
     glPopMatrix();

   glPushMatrix();
     glEnable(GL_LIGHTING);
     glTranslatef(-0.4,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

   glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(-0.8,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

   
   glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(-1.6,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(1.6,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();

   glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(+0.8,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


     glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(1.2,2,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();
  
   glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(1.2,1.3,0);
     glScalef(0.3,0.3,0.3);
      glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


  glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(1.2,0.6,0);
     glScalef(0.3,0.3,0.3);
       glRotatef(5*cos(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


     glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(-1.2,0.6,0);
     glScalef(0.3,0.3,0.3);
       glRotatef(5*sin(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(-1.2,1.3,0);
     glScalef(0.3,0.3,0.3);
     glRotatef(5*sin(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_LIGHTING);
     glTranslatef(-1.2,2,0);
     glScalef(0.3,0.3,0.3);
       glRotatef(5*sin(animation_parameter), 1, 0, 0);
     draw_duck();
    glPopMatrix();
    
    

    drawP();
   glPushMatrix();
    glEnable(GL_LIGHTING);
    drawS();
   glPopMatrix();
    glPushMatrix();
           glEnable(GL_LIGHTING);
        glTranslatef(0, 0.69, 0);
        drawS();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 1.35, 0);
        drawS();
    glPopMatrix();

      glPushMatrix();
          glEnable(GL_LIGHTING);
          drawT();
      glPopMatrix();
     glDisable(GL_LIGHTING);

    glutFullScreen();
   
    glutSwapBuffers();
}


