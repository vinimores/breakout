#include "brick.h"
#include "glew.h"

Brick::Brick(){
    dead = false;
}

void Brick::_draw_cube(){
    //glPushMatrix();
    if (!dead) {

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f,-0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0f, 1.0f,-0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f,-0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 1.0f,-0.5f);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f( 1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0f, 1.0f,-0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f,-0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 0.0f,-0.5f);
    glEnd();
    //glPopMatrix();
    }
    glLoadIdentity();

}

bool Brick::isDead(){
    return dead;
}
