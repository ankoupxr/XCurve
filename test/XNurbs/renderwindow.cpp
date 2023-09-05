#include "renderwindow.h"
#include "ui_renderwindow.h"

renderwindow::renderwindow(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::renderwindow)
{
    tra = -1000.0;
    xRot = yRot = zRot = 0.0;
    oldPoint = QPoint(0, 0);
    trax = 0, tray = 0;

    ui->setupUi(this);
}

renderwindow::~renderwindow()
{
    delete ui;
}

//初始化
void renderwindow::initializeGL()
{
    glClearColor(0,0,0,1.0);//清空当前的所有颜色
    glShadeModel(GL_SMOOTH);//使用平滑着色模式
    glClearDepth(1.0);//设置最远深度值
    glEnable(GL_DEPTH_TEST);//启用深度测试
}

//自适应
void renderwindow::resizeGL(int width,int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, (GLfloat)width/(GLfloat)height, 0.1, 9999.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

//绘图主函数
void renderwindow::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef(trax, tray, tra);
    gluLookAt(0,0,0.0,0.0,0.0,1.0,0.0,-1.0,0.0);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(10.0f);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable(GL_BLEND);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

//    std::vector<Point3dW> cps1 = { Point3dW(60, 100, 0,1),  Point3dW(20, 150, 10,1),
//                                  Point3dW(80, 200, 30,1),Point3dW(100, 100, 30,1),Point3dW(60,100,10,1),Point3dW(60,100,0,1)};
    std::vector<Point3dW> cps1 = { Point3dW(0, 0, 0,1),  Point3dW(100, 100, 0,4),
                                  Point3dW(300, 200, 0,1),Point3dW(400,100,0,1),Point3dW(500,-100,0,1)};
    std::vector<double> kv1 = { 0,0,0,1,2,3,3,3 };
    xnurbs test(cps1,kv1,2);
    test.ComputeRationalCurve();
    test.draw();




//    glColor3f(0.0,0.0,1.0);
//    glBegin(GL_LINES);
//    glVertex3f(100.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);
//    glEnd();
//    glColor3f(1.0,0.0,0.0);
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 100.0, 0.0);
//    glEnd();
//    glColor3f(0.0,1.0,0.0);
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, 100.0);
//    glEnd();
}

//鼠标点击事件
void renderwindow::mousePressEvent(QMouseEvent *event) {
    if(event->buttons()==Qt::LeftButton) {
        oldPoint = event->pos();
    }
}

//鼠标移动事件
void renderwindow::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons()==Qt::LeftButton) {
        QPoint temPoint = e->pos()- oldPoint;
        xRot += temPoint.y() * 0.5;
        yRot += temPoint.x() * 0.5;
        oldPoint = e->pos();
        update();
    }
}

//滚轮事件
void renderwindow::wheelEvent(QWheelEvent *e) {
    tra += e->delta();
    update();
}

