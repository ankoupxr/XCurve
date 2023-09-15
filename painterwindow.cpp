#include "painterwindow.h"
#include "ui_painterwindow.h"
painterwindow::painterwindow(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::painterwindow)
{
    ui->setupUi(this);
    tra = -0.1;
    xRot = yRot = zRot = 0.0;
    oldPoint = QPoint(0, 0);
    trax = 0, tray = 0;
}
painterwindow::~painterwindow()
{
    delete ui;
}
//初始化
void painterwindow::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //用白色清屏
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}
//自适应
void painterwindow::resizeGL(int width,int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height ); //设置视口
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); //平行投影，设置视景体前部和照相机的相对位置

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
//绘图主函数
void painterwindow::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    gluLookAt(0,0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0); //更改照相机的位置以及观看的方向等


    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();

    if(point.size() > 0)
    {
        for(int i = 0; i<= point.size()-1;i++ )
        {
            glColor3f(255.0,0.0,0.0);
            glPointSize(5.0);
            glBegin(GL_POINTS);
            glVertex3f(point[i].GetX(), point[i].GetY(), 0.0);
            glEnd();
        }
        if(IsDrawCurve)
        {

        }
        else{

        }
    }
}


//鼠标点击事件
void painterwindow::mousePressEvent(QMouseEvent *event) {
    oldPoint = event->pos();
    // 将鼠标点击事件的坐标转换为OpenGL坐标
    double x = (oldPoint.x() - width()/2.0)/(width()/2.0);
    double y = (height()/2.0 - oldPoint.y())/(height()/2.0);
    point.push_back(Point3d(x, y, 0.0));
    update();
}


void painterwindow::drawCurve()
{
    std::vector<Point3dW> ControlPoints;
    for(int i = 0; i<= point.size()-1;i++ )
    {
        Point3dW p(point[i].GetX(), point[i].GetY(), 0.0,1);
        ControlPoints.push_back(p);
    }
    std::vector<double> m_knots(11);
    xnurbscurve xc(ControlPoints,m_knots,3);
    curve.push_back(xc);
}

//滚轮事件
void painterwindow::wheelEvent(QWheelEvent *e) {
    //tra += e->delta();
    //update();
}
