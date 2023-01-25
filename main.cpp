#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"



using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
double gammaa,gammaaa,gammaaaa,skyrotate = 0;
double sun=0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,thetaa=0.0;
GLfloat eye_x = 0.0, eye_y = 10.0, eye_z = 150.0;
GLfloat lookat_x = 0.0, lookat_y = 5.0, lookat_z = 0.0;
GLdouble up_x = 0.0;
GLdouble up_y = 1.0;
GLdouble up_z = 0.0;
GLdouble sx=1.0,sy=1.0,sz=1.0;
GLdouble tx,ty,tz=0;
GLdouble wally=7,wallz=0.1;
GLdouble nicher_wally=5.7,nicher_wallz=0.2;
GLdouble ttx,tty,ttz=0;
GLdouble ssx,ssy,ssz=0;
GLdouble dx=0,dz=4.8,bathz=10.1;
GLdouble cardx=-9.6,cardz=-14.8,cashz=-13.6;
GLdouble maindoorl=0.1,maindoorr=-3.6,vaultdoor=-4.1;
GLdouble wdrop = -7.9,waterx=0.0,watery=0.0,waterz=0.0;
GLdouble sdoor = 0.1;

int leftoff,topoff,bottomoff,rightoff=0;
int cardin=0;
int cardout=1;
int n=36;
GLint pass;
GLint password=123;
GLint countt=0,wcountt=0,carcountt=0;

GLboolean sc = false;

double anglePitch=0,angleYaw=90,angleRoll = 0;
GLboolean bRotate = false,skyRotate=true,wall=true, uRotate = false,ventirotate=false,waterDrop=false,sDoor=false, carRotate=false, light0 = false,light1=false,light2=false,light3=false,light4=false,light5=false,light6=false,light7=false,zRotate = false,dooropen=false,bathdoor=false,maindoor=false,vaultDoor=false,fanRotate=false;
int pilotPitch=0,pilotYaw=0,pilotRoll=0;
unsigned int ID,ID1;



//static GLfloat v_box[8][3] =
//{
//    {-2.0, 0.0, 0.0},
//    {2.0, 0.0, 0.0},
//    {-2.0, 0.0, 2.0},
//    {2.0, 0.0, 2.0},
//
//    {-2.0, 2.0, 0.0},
//    {2.0, 2.0, 0.0},
//    {-2.0, 2.0, 2.0},
//    {2.0, 2.0, 2.0}
//};
//
//static GLubyte quadIndices[6][4] =
//{
//    {0,2,3,1},
//    {0,2,6,4},
//    {2,3,7,6},
//    {1,3,7,5},
//    {1,5,4,0},
//    {6,7,5,4}
//};

static GLfloat v_pyramid[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},


};

static GLfloat v_pyramid1[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {0.6, 1.0, 1.0},
    {-0.6, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {0.6, 1.0, -1.0},
    {-0.6,1.0, -1.0},


};


static GLubyte quadIndices[6][4] =
{
    //{4,5,6,7},
    {0,1,2,3},
    {7,6,5,4},
    {2,6,7,3},

    {0,4,5,1},
    {2,1,5,6},
    {7,4,0,3},
};


static GLfloat colors[8][3] =
{
    //polygon colors
    {1.0, 1.0, 1.0},
    {0.5, 0.5, 0.5},
    //quad er shuru ekhan theke
    {0.8,0.5,0.3}, //right surface
    {0.8,0.5,0.5}, //shamner tol
    {0.6,0.4,0.2}, //left surface
    {0.6,0.4,0.2}, //pisertol
    {0.8,0.5,0.3}, //upper surface
    {1.0, 0.5, 0.0} //bottom surface
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawcube(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    for (GLint i = 0; i <6; i++)
    {

        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();

    }
}

void slcube(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    for (GLint i = 0; i <6; i++)
    {

        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid1[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid1[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid1[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid1[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();

    }
}


void triangularPrism(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glBegin(GL_QUADS);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0, 0.5);

    glVertex3f(0.5,0,-0.5);
    glVertex3f(0.5,1,-0.5);
    glVertex3f(-0.5,1,-0.5);
    glVertex3f(-0.5,0,-0.5);

    glVertex3f(0.5,1,-0.5);
    glVertex3f(-0.5,1,-0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(0.5,0,0.5);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,1,-0.5);
    glVertex3f(0.5,0,-0.5);

    glVertex3f(-0.5,0,0.5);
    glVertex3f(-0.5,1,-0.5);
    glVertex3f(-0.5,0,-0.5);
    glEnd();
}




void teapot(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glTexCoord2f(1,1);
    glutSolidTeapot(1.4);

}

void knob(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glutSolidCube(2);

}

void ceiling_light_holder(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix();
    glTranslatef(12,12,8);
    glRotatef(-90,1,0,0);
    glutSolidCone(2.0,3.0,16,20);
    glPopMatrix();
}

void ceiling_light(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(12,12,8);
    glutSolidSphere(1.0,16,20);
    glPopMatrix();
}

void venti_fan(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(0.3,1.3,0.2);
    slcube(1,1,1);
    glPopMatrix();
}


void chair()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3,1.6,-7);
    glScalef(1.2,0.1,1.2);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);

    //chair shamner left leg
    glTranslatef(-0.8,-6,0.8);
    glScalef(0.15,6.5,0.1);
    drawcube(0,0,0);

    //shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    //piser right leg
    glTranslatef(0,0,-16.8);
    drawcube(0,0,0);

    //piser left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8,2.5,-7);
    glScalef(0.15,1, 1.2);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void disk(GLfloat r,
          GLfloat g,
          GLfloat b,
          GLboolean emission = false )
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluDisk(qobj,0,2,20,10);
}

void cyl(GLfloat r,
         GLfloat g,
         GLfloat b,
         GLboolean emission = false )
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluCylinder(qobj,1.5,1.5,2,16,16);
}


void torus(GLfloat r,
           GLfloat g,
           GLfloat b,
           GLboolean emission = false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);
    glutSolidTorus(1.2,2,16,16);
}

void rim(GLfloat r,
         GLfloat g,
         GLfloat b,
         GLboolean emission = false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(1,20,20);

}




void atm()
{
    //atm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.2, -11.4, -14.85);
    glScalef(2.3,1.5,1.7);
    glBindTexture(GL_TEXTURE_2D,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.2, -8.2,-15.9);
    glScalef(2.3,1.7,0.6);
    glBindTexture(GL_TEXTURE_2D,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //atm shade
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.2, -6.1,-14.6);
    glRotatef(-25,1,0,0);
    glScalef(2.3,0.5,1.8);
    glBindTexture(GL_TEXTURE_2D,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //atm card port

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-9.6, -8.6, -15.2);
    glScalef(0.1,0.1,0.1);
    glBindTexture(GL_TEXTURE_2D,7);
    disk( 1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //atm card
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(cardx, -8.6, cardz);
    glScalef(0.2,0.02,0.35);
    glBindTexture(GL_TEXTURE_2D,6);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //atm screen
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.8, -8.4,-15.5);
    glScalef(1.5,1.4,0.3);
    glBindTexture(GL_TEXTURE_2D,4);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //atm keyboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.8,-10.18, -14.6);
    glRotatef(90,1,0,0);
    glScalef(1.5,1.4,0.3);
    glBindTexture(GL_TEXTURE_2D,3);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //atm divider
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-5, -9.2, -13.8);
    glRotatef(90,0,1,0);
    glScalef(3,3.6,0.3);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //cashport
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.2, -10.8, -13.6);
    glScalef(1.5,0.2,0.5);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //cash
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-11.2, -10.7, cashz);
    glScalef(0.22,0.02,0.35);
    glBindTexture(GL_TEXTURE_2D,9);
    drawcube(1,1,1);
    glTranslatef(0,-3,0.1);
    glBindTexture(GL_TEXTURE_2D,9);
    drawcube(1,1,1);
    glTranslatef(0,-3,0.1);
    glBindTexture(GL_TEXTURE_2D,9);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void water_drop()
{
    glPushMatrix();
    ceiling_light_holder(0,0.5,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12, 11.2, 8);
    glScalef(2.2, 2, 2.2);
    glutSolidSphere(1,20,20);
    glPopMatrix();
}

void sky(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,100,25,25);
}

void sphere(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,10,25,25);
}


void fan()
{
    glPushMatrix();
    glTranslatef(27, 13, -0.9);
    glScalef(0.1, 0.1, 1.2);
    drawcube(0.30,0.3,0.3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(23.4,9.4,-2.2);
    glScalef(0.3,0.3,0.3);
    ceiling_light(0,0,0);
    glPopMatrix();

    glTranslatef(27,13,0);
    glRotatef(gammaaa,0, 0, 1 );
    venti_fan(1,1,1);
    glRotatef(120,0,0,1);
    venti_fan(1,1,1);
    glRotatef(120,0,0,1);
    venti_fan(1,1,1);
    glPopMatrix();

}


void tubelight()
{
    glPushMatrix();
    glTranslatef(0, 5.7, 0);
    glScalef(0.12, 0.12, 2.62);
    cyl(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.7, 5.25);
    glScalef(0.1, 0.1, 0.6);
    disk(0.5,0.5,0.5);
    glTranslatef(0, 0, -8.75);
    disk(0.5,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 5.7, 2.6);
    glScalef(0.1, 0.2, 2.9);
    drawcube(0,0,0);
    glPopMatrix();
}



void street_lamp()
{
    //street lamp stick
    glPushMatrix();
    glTranslatef(57.6, -13.3, 51.3);
    glRotatef(-90,1,0,0);
    glScalef(0.3, 0.2, 17.8);
    cyl(0.3,0.3,0.4);
    glPopMatrix();

    //street lamp handle
    glPushMatrix();
    glTranslatef(57.4, 20.5, 51);
    glRotatef(45,0,1,0);
    glScalef(0.2, 0.2, 3.8);
    cyl(0.3,0.3,0.4);
    glPopMatrix();

    //light + cone
    glPushMatrix();
    glTranslatef(50.7, 6, 48.3);
    ceiling_light_holder(0.3,0.3,0.4);
    ceiling_light(0.85,0.85,0.85);
    glPopMatrix();


    //lamp er nicher disk
    glPushMatrix();
    glTranslatef(57.5, -13.3, 51.3);
    glRotatef(90,1,0,0);
    disk(0.3,0.3,0.4);
    glPopMatrix();
}
void light(double x,double y,double z,bool lighton,GLenum Lights,bool spot,bool moon,bool tubelight=false)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat moon_light_diffuse[]  = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat moon_light_specular[] = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);
    if(lighton)
    {
        if(moon)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, moon_light_diffuse);
            glLightfv( Lights, GL_SPECULAR, moon_light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
            glTranslatef(x,y,z);
            glScalef(1.2, 1.1, 1.2);
            glBindTexture(GL_TEXTURE_2D,29);
            sphere(1,1,1,true);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }
        else if(tubelight)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }
        else
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
            glTranslatef(-139.3, 100, -1.5);
            glScalef(0.9, 0.8, 0.9);
            glBindTexture(GL_TEXTURE_2D,28);
            sphere(1,1,1,true);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }


    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }



    //to know the position of strip light
    /*glPushMatrix();
    glTranslatef(-15,4,28);
    glutSolidCube(2);
    glPopMatrix();*/


    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 55.0);
    }


}



void lightt1(double x,double y,double z,bool lighton,GLenum Lights,bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat moon_light_diffuse[]  = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat moon_light_specular[] = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);
    if(lighton)
    {

        glLightfv( Lights, GL_AMBIENT, light_ambient);
        glLightfv( Lights, GL_DIFFUSE, light_diffuse);
        glLightfv( Lights, GL_SPECULAR, light_specular);
        glLightfv( Lights, GL_POSITION, light_position);


    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }




    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 55.0);
    }


}







void cameraPitch()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_y = 30*(sin(anglePitch*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraYaw()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraRoll()
{
    up_x = 1.0*(sin(angleRoll*3.1416/180.0));
    up_y = 1.0*(cos(angleRoll*3.1416/180.0));
}



void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int i = 1;
GLuint ID_[100];

void LoadTexture1(const char*filename)
{
    glGenTextures(1, &ID_[i]);
    glBindTexture(GL_TEXTURE_2D, ID_[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[i++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5, 5, -5, 5, 4, 100);
    gluPerspective(60,1,4,800);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(eye_x,eye_y,eye_z, lookat_x,lookat_y,lookat_z, up_x,up_y,up_z);
    glViewport(0, 0, windowHeight, windowWidth);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glScaled(sx,sy,sz);


    glTranslated(0,-7,0);

//    glPushMatrix();
//    glTranslatef(tx,ty,tz);
//    glScalef(2,2,2);
//    drawcube(1,1,1);
//    glPopMatrix();

    //floor
    glPushMatrix();
    glTranslatef(-15.05,0,0);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(2.9,0,0);
    glScalef(20,0.1,15);
    glBindTexture(GL_TEXTURE_2D,1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //table
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6,2,8);
    glScalef(1.5,0.1,3);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);
    glDisable(GL_TEXTURE_2D);

    // shamner left leg
    glTranslatef(-0.8,-9,0.8);
    glScalef(0.15,10,0.1);
    drawcube(0,0,0);

    // shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    // back right leg
    glTranslatef(0,0,-16);
    drawcube(0,0,0);

    // back left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    //GM wall partition
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,7.2,10.8);
    glScalef(0.15, 7.1,4);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.4,0.4,0.4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,7.2,1.4);
    glScalef(0.15,7.1,1.5);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.4,0.4,0.4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //dorja
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(dx, 3.7, dz);
    glScalef(0.15,3.6,2);
    glBindTexture(GL_TEXTURE_2D,44);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dorjar uporer jinish
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 0, 10.6, 4.8);
    glScalef(0.15,3.4,2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.4,0.4,0.4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chair
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-7.5,1.4,8);
    glScalef(1.2,0.1,1.2);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);
    glDisable(GL_TEXTURE_2D);

    //chair shamner left leg
    glTranslatef(-0.8,-6,0.8);
    glScalef(0.15,6.5,0.1);
    drawcube(0,0,0);

    //shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    //piser right leg
    glTranslatef(0,0,-16.8);
    drawcube(0,0,0);

    //piser left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8.55,2.5,8);
    glScalef(0.15,1, 1.2);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //arekwall partition
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8.5,7.2,0);

    glScalef(8.6,7.1,0.15);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shelf
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-9,0.1,2);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.2,5.5);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-9,3.3,2);
    glRotatef(90,0,1,0);
    glScalef(1.2,3,5.5);
    glBindTexture(GL_TEXTURE_2D,13);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-9,6.3,2);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.2,5.5);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //laptop

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6,2.15,8);
    glScalef(1,0.03,1.2);
    drawcube(0,0,0);


    glTranslatef(0,0.5,0);
    glBindTexture(GL_TEXTURE_2D,15);//===================================================
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.8,3,8);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);

    glTranslatef(-0.03,0,0);
    glBindTexture(GL_TEXTURE_2D,16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(1.3,0,0);
    glScalef(1.4,1,1);
        //cash counter shelf
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.5,1.6,-7);
    glScalef(7.5,1.5,1);
    glBindTexture(GL_TEXTURE_2D,17);
    drawcube(1,1,1);


    glPopMatrix();


    glPushMatrix();
    glTranslatef(7.5,3,-6.6);
    glScalef(7.5,0.2,1.4);
    glBindTexture(GL_TEXTURE_2D,18);
    drawcube(1,1,1);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //counter er aynar frame
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.5,4.2,-6.6);
    glScalef(0.2,1.2,1.4);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,0);

    glTranslatef(35,0,0);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,0);


    glTranslatef(-70,0,0);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //counter ayna
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(11.2,4.7,-5.3);
    glScalef(3.5,0.7,0.2);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);

    glTranslatef(-2.1,0,0);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    //sofa
    glPushMatrix();
    glTranslatef(1,0,2.2);
    glScalef(0.9,0.9,0.9);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10,1,13);
    glScalef(3.5,1,1.3);
    glBindTexture(GL_TEXTURE_2D,20);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10,2.5,14);
    glScalef(3.5,2,0.3);
    glBindTexture(GL_TEXTURE_2D,20);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(6.5,1.3,12.5);
    glScalef(0.8,1.4,1.3);
    glBindTexture(GL_TEXTURE_2D,20);
    drawcube(1,1,1);



    glTranslatef(9,0,0);
    glBindTexture(GL_TEXTURE_2D,20);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //lobbyroom table
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10,2,8.5);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.1,3);
    glBindTexture(GL_TEXTURE_2D,14);
    drawcube(1,1,1);


    glTranslatef(-0.8,-9,0.8);
    glScalef(0.15,10,0.1);
    drawcube(0,0,0);

    glTranslatef(0,0,-16);
    drawcube(0,0,0);

    glTranslatef(10,0,0);
    drawcube(0,0,0);

    glTranslatef(0,0,16);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,2.05,8.5);
    glRotatef(25,0,1,0);
    glScalef(0.8,0.1,1);
    drawcube(0,0,1);


    glTranslatef(0,0.7,0);
    glRotatef(10,0,1,0);
    drawcube(0,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //employee table
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.9,0.9,0.9);
    glTranslatef(-9,1.6,-4.5);
    glScalef(1,1.3,4);
    glBindTexture(GL_TEXTURE_2D,17);
    drawcube(1,1,1);

    glTranslatef(0,1,0);
    glScalef(1.5,0.2,1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.9,0.9,0.9);
    glTranslatef(-9,1.6,-13.2);
    glScalef(1,1.3,1.7);
    glBindTexture(GL_TEXTURE_2D,17);
    drawcube(1,1,1);

    glTranslatef(0,1,0);
    glScalef(1.5,0.2,1);
    drawcube(1,1,1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6.4, 2.6, -9);
    glRotatef(thetaa,1,0,0);
    glPushMatrix();
    //glScalef(0.9,0.9,0.9);
    glTranslatef(-1.6,0.2,0);
    glScalef(1.6,0.2,1.4);
    glBindTexture(GL_TEXTURE_2D,2);
    drawcube(1,1,1);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//
//    glTranslatef(10,10,0);
//    glRotatef(thetaa,0,0,1);
//    glPushMatrix();
//    glTranslatef(-3,0,0);
//    glScalef(3,2,3);
//    glBindTexture(GL_TEXTURE_2D,7);
//    drawcube(1,1,1);
//    glPopMatrix();
//
//
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);


    //chair
    glPushMatrix();
    glTranslatef(-2,0,4);
    chair();

    glTranslatef(0,0,-3.8);
    chair();

    glTranslatef(0,0,-6.2);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16,0,-10);
    glRotatef(180,0,1,0);
    chair();

    glTranslatef(0,0,3.8);
    chair();

    glTranslatef(0,0,6);
    chair();
    glPopMatrix();


    //employee laptop
    glPushMatrix();

    glTranslatef(-2,0.7,-1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(0,0,0);
    glTranslatef(0,0.5,0);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    glBindTexture(GL_TEXTURE_2D,16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    //laptop2

    glPushMatrix();

    glTranslatef(-2,0.7,-4);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(0,0,0);
    glTranslatef(0,0.5,0);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    glBindTexture(GL_TEXTURE_2D,16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();



    //laptop
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-2,0.7,-10);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(0,0,0);
    glTranslatef(0,0.5,0);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    glBindTexture(GL_TEXTURE_2D,16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();






    //stairs
    glPushMatrix();

    glTranslatef(5.9,0,0);

    //stair base 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(21, 0, -5.4);
    glScalef(4,0.3,9.2);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //stair base 1-1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(28.9, 0, 0.2);
    glScalef(3.9,0.3,14.8);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(21,-1,4.8);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(21, -2.5, 6.6);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef( 21, -3.5,8.2);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 21,-4.5,9.8);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //stair base 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(16.9, -5.5, 13);
    glScalef(8,0.3,4);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //stairs2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.8, -7,8.2);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.8, -8.6, 6.6);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.8, -10.2, 5);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.8, -11.8, 3.4);
    glScalef(4,1.2,1);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //nicher floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10.8, -13, 0.2);
    glScalef(28,0.1,17);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //atm stuffs
    glPushMatrix();
    atm();
    glTranslatef(12,0,0);
    atm();
    glPopMatrix();

    //bathroom
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14.8, -12.8, 10.6);
    glScalef(2.2,0.2,2.2);
    glBindTexture(GL_TEXTURE_2D,10);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bathroom wall ================================================
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 10.8, -7.4, 16.9);
    glScalef( 28, nicher_wally, nicher_wallz);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //bathroom wall for dorja
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 2.7, -7, 6.7);
    glRotatef(90,0,1,0);
    glScalef( 1.7,6,0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //bathroom wall for dorja2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 2.7, -7, 14.03);
    glRotatef(90,0,1,0);
    glScalef( 2.3,6,0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bathroom wall for dorja er uporer part
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 2.8, -3, 10);
    glRotatef(90,0,1,0);
    glScalef( 1.8, 2, 0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bathroom dorja@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 2.65, -8.9, bathz);
    glRotatef(90,0,1,0);
    glScalef( 1.7, 3.9, 0.2);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -7.2, -7, 5.2);
    glScalef(10,6,0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tissue roll
    glPushMatrix();
    glTranslatef(-9.6, -9.8, 15.6);
    glRotatef(90,0,1,0);
    glScalef(0.2,0.2,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glTranslatef(0,0,0.2);
    glutSolidTorus(1,2,20,20);
    glPopMatrix();

    //tissue holder
    glPushMatrix();
    glTranslatef(-10.4, -9.8, 16.1);
    glScalef(0.15,0.15,0.6);
    drawcube(0,0,0);

    glTranslatef(14,0,0);
    drawcube(0,0,0);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-9.4, -9.8, 15.6);
    glRotatef(90,0,1,0);
    glScalef(0.15,0.15,1);
    drawcube(0,0,0);
    glPopMatrix();

    //basin
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.2, -8.4, 15.8);
    glBindTexture(GL_TEXTURE_2D,24);
    glScalef(2.3,0.3,1.2);
    drawcube(1,1,1);

    glTranslatef( 0, 0.45, 0.2);
    glScalef(0.6,0.6,0.8);
    glBindTexture(GL_TEXTURE_2D,23);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.2, -10.8, 16);
    glScalef(0.7,2.2,0.7);
    glBindTexture(GL_TEXTURE_2D,25);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //tap
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -2.2, -6.6, 16);
    glScalef(0.2,0.16,0.8);
    glBindTexture(GL_TEXTURE_2D,22);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tap er mukkha
    glPushMatrix();
    glTranslatef(  -2.2, -6.8, 15.4);
    glScalef(0.2,0.16,0.2);
    drawcube(0,1,1);
    glPopMatrix();


    //soapcase
    glPushMatrix();
    glTranslatef( -7, -8.2, 16.4);
    glScalef(0.15,0.15,0.6);
    drawcube(255/255,114/255,118/255);

    glTranslatef(10,0,0);
    drawcube(255/255,114/255,118/255);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-6.25, -8.4, 16.3);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.15,0.9);
    drawcube(40/255, 40/255, 43/255);
    glPopMatrix();


    //soap
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6.25, -8.1, 16.32);
    glRotatef(90,0,1,0);
    glScalef(0.35,0.15,0.6);
    glBindTexture(GL_TEXTURE_2D,26);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //mirror
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -2.2, -4, 16.8);
    glScalef(1.3,1.7,0.2);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dotaalar wall left side
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-16.9, 7.2, 0.1);
    glScalef(0.15,7.1,15);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dotaalar wall backside
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6.5, 7.2, -14.8);
    glRotatef(90,0,1,0);
    glScalef(0.15,7.1,10.5);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //nichtala left side
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-17.1, -7.4, -4);
    glScalef(0.1,5.7, 12.9);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //nichtala left side 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-17.1, -7.4, 14.9);
    glScalef(0.1,5.7, 2.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //nichtala left side final
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-16.7, -9, 11);
    glScalef(0.5, 4, 2.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //venti fan
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(-34.3, -6.6, 21.3);
    glRotatef(90,0,1,0);
    glRotatef(gammaaaa,0, 0, 1 );
    venti_fan(1,1,1);
    glRotatef(90,0,0,1);
    venti_fan(1,1,1);
    glRotatef(90,0,0,1);
    venti_fan(1,1,1);
    glRotatef(90,0,0,1);
    venti_fan(1,1,1);
    glPopMatrix();
    glPopMatrix();

    //ventifan knob
    glPushMatrix();
    glTranslatef(-17.1, -3.3, 10.7);
    glScalef(0.15,0.15,0.15);
    rim(0,0,0);
    glPopMatrix();

    //venti wood
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-16.9, -4.8, 10.8);
    glScalef(0.3, 0.2, 1.9);
    glBindTexture(GL_TEXTURE_2D,17);
    drawcube(1,1,1);
    glTranslatef(0,14.5,0);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);













    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-17.1, -0.8, 0.1);
    glScalef(0.1, 0.9, 15);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.3,0.3,0.3);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //nichtala backside
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 10.8, -7.3, -16.7);
//    glRotatef(90,0,1,0);
    glScalef(28, 5.7, 0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //building er prism layer

    glPushMatrix();
    glTranslatef(10.8, -1.7, 16.1);
    glScalef(56, 1.8, 2);
    triangularPrism(0.5,0.5,0.5);
    glPopMatrix();

    //prismlayer2

    glPushMatrix();
    glTranslatef( 10.8, -1.7, -16);
    glRotatef(180,0,1,0);
    glScalef(56, 1.8, 2);
    triangularPrism(0.5,0.5,0.5);
    glPopMatrix();


    //roof
    glPushMatrix();
    glTranslatef( 11.1, 15, 0);
    glRotatef(90,0,0,1);
    glScalef(1, 29.8, 18);
    drawcube(1,1,1);
    glPopMatrix();
    glPopMatrix();

    //vault pillars
    glPushMatrix();
    glTranslatef(2.7, -6.8, -31.6);
    glScalef( 1.1, 6.6, 1.1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.2, -6.8, -31.6);
    glScalef( 1.1, 6.6, 1.1);
    drawcube(1,1,1);
    glPopMatrix();


    //fan
    glPushMatrix();

    glTranslatef(-16.4,0,0);

    glPushMatrix();
    glTranslatef(-24.3, 12.9, -7.4);
    glRotatef(90,1,0,0);
    glScalef( 1.2, 1.1, 0.6);
    fan();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.4,0,0);
    glPushMatrix();
    glTranslatef( -41,12.9,-7.4);
    glRotatef(90,1,0,0);
    glScalef( 1.2, 1.1, 0.6);
    fan();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-16.4,0,0);
    glPushMatrix();
    glTranslatef( -39.8, 12.9, -21.3);
    glRotatef(90,1,0,0);
    glScalef( 1.2, 1.1, 0.6);
    fan();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.4,0,0);
    glPushMatrix();
    glTranslatef( -21.3, 12.9, -20.2);
    glRotatef(90,1,0,0);
    glScalef( 1.2, 1.1, 0.6);
    fan();
    glPopMatrix();
    glPopMatrix();



    //tubelight===;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;=;


    //tubelight of gm
    glPushMatrix();
    light(-22.1, 16.4, 20.6,light4,GL_LIGHT4,false,false,true);
    glTranslatef(-31.6, 6.2, 5.2);
    tubelight();
    glPopMatrix();


    //tubelight of common room
    glPushMatrix();
    light(0, 14.3, 3.6,light5,GL_LIGHT5,false,false,true);
    glTranslatef( -11.7, 6.3, -14.4);
    glRotatef(-90,0,1,0);
    tubelight();
    glPopMatrix();


    //tubelight of nicher tala
    glPushMatrix();
    light(-8.5, 1.3, -4.7,light2,GL_LIGHT2,false,false,true);
    glTranslatef( -23.1, -7.9, 4.8);
    glRotatef(90,0,1,0);
    tubelight();
    glPopMatrix();


    //ceiling light of bathroom
    glPushMatrix();
    lightt1(-17, -1.2, 10.8,light3,GL_LIGHT3,true);
    glTranslatef( -23.2, -8.4, 6.9);
    glScalef(0.5,0.5,0.5);
    ceiling_light_holder(0.3,0.3,0.4);
    ceiling_light(0.85,0.85,0.85);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17.2, 0, 10.9);
    glScalef(0.1, 0.7, 0.1);
    glRotatef(90,1,0,0);
    cyl(0.3,0.3,0.4);
    glPopMatrix();






    // OUTDOOR ==================================

    //outdoor grass
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-14.2,0);
    glScalef(58.1, 0.7, 58.1);
    glBindTexture(GL_TEXTURE_2D,27);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //outdoor grass
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-14.2,0);
    glScalef(135.4, 0.7, 135.4);
    glBindTexture(GL_TEXTURE_2D,27);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //outdoor street front
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(78.5, -13.9, 3.5);
    glScalef(22.9, 0.5, 91.8);
    glBindTexture(GL_TEXTURE_2D,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //outdoor street left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -1.2, -13.85, 73.3);
    glRotatef(90,0,1,0);
    glScalef(22.9, 0.5, 61.2);
    glBindTexture(GL_TEXTURE_2D,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //outdoor street back
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -81, -13.9, 3.5);
    glScalef(22.9, 0.5, 91.8);
    glBindTexture(GL_TEXTURE_2D,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //outdoor street right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -1.2, -13.85,  -65.4);
    glRotatef(90,0,1,0);
    glScalef(22.9, 0.5, 61.2);
    glBindTexture(GL_TEXTURE_2D,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //outdoor street light ==l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l=l
    glPushMatrix();
    lightt1( 61.2, 28, 71.6,light6,GL_LIGHT6,true);
    street_lamp();
    glPopMatrix();

    glPushMatrix();
    lightt1(-81, 30.9, -61.2,light7,GL_LIGHT7,true);
    glTranslatef(-2.6, 0, 6.6);
    glRotatef(180,0,1,0);

    street_lamp();
    glPopMatrix();




    //sun
    glPushMatrix();
    glRotatef(sun,1,0,0);
    light(-139.3, 78.5, -1.5,light0,GL_LIGHT0,false,false);
    glPopMatrix();
    //moon
    glPushMatrix();
    glRotatef(sun,1,0,0);
    light(-139.3, -100, -1.5,light1,GL_LIGHT1,false,true);
    glPopMatrix();

    //CAR FUNCTION


    glPushMatrix();
    glTranslatef(tx, -9.4, tz+82.7);



    glPushMatrix();
    glRotatef(gammaa,0,1,0);
    glScalef(8, 1.6, 4.1);
    drawcube(1,0,0);

    //car headlight texture
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.01, -6.38378e-16, 0);
    glScalef(2.77556e-17, 0.9, 0.9);
    glBindTexture(GL_TEXTURE_2D,31);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //car side texture-1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.77556e-17, 0, 1.05);
    glScalef(0.5, 0.9, 2.77556e-17);
    glBindTexture(GL_TEXTURE_2D,33);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //car side texture-2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.77556e-17, 0, -1.05);
    glScalef(0.5, 0.9, 2.77556e-17);
    glBindTexture(GL_TEXTURE_2D,33);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //car hood
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 0.05, 2.21, -0.1);
    glScalef(0.42, 2.77556e-17, 0.9);
    glBindTexture(GL_TEXTURE_2D,34);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //car side glass-1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.05, 1.4, 1.02);
    glScalef(0.4, 0.8, 2.77556e-17);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //car side glass-2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.05, 1.4, -1.02);
    glScalef(0.4, 0.8, 2.77556e-17);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //car front glass
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-0.5, 1.65, -2.77556e-17);
    glRotatef(77,0,0,1);
    glScalef(0.6, 2.77556e-17, 1);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //carback glass
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.6, 1.65, -2.77556e-17);
    glRotatef(-77,0,0,1);
    glScalef(0.6, 2.77556e-17, 1);
    glBindTexture(GL_TEXTURE_2D,19);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //carback
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.01,0,0);
    glScalef(2.77556e-17, 0.9, 0.9);
    glBindTexture(GL_TEXTURE_2D,35);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glTranslatef(0.05,1.6,0);
    glScalef(0.7, 0.6, 1);
    slcube(1,0,0);

    glTranslatef(-0.9,-4.3, 1);
    glScalef(0.1, 0.6, 0.1);
    torus(0,0,0);


    glTranslatef(0,0,-19.8);
    glutSolidTorus(1.2,2,16,16);


    glTranslatef(16.6,0,0);
    glutSolidTorus(1.2,2,16,16);

    glTranslatef(0,0,19.8);
    glutSolidTorus(1.2,2,16,16);
    glDisable(GL_TEXTURE_2D);




    glTranslatef(0,0,0.3);
    rim(0.5,0.5,0.5);


    glTranslatef(-16.5,0,0);
    glutSolidSphere(1,20,20);


    glTranslatef(0,0, -10.4);
    glutSolidSphere(1,20,20);


    glTranslatef( 16.5,0,0);
    glutSolidSphere(1,20,20);

    glPopMatrix();


    glPopMatrix();




    //Sky with globe ============================================/././././/.


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glRotatef(skyrotate,0,0,1);
    glScalef(2.3, 2.3, 2);
    glBindTexture(GL_TEXTURE_2D, n);
    sky(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //MAIN GATE-left door

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 23.45, -8.2, maindoorl);
    glRotatef(90,0,1,0);
    glScalef(1.8, 4.7, 0.3);
    glBindTexture(GL_TEXTURE_2D,45);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //MAIN GATE-right door
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 23.45, -8.2, maindoorr);
    glRotatef(90,0,1,0);
    glScalef(1.8, 4.7, 0.3);
    glBindTexture(GL_TEXTURE_2D,46);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //Main gate wall

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 23.7, -7.3, 9.4);
    glRotatef(90,0,1,0);
    glScalef(7.5, 5.6, -0.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //Main gate wall-2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 23.7, -7.3, -11.1);
    glRotatef(90,0,1,0);
    glScalef(5.7, 5.6, -0.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //Main gate wall-uporer extension
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 23.7, -2.6, -1.6);
    glRotatef(90,0,1,0);
    glScalef(5.7, 0.9, -0.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //Main gate uporer chikon maal
    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(23.6, -0.8, 0.1);
    glScalef(0.1, 0.9, 15);
    //glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.3,0.3,0.3);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);


    //vault room
    glPushMatrix();
    glTranslatef(-3.9, -0.1, -23.8);
    glScalef(7.4, 0.2, 8.8);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3.9, 11.7, -23.8);
    glScalef(7.4, 0.2, 8.8);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3.9, 5.8, -32.7);
    glScalef(7.4, 6.1, 0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //vault side walls
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 3.7, 5.8, -23.9);
    glRotatef(90,0,1,0);
    glScalef(8.7, 6.1, 0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -11.3, 5.8, -23.9);
    glRotatef(90,0,1,0);
    glScalef(8.7, 6.1, 0.2);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //vaultdoor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(vaultdoor, 5.8,  -15.2);
    glScalef(7.4, 6.1, 0.2);
    glBindTexture(GL_TEXTURE_2D,38);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //&&&&&&&   Water Drop &&&&&
    glPushMatrix();
    glTranslatef(-18, wdrop, 14.9);
    glScalef(waterx, watery, waterz);
    water_drop();
    glPopMatrix();

    //stair er wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.8, 7.1, 9);
    glScalef( 0.1, 7, 6);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.8, 7.1, -9);
    glScalef( 0.1, 7, 6);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //stair er dorja
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.8, 4.1, sdoor);
    glScalef(0.2, 4, 3);
    glBindTexture(GL_TEXTURE_2D,44);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //stair er upor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(7.8, 11, 0);
    glScalef(0.1, 3, 3);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //wall cover
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(23.6, 7.1, 0.1);
    glScalef( 0.1, 7, 14.9);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


   //dotala front wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.2, 7.1, 15);
    glScalef(27.7, wally, wallz);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(13.5, 7.1, -14.9);
    glScalef(10, 7, 0.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3.8, 12.8, -14.9);
    glScalef(7.4, 1.3, 0.1);
    glBindTexture(GL_TEXTURE_2D,21);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chardiker windowwwwwwwww
    //gm er window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-24, 8, 15);
    glScalef( 4.6, 3.5, 0.3);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //employee room window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -24.7, 8.8, -14.8);
    glScalef( 4.6, 3.5, 0.3);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //nichtalar window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 13.5, -4.9, -16.7);
    glScalef(5, 2.5, 0.3);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dotalar front window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(  23.7, 8.4, -1.1);
    glRotatef(90,0,1,0);
    glScalef( 9, 3.5, 0.3);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //nichtalar back window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -32.1, -5.8, -5.4);
    glRotatef(90,0,1,0);
    glScalef( 4.5, 3.5, 0.3);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //billboard
    glPushMatrix();
    glTranslatef( 21.8, 20.2, 0.3);
    glScalef(1.1, 2.9, 16);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();

    //billboard image
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 22.9, 20.2, 0.3);
    glScalef(0.1, 2.8, 15.8);
    glBindTexture(GL_TEXTURE_2D,40);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //billboard image2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 20.52, 20.2, 0.3);
    glRotatef(180,0,1,0);
    glScalef(0.1, 2.8, 15.8);
    glBindTexture(GL_TEXTURE_2D,40);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //billboard holder1
    glPushMatrix();
    glTranslatef( 21.9, 17.8, 12.2);
    glScalef( 0.5, 1.9, 0.7);
    drawcube(0,0,0);
    glPopMatrix();

    //billboard holder2
    glPushMatrix();
    glTranslatef( 21.9, 17.8, -11.7);
    glScalef( 0.5, 1.9, 0.7);
    drawcube(0,0,0);
    glPopMatrix();


    //entrancepath
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(39.2, -13.3, -1.8);
    glRotatef(90,0,1,0);
    glScalef(5.8, 0.1, 16.5);
    glBindTexture(GL_TEXTURE_2D,41);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 40.8, -9.1, 50.5);
    glScalef(15, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 11.1, -9.1, 50.5);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -18.3, -9.1, 50.5);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-4
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -43.2, -9.1, 50.5);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);










    //fence-5
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 40.6, -9.1, -42.6);
    glScalef(15, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-6
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 11.1, -9.1, -42.6);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-7
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -18.3, -9.1, -42.6);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-8
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -43.2, -9.1, -42.6);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
















    //fence-9
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -58.2, -9.1, 36);
    glRotatef(90,0,1,0);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-10
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -58.2, -9.1, 6.6);
    glRotatef(90,0,1,0);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-11
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -58.2, -9.1, -25.1);
    glRotatef(90,0,1,0);
    glScalef(17.2, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fence-12
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 56, -9.1, 35.8);
    glRotatef(90,0,1,0);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


     //fence-12
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 56, -9.1, 17.8);
    glRotatef(90,0,1,0);
    glScalef(14.7, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //fence-13
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( 56, -9.1, -25.4);
    glRotatef(90,0,1,0);
    glScalef(17.3, 4.2, -0.2);
    glBindTexture(GL_TEXTURE_2D,42);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //goldbar
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8, 1.4, -23.4);
    glScalef(2.3, 1.3, 3.8);
    glBindTexture(GL_TEXTURE_2D,43);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //goldbar-2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-0.4, 1.4, -23.4);
    glScalef(2.3, 1.3, 3.8);
    glBindTexture(GL_TEXTURE_2D,43);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //goldbar-3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.1, 4, -23.4);
    glScalef(2.3, 1.3, 3.8);
    glBindTexture(GL_TEXTURE_2D,43);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //manager signboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14.9, 6.2, 11);
    glScalef(0.1, 0.4, 2);
    glBindTexture(GL_TEXTURE_2D,47);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //cash counter signboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -13.7, 9, -14.5);
    glScalef(2.4, 1.2, 0.1);
    glBindTexture(GL_TEXTURE_2D,48);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //helpdesk signboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef( -31.8, 9.9, -7.3);
    glScalef(0.1, 1.5, 4.1);
    glBindTexture(GL_TEXTURE_2D,49);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);






//    light(-5,13.85,0,light1,GL_LIGHT1,true,false);
//    light(-55,30,28,light2,GL_LIGHT2,false,true);
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 't':
    case 'T':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'w':
        eye_y++;
        lookat_y++;
        glutPostRedisplay();
        break;
    case 's':
        eye_y--;
        lookat_y--;
        glutPostRedisplay();
        break;
    case 'd':
        eye_x++;
        lookat_x++;
        glutPostRedisplay();
        break;
    case 'a':
        eye_x--;
        lookat_x--;
        glutPostRedisplay();
        break;

    case '+':
        eye_z--;
        if(pilotRoll)
        {
            angleRoll++;
        }
        else
        {
            lookat_z--;
        }
        glutPostRedisplay();
        break;
    case '-':
        eye_z++;
        if(pilotRoll)
        {
            angleRoll--;
        }
        else
        {
            lookat_z;
        }
        glutPostRedisplay();
        break;
    case '*':
        sx+=0.1;
        sy+=0.1;
        sz+=0.1;
        glutPostRedisplay();
        break;
    case '/':
        sx-=0.1;
        sy-=0.1;
        sz-=0.1;
        glutPostRedisplay();
        break;
    //for pitch-yaw-roll
    case 'i':
        if(angleRoll<=180)
        {
            angleRoll++;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'j':
        if(angleRoll>=-180)
        {
            angleRoll--;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'o':
        if(angleYaw<180)
        {
            angleYaw++;
            cameraYaw();

        }
        glutPostRedisplay();
        break;
    case 'p':
        if(angleYaw>0)
        {
            angleYaw--;
            cameraYaw();
        }
        glutPostRedisplay();
        break;
    case 'k':
        if(anglePitch<90)
        {
            anglePitch++;
            cameraPitch();

        }
        glutPostRedisplay();
        break;
    case 'l':
        if(anglePitch>-90)
        {
            anglePitch--;
            cameraPitch();
        }
        glutPostRedisplay();
        break;

    //switch for light0
    case '1':
        light0 = !light0;
        glutPostRedisplay();
        break;
    case '2':
        light1 = !light1;
        glutPostRedisplay();
        break;

    //nichtalar tubelight
    case '3':
        light2 = !light2;
        glutPostRedisplay();
        break;
    //nichtalar spotlight
    case '4':
        light3 = !light3;
        glutPostRedisplay();
        break;
    //gm er light
    case '!':
        light4 = !light4;
        glutPostRedisplay();
        break;

    //commonroom er light
    case '@':
        light5 = !light5;
        glutPostRedisplay();
        break;
    //street lamp-1
    case '#':
        light6 = !light6;
        glutPostRedisplay();
        break;
    //street lamp-2
    case '$':
        light7 = !light7;
        glutPostRedisplay();
        break;

    //all fan
    case 'I':
        countt++;
        if(countt%2!=0)
        {
            sndPlaySound("fan.wav",SND_ASYNC);
        }
        else
        {
            sndPlaySound("blank.wav",SND_ASYNC);

        }
        fanRotate = !fanRotate;
        glutPostRedisplay();
        break;
    //bathroom door
    case 'b':
        bathdoor = !bathdoor;
        glutPostRedisplay();
        break;
    case 'B':
        ventirotate = !ventirotate;
        glutPostRedisplay();
        break;
    case 'm':
        sndPlaySound("dooropen.wav",SND_ASYNC);
        maindoor = !maindoor;

        glutPostRedisplay();
        break;


    //for car
    case 'C':
        carcountt++;
        if(carcountt%2!=0)
        {
            sndPlaySound("carsound.wav",SND_ASYNC);
        }
        else
        {
            sndPlaySound("blank.wav",SND_ASYNC);

        }
        carRotate = !carRotate;
        //Car Z point -154.5
        glutPostRedisplay();
        cout<<"Car X point "<<tx<<" \n";
        cout<<"Car z point "<<tz<<" \n";
        cout<<"Right off value "<<rightoff<< " \n";
        break;

    //for pilotview
    case '7':
        pilotPitch = !pilotPitch;
        glutPostRedisplay();
        break;
    case '8':
        wall = !wall;
        glutPostRedisplay();
        break;
    case '9':
        sc = !sc;
        glutPostRedisplay();
        break;
    case '5':
        if(sc)
        {

            ssy -=0.1;
        }
        else
        {
            tty -= 0.1;
        }
        glutPostRedisplay();
        break;
    case '6':
        if(sc)
        {

            ssy +=0.1;
        }
        else
        {
            tty += 0.1;
        }

        glutPostRedisplay();
        break;
    case 'u':
        dooropen =!dooropen;
        glutPostRedisplay();
        break;
    case 'v':
        cin>>pass;
        sndPlaySound("atmsound.wav",SND_ASYNC);

        vaultDoor =!vaultDoor;
        glutPostRedisplay();
        break;
    case 'c':
        if(cardz>-15.5 && cashz==-13.6)
        {
            cardz -=0.05;
            cout<<cardz<<" "<<cardin<<"\n";

        }

        else if(cashz<=-12.8 && cardz<=-14.8)
        {
            cardz +=0.05;
            cashz +=0.05;
        }

        else
        {
            cashz=-13.6;
        }

//        else if(cardz<=-14.8 && cashz<=-12.9 && cardin==1)
//        {
//            cardz+=0.05;
//            cashz+=0.05;
//            if(cardz==-14.8)
//            {
//                cardout=1;
//                cardin=0;
//            }
//        }
        glutPostRedisplay();
        break;
    case 'U':
        zRotate =!zRotate;
        glutPostRedisplay();
        break;
    case 'W':
        wcountt++;
        if(wcountt%2!=0)
        {
            sndPlaySound("wdrop.wav",SND_ASYNC);
        }
        else
        {
            sndPlaySound("blank.wav",SND_ASYNC);

        }
        waterDrop=!waterDrop;
        glutPostRedisplay();
        break;
    case 'S':
        sDoor=!sDoor;
        sndPlaySound("dooropen.wav",SND_ASYNC);
        glutPostRedisplay();
        break;
    case ',':
        thetaa += 0.5;
        glutPostRedisplay();
        break;




    case 27:  // Escape key
        exit(1);
    }


}


void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sc)
        {

            ssz -=0.1;
        }
        else
        {
            ttz -= 0.1;
        }

        break;
    case GLUT_KEY_DOWN:
//do something here
        if(sc)
        {

            ssz +=0.1;
        }
        else
        {
            ttz += 0.1;
        }
        break;
    case GLUT_KEY_LEFT:
//do something here
        if(sc)
        {

            ssx -=0.1;
        }
        else
        {
            ttx -= 0.1;
        }


        break;
    case GLUT_KEY_RIGHT:
//do something here
        if(sc)
        {

            ssx +=0.1;
        }
        else
        {
            ttx += 0.1;
        }
        break;
    }
    cout<<"Starting Point "<<ttx<<", "<<tty<<", "<<ttz<<" \n";
    cout<<"Scale Sizes "<<ssx<<", "<<ssy<<", "<<ssz<<" \n";

    glutPostRedisplay();
}



void animate()
{
    if (bRotate == true)
    {
        theta += 0.4;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.4;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (ventirotate == true)
    {
        gammaaaa += 1;
        if(gammaaaa > 360.0)
            gammaaaa -= 360.0*floor(gammaaaa/360.0);
    }
    if (fanRotate == true)
    {
        gammaaa += 1.8;
        if(gammaaa > 360.0)
            gammaaa -= 360.0*floor(gammaaa/360.0);
    }
    if (skyRotate == true)
    {
        skyrotate+= 0.2;
        if(skyrotate> 360.0)
            skyrotate -= 360.0*floor(skyrotate/360.0);
    }
    if (bathdoor == true)
    {
        if(bathz<=13.7)
        {
            bathz+= 0.05;
        }
    }
    if (bathdoor == false)
    {
        if(bathz>=10.1)
        {
            bathz-= 0.05;
        }

    }

    if (maindoor == true)
    {
        if(maindoorl<=4 && maindoorr >=-7.5)
        {
            maindoorl+= 0.01;
            maindoorr-=0.01;
        }
    }
    if (maindoor == false)
    {
        if(maindoorl>=0.1 && maindoorr <=-3.6)
        {
            maindoorl-= 0.01;
            maindoorr+=0.01;
        }
    }
    if(vaultDoor == true)
    {
        //
        if(vaultdoor>=-20 && pass==password)
        {

            vaultdoor-=0.05;
        }
    }
    if(vaultDoor == false)
    {
        if(vaultdoor<=-3.9)
        {

            vaultdoor+=0.05;
        }
    }
    if(waterDrop==true)
    {

        waterx=0.06;
        watery=0.06;
        waterz=0.06;
        if(wdrop>=-8.6)
        {
            wdrop-=0.008;
        }
        if(wdrop<=-8.6)
        {
            wdrop=-7.9;
        }
    }
    if(waterDrop==false)
    {
        waterx=0.0;
        watery=0.0;
        waterz=0.0;
    }
    if(sDoor==true)
    {
        if(sdoor<=6)
        {
            sdoor+=0.015;
        }
    }
    if(sDoor==false)
    {
        if(sdoor>=0.1)
        {
            sdoor-=0.015;
        }
    }
    if(wall==true)
    {
        wally=7;
        wallz=0.1;
        nicher_wally=5.7;
        nicher_wallz=0.2;
    }
    if(wall==false)
    {
        wally=0;
        wallz=0;
        nicher_wally=0;
        nicher_wallz=0;
    }
    if (zRotate == true)
    {
        sun += 0.2;
        if(sun > 360.0)
            sun -= 360.0*floor(sun/360.0);
        if(sun>=95 && sun<=275)
        {
            light0 = false;
            light1=true;
            light6=true;
            light7=true;
            n=37;
        }
        else
        {
            light0 = true;
            light1=false;
            light6=false;
            light7=false;
            n=36;
        }
    }
    if(carRotate==true)
    {
        if(tx>=90.5 && tz <=-0.5)
        {
            gammaa=-270;
            tz+=0.5;
            cout<<"Car Z point "<<tz<<" \n";
            bottomoff=1;


        }

        else if (bottomoff == 1 && rightoff==1 &&  tz<=0 && tx>=0)
        {

            gammaa=-360;

            tx-=0.5;
//            rightoff=1;
            if(tx==0)
            {
                rightoff=0;
                leftoff=0;
                topoff=0;
                bottomoff=0;
                cout<<"Right off value "<<rightoff<<" \n";
            }
            cout<<"gamma "<<gammaa<<" \n";
        }
        else if(leftoff==1 && tz<=-154.5)
        {
            gammaa=-180;
            tx +=0.5;
            topoff = 1;


        }
        else if(rightoff==1 && tx<=-90)
        {
            gammaa=-90;
            tz-=0.5;
            leftoff = 1;

            cout<<"Car Z point "<<tz<<" \n";
            cout<<"gamma "<<gammaa<<" \n";
        }

        else
        {
            if(rightoff==0)
            {
                tx -= 0.5;

                if(tx==-90)
                {
                    rightoff=1;

                }

                cout<<"Ekhane car point of x "<<tx<<" \n";
            }

        }
    }
    if(dooropen==true)
    {
        if(dx<=0.5)
        {
            dx +=0.05;
        }
        else
        {
            if(dz<=9.8)
            {
                dz +=0.05;
            }

        }
    }
    if(dooropen==false)
    {
        if(dz>4.8)
        {
            dz -=0.05;
        }
        else
        {
            if(dz==4.8 && dx>=0)
            {
                dx-=0.05;
            }


        }
    }


    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Janata Bank, Kuet");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\bfloor.bmp"); //1
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\atmdiv.bmp"); //2
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\numpad.bmp"); //3
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\atmscreen.bmp"); //4
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\atmtext.bmp"); //5
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\atmcard.bmp"); //6
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\atmport.bmp"); //7
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\cashport.bmp"); //8
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\taka.bmp"); //9
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\toilet.bmp"); //10
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\stair.bmp"); //11
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\gmdoor.bmp"); //12
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\shelf.bmp"); //13
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\gmtable.bmp"); //14
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\keyboard.bmp"); //15
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\lscreen.bmp"); //16
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\wood.bmp"); //17
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\cshelf.bmp"); //18
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\cglass.bmp"); //19
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\sofaseat.bmp"); //20
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\wall.bmp"); //21
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\tap.bmp"); //22
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\basin.bmp"); //23
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\basin1.bmp"); //24
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\basin2.bmp"); //25
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\soap.bmp"); //26
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\grass.bmp"); //27
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\sun.bmp"); //28
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\moon.bmp"); //29
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\street.bmp"); //30
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\car front.bmp"); //31
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\car side.bmp"); //32
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\car side 2.bmp"); //33
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\car hood.bmp"); //34
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\car back.bmp"); //35
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\merged.bmp"); //36
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\nightsky.bmp"); //37
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\vault.bmp"); //38
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\window.bmp"); //39
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\janatabill.bmp"); //40
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\entpath.bmp"); //41
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\fence.bmp"); //42
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\goldbar.bmp"); //43
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\door.bmp"); //44
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\mdoorl.bmp"); //45
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\mdoorr.bmp"); //46
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\gm.bmp"); //47
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\ccounter.bmp"); //48
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\helpdesk.bmp"); //49
    LoadTexture1("C:\\Users\\nafir\\OneDrive\\Desktop\\Janata Bank\\gm.bmp"); //50




    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(SpecialInput);
    //sndPlaySound("woo.wav",SND_ASYNC);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    //PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
    glutMainLoop();


    return 0;
}

