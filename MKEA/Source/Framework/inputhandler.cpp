// COMP710 GP 2D Framework 2020

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "player.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void 
InputHandler::ProcessInput(Game& game, Player& player)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_BACKQUOTE)
			{
				if (game.debugMode)
				{
					game.debugMode = false;
					game.infiniteBattery = false;
				}
				else
				{
					game.debugMode = true;
				}
			}
			if (event.key.keysym.sym == SDLK_9)
			{
				if (game.debugMode)
				{
					if (game.infiniteBattery)
					{
						game.infiniteBattery = false;
					} else {
						game.infiniteBattery = true;
					}
				}
			}

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (game.inMainMenu)
				{
					game.Quit();
				}
				else if (game.inGame)
				{
					if (game.gameOver)
					{
						game.Quit();
					}
					else if (game.isPaused)
					{
						game.isPaused = false;
					}
					else
					{
						game.isPaused = true;
					}
				}
				else
				{
					game.Quit();
				}
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				game.playerMoveLeft = true;
				
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				game.playerMoveRight = true;
				
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (game.getPlayerStatus() == onGround)
				{
					player.setPressJump(true);
					game.playJumpSound = true;
				}
				game.playerClimbing = false;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				game.playerClimbing = true;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				game.playerMoveLeft = false;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				game.playerMoveRight = false;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				game.playerClimbing = false;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (!game.inMainMenu && !game.isPaused && !game.gameOver)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						// Turn on torch and play sound
						game.torchOn = true;
						game.PlayTorchSound();
					}
				}
			}
		}

		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (game.inMainMenu || game.isPaused || game.gameOver)
				{
					game.SetMenuClick(true);
				}
				else
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						// Turn on torch and play sound
						if (game.torchOn)
						{
							game.torchOn = false;
							game.PlayTorchSound();
						}
					}
				}
			}
		}
	}
}
