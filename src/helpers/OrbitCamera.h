#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helpers/Constants.h"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 look_target;
    glm::mat4 view_matrix;
    glm::vec2 orbit_rotation = glm::vec2(0.0f, 0.0f);
    glm::vec2 last_pos;
    float zoom_distance = 2.0f;

    Camera(float zoom_distance, glm::vec3 look_target, float ORBIT_SPEED, float ZOOM_SPEED) : zoom_distance(zoom_distance), look_target(look_target), view_matrix(glm::mat4(1.0f)), ZOOM_SPEED(ZOOM_SPEED), ORBIT_SPEED(ORBIT_SPEED)
    {
    }

    void updateOrbitRotation(){
        position = glm::rotate(Constants::X_AXIS, orbit_rotation.x, Constants::Y_AXIS);
        position = glm::rotate(position, -orbit_rotation.y, glm::vec3(-position.z, 0.0f, position.x)) * zoom_distance;
        view_matrix = glm::lookAt(position + look_target, look_target, Constants::Y_AXIS);
    }

    void handleMouse(GLFWwindow * window, double xpos, double ypos)  
    {

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) 
        {
            stopped_dragging = true;
            return;
        }

        glm::vec2 mouse_pos = glm::vec2(xpos, ypos);
        if (stopped_dragging)
        {
            last_pos = mouse_pos;
            stopped_dragging = false;
        }

        glm::vec2 delta_pos = last_pos - mouse_pos;

        orbit_rotation += delta_pos * ORBIT_SPEED;

        float limit = glm::pi<float>() * 0.45f;
    
        if (orbit_rotation.y > limit)
            orbit_rotation.y = limit;

        if (orbit_rotation.y < -limit)
            orbit_rotation.y = -limit;

        last_pos = mouse_pos;
    }

    void handleZoom(GLFWwindow* window, double xoffset, double yoffset){
        zoom_distance -= yoffset * ZOOM_SPEED;
        if (zoom_distance < 0.1f)
            zoom_distance = 0.1f;
    }
private:
    bool stopped_dragging;
    float ORBIT_SPEED;
    float ZOOM_SPEED;
};