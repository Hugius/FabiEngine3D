#include <GLM/gtc/matrix_transform.hpp>
#include <algorithm>

#include <WE3D/CameraManager.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>

CameraManager::CameraManager(ShaderBus& shaderBus) :
	p_shaderBus(shaderBus)
{
	p_aspectRatio = float(Config::getInst().getWindowWidth()) / float(Config::getInst().getWindowHeight());
}

void CameraManager::update(WindowManager & windowManager, float delta)
{
	if (p_firstPersonViewEnabled)
	{
		// Get mouse position
		ivec2 mousePos;
		if (p_mustCenter)
		{
			mousePos = Config::getInst().getWindowSize() / 2;
			p_mustCenter = false;
		}
		else
		{
			mousePos = windowManager.getMousePos();
		}

		// Reset mouse position in the middle of the screen
		windowManager.setMousePos(ivec2(Config::getInst().getWindowWidth() / 2, Config::getInst().getWindowHeight() / 2));

		// Offset between current and last mouse pos
		float xoffset = float(mousePos.x)                              - float(Config::getInst().getWindowWidth() / 2);
		float yoffset = float(Config::getInst().getWindowHeight() / 2) - float(mousePos.y);

		// Applying mouse sensitivity
		xoffset *= (p_mouseSensitivity * delta) / 100.0f;
		yoffset *= (p_mouseSensitivity * delta) / 100.0f;

		// Calculate overall mouse offset
		p_mouseOffset = (xoffset + yoffset) / 2.0f;

		// Calculate pitch & yaw
		p_pitch += yoffset;
		p_yaw = std::fmod((p_yaw + xoffset), 360.0f); // Can't be higher than 360 degrees

		// So the player cannot unnaturally vertically turn its head 
		p_pitch = std::clamp(p_pitch, -89.0f, 89.0f);
	}

	// Limit yaw
	if (p_yaw < 0.0f)
	{
		p_yaw = 360.0f - fabsf(p_yaw);
	}
	p_yaw = std::fmod(p_yaw, 360.0f);

	// Update matrices
	updateMatrices();
}

void CameraManager::updateMatrices()
{
	// Front vector(look direction)
	p_front.x = cos(glm::radians(p_pitch)) * cos(glm::radians(p_yaw));
	p_front.y = sin(glm::radians(p_pitch));
	p_front.z = cos(glm::radians(p_pitch)) * sin(glm::radians(p_yaw));

	// Calculate the view matrix input
	p_front = glm::normalize(p_front);
	p_right = glm::normalize(glm::cross(p_front, vec3(0.0f, 1.0f, 0.0f)));
	p_up    = glm::normalize(glm::cross(p_right, p_front));

	// Projection matrix
	p_projectionMatrix = glm::perspective(glm::radians(p_fov), p_aspectRatio, p_nearZ, p_farZ);

	// View matrix
	p_viewMatrix[0][0] =  p_right.x;
	p_viewMatrix[1][0] =  p_right.y;
	p_viewMatrix[2][0] =  p_right.z;
	p_viewMatrix[0][1] =  p_up.x;
	p_viewMatrix[1][1] =  p_up.y;
	p_viewMatrix[2][1] =  p_up.z;
	p_viewMatrix[0][2] = -p_front.x;
	p_viewMatrix[1][2] = -p_front.y;
	p_viewMatrix[2][2] = -p_front.z;
	p_viewMatrix[3][0] = -glm::dot(p_right, p_pos);
	p_viewMatrix[3][1] = -glm::dot(p_up, p_pos);
	p_viewMatrix[3][2] =  glm::dot(p_front, p_pos);
	
	// Update shaderbus
	p_shaderBus.setCameraYaw(p_yaw);
	p_shaderBus.setCameraPitch(p_pitch);
	p_shaderBus.setCameraPos(p_pos);
	p_shaderBus.setViewMatrix(p_viewMatrix);
	p_shaderBus.setProjectionMatrix(p_projectionMatrix);
	p_shaderBus.setNearZ(p_nearZ);
	p_shaderBus.setFarZ(p_farZ);
}

void CameraManager::translateFollowX(float speed, float delta) // Side movement
{ 
	if (p_freeMovementEnabled)
	{
		p_pos += p_right * ((speed * delta) / 100.0f);
	}
}

void CameraManager::translateFollowZ(float speed, float delta) // Forward movement
{
	if (p_freeMovementEnabled)
	{
		vec3 tempFront = p_front;
		tempFront.x = cos(glm::radians(p_yaw));
		tempFront.z = sin(glm::radians(p_yaw));
		p_pos.x += tempFront.x * ((speed * delta) / 100.0f);
		p_pos.z += tempFront.z * ((speed * delta) / 100.0f);
	}
}

void CameraManager::translateFollowZY(float speed, float delta) // Forward movement
{
	if (p_freeMovementEnabled)
	{
		p_pos.x += p_front.x * ((speed * delta) / 100.0f);
		p_pos.y += p_front.y * ((speed * delta) / 100.0f);
		p_pos.z += p_front.z * ((speed * delta) / 100.0f);
	}
}

void CameraManager::enableFirstPersonView()
{
	p_firstPersonViewEnabled = true;
}

void CameraManager::disableFirstPersonView()
{
	p_firstPersonViewEnabled = false;
}

void CameraManager::enableFreeMovement()
{
	p_freeMovementEnabled = true;
}

void CameraManager::disableFreeMovement()
{
	p_freeMovementEnabled = false;
}

void CameraManager::setFOV(float val)
{
	p_viewMatrix[3][2] = glm::dot(p_front, p_pos);
	p_fov = val;
}

void CameraManager::setMouseSensitivity(float speed)
{
	p_mouseSensitivity = speed;
}

void CameraManager::setYaw(float val)
{
	p_yaw = val;
	p_yaw = std::fmod(p_yaw, 360.0f);
}

void CameraManager::setPitch(float val)
{
	p_pitch = val;
	p_pitch = std::clamp(p_pitch, -89.0f, 89.0f);
}

void CameraManager::setNearZ(float val)
{
	p_nearZ = val;
}

void CameraManager::setFarZ(float val)
{
	p_farZ = val;
}

const vec3 CameraManager::getPosition() const
{
	return p_pos;
}

const vec3 CameraManager::getFront() const
{
	return p_front;
}

const float CameraManager::getYaw() const
{
	return p_yaw;
}

const float CameraManager::getPitch() const
{
	return p_pitch;
}

const float CameraManager::getMouseOffset() const
{
	return p_mouseOffset;
}

const bool CameraManager::isFirstPersonViewEnabled() const
{
	return p_firstPersonViewEnabled;
}

void CameraManager::translate(vec3 translation, float delta)
{
	if (p_freeMovementEnabled)
	{
		p_pos += translation * delta;
	}
}

void CameraManager::setPosition(vec3 val)
{
	if (p_freeMovementEnabled)
	{
		p_pos = val;
	}
}

void CameraManager::invertYaw()
{
	p_yaw = -p_yaw;
}

void CameraManager::invertPitch()
{
	p_pitch = -p_pitch;
}

void CameraManager::center()
{
	p_mustCenter = true;
}

const mat4 & CameraManager::getViewMatrix() const
{
	return p_viewMatrix;
}

const mat4 & CameraManager::getProjectionMatrix() const
{
	return p_projectionMatrix;
}
