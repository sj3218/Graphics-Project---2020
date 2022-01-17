/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#include "CubeMesh.h"

const Point CubeMesh::vertices[8] = { Point(1,1,1), Point(-1,1,1), Point(-1,-1,1), Point(1,-1,1),
                                    Point(1,1,-1), Point(-1,1,-1), Point(-1,-1,-1), Point(1,-1,-1) };
const Mesh::Face CubeMesh::faces[12] = { Mesh::Face(0,1,2),Mesh::Face(0,2,3), Mesh::Face(4,0,3), Mesh::Face(4,3,7),
                                        Mesh::Face(1,5,6), Mesh::Face(1,6,2), Mesh::Face(5,4,7), Mesh::Face(5,7,6),
                                        Mesh::Face(4,5,1), Mesh::Face(4,1,0), Mesh::Face(3,2,6), Mesh::Face(3,6,7) };
const Mesh::Edge CubeMesh::edges[12] = { Mesh::Edge(0,1),Mesh::Edge(1,2), Mesh::Edge(2,3), Mesh::Edge(3,0),
                                        Mesh::Edge(4,5), Mesh::Edge(5,6), Mesh::Edge(6,7), Mesh::Edge(7,4),
                                        Mesh::Edge(0,4), Mesh::Edge(1,5), Mesh::Edge(2,6), Mesh::Edge(3,7) };

CubeMesh::CubeMesh()
{
    InitNormal();
}

int CubeMesh::VertexCount(void)
{
    return sizeof(vertices)/sizeof(Point);
}

Point CubeMesh::GetVertex(int i)
{
    return vertices[i];
}

Vector CubeMesh::Dimensions(void)
{
    //standard cube width, height, and depth = 2
    return Vector(2.f,2.f,2.f);
}

Point CubeMesh::Center(void)
{
    //standard cube center = origin
    return Point(0.f,0.f,0.f);
}

int CubeMesh::FaceCount(void)
{
    return sizeof(faces)/sizeof(Mesh::Face);
}

Mesh::Face CubeMesh::GetFace(int i)
{
    return faces[i];
}

int CubeMesh::EdgeCount(void)
{
    return sizeof(edges)/sizeof(Mesh::Edge);
}

Mesh::Edge CubeMesh::GetEdge(int i)
{
    return edges[i];
}

void CubeMesh::InitNormal()
{
    for (int i = 0; i < FaceCount(); ++i)
    {
        Hcoord P = GetVertex(GetFace(i).index1);
        Hcoord Q = GetVertex(GetFace(i).index2);
        Hcoord R = GetVertex(GetFace(i).index3);

        Vector QP = Q - P;
        Vector RP = R - P;
        Vector normalVector = cross(QP, RP);

        normal.push_back(normalVector.x);
        normal.push_back(normalVector.y);
        normal.push_back(normalVector.z);

        normal.push_back(normalVector.x);
        normal.push_back(normalVector.y);
        normal.push_back(normalVector.z);

        normal.push_back(normalVector.x);
        normal.push_back(normalVector.y);
        normal.push_back(normalVector.z);

        buffers.push_back(P.x);
        buffers.push_back(P.y);
        buffers.push_back(P.z);
        buffers.push_back(1.0f);
        buffers.push_back(Q.x);
        buffers.push_back(Q.y);
        buffers.push_back(Q.z);
        buffers.push_back(1.0f);
        buffers.push_back(R.x);
        buffers.push_back(R.y);
        buffers.push_back(R.z);
        buffers.push_back(1.0f);

    }
}

int CubeMesh::NormalCount(void)
{
    return static_cast<int>(normal.size());
}


std::vector<float> CubeMesh::GetNormal()
{
    return normal;
}

std::vector<float> CubeMesh::GetBuffers()
{
    return buffers;
}
