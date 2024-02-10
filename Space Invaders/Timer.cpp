#include "Timer.h"
#include "raylib.h"

void Timer::Start(float lifetime) {
	this->lifetime = lifetime;
}

bool Timer::Finished() {
	return lifetime <= 0;
}

void Timer::Update() {
	if (lifetime > 0) {
		lifetime -= GetFrameTime();
	}
}

/*bool Freeze(float lifetime) {
	Timer timer = lifetime;
	while (!timer.Finished()) {
		timer.Update();
	}
}*/