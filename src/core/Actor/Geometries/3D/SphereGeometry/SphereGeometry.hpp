#ifndef SPHERE_GEOMETRY_HPP
#define SPHERE_GEOMETRY_HPP

#include <glm/glm.hpp>

#include "core/engine.typedef.hpp"
#include "core/Actor/Geometries/BufferGeometry/BufferGeometry.hpp"


namespace NoxEngine {

    class SphereGeometry: public BufferGeometry<V3D> {
        public:
            explicit SphereGeometry(const float radius, const unsigned short nbPointsH=70, const unsigned short nbPointsV=70);
            ~SphereGeometry();
    };

}

#endif // SPHERE_GEOMETRY_HPP