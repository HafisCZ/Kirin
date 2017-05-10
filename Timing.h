#pragma once

namespace Kirin {

	class FPSLimiter {
		public:
			FPSLimiter();
			void init(float targetFPS);

			void setMaxFPS(float targetFPS);

			void begin();
			float end(); // Return FPS
		private:
			void calculateFPS();

			float _maxFPS;
			float _fps;
			float _frameTime;
			unsigned int _startTicks;
	};

}