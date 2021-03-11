#include "game.h"
using namespace std;

/*
author dan pemilik : Kresna Bayu Sanyoto 181511051 JTK POLBAN
dibuat pada : 27 Januari 2021
matkul : komputer grafik
*/

bool enemyForward = true;
GLint counter=0;
GLint counter2=0;
dSpaceID collision;
dContactGeom contacts[20];
GLint camAngle=0;

void init();
void physic();
void display();
void reshape(int w, int h);
void time(int x);
void specialKey(int key, int x, int y);
void mouseMovement(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void scroll (int button, int dir, int x, int y);
GLuint loadTexture(const char* filename);
static void nearCallback (void *, dGeomID o1, dGeomID o2);

int main(int argc, char** argv)
{
    cout << "List funngsi keyboard :\n";
    cout << "w = Maju\n";
    cout << "s = Mundur\n";
    cout << "a = Geser kiri\n";
    cout << "d = Geser kanan\n";
    cout << "m = Menembak\n";
    cout << "c = Camera Angle\n";
    cout << "===Kresna Bayu S. 181511051===\n";
    cout << "Pastikan capslock tidak menyala\n\n\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("EAS-Kresna Bayu Sanyoto-181511051");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, time, 0);
    init();
    glutMainLoop();
    return 0;
}
coord rotation(coord pointOld, coord rotationPoint, int angle)
{
    GLfloat rad = angle*((22.0f/7.0f)/180.0f);
    coord result;
    GLfloat x1 = pointOld.z-rotationPoint.z, y1 = pointOld.x-rotationPoint.x;
    result.z=x1*cos(rad)-y1*sin(rad);
    result.x=x1*sin(rad)+y1*cos(rad);
    result.z+=rotationPoint.z;
    result.x+=rotationPoint.x;

    return result;
}
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //env texture
    grassTexture=loadTexture("env_texture/grass.bmp");
    skyTexture=loadTexture("env_texture/sky.bmp");
    crownTexture=loadTexture("env_texture/crowd.bmp");
    wallTexture=loadTexture("env_texture/wall.bmp");
    //car texture
    hoodTexture=loadTexture("car_texture/hood_texture.bmp");
    backSposorTexture=loadTexture("car_texture/back_sponsor.bmp");
    //kontol
    dInitODE2(0);
    collision=dHashSpaceCreate(0);
    // Player section
    carPlayer.geometri = dCreateBox(0,6,8,21);
    dGeomSetPosition(carPlayer.geometri, carPlayer.pos.x, carPlayer.pos.y, carPlayer.pos.z);
    carPlayer.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(carPlayer.space, 0);
    dSpaceAdd(carPlayer.space, carPlayer.geometri);
    // Enemy section
    carEnemy[0].pos.z=80;
    carEnemy[0].geometri = dCreateBox(0,21,8,6);
    dGeomSetPosition(carEnemy[0].geometri, carEnemy[0].pos.x, carEnemy[0].pos.y, carEnemy[0].pos.z);
    carEnemy[0].space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(carEnemy[0].space, 0);
    dSpaceAdd(carEnemy[0].space, carEnemy[0].geometri);
    // Missile section
    carPlayer.carMissile.pos.x=300.0;
    carPlayer.carMissile.pos.y=0.0;
    carPlayer.carMissile.pos.z=300.0;
    carPlayer.carMissile.geometri = dCreateBox(0,2,2,2);
    dGeomSetPosition(carPlayer.carMissile.geometri, carPlayer.carMissile.pos.x+3, carPlayer.carMissile.pos.y, carPlayer.carMissile.pos.z+3);
    carPlayer.carMissile.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(carPlayer.carMissile.space, 0);
    dSpaceAdd(carPlayer.carMissile.space, carPlayer.carMissile.geometri);
    // Enemy missile section
    carEnemy[0].carMissile.pos.x=300.0;
    carEnemy[0].carMissile.pos.y=0.0;
    carEnemy[0].carMissile.pos.z=300.0;
    carEnemy[0].carMissile.geometri = dCreateBox(0,2,2,2);
    dGeomSetPosition(carEnemy[0].carMissile.geometri, carEnemy[0].carMissile.pos.x+3, carEnemy[0].carMissile.pos.y, carEnemy[0].carMissile.pos.z-4);
    carEnemy[0].carMissile.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(carEnemy[0].carMissile.space, 0);
    dSpaceAdd(carEnemy[0].carMissile.space, carEnemy[0].carMissile.geometri);
    // Skybox section depan
    skyboxGame.depan.sisi.x=0.0;
    skyboxGame.depan.sisi.y=0.0;
    skyboxGame.depan.sisi.z=120.0;
    skyboxGame.depan.geometri = dCreateBox(0,239,10,1);
    dGeomSetPosition(skyboxGame.depan.geometri, skyboxGame.depan.sisi.x, skyboxGame.depan.sisi.y, skyboxGame.depan.sisi.z);
    skyboxGame.depan.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(skyboxGame.depan.space, 0);
    dSpaceAdd(skyboxGame.depan.space, skyboxGame.depan.geometri);
    // Skybox section belakang
    skyboxGame.belakang.sisi.x=0.0;
    skyboxGame.belakang.sisi.y=0.0;
    skyboxGame.belakang.sisi.z=-120.0;
    skyboxGame.belakang.geometri = dCreateBox(0,239,10,1);
    dGeomSetPosition(skyboxGame.belakang.geometri, skyboxGame.belakang.sisi.x, skyboxGame.belakang.sisi.y, skyboxGame.belakang.sisi.z);
    skyboxGame.belakang.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(skyboxGame.belakang.space, 0);
    dSpaceAdd(skyboxGame.belakang.space, skyboxGame.belakang.geometri);
    // Skybox section kanan
    skyboxGame.kanan.sisi.x=-120.0;
    skyboxGame.kanan.sisi.y=0.0;
    skyboxGame.kanan.sisi.z=0.0;
    skyboxGame.kanan.geometri = dCreateBox(0,1,10,239);
    dGeomSetPosition(skyboxGame.kanan.geometri, skyboxGame.kanan.sisi.x, skyboxGame.kanan.sisi.y, skyboxGame.kanan.sisi.z);
    skyboxGame.kanan.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(skyboxGame.kanan.space, 0);
    dSpaceAdd(skyboxGame.kanan.space, skyboxGame.kanan.geometri);
    // Skybox section kiri
    skyboxGame.kiri.sisi.x=120.0;
    skyboxGame.kiri.sisi.y=0.0;
    skyboxGame.kiri.sisi.z=0.0;
    skyboxGame.kiri.geometri = dCreateBox(0,1,10,239);
    dGeomSetPosition(skyboxGame.kiri.geometri, skyboxGame.kiri.sisi.x, skyboxGame.kiri.sisi.y, skyboxGame.kiri.sisi.z);
    skyboxGame.kiri.space =  dSimpleSpaceCreate(collision);
    dSpaceSetCleanup(skyboxGame.kiri.space, 0);
    dSpaceAdd(skyboxGame.kiri.space, skyboxGame.kiri.geometri);
    // set warna enemy
    carEnemy[0].color.x=0.580;
    carEnemy[0].color.y=1;
    carEnemy[0].color.z=0.541;
}
void physic(){
    // car movement logic
    if(carPlayer.status==true){
        carPlayer.pos.z+= carPlayer.movement.z;
        carPlayer.pos.x+= carPlayer.movement.x;
    }

    if(carPlayer.movement.z!=0){
        if(carPlayer.movement.z<0){
            carPlayer.movement.z+=0.005;
        }else{
            carPlayer.movement.z-=0.005;
        }
    }
    if(carPlayer.movement.z>=0.6)
    {
        carPlayer.movement.z=0.6;
    }
    if(carPlayer.movement.z<=-0.3)
    {
        carPlayer.movement.z= -0.3;
    }
    if(carPlayer.movement.x!=0){
        if(carPlayer.movement.x<0){
            carPlayer.movement.x+=0.005;
        }else{
            carPlayer.movement.x-=0.005;
        }
    }
    if(carPlayer.movement.x>=0.3)
    {
        carPlayer.movement.x=0.3;
    }
    if(carPlayer.movement.x<=-0.3)
    {
        carPlayer.movement.x= -0.3;
    }
    // car missile logic
    if(carPlayer.carMissile.status==true){
        carPlayer.carMissile.acceleration+=0.5;
    }
    if(carPlayer.carMissile.acceleration==55&&carPlayer.carMissile.pos.z!=300){
        carPlayer.carMissile.pos.z=300.0;
        carPlayer.carMissile.pos.x=300.0;
        carPlayer.carMissile.acceleration=0;
        carPlayer.carMissile.status=false;
    }
    // level logic
    if(carEnemy[0].status==false){
        if(carEnemy[0].level<3.0){
            carEnemy[0].level++;
            carEnemy[0].status=true;
        }else{
            carEnemy[0].status=false;
        }
    }

    for(int i=0; i<=0 ;i++){
        if(carEnemy[i].carMissile.status==true){
            if(carEnemy[i].carMissile.pos.z==300.0&&carEnemy[i].carMissile.pos.x==300.0){
                carEnemy[i].carMissile.pos.z=carEnemy[i].pos.z;
                carEnemy[i].carMissile.pos.x=carEnemy[i].pos.x;
            }
        }
            //enemy missile logic
        if(counter==(120/carEnemy[i].level)&&carEnemy[i].status==true){
            carEnemy[i].carMissile.status=true;
            counter=0;
        }
        if(carEnemy[i].carMissile.status==true){
            carEnemy[i].carMissile.acceleration+=0.5;
        }
        if(carEnemy[i].carMissile.acceleration==55&&carEnemy[i].carMissile.pos.z!=300){
            carEnemy[i].carMissile.pos.z=300.0;
            carEnemy[i].carMissile.pos.x=300.0;
            carEnemy[i].carMissile.acceleration=0;
            carEnemy[i].carMissile.status=false;
        }

        //enemy car movement logic
        if(carEnemy[i].status==true){
            if(enemyForward==true){
                if(carEnemy[i].level==1.0){
                    carEnemy[i].pos.x+=(0.2);
                }
                if(carEnemy[i].level==2.0){
                    carEnemy[i].pos.x+=(0.4);
                }
                if(carEnemy[i].level==3.0){
                    carEnemy[i].pos.x+=(0.6);
                }

            }else{
                if(carEnemy[i].level==1.0){
                    carEnemy[i].pos.x-=(0.2);
                }
                if(carEnemy[i].level==2.0){
                    carEnemy[i].pos.x-=(0.4);
                }
                if(carEnemy[i].level==3.0){
                    carEnemy[i].pos.x-=(0.6);
                }
            }
        if(carEnemy[i].pos.x>=60){enemyForward=false;}
        if(carEnemy[i].pos.x<=-60) {enemyForward=true;}
        }
    }


    //reset geomposition
    dGeomSetPosition(carPlayer.geometri, carPlayer.pos.x, carPlayer.pos.y, carPlayer.pos.z);
    dGeomSetPosition(carEnemy[0].geometri, carEnemy[0].pos.x, carEnemy[0].pos.y, carEnemy[0].pos.z);
    dGeomSetPosition(carPlayer.carMissile.geometri, carPlayer.carMissile.pos.x+3, carPlayer.carMissile.pos.y, carPlayer.carMissile.pos.z+carPlayer.carMissile.acceleration+3);
    dGeomSetPosition(carEnemy[0].carMissile.geometri, carEnemy[0].carMissile.pos.x+3, carEnemy[0].carMissile.pos.y, carEnemy[0].carMissile.pos.z-4-carEnemy[0].carMissile.acceleration);
    counter++;
    //Tindakan jika terjadi collision
    if(dCollide(carPlayer.geometri, carEnemy[0].geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.status=false;
        carEnemy[0].status=false;
    }
    if(dCollide(carPlayer.geometri, carEnemy[0].carMissile.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.status=false;
        printf("player hit\n");
    }
    if(dCollide(carEnemy[0].geometri, carPlayer.carMissile.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        counter2++;
    }
    if((counter2%20==0)&&(counter2!=0)){
        carEnemy[0].status=false;
        printf("enemy hit\n");
    }
    if(dCollide(carPlayer.geometri, skyboxGame.depan.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.movement.z=0.0;
    }
    if(dCollide(carPlayer.geometri, skyboxGame.belakang.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.movement.z=0.0;
    }
    if(dCollide(carPlayer.geometri, skyboxGame.kiri.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.movement.x=0.0;
    }
    if(dCollide(carPlayer.geometri, skyboxGame.kanan.geometri, 1, &contacts[0], sizeof(dContactGeom)) > 0){
        carPlayer.movement.x=0.0;
    }
    //dSpaceCollide (collision,0,&nearCallback);
    //printf("%d \n", carEnemy.status);
    printf("level %f counter %i\n",carEnemy[0].level,counter2);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(camAngle==0){
        gluLookAt(0.0+carPlayer.pos.x, 15.0+carPlayer.pos.y, -30.0+carPlayer.pos.z,  0.0+carPlayer.pos.x, 0.0+carPlayer.pos.y, 10.0+carPlayer.pos.z,  0.0, 1.0, 0.0);
    }
    if(camAngle==1){
        gluLookAt(0.0+carPlayer.pos.x, 5.0+carPlayer.pos.y, 10.0+carPlayer.pos.z,  0.0+carPlayer.pos.x, 0.0+carPlayer.pos.y, 40.0+carPlayer.pos.z,  0.0, 1.0, 0.0);
    }
    if(camAngle==2){
        gluLookAt(50.0, 50.0, -85.0,  0.0, 0.0, 10.0,  0.0, 1.0, 0.0);
    }
    if(camAngle==3){
        gluLookAt(0.0, 50.0, -85.0,  0.0, 0.0, 10.0,  0.0, 1.0, 0.0);
    }
    if(camAngle==4){
        gluLookAt(-50.0, 50.0, -85.0,  0.0, 0.0, 10.0,  0.0, 1.0, 0.0);
    }
    if(camAngle==5){
        gluLookAt(150.0, 50.0, 0.0,  0.0, 0.0, 10.0,  0.0, 1.0, 0.0);
    }

    carModel(carPlayer);
    carModelEnemy(carEnemy[0]);

    arena();

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 320.0f);
    glMatrixMode(GL_MODELVIEW);
}
void time(int x)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, time, 0);
    physic();
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key){
    case 'w':
        {
            if(dCollide(carPlayer.geometri, skyboxGame.depan.geometri, 1, &contacts[0], sizeof(dContactGeom)) == 0){
                carPlayer.movement.z+=0.05;
            }
            glutPostRedisplay();

            break;
        }
    case 's':
        {
            if(dCollide(carPlayer.geometri, skyboxGame.belakang.geometri, 1, &contacts[0], sizeof(dContactGeom)) == 0){
                carPlayer.movement.z-=0.05;
            }
            glutPostRedisplay();
            break;
        }
    case 'a':
        {
            if(dCollide(carPlayer.geometri, skyboxGame.kiri.geometri, 1, &contacts[0], sizeof(dContactGeom)) == 0){
                carPlayer.movement.x+=0.05;
            }
            glutPostRedisplay();
            break;
        }
    case 'd':
        {
            if(dCollide(carPlayer.geometri, skyboxGame.kanan.geometri, 1, &contacts[0], sizeof(dContactGeom)) == 0){
                carPlayer.movement.x-=0.05;
            }
            glutPostRedisplay();
            break;
        }
    case 'm':
        {
            carPlayer.carMissile.status = true;
            if(carPlayer.carMissile.pos.z==300.0&&carPlayer.carMissile.pos.x==300.0){
                carPlayer.carMissile.pos.z=carPlayer.pos.z;
                carPlayer.carMissile.pos.x=carPlayer.pos.x;
            }
            glutPostRedisplay();
            break;
        }
    case 'c':
        {
            camAngle++;
            if(camAngle>5){
                camAngle=0;
            }
            glutPostRedisplay();
            break;
        }
    }
}
GLuint loadTexture(const char* filename)
{
	BmpLoader bl(filename);
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bl.iWidth, bl.iHeight,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bl.textureData);
	return textureId;
}
static void nearCallback (void *, dGeomID o1, dGeomID o2)
{
    int i,n;

    const int N = 4;
    dContact contact[N];
    n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
    if (n > 0) {
        for (i=0; i<n; i++) {
            printf("contact (%f, %f) => pos: (%f, %f, %f), depth: %f, side1: %d, side2: %d, normal: (%f, %f, %f)\n",
              dGeomGetPosition(contact[i].geom.g1)[0],
              dGeomGetPosition(contact[i].geom.g2)[0],
              contact[i].geom.pos[0],
              contact[i].geom.pos[1],
              contact[i].geom.pos[2],
              contact[i].geom.depth,
              contact[i].geom.side1,
              contact[i].geom.side2,
              contact[i].geom.normal[0],
              contact[i].geom.normal[1],
              contact[i].geom.normal[2]
            );
        }
    }
}
