#pragma once

#include "vector3D.h"
#include <GL/glut.h>

class Camera
{
	public:
		enum CAM_TYPE { LAND_CAM, AIR_CAM };

	private:
		CAM_TYPE CameraType;
		Vector3D Position;
		Vector3D Along;
		Vector3D Up;
		Vector3D Forward;

	public:
		Camera(void);
		Camera(CAM_TYPE ct);
		~Camera(void);

		void SetCameraType(CAM_TYPE ct);
		void Reset(void);
		void Update();
		Vector3D GetPosition();
		// Get the direction of the camera
		Vector3D GetDirection(void);
		void SetPosition( GLfloat x, GLfloat y, GLfloat z );
		void SetDirection( GLfloat x, GLfloat y, GLfloat z );

		void Pitch(GLfloat theta);
		void Yaw(GLfloat theta);
		void Roll(GLfloat theta);
		void Walk(GLfloat delta);
		void Strafe(GLfloat delta);
		void Fly(GLfloat delta);

		//2d camera zoom
		bool isZoomIn;
		void ZoomIn(float limit , float speed);
		bool isZoomOut;
		void ZoomOut(float limit , float speed);
		//pan left right
		bool isPanLeft;
		void PanLeft(float limit , float speed);
		bool isPanRight;
		void PanRight(float limit , float speed);
		//pan up down
		bool isPanUp;
		void PanUp(float limit , float speed);
		bool isPanDown;
		void PanDown(float limit , float speed);
		// Toggle HUD mode
		void SetHUD(bool m_bHUDmode);
};
