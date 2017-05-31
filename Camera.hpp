#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

BEGIN_XE_NAMESPACE

class Camera
{
public:
	Camera() :
		_focus(0, 0),
		_pitch(0),
		_yaw(0),
		_altitude(10),
		_fovY(0.78539816339f),
		_aspectRatio(4.0f / 3.0f),
		_near(0.1f),
		_far(500.0f),
		_projection(1.0f),
		_view(1.0f),
		_eye(0.0f),
		_center(0.0f),
		_viewChanged(true),
		_projectionChanged(true),
		_viewProjectionChanged(true)
	{ }

	void translate(float x, float z)
	{
		viewChanged();
		_focus.x = _focus.x + x;
		_focus.y = _focus.y + z;
	}

	void zoom(float altitudeDelta)
	{
		viewChanged();
		_altitude = _altitude + altitudeDelta;
	}

	void rotate(float yawDelta)
	{
		viewChanged();
		_yaw = _yaw + yawDelta;
	}

	void tilt(float pitchDelta)
	{
		viewChanged();
		_pitch = _pitch + pitchDelta;
	}

	glm::mat4 projection()
	{
		if (_projectionChanged)
		{
			updateProjection();
		}
		return _projection;
	}

	glm::mat4 view()
	{
		if (_viewChanged)
		{
			updateView();
		}
		return _view;
	}

	glm::mat4 viewProjection()
	{
		if (_viewProjectionChanged)
		{
			updateViewProjection();
		}
		return _viewProjection;
	}

	glm::vec3 eye() const { return _eye; }
	glm::vec3 center() const { return _center; }

private:
	void viewChanged()
	{
		_viewChanged = true;
		_viewProjectionChanged = true;
	}

	void projectionChanged()
	{
		_projectionChanged = true;
		_viewProjectionChanged = true;
	}

	void updateProjection()
	{
		_projection = glm::perspective(_fovY, _aspectRatio, _near, _far);
		_projectionChanged = false;
	}

	void updateView()
	{
		auto eye = glm::vec3(_focus.x, _altitude, _focus.y + _altitude / 1.5f);
		auto center = glm::vec3(_focus.x, 0.0f, _focus.y);
		auto up = glm::vec3(0.0f, 1.0f, 0.0f);
		_view = glm::lookAt(eye, center, up);
		_eye = eye;
		_center = center;
		_viewChanged = false;
	}

	void updateViewProjection()
	{
		_viewProjection = projection() * view();
		_viewProjectionChanged = false;
	}

	glm::vec2 _focus;
	float _pitch;
	float _yaw;
	float _altitude;
	float _fovY;
	float _aspectRatio;
	float _near;
	float _far;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProjection;
	glm::vec3 _eye;
	glm::vec3 _center;

	bool _viewChanged;
	bool _projectionChanged;
	bool _viewProjectionChanged;
};

END_XE_NAMESPACE
