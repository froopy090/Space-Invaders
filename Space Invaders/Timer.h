#pragma once


class Timer
{
private:
	float lifetime;

public:
	void Start(float lifetime);
	//void Start();
	bool Finished();
	void Update();
};

