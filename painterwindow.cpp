#include "painterwindow.h"
#include "ui_painterwindow.h"
painterwindow::painterwindow(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::painterwindow)
{
    ui->setupUi(this);
    tra = -1000.0;
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
    glClearColor(128.0,128.0,105.0,1);//清空当前的所有颜色
    glShadeModel(GL_SMOOTH);//使用平滑着色模式
    glClearDepth(1.0);//设置最远深度值
    glEnable(GL_DEPTH_TEST);//启用深度测试
}
//自适应
void painterwindow::resizeGL(int width,int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, (GLfloat)width/(GLfloat)height, 0.1, 9999.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
//绘图主函数
void painterwindow::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef(0, 0, tra);
    gluLookAt(0,0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

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
    }
}


//鼠标点击事件
void painterwindow::mousePressEvent(QMouseEvent *event) {
        oldPoint = event->pos();
        // 将鼠标点击事件的坐标转换为OpenGL坐标
        double ox = this->width() / 2;
        double oy = this->height() / 2;
        double openglx = 0.0;
        double opengly = 0.0;
        openglx = (oldPoint.x() - ox);
        opengly = -(oldPoint.y() - oy);
        point.push_back(Point3d(openglx, opengly, 0.0));
        update();
}



//滚轮事件
void painterwindow::wheelEvent(QWheelEvent *e) {
    tra += e->delta();
    update();
}
