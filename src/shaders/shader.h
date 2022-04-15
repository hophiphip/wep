#pragma once

#include <string>

class Shader {
    public:
        unsigned int id;

    public:
        Shader(const std::string &vertex_shader, const std::string &fragmet_shader);

        void use();

        void  setBool(const std::string &name, bool  value) const;
        void   setInt(const std::string &name, int   value) const;
        void setFloat(const std::string &name, float value) const; 
};