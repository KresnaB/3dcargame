#include "game.h"
GLuint grassTexture, hoodTexture, backSposorTexture, skyTexture, crownTexture, wallTexture;
car carPlayer;
car carEnemy[1];
skybox skyboxGame;
void carModel(car mobil)
{
    glPushMatrix();
    glTranslatef(mobil.pos.x,mobil.pos.y,mobil.pos.z);
    //glRotatef(spin_y, 0.0, 1.0, 0.0);


    // badan mobil bagian depan
    glColor3f(0.956, 0.592, 0.203);
    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(3.0,1.0,8.0);
        glVertex3f(2.8,3.5,10.5);
        glVertex3f(3.0,4.0,8.0);
        glVertex3f(0.0,3.5,10.7);
        glVertex3f(0.0,4.0,8.0);
        glVertex3f(-2.8,3.5,10.5);
        glVertex3f(-3.0,4.0,8.0);
        glVertex3f(-2.8,1.0,10.5);
        glVertex3f(-3.0,1.0,8.0);
        glVertex3f(0.0,1.1,10.7);
        glVertex3f(0.0,1.1,8.0);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(3.0,1.0,8.0);
    glEnd();
    // depan mobil | bagian bumper depan
    glColor3f(0.964, 0.639, 0.298);
    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(2.8,3.5,10.5);
        glVertex3f(0.0,1.1,10.7);
        glVertex3f(0.0,3.5,10.7);
        glVertex3f(-2.8,1.0,10.5);
        glVertex3f(-2.8,3.5,10.5);
    glEnd();
    //lampu depan
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(2.6,3.2,10.55);
        glVertex3f(1.6,3.2,10.6);
        glVertex3f(1.6,2.7,10.6);
        glVertex3f(2.6,2.7,10.55);

        glVertex3f(-2.6,3.2,10.55);
        glVertex3f(-1.6,3.2,10.6);
        glVertex3f(-1.6,2.7,10.6);
        glVertex3f(-2.6,2.7,10.55);
    glEnd();
    // hood
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, hoodTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.956, 0.541, 0.101);
    glBegin(GL_QUADS);
        glTexCoord3f(1,0,0); glVertex3f(3.0,4.0,8.0);
        glTexCoord3f(1,1,0); glVertex3f(3.0,4.0,4.0);
        glTexCoord3f(0,1,0); glVertex3f(-3.0,4.0,4.0);
        glTexCoord3f(0,0,0); glVertex3f(-3.0,4.0,8.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //panel body di atas ban kiri depan
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-3.0,1.0,8.0);
        glVertex3f(-3.0,4.0,8.0);
        glVertex3f(-3.0,2.5,7.0);
        glVertex3f(-3.0,4.0,6.0);
        glVertex3f(-3.0,2.5,5.0);
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(-3.0,1.0,4.0);
    glEnd();
    //panel body di atas ban kanan depan
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(3.0,1.0,8.0);
        glVertex3f(3.0,4.0,8.0);
        glVertex3f(3.0,2.5,7.0);
        glVertex3f(3.0,4.0,6.0);
        glVertex3f(3.0,2.5,5.0);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,1.0,4.0);
    glEnd();

    glBegin(GL_QUADS);
        // rangka kaca depan
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(-3.0,6.0,1.0);
        // kaca depan
        glColor3f(0.317, 0.309, 0.301);
        glVertex3f(-2.8,4.0,4.08);
        glVertex3f(2.8,4.0,4.08);
        glVertex3f(2.8,5.9,1.14);
        glVertex3f(-2.8,5.9,1.14);
        //atap mobil
        glColor3f(0.913, 0.494, 0.047);
        glVertex3f(-3.0,6.0,1.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(-3.0,6.0,-3.0);
    glEnd();


    //pintu sebelah kiri
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.960, 0.6, 0.219);
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(-3.0,6.0,1.0);
        glVertex3f(-3.0,6.0,-3.0);
        glVertex3f(-3.0,4.5,-5.0);
        glVertex3f(-3.0,2.5,-5.0);
        glVertex3f(-3.0,1.0,-4.0);
        glVertex3f(-3.0,1.0,1.5);
        glVertex3f(-3.0,1.0,4.0);
    glEnd();
    //pintu sebelah kanan
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,1.0,-4.0);
        glVertex3f(3.0,1.0,1.5);
        glVertex3f(3.0,1.0,4.0);
    glEnd();
    glBegin(GL_QUADS);
        //bawah mobil
        glVertex3f(-3.0,1.0,4.0);
        glVertex3f(3.0,1.0,4.0);
        glVertex3f(3.0,1.0,-4.0);
        glVertex3f(-3.0,1.0,-4.0);
        // kaca kiri depan
        glColor3f(0.317, 0.309, 0.301);
        glVertex3f(-3.1,4.0,3.5);
        glVertex3f(-3.1,5.8,0.8);
        glVertex3f(-3.1,5.8,-0.8);
        glVertex3f(-3.1,4.0,-0.8);
        // kaca kanan depan
        glVertex3f(3.1,4.0,3.5);
        glVertex3f(3.1,5.8,0.8);
        glVertex3f(3.1,5.8,-1.0);
        glVertex3f(3.1,4.0,-1.0);
        //handle
        glVertex3f(3.1,3.5,0.0);
        glVertex3f(3.1,3.5,0.8);
        glVertex3f(3.1,3.2,0.8);
        glVertex3f(3.1,3.2,0.0);

        glVertex3f(-3.1,3.5,0.0);
        glVertex3f(-3.1,3.5,0.8);
        glVertex3f(-3.1,3.2,0.8);
        glVertex3f(-3.1,3.2,0.0);
        // kaca belakang
        glVertex3f(-2.8,5.9,-3.3);
        glVertex3f(2.8,5.9,-3.3);
        glVertex3f(2.8,4.5,-5.0);
        glVertex3f(-2.8,4.5,-5.0);
        //rangka kaca belakang
        glColor3f(0.956, 0.560, 0.145);
        glVertex3f(-3.0,6.0,-3.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(-3.0,4.5,-5.0);

    glEnd();
    //panel body di atas ban kelakang
    glBegin(GL_QUAD_STRIP);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,2.5,-7.5);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(3.0,4.0,-7.0);
        glVertex3f(-3.0,4.5,-5.0);
        glVertex3f(-3.0,4.0,-7.0);
        glVertex3f(-3.0,2.5,-5.0);
        glVertex3f(-3.0,2.5,-7.5);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,2.5,-7.5);
    glEnd();
    //bodi belakang
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.964, 0.6, 0.215);
        glVertex3f(3.0,1.0,-8.0);
        glVertex3f(3.0,1.5,-10.0);
        glVertex3f(3.0,4.0,-7.0);
        glVertex3f(3.0,4.5,-10.5);
        glVertex3f(-3.0,4.0,-7.0);
        glVertex3f(-3.0,4.5,-10.5);
        glVertex3f(-3.0,1.0,-8.0);
        glVertex3f(-3.0,1.5,-10.0);
        glVertex3f(3.0,1.0,-8.0);
        glVertex3f(3.0,1.5,-10.0);
    glEnd();

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backSposorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        //bumper belakang
        glColor3f(0.964, 0.631, 0.274);
        glTexCoord3f(0,0,0); glVertex3f(3.0,1.5,-10.0);
        glTexCoord3f(1,0,0); glVertex3f(-3.0,1.5,-10.0);
        glTexCoord3f(1,1,0); glVertex3f(-3.0,4.5,-10.5);
        glTexCoord3f(0,1,0); glVertex3f(3.0,4.5,-10.5);
        //lampu belakang
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-2.6,3.5,-10.4);
        glVertex3f(-1.2,3.5,-10.4);
        glVertex3f(-1.2,4.2,-10.5);
        glVertex3f(-2.6,4.2,-10.5);

        glVertex3f(2.6,3.5,-10.4);
        glVertex3f(1.2,3.5,-10.4);
        glVertex3f(1.2,4.2,-10.5);
        glVertex3f(2.6,4.2,-10.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //ban
    glColor3f(0.470, 0.517, 0.529);
    //tire front right
    glTranslatef(3.0f, 1.0f, 6.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire front left
    glTranslatef(-6.0f, 0.0f, 0.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire back left
    glTranslatef(0.0f, 0.0f, -12.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire back right
    glTranslatef(6.0f, 0.0f, 0.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    glBegin(GL_QUADS);
        //turret
        glVertex3f(1,4.5,3);
        glVertex3f(1,5.5,3);
        glVertex3f(0,5.5,3);
        glVertex3f(0,4.5,3);

        glVertex3f(1,4.5,7);
        glVertex3f(1,5.5,7);
        glVertex3f(0,5.5,7);
        glVertex3f(0,4.5,7);

        glVertex3f(1,4.5,3);
        glVertex3f(1,5.5,3);
        glVertex3f(1,5.5,7);
        glVertex3f(1,4.5,7);

        glVertex3f(0,4.5,3);
        glVertex3f(0,5.5,3);
        glVertex3f(0,5.5,7);
        glVertex3f(0,4.5,7);

        glVertex3f(0,5.5,3);
        glVertex3f(0,5.5,7);
        glVertex3f(1,5.5,7);
        glVertex3f(1,5.5,3);

    glEnd();
    glPushMatrix();
    if(mobil.carMissile.status==true){
        glTranslatef(-mobil.pos.x,mobil.pos.y,-mobil.pos.z);
        glTranslatef(mobil.carMissile.pos.x,0,mobil.carMissile.pos.z+mobil.carMissile.acceleration+3);

        glBegin(GL_QUADS);
            glColor3f(1, 0.058, 0.098);
            glVertex3f(0,4.5,4);
            glVertex3f(0,5.5,4);
            glVertex3f(1,5.5,4);
            glVertex3f(1,4.5,4);

            glVertex3f(0,4.5,3);
            glVertex3f(0,5.5,3);
            glVertex3f(1,5.5,3);
            glVertex3f(1,4.5,3);

            glVertex3f(0,4.5,3);
            glVertex3f(0,5.5,3);
            glVertex3f(0,5.5,4);
            glVertex3f(0,4.5,4);

            glVertex3f(1,4.5,3);
            glVertex3f(1,5.5,3);
            glVertex3f(1,5.5,4);
            glVertex3f(1,4.5,4);

            glVertex3f(1,5.5,3);
            glVertex3f(1,5.5,4);
            glVertex3f(0,5.5,4);
            glVertex3f(0,5.5,3);
        glEnd();
    }
    glPopMatrix();
    glPopMatrix();
}
void carModelEnemy(car mobil)
{
    glPushMatrix();
    glTranslatef(mobil.pos.x,mobil.pos.y,mobil.pos.z);
    glRotatef(-90, 0.0, 1.0, 0.0);
    //glRotatef(spin_y, 0.0, 1.0, 0.0);


    // badan mobil bagian depan
    glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(3.0,1.0,8.0);
        glVertex3f(2.8,3.5,10.5);
        glVertex3f(3.0,4.0,8.0);
        glVertex3f(0.0,3.5,10.7);
        glVertex3f(0.0,4.0,8.0);
        glVertex3f(-2.8,3.5,10.5);
        glVertex3f(-3.0,4.0,8.0);
        glVertex3f(-2.8,1.0,10.5);
        glVertex3f(-3.0,1.0,8.0);
        glVertex3f(0.0,1.1,10.7);
        glVertex3f(0.0,1.1,8.0);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(3.0,1.0,8.0);
    glEnd();
    // depan mobil | bagian bumper depan
    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.8,1.0,10.5);
        glVertex3f(2.8,3.5,10.5);
        glVertex3f(0.0,1.1,10.7);
        glVertex3f(0.0,3.5,10.7);
        glVertex3f(-2.8,1.0,10.5);
        glVertex3f(-2.8,3.5,10.5);
    glEnd();
    //lampu depan
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(2.6,3.2,10.55);
        glVertex3f(1.6,3.2,10.6);
        glVertex3f(1.6,2.7,10.6);
        glVertex3f(2.6,2.7,10.55);

        glVertex3f(-2.6,3.2,10.55);
        glVertex3f(-1.6,3.2,10.6);
        glVertex3f(-1.6,2.7,10.6);
        glVertex3f(-2.6,2.7,10.55);
    glEnd();
    // hood
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, hoodTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
    glBegin(GL_QUADS);
        glTexCoord3f(1,0,0); glVertex3f(3.0,4.0,8.0);
        glTexCoord3f(1,1,0); glVertex3f(3.0,4.0,4.0);
        glTexCoord3f(0,1,0); glVertex3f(-3.0,4.0,4.0);
        glTexCoord3f(0,0,0); glVertex3f(-3.0,4.0,8.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //panel body di atas ban kiri depan
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-3.0,1.0,8.0);
        glVertex3f(-3.0,4.0,8.0);
        glVertex3f(-3.0,2.5,7.0);
        glVertex3f(-3.0,4.0,6.0);
        glVertex3f(-3.0,2.5,5.0);
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(-3.0,1.0,4.0);
    glEnd();
    //panel body di atas ban kanan depan
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(3.0,1.0,8.0);
        glVertex3f(3.0,4.0,8.0);
        glVertex3f(3.0,2.5,7.0);
        glVertex3f(3.0,4.0,6.0);
        glVertex3f(3.0,2.5,5.0);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,1.0,4.0);
    glEnd();

    glBegin(GL_QUADS);
        // rangka kaca depan
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(-3.0,6.0,1.0);
        // kaca depan
        glColor3f(0.317, 0.309, 0.301);
        glVertex3f(-2.8,4.0,4.08);
        glVertex3f(2.8,4.0,4.08);
        glVertex3f(2.8,5.9,1.14);
        glVertex3f(-2.8,5.9,1.14);
        //atap mobil
        glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
        glVertex3f(-3.0,6.0,1.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(-3.0,6.0,-3.0);
    glEnd();


    //pintu sebelah kiri
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-3.0,4.0,4.0);
        glVertex3f(-3.0,6.0,1.0);
        glVertex3f(-3.0,6.0,-3.0);
        glVertex3f(-3.0,4.5,-5.0);
        glVertex3f(-3.0,2.5,-5.0);
        glVertex3f(-3.0,1.0,-4.0);
        glVertex3f(-3.0,1.0,1.5);
        glVertex3f(-3.0,1.0,4.0);
    glEnd();
    //pintu sebelah kanan
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(3.0,4.0,4.0);
        glVertex3f(3.0,6.0,1.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,1.0,-4.0);
        glVertex3f(3.0,1.0,1.5);
        glVertex3f(3.0,1.0,4.0);
    glEnd();
    glBegin(GL_QUADS);
        //bawah mobil
        glVertex3f(-3.0,1.0,4.0);
        glVertex3f(3.0,1.0,4.0);
        glVertex3f(3.0,1.0,-4.0);
        glVertex3f(-3.0,1.0,-4.0);
        // kaca kiri depan
        glColor3f(0.317, 0.309, 0.301);
        glVertex3f(-3.1,4.0,3.5);
        glVertex3f(-3.1,5.8,0.8);
        glVertex3f(-3.1,5.8,-0.8);
        glVertex3f(-3.1,4.0,-0.8);
        // kaca kanan depan
        glVertex3f(3.1,4.0,3.5);
        glVertex3f(3.1,5.8,0.8);
        glVertex3f(3.1,5.8,-1.0);
        glVertex3f(3.1,4.0,-1.0);
        //handle
        glVertex3f(3.1,3.5,0.0);
        glVertex3f(3.1,3.5,0.8);
        glVertex3f(3.1,3.2,0.8);
        glVertex3f(3.1,3.2,0.0);

        glVertex3f(-3.1,3.5,0.0);
        glVertex3f(-3.1,3.5,0.8);
        glVertex3f(-3.1,3.2,0.8);
        glVertex3f(-3.1,3.2,0.0);
        // kaca belakang
        glVertex3f(-2.8,5.9,-3.3);
        glVertex3f(2.8,5.9,-3.3);
        glVertex3f(2.8,4.5,-5.0);
        glVertex3f(-2.8,4.5,-5.0);
        //rangka kaca belakang
        glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
        glVertex3f(-3.0,6.0,-3.0);
        glVertex3f(3.0,6.0,-3.0);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(-3.0,4.5,-5.0);

    glEnd();
    //panel body di atas ban kelakang
    glBegin(GL_QUAD_STRIP);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,2.5,-7.5);
        glVertex3f(3.0,4.5,-5.0);
        glVertex3f(3.0,4.0,-7.0);
        glVertex3f(-3.0,4.5,-5.0);
        glVertex3f(-3.0,4.0,-7.0);
        glVertex3f(-3.0,2.5,-5.0);
        glVertex3f(-3.0,2.5,-7.5);
        glVertex3f(3.0,2.5,-5.0);
        glVertex3f(3.0,2.5,-7.5);
    glEnd();
    //bodi belakang
    glBegin(GL_QUAD_STRIP);
        glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
        glVertex3f(3.0,1.0,-8.0);
        glVertex3f(3.0,1.5,-10.0);
        glVertex3f(3.0,4.0,-7.0);
        glVertex3f(3.0,4.5,-10.5);
        glVertex3f(-3.0,4.0,-7.0);
        glVertex3f(-3.0,4.5,-10.5);
        glVertex3f(-3.0,1.0,-8.0);
        glVertex3f(-3.0,1.5,-10.0);
        glVertex3f(3.0,1.0,-8.0);
        glVertex3f(3.0,1.5,-10.0);
    glEnd();

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backSposorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        //bumper belakang
        glColor3f(mobil.color.x, mobil.color.y, mobil.color.z);
        glTexCoord3f(0,0,0); glVertex3f(3.0,1.5,-10.0);
        glTexCoord3f(1,0,0); glVertex3f(-3.0,1.5,-10.0);
        glTexCoord3f(1,1,0); glVertex3f(-3.0,4.5,-10.5);
        glTexCoord3f(0,1,0); glVertex3f(3.0,4.5,-10.5);
        //lampu belakang
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-2.6,3.5,-10.4);
        glVertex3f(-1.2,3.5,-10.4);
        glVertex3f(-1.2,4.2,-10.5);
        glVertex3f(-2.6,4.2,-10.5);

        glVertex3f(2.6,3.5,-10.4);
        glVertex3f(1.2,3.5,-10.4);
        glVertex3f(1.2,4.2,-10.5);
        glVertex3f(2.6,4.2,-10.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //ban
    glColor3f(0.470, 0.517, 0.529);
    //tire front right
    glTranslatef(3.0f, 1.0f, 6.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire front left
    glTranslatef(-6.0f, 0.0f, 0.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire back left
    glTranslatef(0.0f, 0.0f, -12.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    //tire back right
    glTranslatef(6.0f, 0.0f, 0.0f);
    //glTranslatef(carPos.x, 0.0f, carPos.z);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.75,0.75,10,10);
    glRotatef(-90,0,1,0);
    //glTranslatef(-carPos.x, 0.0f, -carPos.z);
    glBegin(GL_QUADS);
        glVertex3f(0,4.5,3);
        glVertex3f(0,5.5,3);
        glVertex3f(-8,5.5,3);
        glVertex3f(-8,4.5,3);

        glVertex3f(0,4.5,4);
        glVertex3f(0,5.5,4);
        glVertex3f(-8,5.5,4);
        glVertex3f(-8,4.5,4);

        glVertex3f(0,4.5,3);
        glVertex3f(0,5.5,3);
        glVertex3f(0,5.5,4);
        glVertex3f(0,4.5,4);

        glVertex3f(-8,4.5,3);
        glVertex3f(-8,5.5,3);
        glVertex3f(-8,5.5,4);
        glVertex3f(-8,4.5,4);

        glVertex3f(0,5.5,3);
        glVertex3f(0,5.5,4);
        glVertex3f(-8,5.5,4);
        glVertex3f(-8,5.5,3);

    glEnd();
    if(mobil.carMissile.status==true){
        glRotatef(90,0,1,0);
        glTranslatef(-mobil.pos.x,mobil.pos.y,-mobil.pos.z);
        glTranslatef(mobil.carMissile.pos.x+4,0,mobil.carMissile.pos.z-mobil.carMissile.acceleration-10);


        glBegin(GL_QUADS);
            glColor3f(1, 0.058, 0.098);
            glVertex3f(-8,4.5,4);
            glVertex3f(-8,5.5,4);
            glVertex3f(-7,5.5,4);
            glVertex3f(-7,4.5,4);

            glVertex3f(-8,4.5,3);
            glVertex3f(-8,5.5,3);
            glVertex3f(-7,5.5,3);
            glVertex3f(-7,4.5,3);

            glVertex3f(-8,4.5,3);
            glVertex3f(-8,5.5,3);
            glVertex3f(-8,5.5,4);
            glVertex3f(-8,4.5,4);

            glVertex3f(-7,4.5,3);
            glVertex3f(-7,5.5,3);
            glVertex3f(-7,5.5,4);
            glVertex3f(-7,4.5,4);

            glVertex3f(-7,5.5,3);
            glVertex3f(-7,5.5,4);
            glVertex3f(-8,5.5,4);
            glVertex3f(-8,5.5,3);
        glEnd();
    }
    glPopMatrix();
}
void arena()
{
    glPushMatrix();
    //grass
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
        glTexCoord3f(0,20,0); glVertex3f(150,-0.1,150);
        glTexCoord3f(0,0,0); glVertex3f(150,-0.1,-150);
        glTexCoord3f(20,0,0); glVertex3f(-150,-0.1,-150);
        glTexCoord3f(20,20,0); glVertex3f(-150,-0.1,150);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //sky
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, skyTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1,1,1);
        glTexCoord3f(0,0,0); glVertex3f(150,0,150);
        glTexCoord3f(0,1,0); glVertex3f(150,100,150);
        glTexCoord3f(1,0,0); glVertex3f(-150,0,150);
        glTexCoord3f(1,1,0); glVertex3f(-150,100,150);
        glTexCoord3f(2,0,0); glVertex3f(-150,0,-150);
        glTexCoord3f(2,1,0); glVertex3f(-150,100,-150);
        glTexCoord3f(3,0,0); glVertex3f(150,0,-150);
        glTexCoord3f(3,1,0); glVertex3f(150,100,-150);
        glTexCoord3f(4,0,0); glVertex3f(150,0,150);
        glTexCoord3f(4,1,0); glVertex3f(150,100,150);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1,1,1);
        glTexCoord3f(80,2,0); glVertex3f(120,0,120);
        glTexCoord3f(80,0,0); glVertex3f(120,5,120);
        glTexCoord3f(60,2,0); glVertex3f(-120,0,120);
        glTexCoord3f(60,0,0); glVertex3f(-120,5,120);
        glTexCoord3f(40,2,0); glVertex3f(-120,0,-120);
        glTexCoord3f(40,0,0); glVertex3f(-120,5,-120);
        glTexCoord3f(20,2,0); glVertex3f(120,0,-120);
        glTexCoord3f(20,0,0); glVertex3f(120,5,-120);
        glTexCoord3f(0,2,0); glVertex3f(120,0,120);
        glTexCoord3f(0,0,0); glVertex3f(120,5,120);
    glEnd();
    //glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1,1,1);
        glTexCoord3f(0,0,0); glVertex3f(149,0,149);
        glTexCoord3f(0,1,0); glVertex3f(149,15,149);
        glTexCoord3f(1,0,0); glVertex3f(-149,0,149);
        glTexCoord3f(1,1,0); glVertex3f(-149,15,149);
        glTexCoord3f(2,0,0); glVertex3f(-149,0,-149);
        glTexCoord3f(2,1,0); glVertex3f(-149,15,-149);
        glTexCoord3f(3,0,0); glVertex3f(149,0,-149);
        glTexCoord3f(3,1,0); glVertex3f(149,15,-149);
        glTexCoord3f(4,0,0); glVertex3f(149,0,149);
        glTexCoord3f(4,1,0); glVertex3f(149,15,149);
    glEnd();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, crownTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1,1,1);
        glTexCoord3f(8,1,0); glVertex3f(120,5,120);
        glTexCoord3f(8,0,0); glVertex3f(149,15,149);
        glTexCoord3f(6,1,0); glVertex3f(-120,5,120);
        glTexCoord3f(6,0,0); glVertex3f(-149,15,149);
        glTexCoord3f(4,1,0); glVertex3f(-120,5,-120);
        glTexCoord3f(4,0,0); glVertex3f(-149,15,-149);
        glTexCoord3f(2,1,0); glVertex3f(120,5,-120);
        glTexCoord3f(2,0,0); glVertex3f(149,15,-149);
        glTexCoord3f(0,1,0); glVertex3f(120,5,120);
        glTexCoord3f(0,0,0); glVertex3f(149,15,149);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
