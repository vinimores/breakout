#include <glew.h>
#include "glwidget.h"
#include <QDebug>
#include <iostream>
#include <QKeyEvent>
#include <QTimer>
#include <math.h>
#define PI 3.1415926535898

#define checkImageWidth 200
#define checkImageHeight 200
static GLuint texName;

GLWidget::GLWidget(QWidget *parent)
: QGLWidget(parent)
{
_width = 0;
_height = 0;
image = QImage(":/tex.jpg");
std::cout << image.depth() <<  std::endl;
image = image.rgbSwapped();
x_bar = 0.0f;
posX_ball = 0.0f;
posY_ball = -5.5f;
dir_H_ball = true;
dir_Y_ball = true;
msg = new QMessageBox();
pontuacao = 0;
for(int y=0; y<3; y++){
    for(int x=0; x<8; x++){
        brick[y][x] = new Brick();
    }
}
mostrou = false;
_tick();
_tick2();
}
GLWidget::~GLWidget(){

}

void GLWidget::_tick()
{
updateGL(); // triggers paintGL(
QTimer::singleShot(2, this, SLOT(_tick()));
}

void GLWidget::_tick2(){
    update_var();
    QTimer::singleShot(20, this, SLOT(_tick2()));
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texName);

    glEnable(GL_LIGHT0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageHeight,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    float x_draw_cube = -9.5f;
    float y_draw_cube = 5.0f;
    for(int y=0; y<3; y++){
        for(int x=0; x<8; x++){
            glTranslatef(x_draw_cube, y_draw_cube, -14.0f);
            brick[y][x]->posX = x_draw_cube;
            brick[y][x]->posY = y_draw_cube;
            brick[y][x]->_draw_cube();
            x_draw_cube = x_draw_cube + 2.5f;
        }
        x_draw_cube = -9.5f;
        y_draw_cube = y_draw_cube - 1.5f;
    }

    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);

    _draw_bar();

    glLoadIdentity();

    _draw_ball();

    glFlush();
}

void GLWidget::_draw_ball(){
    _quadratic = gluNewQuadric();
    glPushMatrix();
    glTranslatef(posX_ball, posY_ball, -14.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    gluSphere(_quadratic, 0.35f, 360, 10);
    glPopMatrix();
}

void GLWidget::_draw_bar(){

    glTranslatef(x_bar, -6.0f, -12.0f);

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.3f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.0f, 0.3f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f,-1.0f);
    glVertex3f(1.0f, 0.3f,-1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.0f, 0.3f,-1.0f);
    glVertex3f(1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 0.3f,-1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.3f,-1.0f);
    glVertex3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.3f, 0.0f);
    glVertex3f( 1.0f, 0.3f, 0.0f);
    glVertex3f( 1.0f, 0.3f,-1.0f);
    glVertex3f(-1.0f, 0.3f,-1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 0.0f,-1.0f);
    glEnd();

    glLoadIdentity();
}

void GLWidget::update_var(){
    if(dir_H_ball){
        posX_ball += 0.1f;
    }else{
        posX_ball -= 0.1f;
    }

    if(dir_Y_ball){
        posY_ball += 0.1f;
    }else{
        posY_ball -= 0.1f;
    }

    if(posX_ball > 10.5f && dir_H_ball){
        dir_H_ball = false;
    } else if(posX_ball < -12.5f && !dir_H_ball){
        dir_H_ball = true;
    }

    if(posY_ball > 7.0f && dir_Y_ball){
        dir_Y_ball = false;
    } else if(posY_ball < -9.0f && !dir_Y_ball){
        die();
    }

    if(     (posY_ball <= -6.0f) &&
            (posY_ball >= -6.5f) &&
            ((posX_ball >= x_bar-1.5f)) &&
            ((posX_ball <= x_bar+1.0f))){
        dir_Y_ball = true;
    }

    for(int y=0; y<3; y++){
        for(int x=0; x<8; x++){
            if((brick[y][x]->posY <= posY_ball)
                    &&((brick[y][x]->posY >= posY_ball-1))
                    &&((posX_ball >=brick[y][x]->posX-1.5)
                       &&(posX_ball <=brick[y][x]->posX+1.5)
                       && !brick[y][x]->dead)){
                brick[y][x]->dead = true;
                pontuacao = pontuacao + 10;
                if(dir_H_ball && dir_Y_ball){
                    dir_H_ball = true;
                    dir_Y_ball = false;
                } else if (!dir_H_ball && dir_Y_ball){
                    dir_H_ball = true;
                    dir_Y_ball = true;
                } else if(dir_H_ball && !dir_Y_ball){
                    dir_H_ball = false;
                    dir_Y_ball = true;
                } else if (!dir_H_ball && !dir_Y_ball){
                    dir_H_ball = true;
                    dir_Y_ball = true;
                }
            }
        }
    }

    if(pontuacao >= 240){
        if(!mostrou){
        msg->setText("Voce ganhou!!!");
        msg->show();
        mostrou = true;
        reset();
        }
    }
}

void GLWidget::reset(){
    x_bar = 0.0f;
    posX_ball = 0.0f;
    posY_ball = -5.5f;
    dir_H_ball = true;
    dir_Y_ball = true;
    pontuacao = 0;
    for(int y=0; y<3; y++){
        for(int x=0; x<8; x++){
            brick[y][x]->dead = false;
        }
    }
}

void GLWidget::die(){
    QString str;
    str.append(QString("%1").arg(pontuacao));
    msg->setText("Voce morreu com: "+str+" pontos.");
    msg->show();
    reset();
}

void GLWidget::resizeGL( int w, int h)
{
    _width = w;
    _height = h;

    glViewport ( 0, 0, w, h );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();

    if (h == 0)
        gluPerspective ( 60, ( float ) w, 1.0, 100.0 );
    else
        gluPerspective ( 60, ( float ) w / ( float ) h, 1.0, 100.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ( );
}


void GLWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
        if(x_bar>-10.0f){
            x_bar = x_bar - 0.2f;
        }else{
            x_bar = x_bar;
        }
        qDebug()<<"Valor do X"<<x_bar;
        break;

    case Qt::Key_Right:
        if(x_bar<8){
            x_bar = x_bar + 0.2f;
        }else{
            x_bar = x_bar;
        }
        qDebug()<<"Valor do X"<<x_bar;
        break;

    case Qt::Key_F2:
        qDebug()<<"Tecla F2";
        reset();
        break;
    default:
        break;
    }
}
