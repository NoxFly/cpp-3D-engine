#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <GL/glew.h>

class Shader {
	public:
        static void setShadersPath(const std::string& shadersPath);

		Shader();
		Shader(const std::string& shaderName, GLuint glVersion);
		~Shader();

        bool load();
        void use();

        GLuint getId() const;
        GLuint getGLSLversion() const;
        std::string getName() const;

        // utility uniform functions
        void setBool(const std::string& name, bool value) const;  
        void setInt(const std::string& name, int value) const;   
        void setFloat(const std::string& name, float value) const;

    protected:
        GLuint glVersion, vertexID, fragmentID, programID;
		std::string shaderName;

        bool checkCompileErrors(GLuint& shader, const std::string& type);
        bool compileShader(GLuint& shader, const std::string& type, const std::string& filepath);
        void destroyShader();

        static std::map<GLuint, GLuint> GLSLversions;
        static std::string shadersPath;
};

#endif // SHADER_H