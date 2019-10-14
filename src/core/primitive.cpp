#include "core/primitive.h"

#include "core/meshes/mesh.h"

const Mesh Primitive::cube_mesh = Mesh::FromFile("resources/meshes/cube.json");
const Mesh Primitive::quad_mesh = Mesh::FromFile("resources/meshes/quad.json");
const Mesh Primitive::test_mesh = Mesh::FromFile("resources/meshes/test.json");