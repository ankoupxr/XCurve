#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>
#include <GL/glut.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <vector>
#include <QFileDialog>
#include <xnurbscurve.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <point3dw.h>
#include <xcurve.h>
#include <xnurbssurface.h>
#include <mesh.h>
#include <xnurbscircle.h>

namespace Ui {
class renderwindow;
}

class renderwindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit renderwindow(QWidget *parent = nullptr);
    ~renderwindow();
    void drawQuads(int r, int g, int b);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *e);

private slots:
    //void clcFunc(); //清屏
    //void draw(surfaceInfo *i); //绘图槽函数


private:
    Ui::renderwindow *ui;
    GLfloat tra, xRot, yRot, zRot; //控制缩放等的多个数值
    double trax, tray; //控制视景体平移的两个参量
    QPoint oldPoint; //当前鼠标点击的QPoint类型值
    GLUnurbsObj* pNurb;
    xnurbscircle* test;
};

#endif // RENDERWINDOW_H
