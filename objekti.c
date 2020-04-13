#include "objekti.h"


void draw_duck(){
	glShadeModel(GL_FLAT);
        /*telo*/
    glPushMatrix();
        glColor3f(1,1,0);
	glTranslatef(0.15,0.6,0);
        glutSolidSphere(0.4, 100,100);
    glPopMatrix();


	/*glava*/
     glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(0.1,1.17,0);
        glutSolidSphere(0.2, 100,100);
       glPopMatrix();

	

	/*oci*/

     /*levo*/
      glPushMatrix();
        glColor3f(0,0,0);
	glTranslatef(0.1,1.3,0.3);
        glutSolidSphere(0.02, 100,100);
       glPopMatrix();

	 /*desno*/
      glPushMatrix();
        glColor3f(0,0,0);
	glTranslatef(0.3,1.33,0.3);
        glutSolidSphere(0.02, 100,100);
       glPopMatrix();

	/*kljun*/
       glPushMatrix();
        glColor3f(1,0.5,0);
	glTranslatef(0.15,1.20,0.2);
        glutSolidCone(0.07,0.4,25,30);
       glPopMatrix();

	/*noge*/
        
     glPushMatrix();
	glDisable(GL_LIGHTING);
	 glColor3f(1,0.5,0);
         glScalef(0.4,1.5,0.3);
         glutSolidCube(0.25);
      glPopMatrix();

       glPushMatrix();
	 glColor3f(1,0.5,0);
	 glTranslatef(0.28,0,-0.05);
         glScalef(0.4,1.5,0.3);
         glutSolidCube(0.25);
      glPopMatrix();

	/*stopala*/	

     glPushMatrix();
	
	  glColor3f(1,0.5,0);
	  glTranslatef(0.28,-0.2,0.04);
          glScalef(1,0.1,1);
          glutSolidCube(0.25);
      glPopMatrix();

	glPushMatrix();
	  glColor3f(1,0.5,0);
	  glTranslatef(-0.02,-0.2,0.04);
          glScalef(1,0.1,1);
          glutSolidCube(0.25);
      glPopMatrix();
	

	
	glPushMatrix();
		
	  glColor3f(1,1,0);
           
	   glTranslatef(0.55,0.7,0);
		  
	  glRotatef(-30,0,0,1);
	glScalef(1.5,0.2,1.9);
          glutSolidCube(0.25);
 glPopMatrix();

	
      glPushMatrix();
		
	  glColor3f(1,1,0);
           
	   glTranslatef(-0.3,0.7,0);
	   glRotatef(30,0,0,1);
	   glScalef(1.5,0.2,1.9);
          glutSolidCube(0.25);
 glPopMatrix();
	 
     
    
	


}
