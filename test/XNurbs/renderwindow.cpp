#include "renderwindow.h"
#include "ui_renderwindow.h"

renderwindow::renderwindow(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::renderwindow)
{
    ui->setupUi(this);
}

renderwindow::~renderwindow()
{
    delete ui;
}

//初始化
void renderwindow::initializeGL()
{
//    glClearColor(1.0,1.0,1.0,1.0);//清空当前的所有颜色
//    glShadeModel(GL_SMOOTH);//使用平滑着色模式
//    glClearDepth(1.0);//设置最远深度值
//    glEnable(GL_DEPTH_TEST);//启用深度测试
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glEnable( GL_DEPTH_TEST );
}

//自适应
void renderwindow::resizeGL(int width,int height)
{
//    glViewport( 0, 0, (GLint)width, (GLint)height );//设置视口的大小和位置
//    glMatrixMode(GL_PROJECTION);//指定当前矩阵为投影矩阵
//    glLoadIdentity();//将当前矩阵重置为单位矩阵
//    gluPerspective( 45, (GLfloat)width/(GLfloat)height, 0.1, 9999.0 );//设置透视投影矩阵
//    glMatrixMode( GL_MODELVIEW );//指定当前矩阵为模型视图矩阵
//    glLoadIdentity();//将当前矩阵重置为单位矩阵
    if ( height == 0 )
        height = 1;

    glViewport( 0, 0, (GLint)width, (GLint)height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

float int2float(int intensity) {
    return (float)intensity / 255.0f;
}

void renderwindow::drawQuads(int r, int g, int b) {
    const GLfloat x1 = -0.05f, x2 = 0.05f;
    const GLfloat y1 = -0.05f, y2 = 0.05f;
    const GLfloat point[4][2] = { { x1,y1 },{ x1,y2 },{ x2,y2 },{ x2,y1 } };

    glColor3f(int2float(r), int2float(g), int2float(b));
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(point[i]);
    }
    glEnd();
}

//绘图主函数
void renderwindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //front
    glPushMatrix();
    glTranslatef(-0.4f, 0, 0);
    drawQuads(255, 255, 0);
    glPopMatrix();


    //front
    glPushMatrix();
    glTranslatef(0, 0, 0.05f);
    drawQuads(0, 255, 0);
    glPopMatrix();

    //behind
    glPushMatrix();
    glTranslatef(0, 0, -0.05f);
    drawQuads(255, 255, 0);
    glPopMatrix();

    //left
    glPushMatrix();
    glTranslatef(-0.05f, 0, 0);
    glRotatef(90, 0, 1, 0);
    drawQuads(0, 255, 255);
    glPopMatrix();

    //right
    glPushMatrix();
    glTranslatef(0.05f, 0, 0);
    glRotatef(270, 0, 1, 0);
    drawQuads(255, 0, 0);
    glPopMatrix();

    //top
    glPushMatrix();
    glTranslatef(0, 0.05f, 0);
    glRotatef(90, 1, 0, 0);
    drawQuads(0, 0, 255);
    glPopMatrix();

    //bottom
    glPushMatrix();
    glTranslatef(0, -0.05f, 0);
    glRotatef(270, 1, 0, 0);
    drawQuads(255, 0, 255);
    glPopMatrix();

    //repaint
    update();

//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glTranslatef(trax,  tray, tra);
//    gluLookAt(0,0,0.0,0.0,0.0,1.0,0.0,-1.0,0.0);

//    glRotatef(xRot, 1.0, 0.0, 0.0);
//    glRotatef(yRot, 0.0, 1.0, 0.0);
//    glRotatef(zRot, 0.0, 0.0, 1.0);

//    glColor3f(0.0, 0.0, 0.0);
//    glPointSize(10.0f);

//    std::vector<std::vector<Point3dW>> ctrlpoints;
//    std::vector<std::vector<std::vector<float>>> rctrlpoints={
//        {{100.0,270.0,0.0},//p00
//         {105.0,180.0,0.0},//p01
//         {110.0,160.0,0.0},//p02
//         {155.0,100.0,0.0}},//p03
//        {{180.0,200.0,0.0},//p10
//         {190.0,130.0,0.0},//p11
//         {200.0,110.0,0.0},//p12
//         {240.0,70.0,0.0}},//p13
//        {{310.0,200.0,0.0},//p20
//         {320.0,130.0,0.0},//p21
//         {330.0,110.0,0.0},//p22
//         {370.0,70.0,0.0}},//p23
//        {{420.0,270.0,0.0},//p30
//         {430.0,180.0,0.0},//p31
//         {440.0,160.0,0.0},//p32
//         {490.0,120.0,1.0}}//p33
//    };

//    for (int i = 0; i < rctrlpoints.size(); i++)
//    {
//        std::vector<Point3dW> temp;
//        for (int j= 0; j < rctrlpoints[0].size(); j++)
//        {
//            Point3dW p1(rctrlpoints[i][j][0],rctrlpoints[i][j][1],
//                        rctrlpoints[i][j][2],0.0);
//            temp.push_back(p1);
//        }
//        ctrlpoints.push_back(temp);
//    }

//    std::vector<float> knots={0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
//    xnurbs test(ctrlpoints,knots);
//    test.draw();

//    glColor3f(0.0,0.0,1.0);
//    glBegin(GL_LINES);
//    glVertex3f(500.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);
//    glEnd();
//    glColor3f(1.0,0.0,0.0);
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 500.0, 0.0);
//    glEnd();
//    glColor3f(0.0,1.0,0.0);
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, -500.0);
//    glEnd();
}
