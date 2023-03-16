#ifndef CUBE_HPP
#define CUBE_HPP

#include <string>
#include <glm/glm.hpp>

#include "core/Actor/Objects/Object3D/Object3D.hpp"
#include "utils/Color.hpp"


namespace NoxEngine {

    class Cube: public Object3D {
        public:
            explicit Cube(const float size);
            explicit Cube(const float size, const Color& color);
            explicit Cube(const float size, const std::string& textureName);
            explicit Cube(const float size, const std::string& textureName, const Color& color);
            ~Cube();

        protected:

    };

}

#endif // CUBE_HPP