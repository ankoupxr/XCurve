#ifndef MESH_H
#define MESH_H

#include <GL/glut.h>
#include <point3d.h>
#include <fstream>
#include <iostream>

class Mesh
{
public:
    Mesh();
    void draw();
    void ReadObj(std::string filename);
private:
    std::vector<std::vector<int>> m_FaceArray;
    std::vector<Point3d> m_Vertex;
};

#endif // MESH_H
