#ifndef PAINTERWINDOW_H
#define PAINTERWINDOW_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <GL/glut.h>
#include <point3d.h>
#include <vector>

namespace Ui {
class painterwindow;
}

class painterwindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit painterwindow(QWidget *parent = nullptr);
    ~painterwindow();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *e);

private:
    Ui::painterwindow *ui;
    GLfloat tra, xRot, yRot, zRot; //控制缩放等的多个数值
    double trax, tray; //控制视景体平移的两个参量
    QPoint oldPoint; //当前鼠标点击的QPoint类型值
    std::vector<Point3d> point;
};

#endif // PAINTERWINDOW_H
