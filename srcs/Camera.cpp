#include "Camera.hpp"

ostream& operator<<(ostream& os, const Camera& cam)
{
    os << "Camera:\n";
    os << "  Position: (" << cam.position.x << ", " << cam.position.y << ", " << cam.position.z << ")\n";
    os << "  Front:    (" << cam.front.x << ", " << cam.front.y << ", " << cam.front.z << ")\n";
    os << "  Up:       (" << cam.up.x << ", " << cam.up.y << ", " << cam.up.z << ")\n";
    os << "  Right:    (" << cam.right.x << ", " << cam.right.y << ", " << cam.right.z << ")\n";
    os << "  WorldUp:  (" << cam.worldUp.x << ", " << cam.worldUp.y << ", " << cam.worldUp.z << ")\n";
    os << "  Yaw: " << cam.yaw << ", Pitch: " << cam.pitch << "\n";
    os << "  Speed: " << cam.speed << ", Sensitivity: " << cam.sensitivity << "\n";
    return os;
}

Camera::Camera(Vec3 startPos, Vec3 upDir, float yawAngle, float pitchAngle):
position(startPos), front({0.0f, 0.0f, -1.0f}), up({0.0f, 1.0f, 0.0f}), right(), worldUp(upDir), yaw(yawAngle), pitch(pitchAngle), speed(0.2f), sensitivity(0.1f)
{}

Camera::~Camera() {}

Matrix	Camera::getViewMatrix() const
{
	return Matrix::lookAt(position, position + front, up);
}

void	Camera::moveForward()
{
	position += front * speed;
}

void	Camera::moveBackward()
{
	position -= front * speed;
}

void	Camera::moveLeft()
{
	right = Vec3::cross(front, worldUp).normalized();
	position -= right * speed;
}

void	Camera::moveRight()
{
	right = Vec3::cross(front, worldUp).normalized();
	position += right * speed;
}

void	Camera::moveUp()
{
	position += worldUp * speed;

}

void	Camera::moveDown()
{
	position -= worldUp * speed;

}

void	Camera::processMouse(float offsetX, float offsetY)
{
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	updateVectors();
}

void Camera::updateVectors()
{
	Vec3 newFront;

	newFront.x = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
	newFront.y = sin(pitch * M_PI / 180.0f);
	newFront.z = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
	front = newFront.normalized();

	up = Vec3::cross(right, front).normalized();
	right = Vec3::cross(front, worldUp).normalized();
}

void Camera::mouseMovement(GLFWwindow *window)
{
	// (void)window;
	double xpos = 0.0, ypos = 0.0;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double offsetX = xpos - lastX;
	double offsetY = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	processMouse(offsetX, offsetY);
}

void Camera::camInput(GLFWwindow *window)
{
	//move Cam
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) moveRight();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) moveUp();
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) moveDown();

	//reset Cam
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		position = {0.0f, 0.0f, 7.0f};
		yaw = -90.0f;
		pitch = 0.0f;
		sensitivity = 0.1f;
		updateVectors();
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		mouseMovement(window);
	} else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstMouse = true;
	}
}
