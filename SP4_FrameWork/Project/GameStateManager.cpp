#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "gamestate.h"

bool CGameStateManager::Init(const char* title, int width, int height, 
						 int bpp, bool fullscreen)
{
	m_bFullscreen = fullscreen;
	m_bRunning = true;

	cout << "CGameStateManager::Init\n" << endl;

	return true;
}

void CGameStateManager::Cleanup()
{
	// cleanup the all states
	while ( !StackOfStates.empty() )
	{
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_bFullscreen )
	{
	}

	cout << "CGameStateManager::Cleanup\n" << endl;
}

void CGameStateManager::ChangeState(CGameState* state) 
{
	// cleanup the current state
	if ( !StackOfStates.empty() ) 
	{
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init();
	cout << "CGameStateManager::ChangeState\n" << endl;
}

void CGameStateManager::PushState(CGameState* state)
{
	// pause current state
	if ( !StackOfStates.empty() )
	{
		StackOfStates.back()->Pause();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init();
	cout << "CGameStateManager::PushState\n" << endl;
}

CGameState* CGameStateManager::getActiveState ()
{
	return StackOfStates.back();
}
void CGameStateManager::PopState()
{
	// cleanup the current state
	if ( !StackOfStates.empty() )
	{
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// resume previous state
	if ( !StackOfStates.empty() )
	{
		StackOfStates.back()->Resume();
	}
	cout << "CGameStateManager::PopState\n" << endl;
}


void CGameStateManager::HandleEvents() 
{
	// let the state handle events
	StackOfStates.back()->HandleEvents(this);
	//cout << "CGameStateManager::HandleEvents\n" << endl;
}

void CGameStateManager::Update()
{
	// let the state update the theGSM
	StackOfStates.back()->Update(this);
	//cout << "CGameStateManager::Update\n" << endl;
}

void CGameStateManager::Draw()
{
	// let the state draw the screen
	StackOfStates.back()->Draw(this);
	//cout << "CGameStateManager::Draw\n" << endl;
}
