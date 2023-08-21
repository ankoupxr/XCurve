
#include "xnurbs.h"

xnurbs::xnurbs()
{

}

xnurbs::xnurbs(std::vector<std::vector<Point3dW>> controlPoints,std::vector<float> knots)
{
    this->m_controlPoints = controlPoints;
    this->m_knots = knots;

    this->m_glcontrolPoints = new float**[controlPoints.size()];
    for (int i = 0; i < controlPoints.size(); i++)
    {
        m_glcontrolPoints[i] = new float*[controlPoints.size()];
        for (int j = 0;j < m_controlPoints[0].size(); j++)
        {
            m_glcontrolPoints[i][j] = new float[m_controlPoints[0].size()];
            m_glcontrolPoints[i][j][0] = m_controlPoints[i][j].GetX();
            m_glcontrolPoints[i][j][1] = m_controlPoints[i][j].GetY();
            m_glcontrolPoints[i][j][2] = m_controlPoints[i][j].GetZ();
            m_glcontrolPoints[i][j][3] = m_controlPoints[i][j].GetW();
        }
    }

    this->m_glknots = new float[m_knots.size()];
    for(int i = 0; i < m_knots.size(); i++)
    {
        m_glknots[i] = m_knots.at(i);
    }

    pNurb = gluNewNurbsRenderer();
    //设置采样容差
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
    //填充一个实体的表面
    gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
}

xnurbs::~xnurbs()
{
    this->m_controlPoints.clear();
    this->m_knots.clear();
    if (pNurb)
        gluDeleteNurbsRenderer(pNurb);
}

void xnurbs::draw()
{
    glPushMatrix();
    //绘制控制点和控制线
    glScaled(0.2,0.2,0.2);
    glPointSize(4.0f);
    glColor3f(0.0, 0.0, 1.0);
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    for (int i = 0;i < m_controlPoints.size(); i++)
    {
        for (int j = 0;j < m_controlPoints[0].size(); j++)
        {
            glVertex3fv(m_glcontrolPoints[i][j]);
        }
    }
    glEnd();
    //绘制控制线
    glLineWidth(1.5f);
    glColor3f(0.0,1.0,1.0);
    for (int i=0;i < m_controlPoints.size();i++)
    {
        glBegin(GL_LINE_STRIP);
        for (int j = 0;j < m_controlPoints[0].size(); j++)
        {
            glVertex3fv(m_glcontrolPoints[i][j]);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (int j = 0;j < m_controlPoints[0].size(); j++)
        {
            glVertex3fv(m_glcontrolPoints[j][i]);
        }
        glEnd();
    }

    glLineWidth(1.0f);
    glColor3d(0.0,0.0,0.0);

    gluNurbsProperty(pNurb,GLU_SAMPLING_TOLERANCE,25.0); //设置属性
    gluNurbsProperty(pNurb,GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
    gluBeginSurface(pNurb);//开始绘制
    //绘制B样条控制曲面
    gluNurbsSurface(pNurb,
                    m_knots.size(),m_glknots,
                    m_knots.size(),m_glknots,
                    4*3,
                    3,
                    &m_glcontrolPoints[0][0][0],
                    4, 4,
                    GL_MAP2_VERTEX_3);

    gluEndSurface(pNurb); //结束绘制

}
