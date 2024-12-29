#pragma once
//class CCore;

class CTimeManager
{
public :
		static UINT	GetFPS();
		static float GetDeltaTime();

		//CTimeManager();
		//virtual ~CTimeManager();

		static void	Init();
		static void	Update();

//private:
		/// Frame Delta Time

		static LARGE_INTEGER m_liCpuFrequency;
		static LARGE_INTEGER m_liPrevFrequency;
		static LARGE_INTEGER m_liCurrentFrequency;
		static UINT	m_uiFPS;

		static float	m_fDeltaTime;


		/// Frame Per Second
		//UINT	m_uiUpdateCount;
		//float	m_fUpdateOnSecond;	

		/// Chrono Time
		//chrono::high_resolution_clock::time_point curTime;
		//chrono::high_resolution_clock::time_point prevTime;
};	

//#define TIME		CTimeManager
//#define FPS			CTimeManager::GetFPS()
//#define DeltaTime	CTimeManager::GetDeltaTime()


