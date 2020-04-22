#include <GL/glut.h>
#include "objekti.h"






void draw_duck(){

               //materijal patke
  GLfloat ambient_duck[] = { 0.3, 0.3, 0.5, 1};
    GLfloat diffuse_duck[] = { 0.01, 0.01, 0.1, 1 };
    GLfloat specular_duck[] = { 0.01, 0.1, 0.3, 1 };
    GLfloat shininess_duck = 0.2;

    //postavljanje materijala patke
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_duck);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_duck);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_duck);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_duck);
  

     
    
     glShadeModel(GL_SMOOTH);
	
        /*telo*/
    glPushMatrix();
	
        glColor3f(1,1,0);
        glRotatef(5*animation_parameter,0,1, 0);
	glTranslatef(0,0.6,0);
        glutSolidSphere(0.4, 100,100);

 
       
     
          glColor3f(1,1,0); 
	  glRotatef(-10*sin(animation_parameter), 0, 1, 0);
          glRotatef(-30,0,0,1);
          glTranslatef(0.35,0.3,0);
	  glScalef(1.5,0.2,1.9);
          glutSolidCube(0.25);
  
          

          glColor3f(1,1,0);
	  glTranslatef(-0.55,-0.5,0);
	  glScalef(1.5,0.6,0.8);
          glutSolidCube(0.25);
    glPopMatrix();


	/*glava*/
     glPushMatrix();
        glRotatef(5*animation_parameter,0,1, 0);
        glColor3f(1,1,0);
   
        glTranslatef(0,1.15,0);
        glutSolidSphere(0.2, 100,100);
     

	

	/*oci*/

     /*levo*/
      
        glColor3f(0,0,0);
          
	  glTranslatef(-0.083,0.065,0.17);
        glutSolidSphere(0.02, 100,100);
       

	 /*desno*/
      
        glColor3f(0,0,0);
        
	  glTranslatef(0.14,-0.002,0.03);
        glutSolidSphere(0.02, 100,100);
      

	/*kljun*/
	
        glColor3f(1,0.5,0);
	 glTranslatef(-0.07,-0.065,-0.03);
        glutSolidCone(0.07,0.4,25,30);
               
        glPopMatrix();

	/*noge*/
        
	glPushMatrix();
	glDisable(GL_LIGHTING);
	 glColor3f(1,0.5,0);
         glRotatef(-20*sin(animation_parameter), 1, 0, 0);
	  glTranslatef(-0.10,0.05,0);
          glScalef(0.4,1.7,0.3);
         glutSolidCube(0.25);
        glPopMatrix();

       glPushMatrix();
	 glColor3f(1,0.5,0);
           glRotatef(-20*cos(animation_parameter), 1, 0, 0);
	  glTranslatef(0.11,0.04,-0.05);
          glScalef(0.4,1.7,0.3);
         glutSolidCube(0.25);
      glPopMatrix();

	/*stopala*/	

     glPushMatrix();
	
	  glColor3f(1,0.5,0);
         glRotatef(-10*sin(animation_parameter), 1, 0, 0);
	  glTranslatef(0.13,-0.14,0.04);
          glScalef(1,0.3,1);
          glutSolidCube(0.25);
      glPopMatrix();

	glPushMatrix();
          glRotatef(-10*sin(animation_parameter), 1, 0, 0);
	  glColor3f(1,0.5,0);
	  glTranslatef(-0.11,-0.13,0.04);
          glScalef(1,0.3,1);
          glutSolidCube(0.25);
      glPopMatrix();
	

	
     
     
	 
     
   
}
void drawP(){

        glPushMatrix(); 
		 
		glTranslatef(0, -1, 0);
		glColor3f(0.4,0.4,0.4);
		glScalef(6, 0, 5);
		glutSolidCube(1);
	glPopMatrix();

}

void drawS(){


  

	glPushMatrix(); 
                glColor3f(0.3,0.4,0.5);
 		   
		glTranslatef(0, 0.5, 0);
		
		glScalef(4.5, 0.08, 1.2);
		glutSolidCube(1);
	glPopMatrix();



}

/* iscrtavanje tezge*/
void drawT(){


	glPushMatrix(); 
                
                glColor3f(0.3,0.1,0.5);
 		 
		glTranslatef(0, -0.5, 0);
		
		glScalef(5.8, 0.9, 2);
		glutSolidCube(1);
	glPopMatrix();

}
