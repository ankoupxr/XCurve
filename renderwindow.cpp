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

    test = new Mesh();
    test->ReadObj("G:/pxr/opencode/XCurve/data/test.obj");
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

//    std::vector<Point3dW> cps1 = { Point3dW(-280, 30, 0,1),  Point3dW(-250, 180, 0,2),
//                                  Point3dW(0, 100, 0,2.0),Point3dW(-100, -100, 0,2.0),
//                                  Point3dW(250,-100,0,2.0),Point3dW(130,120,0,2.0),
//                                  Point3dW(250,160,0,1)};
//    std::vector<Point3dW> cps1 = { Point3dW(0, 0, 0,1),  Point3dW(100, 100, 0,4),
//                                  Point3dW(300, 200, 0,1),Point3dW(400,100,0,1),Point3dW(500,-100,0,1)};
//    std::vector<double> knot(11);
//    xnurbscurve test(cps1,knot,3);
//    test.ComputeRationalCurve();
//    test.draw();

//    std::vector<std::vector<Point3dW>> cps1 ={
//        {Point3dW(82, -100, 200,1),Point3dW(-14, 65, 150,1),  Point3dW(-146, 94, 50,1),Point3dW(-254, 80, 0,1),Point3dW(-301, 40, 50,1)},
//        {Point3dW(147, 68, 150,1),Point3dW(52, 117,100,1),  Point3dW(-68, 146, 50,1),Point3dW(-173, 135, -10,1),Point3dW(-238, 131, -10,1)},
//        {Point3dW(227, 132, 140,1),Point3dW(125, 154, 80,1),  Point3dW(0, 178, 30,1),Point3dW(-109, 166, -50,1),Point3dW(-164, 174, 0,1)},
//        {Point3dW(337, 131, 150,1),Point3dW(205, 173, 50,1),  Point3dW(75, 203, 0,1),Point3dW(-51, 188, -70,1),Point3dW(-116, 178, -100,1)},
//        {Point3dW(390, 50, 150,1),Point3dW(288, 162, 50,1),  Point3dW(172, 208, 0,1),Point3dW(48, 201, -70,1),Point3dW(-8, 200, 50,1)}
//    };

//    std::vector<std::vector<Point3dW>> cps1 ={
//        {Point3dW(0, 0, 0,1),Point3dW(100, 0, 100,1),  Point3dW(200, 0, 200,1),Point3dW(300, 0, 100,1),Point3dW(400,0,0,1)},
//        {Point3dW(0,100,200,1),Point3dW(100,100,300,1),  Point3dW(200,100,300,1),Point3dW(300,100,300,1),Point3dW(400,100,200,1)},
//        {Point3dW(0,200,200,1),Point3dW(100,200,300,1),  Point3dW(200,200,350,1),Point3dW(300,200,300,1),Point3dW(400,200,200,1)},
//        {Point3dW(0,300,200,1),Point3dW(100,300,300,1),  Point3dW(200,300,300,1),Point3dW(300,300,300,1),Point3dW(400,300,200,1)},
//        {Point3dW(0, 400, 100,1),Point3dW(100, 400, 200,1),  Point3dW(200, 400, 200,1),Point3dW(300, 400, 200,1),Point3dW(400, 400, 100,1)}
//    };

//    std::vector<std::vector<double>> u(5);
//    std::vector<std::vector<double>> v(5);
//    for(int i=0;i<5;i++)
//    {
//        u[i].resize(4+3+2);
//                v[i].resize(4+3+2);
//    }

//    XNurbsSurface test(cps1,v,u,4,4);
//    test.ComputeNurbsSurface();
//    test.draw();

    test->draw();

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

