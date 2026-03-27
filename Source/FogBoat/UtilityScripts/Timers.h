// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FOGBOAT_API FTimer : FTickableGameObject
{
public:
	virtual ~FTimer();

	float Time;
	float Progress = Time / InitialTime;

	DECLARE_MULTICAST_DELEGATE(OnTimerStartEvent);
	OnTimerStartEvent OnTimerStart;
	DECLARE_MULTICAST_DELEGATE(OnTimerStopEvent);
	OnTimerStopEvent OnTimerStop;

protected:
	float InitialTime;

	FTimer(float Value);

private:
	bool IsRunning;

public:
	void Start();
	void Stop();

	void Resume() { IsRunning = true; }
	void Pause() { IsRunning = false; }

	bool GetIsRunning() { return IsRunning; }

	virtual void Tick(float DeltaTime) override = 0;
	// Override functions to control ticking
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MyTickableObject, STATGROUP_Tickables);
	}
    
	// You can override this to conditionally enable/disable ticking
	virtual bool IsTickable() const override
	{
		return true; 
	}
};

class CountdownTimer : public FTimer
{
public:
	CountdownTimer(float Value) : FTimer(Value)
	{
	};
	virtual ~CountdownTimer() override;

	bool IsFinished = Time <= 0;

	virtual void Tick(float DeltaTime) override;

	void Reset();
	void Reset(float NewTime);
};

class StopwatchTimer : public FTimer
{
public:
	StopwatchTimer() : FTimer(0)
	{
	};
	virtual ~StopwatchTimer() override;

	virtual void Tick(float DeltaTime) override;

	void Reset();
	float GetTime();
};
