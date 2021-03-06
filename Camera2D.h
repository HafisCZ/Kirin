#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Kirin {

	class Camera2D
	{
		public:
			Camera2D();
			~Camera2D();

			void init(int screenWidth, int screenHeight);
			void update();
			
			glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
			bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

			void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
			void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

			glm::mat4 getCameraMatrix() { return _cameraMatrix; }
			glm::vec2 getPosition() { return _position; }
			float getScale() { return _scale; }

		private:
			int _screenWidth, _screenHeight;
			bool _needsMatrixUpdate;
			float _scale;
			glm::vec2 _position;
			glm::mat4 _cameraMatrix;
			glm::mat4 _orthoMatrix;
	};

}