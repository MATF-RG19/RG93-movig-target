#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "objekti.h"


#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define PI 3.1415926535




/* struktura za metak*/

typedef struct Metak{
  double x,y,z;
  double dx,dy,dz;
  bool exists;
} Metak;


Metak metak[20];

/* Promenljive */

int animation_parameter = 0;
int animation_ongoing = 0;
int horizontal_parameter = 0;
int vertical_parameter = 0;
int turnRight = 0;
int turnLeft = 0;
int turnUp = 0;
int turnDown = 0;
int shoot=0;
int shootp=0;



/* Deklaracija callback funkcija*/
static void on_display();
static void on_timer(int id);
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


/*funkcija za radijane*/
double to_radians(double angle){
	return angle * PI /180.0;	

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
        case 'h':
        case 'H':
            animation_ongoing = 0;
            break;
            
           /*dugme za podesavanje kretanja puske*/
        case 'r':
        case 'R':
            animation_parameter = 0;
            horizontal_parameter = 0;
            turnLeft = 0;
            turnRight = 0;
            glutPostRedisplay();
            break;
          case 'd':
          case 'D':
                turnLeft=0;
		 turnRight=1;
		 break;
		
	  case 'a':
         			case 'A':
                turnLeft=1;
		            turnRight=0;
		            break;
          case 'w':
          case 'W':
            turnUp = 1;
            turnDown = 0;
            break;
          case 's':
          case 'S':
            turnUp = 0;
            turnDown = 1;
            break;  
          case 'p':
          case 'P':
     			
     			for(int i = 0; i < 20; i++) {
      				if(!metak[i].exists){
      
      					double speed =0.3;
     
      /* racunamo brzinu metka po osama  pomocu sfernih koordinata  */
      					metak[i].dy=speed * sin(to_radians(vertical_parameter));
      					metak[i].dx=speed*cos(to_radians(vertical_parameter))*sin(to_radians(horizontal_parameter));
      					metak[i].dz=speed*cos(to_radians(vertical_parameter))*cos(to_radians(horizontal_parameter))*(-1);
      
      
      /*postavljamo pocetnu poziciju metka na vrh puske
      njega racunamo tako sto na poziciju centra puske  dodamo
      vec izracunate pomeraje po osama pomnozimo duzinom puske(trenutno 1.5)*/
      					metak[i].x=0+1.5*metak[i].dx/speed;
      					metak[i].y=0.4+1.5*metak[i].dy/speed;
      					metak[i].z=6.5+1.5*metak[i].dz/speed;
      			
      				    metak[i].exists = true;
             			break;
            
            }
        }   
           break;      
        case 27:
          exit(0);
          break;
    }
}


void on_timer(int id) {
    if (id == TIMER_ID) {
       

        animation_parameter += 1;
		/*promena parametara za animaciju puske po vertikali i horizontali*/
        if(turnRight && horizontal_parameter < 16.15)
		      horizontal_parameter += 2;
        if(turnLeft && horizontal_parameter > -16.15)
		      horizontal_parameter -= 2;

        if(turnUp && vertical_parameter < 14.5)
          vertical_parameter += 1;
        if(turnDown && vertical_parameter > 4)
          vertical_parameter -= 1;
        /*podesavanje parametara za animaciju metka, ispucavanje metka*/  
     	for(int i = 0; i < 20; i++) {
      		if(metak[i].exists){
      			metak[i].x +=  metak[i].dx;
      			metak[i].y +=  metak[i].dy;
      			metak[i].z +=  metak[i].dz;
        if(fabs(metak[i].x)>15 ||  fabs(metak[i].y)>15 || fabs(metak[i].z)>20)
             metak[i].exists=false;
            }
        } 
          
          

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

   
  
  
   /*Iscrtavanje veceg boroja pilica pozivanjem funkcija, iscrtavanje i ostalih objekata, pod, tezga police*/
 
   glPushMatrix();
    glTranslatef(-2,0.6,0);
    draw_duck();
    for(int i = 0 ; i < 10 ; i++)
      {
        glTranslatef(0.4,0,0);
        draw_duck();
      }
   glPopMatrix();


   glPushMatrix();
    glTranslatef(-2,1.3,0);
    draw_duck();
    for(int i = 0 ; i < 10 ; i++)
      {
        glTranslatef(0.4,0,0);
        draw_duck();
      }
   glPopMatrix();

   glPushMatrix();
    glTranslatef(-2,2,0);
    draw_duck();
    for(int i = 0 ; i < 10 ; i++)
      {
        glTranslatef(0.4,0,0);
        draw_duck();
      }
   glPopMatrix();



    drawP();


    //draw_axes(50);
    
   
  
    glPushMatrix();
    	glEnable(GL_LIGHTING);
      glTranslatef(0, 0.4,6.5);
    	glRotatef(horizontal_parameter,0,-1,0);
      glRotatef(vertical_parameter,1,0,0);
         puska();
         
    glPopMatrix();
    
    
     for(int i = 0; i < 20; i++) {
      if(metak[i].exists) {
        glPushMatrix();
          glTranslatef(metak[i].x, metak[i].y, metak[i].z);
          drawBall();
        glPopMatrix();
      }
    }
  
  
  
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


