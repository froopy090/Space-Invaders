#pragma once


class Timer
{
private:
	float lifetime;

public:
	void Start(float lifetime);
	bool Finished();
	void Update();
};

