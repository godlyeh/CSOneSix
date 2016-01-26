// ===================================================================================
// External for engine, needed for client time
extern cl_enginefunc_t g_oEngine;
// ===================================================================================

// ===================================================================================
// Timer class
#define UpdateTime() { Timeleft = StartTime + TimeSet - g_oEngine.GetClientTime(); \
					   if (Timeleft < 0) Timeleft = 0; }

class Timer
{
public:
	Timer(float IntervalSeconds)
	{
		Start(IntervalSeconds);
	}

	void Start(float IntervalSeconds)
	{
		if (Started == false)
		{
			StartTime = g_oEngine.GetClientTime();
			TimeSet = IntervalSeconds;
			UpdateTime();
			Started = true;
		}
	}

	void Reset(float IntervalSeconds)
	{
		Started = false;
		Start(IntervalSeconds);
	}

	void Reset()
	{
		Reset(TimeSet);
	}

	void Stop()
	{
		StartTime = g_oEngine.GetClientTime() + TimeSet;
		Timeleft = 0;
	}

	bool Running()
	{
		UpdateTime();
		return Timeleft > 0;
	}

	float TimeLeft()
	{
		UpdateTime();
		return Timeleft;
	}

private:
	float Timeleft = 0;
	float StartTime = 0;
	float TimeSet = 0;
	bool Started = false;
};
// ===================================================================================