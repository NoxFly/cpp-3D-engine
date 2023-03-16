#include "Geometry.hpp"


namespace NoxEngine {

    std::string Geometry::objectsPath = "./";

    void Geometry::setObjectsPath(const std::string& objectsPath) {
        Geometry::objectsPath = ((objectsPath[0] == '/') ? "." : "") + objectsPath;
    }


    Geometry::Geometry():
        m_hasLoaded(false),
        m_VAO(0), m_VBO(0), m_EBO(0),
        m_data{},
        m_vertexCount(0), m_elementCount(0)
    {}

    Geometry::Geometry(const Geometry& copy):
        Geometry()
    {
        m_data = copy.m_data;

        m_VAO = copy.m_VAO;
        m_VBO = copy.m_VBO;
        m_EBO = copy.m_EBO;

        m_vertexCount = copy.m_vertexCount;
        m_elementCount = copy.m_elementCount;

        m_hasLoaded = copy.m_hasLoaded;
    }

    const Geometry& Geometry::operator=(const Geometry& copy) {
        m_data = copy.m_data;

        m_VAO = copy.m_VAO;
        m_VBO = copy.m_VBO;
        m_EBO = copy.m_EBO;

        m_vertexCount = copy.m_vertexCount;
        m_elementCount = copy.m_elementCount;

        m_hasLoaded = copy.m_hasLoaded;

        return *this;
    }

    Geometry::~Geometry() {
        // TODO : Lifespan of the VAO/VBO/EBO depends of the lifespan of the geometry.
        //        It will be deleted, even if we copy the geometry, and the original is destroyed.
        /*deleteVAO();
        deleteVBO();
        deleteEBO();*/
    }

    const bool Geometry::hasLoaded() const {
        return m_hasLoaded;
    }


    const GLuint Geometry::getVAO() const  noexcept
    {
        return m_VAO;
    }

    const GLuint Geometry::getEBO() const  noexcept
    {
        return m_EBO;
    }

    const GLuint Geometry::getVertexCount() const {
        return m_vertexCount;
    }

    const GLuint Geometry::getElementCount() const {
        return m_elementCount;
    }

    void Geometry::deleteVBO() noexcept
    {
        if (glIsBuffer(m_VBO) == GL_TRUE)
            glDeleteBuffers(1, &m_VBO);
    }

    void Geometry::deleteVAO() noexcept
    {
        if (glIsVertexArray(m_VAO) == GL_TRUE)
            glDeleteVertexArrays(1, &m_VAO);
    }

    void Geometry::deleteEBO() noexcept
    {
        if (glIsBuffer(m_EBO) == GL_TRUE)
            glDeleteBuffers(1, &m_EBO);
    }

    bool Geometry::load() {
        return false;
    }

}