#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <ode/ode.h>
#include "BmpLoader.h"
#include <iostream>

typedef struct{
    GLfloat x,y,z = 0.0;
}coord;

typedef struct{
    GLfloat acceleration= 0.0;
    bool status =false;
    coord pos;
    dSpaceID space;
    dGeomID geometri;
}missile;

typedef struct{
    coord pos;
    coord movement;
    missile carMissile;
    bool status=true;
    coord color;
    GLfloat level=1.0;
    dSpaceID space;
    dGeomID geometri;
}car;

typedef struct{
    coord sisi;
    dSpaceID space;
    dGeomID geometri;
}skyboxComponent;

typedef struct{
    skyboxComponent kanan;
    skyboxComponent kiri;
    skyboxComponent depan;
    skyboxComponent belakang;
}skybox;

extern GLuint grassTexture, hoodTexture, backSposorTexture, skyTexture, crownTexture, wallTexture;
extern car carPlayer;
extern car carEnemy[1];
extern skybox skyboxGame;

void carModel(car mobil);
void carModelEnemy(car mobil);
void arena();
