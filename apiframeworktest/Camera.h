#ifndef CAMERA_H
#define CAMERA_H

typedef struct tagCameraInfo
{
	float x;
	float y;

	int width;
	int height;

	int backWidth;
	int backHeight;
}CAMERA_INFO;


class Camera
{
public:
	Camera();
	~Camera();

public:
	void Init(int width, int height, int backWidth, int backHeight);
	void Release();

	bool CheckCamraX();
	bool CheckCamraY();
	 
	void CameraShake()
	{
		m_Flag *= -1;
	}

	void SetPos(float x, float y) { m_pCameraInfo->x = x; m_pCameraInfo->y = y; }

	void SetX(float x) { m_pCameraInfo->x = x; }
	float GetX() { return m_pCameraInfo->x; }

	void SetY(float y) { m_pCameraInfo->y = y; }
	float GetY() { return m_pCameraInfo->y; }

	void SetWidth(int width) { m_pCameraInfo->width = width; }
	int GetWidth() { return m_pCameraInfo->width; }

	void SetHeight(int height) { m_pCameraInfo->height = height; }
	int GetHeight() { return m_pCameraInfo->height; }

	void SetBackWidth(int backWidth) { m_pCameraInfo->backWidth = backWidth; }
	int GetBackWidth() { return m_pCameraInfo->backWidth; }

	void SetBackHeight(int backHeight) { m_pCameraInfo->backHeight = backHeight; }
	int GetBackHeight() { return m_pCameraInfo->backHeight; }

	int GetLeft()
	{
		if (!CheckCamraX())
		{
			return (m_pCameraInfo->x <= m_pCameraInfo->backWidth / 2) ? 0
				: m_pCameraInfo->backWidth - m_pCameraInfo->width;
		}

		else
		{
			return (int)m_pCameraInfo->x - m_pCameraInfo->width / 2;
		}
	}

	int GetTop()
	{
		if (!CheckCamraY())
		{
			return (m_pCameraInfo->y <= m_pCameraInfo->backHeight / 2) ? 0
				: m_pCameraInfo->backHeight - m_pCameraInfo->height;
		}

		else
		{
			return (int)m_pCameraInfo->y - m_pCameraInfo->height / 2;
		}
	}

	RECT GetRect()
	{
		RECT rc = { (int)m_pCameraInfo->x - m_pCameraInfo->width / 2,
				   (int)m_pCameraInfo->y - m_pCameraInfo->height / 2,
				   (int)m_pCameraInfo->x + m_pCameraInfo->width / 2,
					(int)m_pCameraInfo->y + m_pCameraInfo->height / 2 };

		return rc;
	}

	void SetIsShaking(bool isShaking) {
		m_IsShaking = isShaking;
		m_ShakeAmount = m_IsShaking ? 6.0f : 0.0f;
	}
	bool GetIsShaking() { return m_IsShaking; }

	float GetShakeNumber() { return m_ShakeAmount * m_Flag; }


private:
	CAMERA_INFO* m_pCameraInfo;

	bool m_IsShaking;
	float m_ShakeAmount;
	int m_Flag;

};


#endif // !CAMERA_H




