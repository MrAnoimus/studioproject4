#pragma once
#include "GameStateManager.h"
#include "RandomEvent.h"
#include "Resource.h"

class CGameState
{
	public:
		virtual bool Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(CGameStateManager* theGSM) = 0;
		virtual void Update(CGameStateManager* theGSM) = 0;
		virtual void Draw(CGameStateManager* theGSM) = 0;

		virtual void KeyboardDown(unsigned char key, int x, int y) = 0;
		virtual void KeyboardUp(unsigned char key, int x, int y) = 0;

		virtual void changeSize(int w ,int h) = 0;
		virtual void MouseClick(int button,int state,int x,int y) = 0;
		virtual void MouseMove(int x, int y) = 0;

		void ChangeState(CGameStateManager* theGSM, CGameState* state)
		{
			theGSM->ChangeState(state);
		}

	protected:
		CGameState()
		{
		}
		CResource resource;
		CRandomEvent REvent;
};
