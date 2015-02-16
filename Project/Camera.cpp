#include "Camera.h"
#include <iostream>

Camera::Camera(void)
{
	SetCameraType(LAND_CAM);
	Reset();
}

Camera::Camera(CAM_TYPE ct)
{
	SetCameraType(ct);
	Reset();
}

Camera::~Camera(void)
{
}

void Camera::SetCameraType(CAM_TYPE ct)
{
	CameraType = ct;
}

void Camera::Reset(void)
{
	Position = Vector3D(0.0, 0.0, 0.0);
	Along = Vector3D(1.0, 0.0, 0.0);
	Up = Vector3D(0.0, 1.0, 0.0);
	Forward = Vector3D(0.0, 0.0, -1.0);
//	Update();
}

void Camera::Update()
{
	gluLookAt(Position.x, Position.y, Position.z, Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, 0.0f,1.0f,0.0f);
	speed = 4.0f;
	//camera zoom
	if(isZoomOut)
	{
		ZoomOut(-800,speed);
	}
	if(isZoomIn)
	{
		ZoomIn(-500,speed);
	}
	if(isPanLeft)
	{
		PanLeft(800,speed);
	}
	if(isPanRight)
	{
		PanRight(0,speed);
	}
	if(isPanUp)
	{
		PanUp(600,speed);
	}
	if(isPanDown)
	{
		PanDown(0,speed);
	}
}

Vector3D Camera::GetPosition()
{
	return Position;
}

void Camera::SetPosition( GLfloat x, GLfloat y, GLfloat z )
{
	this->Position.Set( x, y, z );
}

void Camera::SetDirection( GLfloat x, GLfloat y, GLfloat z )
{
	this->Forward.Set( x, y, z );
}

void Camera::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}
void Camera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void Camera::Roll(GLfloat theta)
{
}
void Camera::Walk(GLfloat delta)
{
	Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
}
void Camera::Strafe(GLfloat delta)
{
	Along = Forward.crossVector3D( Up );
	Along.normalizeVector3D();
	Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
}
void Camera::Fly(GLfloat delta)
{
}

void Camera::ZoomIn(float limit , float speed)
{
	Position.Set(Position.x,Position.y,Position.z + speed);
	if(Position.z >= limit )
	{
		isZoomIn = false;
		Position.z = limit;
	}
}
void Camera::ZoomOut(float limit , float speed)
{
	Position.Set(Position.x,Position.y,Position.z - speed);
	if(Position.z <= limit )
	{
		isZoomOut = false;
		Position.z = limit;
	}
}

void Camera::PanLeft(float limit , float speed)
{
	Position.Set(Position.x + speed,Position.y,Position.z);
	if(Position.x >=limit )//800
	{
		isPanLeft = false;
		Position.x = limit;
	}
}

void Camera::PanRight(float limit , float speed)
{
	Position.Set(Position.x - speed,Position.y,Position.z);
	if(Position.x <=limit )//0
	{
		isPanRight = false;
		Position.x = limit;
	}
}
void Camera::PanUp(float limit , float speed)
{
	Position.Set(Position.x,Position.y + speed,Position.z);
	if(Position.y >= limit )//600
	{
		isPanUp = false;
		Position.y = limit;
	}
}
void Camera::PanDown(float limit , float speed)
{
	Position.Set(Position.x,Position.y - speed,Position.z);
	if(Position.y <= limit )//0
	{
		isPanDown = false;
		Position.y = limit;
	}
}
// Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, 800 , 600, 0, -1, 1 );      
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable( GL_DEPTH_TEST );
	}
}

// Get the direction of the camera
Vector3D Camera::GetDirection(void)
{
	return Forward;
}
