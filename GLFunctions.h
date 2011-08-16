

#include "Segment.h"
#include "Vec3f.h"
#include "MatrixCoord3D.h"
#include "AABB.h"


void buildSegmentVertices (const Segment& s, const Vec3f& color, const float& pitch, const float& height, const float& thickness, const unsigned int& offset, float* vertexArray, float* colorArray, unsigned int *ind);

void buildTerminalVertices (const MatrixCoord3D& c, const Vec3f& color, const float& pitch, const float& height, const float& thickness, const unsigned int& offset, float* vertexArray, float* colorArray, unsigned int *ind);

AABB buildBox (const Segment& s, const float& pitch, const float& height, const float& thickness);

AABB buildBox (const MatrixCoord3D& c, const float& pitch, const float& height, const float& thickness);
