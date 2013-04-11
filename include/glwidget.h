#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGLWidget>
class Model;

class GLWidget : public QGLWidget
{
    Q_OBJECT

private:
    Model* model;
    //QTimer *timer;
    //QTime time;
    GLuint filter, texture[3];
    //Sector sector1;
    GLfloat xpos, yrot, zpos, lookupdown;
    GLfloat walkbias, walkbiasangle;
    bool lightChanged, filterChanged, blendChanged;
    int changeAmount;
    //QHash<GLuint, QString> filterName;
    bool keyUp, keyDown, keyLeft, keyRight, keyPageUp, keyPageDown;
public:
    explicit GLWidget(QWidget *parent = 0);
    void resizeGL(int, int);
    void initializeGL();
    void paintGL();
    void drawSector();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void changeEvent(QEvent *);
    bool setupWorld();
signals:

public slots:

};

#endif // GRAPHWIDGET_H
