#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>
#include <GL/glut.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QOpenGLFunctions_3_3_Core>
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
#include <xnurbs.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <point3dw.h>

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

private slots:
    //void clcFunc(); //清屏
    //void draw(surfaceInfo *i); //绘图槽函数


private:
    Ui::renderwindow *ui;
    GLfloat tra, xRot, yRot, zRot; //控制缩放等的多个数值
    double trax, tray; //控制视景体平移的两个参量
    QPoint oldPoint; //当前鼠标点击的QPoint类型值
    bool isInputting;
    //QVector<Point> pointVector; //存放点的容器
    //void drawPoint(Point a); //绘制点的函数
    //void drawLines(Point a, Point b); //绘制直线函数
    //Point p[5][5]; //全局变量存放控制顶点
    double *ut, *vt; //两个存放double类型的数组的指针
    bool isDraw, isRead; //用于判断绘制曲面的两个布尔值
};

#endif // RENDERWINDOW_H
