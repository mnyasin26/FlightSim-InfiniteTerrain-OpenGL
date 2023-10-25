#pragma once
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

void initializePlaneVAO(const int res, const int width, GLuint * planeVAO, GLuint * planeVBO, GLuint * planeEBO);

glm::vec3 genRandomVec3();


#define ASSERT_GL_ERRORS() assertGLErrorsImpl(__func__)

namespace fly
{

    const float PI = 3.1415926535;

    bool assertGLErrorsImpl(const char* caller);

    template <typename T>
    constexpr inline T sq(T val)
    {
        return val * val;
    }

    template <typename T>
    constexpr inline T sign(T x)
    {
        return x != 0 ? x / std::abs(x) : 0;
    }

    template <typename T, typename U>
    inline T lerp(T t, U&& a, U&& b)
    {
        return a * (1 - t) + b * t;
    }

    inline glm::vec3 component_wise_apply(const glm::vec3& a, const glm::vec3& b,
        const float& (*f)(const float&, const float&))
    {
        return { f(a.x, b.x), f(a.y, b.y), f(a.z, b.z) };
    }

    inline std::ostream& operator<<(std::basic_ostream<char>& out, const glm::vec3& vec)
    {
        out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"
            << "; ";
        return out;
    }

}



namespace fly
{

    // Simple wrapper for a vao
    class VertexArrayObject
    {
    public:
        VertexArrayObject() { glGenVertexArrays(1, &m_object); }
        ~VertexArrayObject() { glDeleteVertexArrays(1, &m_object); }
        void bind() { glBindVertexArray(m_object); }
        void unbind() {/* glBindVertexArray(0)*/ }

        VertexArrayObject(const VertexArrayObject& other) = delete;
        const VertexArrayObject operator=(const VertexArrayObject& other) = delete;
    private:
        GLuint m_object;
    };

}



namespace fly
{

    // Not actually used...
    class Renderer
    {
    public:
        virtual ~Renderer() {}
        virtual void  draw() = 0;
        // Just draw, with whatever shader's bound. Used to create the shadow map.
        virtual void  rawDraw() = 0; // I really dig that rhyme

        virtual void setProjection(const glm::mat4& proj) = 0;
        virtual void setView(const glm::mat4& view) = 0;
    };

}



namespace fly
{

    struct AABB
    {
        glm::vec3 position;
        glm::vec3 dimensions;
    };

    struct OBB
    {
        OBB(const glm::vec3& dimensions, const glm::mat4& transformation);
        AABB getAABB() const;

        glm::vec3 points[8];
    };

}




#endif // UTILITY_H
