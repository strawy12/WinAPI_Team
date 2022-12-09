#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	m_pCameraInfo = nullptr;
	m_Flag = -1;
}

Camera::~Camera()
{
}

void Camera::Init(int width, int height, int backWidth, int backHeight)
{
	if (m_pCameraInfo)
	{
		Release();
	}

	m_pCameraInfo = new CAMERA_INFO;
	m_pCameraInfo->width = width;
	m_pCameraInfo->height = height;
	m_pCameraInfo->backWidth = backWidth;
	m_pCameraInfo->backHeight = backHeight;
}

void Camera::Release()
{
	if (m_pCameraInfo)
		delete m_pCameraInfo;
}

bool Camera::CheckCamraX()
{
	if (!m_pCameraInfo)
		return false;

	if (m_pCameraInfo->x - m_pCameraInfo->width / 2 <= 0 ||
		m_pCameraInfo->x + m_pCameraInfo->width / 2 >= m_pCameraInfo->backWidth)
	{
		return false;
	}

	return true;
}

bool Camera::CheckCamraY()
{
	if (!m_pCameraInfo)
		return false;

	if (m_pCameraInfo->y - m_pCameraInfo->height / 2 <= 0 ||
		m_pCameraInfo->y + m_pCameraInfo->height / 2 >= m_pCameraInfo->backHeight)
	{
		return false;
	}

	return true;
}

