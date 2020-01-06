#include "primitive.h"

#include "meshes/cube_mesh.h"

const Mesh Primitive::cube_mesh = Mesh::FromFile("resources/meshes/cube.json");
const Mesh Primitive::quad_mesh = Mesh::FromFile("resources/meshes/quad.json");