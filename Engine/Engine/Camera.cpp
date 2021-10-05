#include "Camera.h"

namespace diffusion {

Camera::Camera(Game& game)
    : m_game(game)
{
    m_projection_matrix = glm::perspective(
        static_cast<float>(glm::radians(60.0f)),  // ������������ ���� ������ � ��������. ������ ����� 90&deg; (����� �������) � 30&deg; (�����)
        16.0f / 9.0f,                          // ��������� ������. ������� �� �������� ������ ����. ��������, ��� 4/3 == 800/600 == 1280/960
        0.1f,                                  // ������� ��������� ���������. ������ ���� ������ 0.
        100.0f                                 // ������� ��������� ���������.
    );

    //recalculate_state();
    m_camera_matrix = glm::lookAt(
        m_camera_position, // ������� ������ � ������� ������������
        m_camera_target,   // ��������� ���� �� �������� � ������� ������������
        m_up_vector        // ������, ����������� ����������� �����. ������ (0, 1, 0)
    );
}

void Camera::move_forward(float multiplier)
{
    glm::vec3 direction = glm::normalize(m_camera_target - m_camera_position) * multiplier;
    m_camera_position += direction;
    m_camera_target += direction;
    recalculate_state();

    callback_list(direction);
}

void Camera::move_backward(float multiplier)
{
    glm::vec3 direction = glm::normalize(m_camera_target - m_camera_position) * multiplier;
    m_camera_position -= direction;
    m_camera_target -= direction;
    recalculate_state();

    callback_list(-direction);
}

void Camera::move_left(float multiplier)
{
    glm::vec3 forward_vec = glm::normalize(m_camera_target - m_camera_position);
    glm::vec3 direction = glm::cross(forward_vec, m_up_vector) * multiplier;
    m_camera_position -= direction;
    m_camera_target -= direction;
    recalculate_state();

    callback_list(-direction);
}

void Camera::move_right(float multiplier)
{
    glm::vec3 forward_vec = glm::normalize(m_camera_target - m_camera_position);
    glm::vec3 direction = glm::cross(forward_vec, m_up_vector) * multiplier;
    m_camera_position += direction;
    m_camera_target += direction;
    recalculate_state();

    callback_list(direction);
}

void Camera::move_up(float multiplier)
{
    glm::vec3 direction = glm::vec3(m_up_vector * multiplier);
    m_camera_position += direction;
    m_camera_target += direction;
    recalculate_state();

    callback_list(direction);
}

void Camera::move_down(float multiplier)
{
    glm::vec3 direction = glm::vec3(m_up_vector * multiplier);
    m_camera_position -= direction;
    m_camera_target -= direction;
    recalculate_state();

    callback_list(-direction);
}

void Camera::recalculate_state()
{
    m_camera_matrix = glm::lookAt(
        m_camera_position, // ������� ������ � ������� ������������
        m_camera_target,   // ��������� ���� �� �������� � ������� ������������
        m_up_vector        // ������, ����������� ����������� �����. ������ (0, 1, 0)
    );

    m_game.update_camera_projection_matrixes(m_camera_matrix, m_projection_matrix);
}

} // namespace diffusion {