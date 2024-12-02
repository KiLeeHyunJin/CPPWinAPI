#pragma once
static class Process
{
public : 
	static Process* Instance();
	void Update();
private : 
	static Process* instance;
	Process();
	~Process();
};

