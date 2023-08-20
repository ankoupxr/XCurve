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
