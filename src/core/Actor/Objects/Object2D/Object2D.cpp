#include "Object2D.hpp"

#include "Console/Console.hpp"


namespace NoxEngine {

    Object2D::Object2D():
        Actor<V2D>()
    {}

    Object2D::Object2D(Geometry* geometry, Material<V2D>* material):
        Actor<V2D>(geometry, material)
    {}

    Object2D::~Object2D()
    {}

}