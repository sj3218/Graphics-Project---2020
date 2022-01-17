/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#ifndef CS250_CUBEMESH_H
#define CS250_CUBEMESH_H

#include "Mesh.h"
#include <vector>

class CubeMesh : public Mesh {
  public:
      CubeMesh();

    int VertexCount(void) override;
    Point GetVertex(int i) override;
    Vector Dimensions(void) override;
    Point Center(void) override;
    int FaceCount(void) override;
    Face GetFace(int i) override;
    int EdgeCount(void) override;
    Edge GetEdge(int i) override;

    void InitNormal();
    int NormalCount(void);

    std::vector<float> GetNormal();
    std::vector<float> GetBuffers();

  private:
    static const Point vertices[8];
    static const Face faces[12];
    static const Edge edges[12];

    std::vector<float> normal;
    std::vector<float> buffers;
};

#endif

