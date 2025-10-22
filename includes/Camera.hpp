#pragma once
#include "Vec3.hpp"
#include "Matrix.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera
{
	public:
		Vec3	position;
		Vec3	front;
		Vec3	up;
		Vec3	right;
		Vec3	worldUp;

		float	yaw;
		float	pitch;
		float	speed;
		float	defaultSpeed[1] = {0.2f};
		float	sensitivity;
		bool	firstMouse = true;
		double	lastX = 0.0;
		double	lastY = 0.0;

		Camera(Vec3 startPos = {0.0f, 0.0f, 7.0f}, Vec3 upDir = {0.0f, 1.0f, 0.0f}, float yawAngle = -90.0f, float pitchAngle = 0.0f);
		~Camera();

		Matrix	getViewMatrix() const;
		void	moveForward();
		void	moveBackward();
		void	moveLeft();
		void	moveRight();
		void	moveUp();
		void	moveDown();

		void	camInput(GLFWwindow *window);
		void	updateVectors();
};
