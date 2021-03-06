#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include<string.h>
#include <math.h>
#include "objekti.h"
#include "image.h"


#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define PI 3.1415926535

#define FILENAME0 "Teksture/plocice.bmp"
#define FILENAME1 "Teksture/pozadina4.bmp"
#define FILENAME2 "Teksture/start.bmp"
#define FILENAME3 "Teksture/end.bmp"
/*niz u kome su smestene teksture*/
GLuint textures[4];

/* struktura za metak*/

typedef struct Metak{
  double x,y,z;
  double dx,dy,dz;
  bool exists;
} Metak;

/*struktura za pilice*/
typedef struct Pilici{
  double x;
  double y;
  double z;
  bool alive;

} P;
/*promenljiva kojom odredjujem proj pilica koje mogu pogoditi sa vrednoscu X*/
int br=10;
/*Niz pilica*/
P pilici[33];
/*Niz metaka*/
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


int window_width,window_height;
/*promenljiva za izracunavanje skora*/
int score=0;

/* Deklaracija callback funkcija*/
static void on_display();
static void on_timer(int id);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void inicijalizacijaTekstura(void);
static void draw_start_screen();
static void draw_end_screen();


/*funkcija u kojoj radim proveru kolizije, tacnije proveravam udaljenost loptice i samog pileta, ovde  proveravam da li je metak dovoljno blizu pilite da bi ono nestalo
, u formiranju ove funkcije posluzila sam se i nekim matematickim formulama*/

bool proveri_koliziju(P *pilici,Metak *metak){
	double x= fmax(pilici->x-0.2,fmin(metak->x,pilici->x+0.2));
        double y= fmax(pilici->y,fmin(metak->y,pilici->y+0.6));
	double z= fmax(pilici->z-0.2,fmin(metak->z,pilici->z+0.2));
	
	double distance = (x-metak->x) *(x-metak->x)+
			   (y-metak->y) *(y-metak->y)+
			   (z-metak->z) *(z-metak->z);
			   
	return distance <0.05*0.05;
}

int main(int argc, char **argv){

    /* inicijalizacija */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("moving-target");
    glutFullScreen();
     
    /*teksture koje se koriste*/
    inicijalizacijaTekstura();
 
    /*pozivanje callback funkcija*/
    glutDisplayFunc(draw_start_screen);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

	
    /* obavlja se OpenGL inicijalizacija */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.4, 0.5, 0.6, 0);

       
    glShadeModel(GL_SMOOTH);
       


  /* prilagodjavanje svetlosti i postavljanje parametara , uzeto sa casa i podesavano prema potrebama*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
    GLfloat shininess = 20; 

    /*pozicija svetla, difuzno,ambijentalno i spekularno*/
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
   
    /*inicijalizacija svakog pileta iz niza pilici, kako bih bih znala koje bile se gde nalazi, i proverom da li kolizija vazi ustanovila da li pile treba da nestane*/ 
   
   for(int i =0;i<3;i++){
   	for(int j =0;j<11;j++){
   	  pilici[i*11 +j ].x= -2 + 0.4*j;
   	  pilici[i*11 +j ].y= 0.6 + 0.7*i;
   	  pilici[i*11 +j ].z= 0;
   	  pilici[i*11 +j ].alive= true;
   	}
   
   }   
   

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


/*funkcija za radijane, jee mi je bila potrebna pri racunanju nekih uglova*/
double to_radians(double angle){
	return angle * PI /180.0;	

}


void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        /*
              Omoguceno  pokretanje, zaustavljanje i restartovanje animacije 
         */
         
         /*pokretanje animacije*/
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                glutDisplayFunc(on_display);
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
         /*zaustavljanje animacije*/
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
            score=0;
            
            glutPostRedisplay();
            break;
          /*kretanje puske nadesno*/
        case 'd':
        case 'D':
            turnLeft=0;
	    turnRight=1;
            break;
	/*kretanje puske nalevo*/	
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
      /*kretanje puske na dole*/
        case 's':
        case 'S':
            turnUp = 0;
            turnDown = 1;
            break; 
       /*dugme za upucavanje puske*/  
         case 'p':
         case 'P':
     		
     			for(int i = 0; i < 20; i++) {
      				if(!metak[i].exists){
      
      					double speed =0.5;
     
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
     	       /*povecavamo koordinat emetka , kretanje metka*/
      		if(metak[i].exists){
      			metak[i].x +=  metak[i].dx;
      			metak[i].y +=  metak[i].dy;
      			metak[i].z +=  metak[i].dz;
    
        /*ogranicenje kretanja metaka, stavljanje u odredjeni opseg*/			  			
        if(fabs(metak[i].x)>4.4 ||  fabs(metak[i].y)>4.4 || fabs(metak[i].z)>5)
             metak[i].exists=false;
            }
        
      
          
       }  
        /*kretanje kroz niz patki i proveravanje da li patka postoji, ako je nacrtana i ako vazi kolizija tj. da mi je metak dovoljno blizu patke sklanjam je, promenom na true,cime dobijamo da vise nece biti iscrtavana*/ 
       
       for(int i = 0; i < 20; i++){
       	if(fabs(metak[i].z) > 0.2+ 0.05)
       		continue;
       	for(int j =0;j< 33;j++){
       		if(pilici[j].alive && proveri_koliziju(&pilici[j],&metak[i])){
       			pilici[j].alive = false;
       			
       			if(j%2==0){
       			/*uvecavanje skora za odredjene pilice koje pogodimo, odredjenim indeksom*/
       		       if(j==32){
       			 score =0;
       			}
       			else{
       			score= score +50;
       			}
       			}
       			/*u suprotnom umanjivanje*/
       		
       			else{
       			 br--;
       			 score -=5;
       			}
       			metak[i].exists=false;
       		}
       	
       	}
       	/*izlazak iz programa i prikaz krajnjeg ekrana*/
       	if(br ==0){
       		
			glutDisplayFunc(draw_end_screen);
       		
       	}
       }

     }  
   
    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
}

void on_reshape(int width, int height) {
    
    window_width =width;
    window_height =height;
    glViewport(0, 0, width, height);

	/*podesavanje projekcije*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 20);
}

void on_display() {
    
	/*brisanje predhonog sadrzaja prozora*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*podesavanje tacke pogleda*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_TEXTURE_2D);	
   /*podesavanje kamere*/
    gluLookAt(
            0, 1, 9,
            0, 0.7, 0,
            0, 3, 0
        );
        
  /*Ispisisvanje skora na ekaranu*/
   
   glPushMatrix();
   glDisable(GL_LIGHTING);
   char score_str[50];
	 glColor3f(0,1,0);
   glRasterPos2f(-2.4,3);
   sprintf(score_str, "Score: %d", score);
   int length = strlen(score_str);
    
   for (int i = 0; i < length; i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score_str[i]);
     }
   
   glEnable(GL_LIGHTING);
   glPopMatrix();
      
      
   glPushMatrix();
   glDisable(GL_LIGHTING);
   char score_x[50];
	 glColor3f(1,0,0);
   glRasterPos2f(-2.4,2.7);
   sprintf(score_x, "Broj pogodjenih x: %d", br);
   int length1 = strlen(score_x);
   for (int i = 0; i < length1; i++) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score_x[i]);
    }
   
  glEnable(GL_LIGHTING);
  glPopMatrix();
     
   /*Postavljanje koordinata pozadine, teksture pozdine*/
  
       glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBegin(GL_QUADS);
        
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, 0);
            glVertex3f(-6, -4,- 3);

            glTexCoord2f(1, 0);
            glVertex3f(6, -4, -3);

            glTexCoord2f(1, 1);
            glVertex3f(6, 4, -3);

            glTexCoord2f(0, 1);
            glVertex3f(-6, 4, -3);
   
        glEnd();
            
      glBindTexture(GL_TEXTURE_2D, 0);
   
   /*Postavljanje koordinata poda*/
     glBindTexture(GL_TEXTURE_2D, textures[0]);

        glBegin(GL_QUADS);

       glNormal3f(0, 1, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(-3,-1, -2.5);
        
        glTexCoord2f(0, 1);
        glVertex3f(-3,-1, +2.5);
        
        glTexCoord2f(1, 1);
        glVertex3f(+3,-1, +2.5);
        
        glTexCoord2f(1, 0);
        glVertex3f(+3,-1, -2.5);
     glEnd();

     
      glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
 
   /*Iscrtavanje veceg boroja pilica pozivanjem funkcija, iscrtavanje i ostalih objekata, pod, tezga police*/
 
 
   glPushMatrix();
  
    
    for(int i = 0 ; i < 32 ; i++)
     {
       glTranslatef(pilici[i].x,pilici[i].y,pilici[i].z);
       /*ovim proveravam da li ima potrebe da se pile  iscrta, ili je pogodjeno i nestalo*/
    
        if(pilici[i].alive)
        	draw_duck();
       glTranslatef(-pilici[i].x,-pilici[i].y,-pilici[i].z);
       
    }
    glTranslatef(2,2,0);
    if(pilici[32].alive)
    draw_duck_ugly();
    
    
    
   glPopMatrix();
  /*pozivanje funkcije za iscrtavanje poda*/
    drawP();

    //draw_axes(50);
  /*poziv funkcije za icrtavanje puske*/
    glPushMatrix();
    	glEnable(GL_LIGHTING);
      glTranslatef(0, 0.4,6.5);
    	glRotatef(horizontal_parameter,0,-1,0);
      glRotatef(vertical_parameter,1,0,0);
         puska();
    glPopMatrix();
    
    /*iscrtavanje loptica koje predstavljaju metak*/
     for(int i = 0; i < 20; i++) {
      if(metak[i].exists) {
        glPushMatrix();
          glTranslatef(metak[i].x, metak[i].y, metak[i].z);
          drawBall();
        glPopMatrix();
      }
    }
  
   /*iscrtavanje polica i tezge*/
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
    /*iskljucujem osvetljenje*/
   glDisable(GL_LIGHTING);
   glutSwapBuffers();
}

static void inicijalizacijaTekstura(void){
    /*funkcija sa sedmog casa vezbi koja koristi biblioteku image.c,uzeto i odradjeno za potrebe pozadine, poda ,krajnjeg i pocetnog ekrana*/

    Image * image;
    glEnable(GL_DEPTH_TEST);

    /*ukljucivanje odredjenih flegova za prilepljivanje tekstura tekstura*/
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    /*inicijalizacija*/
    image = image_init(0, 0);
    glGenTextures(5, textures);
    
    
    /*Tekstura poda*/
   image_read(image, FILENAME0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    /*Tekstura pozadine*/
    image_read(image, FILENAME1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
                 
                 
                 
       /*Tekstura pocetka igre(start game)*/
    image_read(image, FILENAME2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	/*Tekstura zavresetka igre(end game)*/
    image_read(image, FILENAME3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


    /*Iskljucujemo aktivnu teksturu*/
    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}


/*Funkcija za postavljanje teksture za zavrsetak igre
//Moralo je da se izvrse odredjene promene  postavljanje u orogonu projekciju i jos neka prilagodjavanja*/
static void draw_end_screen(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);

    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
  
		gluOrtho2D(0, window_width,0, window_height);
		
		glMatrixMode(GL_MODELVIEW);
  		glLoadIdentity();

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0,0);

			glTexCoord2f(0, 1);
			glVertex2f(0, window_height);

			glTexCoord2f(1, 1);
			glVertex2f(window_width,window_height);

			glTexCoord2f(1, 0);
			glVertex2f(window_width,0);
		glEnd();
		
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();

}
/*Funkcija za postavljanje teksture za pocetak igre*/
static void draw_start_screen(){
                                                                                                                                         
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);

  glMatrixMode(GL_PROJECTION);
	glPushMatrix();
  glLoadIdentity();
  
		gluOrtho2D(0, window_width,0, window_height);
		
		glMatrixMode(GL_MODELVIEW);
  		glLoadIdentity();

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0,0);

			glTexCoord2f(0, 1);
			glVertex2f(0, window_height);

			glTexCoord2f(1, 1);
			glVertex2f(window_width,window_height);

			glTexCoord2f(1, 0);
			glVertex2f(window_width,0);
		glEnd();
		
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_TEXTURE_2D);

   glutSwapBuffers();

}


