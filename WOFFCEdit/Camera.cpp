#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	m_moveSpeed = 0.3;
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

	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	if (input.mouse_right)
	{
		float rotX = input.mouse_x - m_prevX;
		float rotY = input.mouse_y - m_prevY;

		m_camOrientation.y -= rotX * m_camRotRate;
		m_camOrientation.x -= rotY * m_camRotRate;

		if (m_camOrientation.x > 90)
		{
			m_camOrientation.x = 90;
		}
		if (m_camOrientation.x < -90)
		{
			m_camOrientation.x = -90;
		}
	}

	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input and update stuff
	if (input.forward)
	{
		m_camPosition += m_camLookDirection * m_moveSpeed;
	}
	if (input.back)
	{
		m_camPosition -= m_camLookDirection * m_moveSpeed;
	}
	if (input.right)
	{
		m_camPosition += m_camRight * m_moveSpeed;
	}
	if (input.left)
	{
		m_camPosition -= m_camRight * m_moveSpeed;
	}
	if (input.up)
	{
		m_camPosition.y += m_moveSpeed;
	}
	if (input.down)
	{
		m_camPosition.y -= m_moveSpeed;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	// update previous position
	m_prevX = input.mouse_x;
	m_prevY = input.mouse_y;
}