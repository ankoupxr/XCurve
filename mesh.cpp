
#include "mesh.h"

Mesh::Mesh()
{

}


void Mesh::ReadObj(std::string filename)
{
    std::string line;
    std::fstream fs;
    fs.open(filename, std::ios::in);

    while (std::getline(fs, line)) {
        std::vector<std::string> parameters;
        std::stringstream ss(line);
        std::string parameter;

        while (std::getline(ss, parameter, ' ')) {
            parameters.push_back(parameter);
        }

        if (parameters[0] == "v") {   // 如果是顶点的话
            Point3d Point;
            Point.SetX(std::stof(parameters[1]) * 100);
            Point.SetY(std::stof(parameters[2]) * 100);
            Point.SetZ(std::stof(parameters[3]) * 100);
            m_Vertex.push_back(Point);
        }
        else if (parameters[0] == "f") {   // 如果是面的话，存放三个顶点的索引
            std::vector<int> faceIndex;
            for (int i = 1; i < 4; i++) {
                std::string x = parameters[i];
                std::string ans = "";
                for (int j = 0; j < x.length(); j++) {   // 跳过 '/'
                    char ch = x[j];
                    if (ch != '/') {
                        ans += ch;
                    }
                    else {
                        break;
                    }
                }
                int index = std::stoi(ans);
                index = index - 1;  // 因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                faceIndex.push_back(index);
            }
            m_FaceArray.push_back(faceIndex);
        }
    }
    fs.close();
}

void Mesh::draw()
{
    for (int i = 0; i < m_FaceArray.size(); i++)
    {
        GLdouble VN[3];
        GLdouble SV1[3];
        GLdouble SV2[3];
        GLdouble SV3[3];

        if ((m_FaceArray[i]).size() != 3) {

        }
        else {

            GLint firstVertexIndex = (m_FaceArray[i])[0];//取出顶点索引
            GLint secondVertexIndex = (m_FaceArray[i])[1];
            GLint thirdVertexIndex = (m_FaceArray[i])[2];
            glColor3f(255,0,0);
            glBegin(GL_LINE_LOOP);//开始绘制
            SV1[0] = (m_Vertex[firstVertexIndex]).GetX();//第一个顶点
            SV1[1] = (m_Vertex[firstVertexIndex]).GetY();
            SV1[2] = (m_Vertex[firstVertexIndex]).GetZ();
            glVertex3d(SV1[0],SV1[1],SV1[2]);

            SV2[0] = (m_Vertex[secondVertexIndex]).GetX(); //第二个顶点
            SV2[1] = (m_Vertex[secondVertexIndex]).GetY();
            SV2[2] = (m_Vertex[secondVertexIndex]).GetZ();
            glVertex3d(SV2[0],SV2[1],SV2[2]);

            SV3[0] = (m_Vertex[thirdVertexIndex]).GetX(); //第三个顶点
            SV3[1] = (m_Vertex[thirdVertexIndex]).GetY();
            SV3[2] = (m_Vertex[thirdVertexIndex]).GetZ();
            glVertex3d(SV3[0],SV3[1],SV3[2]);
            glEnd();

//            GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
//            //(x2-x1,y2-y1,z2-z1)
//            vec1[0] = SV1[0] - SV2[0];
//            vec1[1] = SV1[1] - SV2[1];
//            vec1[2] = SV1[2] - SV2[2];

//            //(x3-x2,y3-y2,z3-z2)
//            vec2[0] = SV1[0] - SV3[0];
//            vec2[1] = SV1[1] - SV3[1];
//            vec2[2] = SV1[2] - SV3[2];

//            //(x3-x1,y3-y1,z3-z1)
//            vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
//            vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
//            vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

//            GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

//            VN[0] = vec3[0] / D;
//            VN[1] = vec3[1] / D;
//            VN[2] = vec3[2] / D;

//            glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

//            glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
//            glVertex3f(SV2[0], SV2[1], SV2[2]);
//            glVertex3f(SV3[0], SV3[1], SV3[2]);
        }
    }
}
