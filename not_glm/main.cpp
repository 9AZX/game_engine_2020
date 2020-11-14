#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "not_glm_matrix4.hpp"
#include "not_glm_matrix4x3.hpp"
#include "not_glm_vector3.hpp"
#include "not_glm_vector2.hpp"
#include "not_glm_quaternions.hpp"
#include "not_glm_vector4.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    NotGLM::Matrix4 ourLookAt(NotGLM::Vector3 eye, NotGLM::Vector3 center, NotGLM::Vector3 up)
    {
        auto normalize = [](NotGLM::Vector3 v)
        {
            float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
            return NotGLM::Vector3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
        };

        auto cross = [](NotGLM::Vector3 v, NotGLM::Vector3 v2)
        {
            return NotGLM::Vector3((v.y * v2.z) - (v.z * v2.y),
                (v.z * v2.x) - (v.x * v2.z),
                (v.x * v2.y) - (v.y * v2.x));
        };

        NotGLM::Vector3 f = normalize(center - eye);

        NotGLM::Vector3 s(normalize(cross(f, up)));
        NotGLM::Vector3 u(cross(s, f));

        NotGLM::Matrix4 Result = NotGLM::Matrix4(1.0);
        Result.matrixData[0] = s.x;
        Result.matrixData[4] = s.y;
        Result.matrixData[8] = s.z;
        Result.matrixData[1] = u.x;
        Result.matrixData[5] = u.y;
        Result.matrixData[9] = u.z;
        Result.matrixData[2] = -f.x;
        Result.matrixData[6] = -f.y;
        Result.matrixData[10] = -f.z;
        Result.matrixData[12] = -s.dot(eye);
        Result.matrixData[13] = -u.dot(eye);
        Result.matrixData[14] = f.dot(eye);
        return Result;
    }

    glm::mat4 ourLookAt2(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
    {
        auto normalize = [](glm::vec3 v)
        {
            float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
            return glm::vec3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
        };

        auto cross = [](glm::vec3 v, glm::vec3 v2)
        {
            return glm::vec3((v.y * v2.z) - (v.z * v2.y),
                (v.z * v2.x) - (v.x * v2.z),
                (v.x * v2.y) - (v.y * v2.x));
        };

        glm::vec3 f = normalize(center - eye);

        glm::vec3 s(normalize(cross(f, up)));
        glm::vec3 u(cross(s, f));

        glm::mat4 Result = glm::mat4(1.0);
        Result[0][0] = s.x;
        Result[1][0] = s.y;
        Result[2][0] = s.z;
        Result[0][1] = u.x;
        Result[1][1] = u.y;
        Result[2][1] = u.z;
        Result[0][2] = -f.x;
        Result[1][2] = -f.y;
        Result[2][2] = -f.z;
        Result[3][0] = -glm::dot(s, eye);
        Result[3][1] = -glm::dot(u, eye);
        Result[3][2] = glm::dot(f, eye);
        return Result;
    }
private:
};

int main() {
    HelloTriangleApplication app;

    try {
        NotGLM::Matrix4 mat = NotGLM::Matrix4(1.0);
        NotGLM::Vector3 eye = NotGLM::Vector3(1.0, 1.0, 1.0);
        NotGLM::Vector3 center = NotGLM::Vector3(1.0, 1.0, 1.0);
        NotGLM::Vector3 up = NotGLM::Vector3(1.0, 1.0, 1.0);
        mat = app.ourLookAt(eye, center, up);

        mat.show();

        glm::mat4 mat2 = glm::mat4(1.0);
        glm::vec3 eye2 = glm::vec3(1.0, 1.0, 1.0);
        glm::vec3 center2 = glm::vec3(1.0, 1.0, 1.0);
        glm::vec3 up2 = glm::vec3(1.0, 1.0, 1.0);
        mat2 = app.ourLookAt2(eye2, center2, up2);

        std::cout << glm::to_string(mat2) << std::endl;

        /*NotGLM::Vector2 vec = NotGLM::Vector2(1.0, 2.0);
        vec.show();
        
        glm::vec2 vec2 = glm::vec2(1.0, 2.0);
        std::cout << glm::to_string(vec2) << std::endl;*/

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
