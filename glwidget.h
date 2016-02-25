#pragma once
#include <glew.h>
#include <QGLWidget>
#include <QMessageBox>
#include <brick.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
    int _width;
    int _height;
    QImage image;
    GLUquadricObj * _quadratic;
    float x_bar;
    float posX_ball;
    float posY_ball;
    boolean dir_H_ball;
    boolean dir_Y_ball;
    GLfloat circle_points;
    GLfloat angle, raioX, raioY;
    QMessageBox *msg;
    int pontuacao;
    Brick *brick[3][8];
    bool mostrou;

public:
    explicit GLWidget(QWidget* parent = 0);
    virtual ~GLWidget();

    // OpenGL initialization
    void initializeGL();

    // Viewport resizing
    void resizeGL( int width, int height);

    // Painting
    void paintGL();

    void reset();
    void die();
    void _draw_ball();
    void _draw_cube();
    void _draw_bar();
    void update_var();
    void keyPressEvent(QKeyEvent *e);

public slots:
    void _tick();
    void _tick2();
};
