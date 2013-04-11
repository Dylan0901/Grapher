#include "glwidget.h"
#include "model.h"
#include "types3d.h"
#include "events.h"
#include <QTimer>
#include <QKeyEvent>
#include <QImage>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    model = new Model;
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(30);
    this->setCursor(Qt::BlankCursor);
    setMouseTracking(true);
}

void GLWidget::resizeGL(int width, int height)
{
    if (0 == height) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<GLfloat>(width)/height, 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);
    QImage img = convertToGLFormat(QImage("wall.jpg"));
    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.width(), img.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits());

    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSector();
    model->play();
}

void GLWidget::drawSector()
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    Bundle& bundle = model->getBundle();
    Vertex& angle = bundle.angle;
    glRotatef(angle.y, 1.0f, 0.0f, 0.0f);
    glRotatef(-1 * angle.x, 0.0f, 1.0f, 0.0f);
    Vertex& position = bundle.position;
    glTranslatef(position.x, position.y, position.z);
    Sector sector = bundle.sector;
    std::vector<Face>::iterator i;
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    for (i = sector.faces.begin(); i != sector.faces.end(); ++i) {
        if (i->quad) {
            glBegin(GL_QUADS);
                glNormal3f(0.0f, 0.0f, 1.0f);
                for (int j = 0; j < 4; ++j) {
                    glTexCoord3f(i->txt[j].x, i->txt[j].y, i->txt[j].z);
                    glVertex3f(i->vertex[j].x, i->vertex[j].y, i->vertex[j].z);
                }
            glEnd();
        } else {
            glBegin(GL_TRIANGLES);
                glNormal3f(0.0f, 0.0f, 1.0f);
                for (int j = 0; j < 3; ++j) {
                    glTexCoord3f(i->txt[j].x, i->txt[j].y, i->txt[j].z);
                    glVertex3f(i->vertex[j].x, i->vertex[j].y, i->vertex[j].z);
                }
            glEnd();
        }
    }
    glPopMatrix();
}


void GLWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_F1:
        setWindowState(windowState() ^ Qt::WindowFullScreen);
        break;
    case Qt::Key_W:
        model->omitEvent(up_key_pressed);
        //direct_y = 0.01f;
        break;
    case Qt::Key_S:
        model->omitEvent(down_key_pressed);
        break;
    case Qt::Key_A:
        model->omitEvent(left_key_pressed);
        break;
    case Qt::Key_D:
        model->omitEvent(right_key_pressed);
        break;
    default:
        QGLWidget::keyPressEvent(event);
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_W:
        model->omitEvent(up_key_released);
        //direct_y = 0.0f;
        break;
    case Qt::Key_S:
        model->omitEvent(down_key_released);
        break;
    case Qt::Key_A:
        model->omitEvent(left_key_released);
        break;
    case Qt::Key_D:
        model->omitEvent(right_key_released);
        break;
    default:
        QGLWidget::keyPressEvent(event);
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    float angle_x = (float)event->x() - this->width()/2 + 8,
          angle_y = (float)event->y() - this->height()/2 + 30,
          center_x = this->pos().x() + this->width()/2,
          center_y = this->pos().y() + this->height()/2;
    model->rotate(angle_x, angle_y);
    SetCursorPos(center_x, center_y);
    event->accept();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void GLWidget::changeEvent(QEvent* event)
{
    switch(event->type()) {
    case QEvent::WindowStateChange:
        if (windowState() == Qt::WindowFullScreen) {
            setCursor(Qt::BlankCursor);
        } else {
            unsetCursor();
        }
        break;
    default:
        break;
    }
}
