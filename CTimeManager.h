#pragma once

class CCore;

class CTimeManager : public SingleTon<CTimeManager>
{
	public :
		UINT	GetFPS()		const;
		float	GetDeltaTime()	const;


		friend CCore;
		friend SingleTon<CTimeManager>;
	private :
		CTimeManager();
		virtual ~CTimeManager();

		void	Init();
		void	Release();

		void	Update();

		UINT	m_uiFPS;
		UINT	m_uiUpdateCount;

		float	m_fUpdateOnSecond;
		float	m_fDeltaTime;

		chrono::high_resolution_clock::time_point curTime;
		chrono::high_resolution_clock::time_point prevTime;
};	
#define TIME		CTimeManager::GetInstance()
#define FPS			CTimeManager::GetInstance()->GetFPS()
#define DeltaTime	CTimeManager::GetInstance()->GetDeltaTime()


