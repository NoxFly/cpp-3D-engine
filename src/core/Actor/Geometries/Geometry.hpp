#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>


namespace NoxEngine {

    class Geometry {
        public:
            explicit Geometry();
            explicit Geometry(const std::vector<float> vertices);
            explicit Geometry(const std::vector<float> vertices, const std::vector<float> colors);
            explicit Geometry(const std::vector<float> vertices, const std::vector<float> colors, const std::vector<float> textures);
            ~Geometry();

            void setVertices(const std::vector<float> vertices);
            void setColors(const std::vector<float> colors);
            void setTextures(const std::vector<float> textures);

            std::vector<float> getVertices() const;
            std::vector<float> getColors() const;
            std::vector<float> getTextures() const;

        protected:
            std::vector<float> m_vertices;
            std::vector<float> m_colors;
            std::vector<float> m_textures;
    };

}

#endif // GEOMETRY_HPP