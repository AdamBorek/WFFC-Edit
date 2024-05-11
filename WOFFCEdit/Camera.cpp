#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	m_moveSpeed = 0.2;
	m_camRotRate = 1.0;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
}

void Camera::Update(InputCommands input)
{
	if (input.mouse_right)
	{
		float rotX = input.mouse_x - lastX;
		float rotY = input.mouse_y - lastY;

		m_camOrientation.y -= rotX * m_camRotRate;
		m_camOrientation.x -= rotY * m_camRotRate;

		// Clamp vertical rotation to prevent flipping
		if (m_camOrientation.x > 90)
		{
			m_camOrientation.x = 90;
		}
		if (m_camOrientation.x < -90)
		{
			m_camOrientation.x = -90;
		}
	}

	float angleY = m_camOrientation.y * XM_PI / 180.0f;
	float angleX = m_camOrientation.x * XM_PI / 180.0f;
	m_camLookDirection.x = sin(angleY) * cos(angleX);
	m_camLookDirection.y = sin(angleX);
	m_camLookDirection.z = cos(angleY) * cos(angleX);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input
	Vector3 moveDirection = Vector3::Zero;
	if (input.forward)   moveDirection += m_camLookDirection;
	if (input.back)      moveDirection -= m_camLookDirection;
	if (input.right)     moveDirection += m_camRight;
	if (input.left)      moveDirection -= m_camRight;
	if (input.up)        moveDirection.y += 1.0f;
	if (input.down)      moveDirection.y -= 1.0f;

	m_camPosition += moveDirection * m_moveSpeed;

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	// update previous position
	lastX = input.mouse_x;
	lastY = input.mouse_y;
}