// COMP710 GP 2D Framework 2020

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "map.h"
#include "tile.h"
#include "player.h"
#include "torch.h"
#include "enemy.h"
#include "meleeenemy.h"
#include "shooterenemy.h"
#include "entity.h"
#include "trap.h"
#include "animatedsprite.h" 
#include "Trap.h"
#include "Ladder.h"
#include "Button.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <string.h>
#include <sstream>
#include <cstdio>
#include<thread> 

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, isGameActive(false)
, displaySplash(true)
, levelLoaded(false)
, playerMoveLeft(false)
, playerMoveRight(false)
, scrollLevel(false)
, localPlayer(0)
, playPlayerRunAnimation(false)
, playPlayerJumpAnimation(false)
, inGameOver(false)
, GameOverClick(false)
, currentPlayerAction(playerIdle)
, currentPlayerFacing(FacingRight)
{

}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}
//this method will display the splashscreen then move onto the menu
void Game::SplashScreen(BackBuffer& backBuffer)
{
	if (displaySplash == true)
	{
		splashSprite = new Sprite();
		splashSprite = m_pBackBuffer->CreateSprite("assets\\AUTLogo.png");
		splashSprite->Draw(*m_pBackBuffer);
		backBuffer.Present();
		SDL_Delay(3000);
		backBuffer.Clear();
		displaySplash = false;
		splashSprite = NULL;
	}
}
bool 
Game::Initialise()
{
	const int width = 1920;
	const int height = 1080;

	m_pBackBuffer = new BackBuffer();

	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(0, 0, 0);

	// Initialize Debug Variables
	debugMode = false;
	infiniteBattery = false;

	InitializeSounds();

	// Initialize Game States
	inMainMenu = true;
	inInstructions = false;
	inGame = false;
	isPaused = false;
	gameOver = false;
	SetMenuClick(false);


	// Initialize Sprites
	buttonSpritePlay = new Sprite();
	buttonSpritePlay = m_pBackBuffer->CreateSprite("assets\\buttons\\playLight.png");
	buttonSpritePlayDark = new Sprite();
	buttonSpritePlayDark = m_pBackBuffer->CreateSprite("assets\\buttons\\playDark.png");

	buttonSpriteInstructions = new Sprite();
	buttonSpriteInstructions = m_pBackBuffer->CreateSprite("assets\\buttons\\instructionsLight.png");
	buttonSpriteInstructionsDark = new Sprite();
	buttonSpriteInstructionsDark = m_pBackBuffer->CreateSprite("assets\\buttons\\instructionsDark.png");

	buttonSpriteExit = new Sprite();
	buttonSpriteExit = m_pBackBuffer->CreateSprite("assets\\buttons\\exitLight.png");
	buttonSpriteExitDark = new Sprite();
	buttonSpriteExitDark = m_pBackBuffer->CreateSprite("assets\\buttons\\exitDark.png");

	pauseBackgroundSprite = new Sprite();
	pauseBackgroundSprite = m_pBackBuffer->CreateSprite("assets\\buttons\\pause.png");

	controlsSprite = new Sprite();
	controlsSprite = m_pBackBuffer->CreateSprite("assets\\buttons\\controls.png");

	titleSprite = new Sprite();
	titleSprite = m_pBackBuffer->CreateSprite("assets\\buttons\\title.png");

	torchSprite = new Sprite();
	torchSprite = m_pBackBuffer->CreateSprite("assets\\torch.png");
	torchSpriteDark = new Sprite();
	torchSpriteDark = m_pBackBuffer->CreateSprite("assets\\torchDark.png");

	tileDark = new Sprite();
	tileDark = m_pBackBuffer->CreateSprite("assets\\tileDark.png");
	tileLight = new Sprite();
	tileLight = m_pBackBuffer->CreateSprite("assets\\tile.png");

	tileLLight = new Sprite();
	tileLLight = m_pBackBuffer->CreateSprite("assets\\tileL.png");
	tileLDark = new Sprite();
	tileLDark = m_pBackBuffer->CreateSprite("assets\\tileLDark.png");
	tileRLight = new Sprite();
	tileRLight = m_pBackBuffer->CreateSprite("assets\\tileR.png");
	tileRDark = new Sprite();
	tileRDark = m_pBackBuffer->CreateSprite("assets\\tileRDark.png");

	tileCover = new Sprite();
	tileCover = m_pBackBuffer->CreateSprite("assets\\darkCover.png");

	trap = new Sprite();
	trap = m_pBackBuffer->CreateSprite("assets\\trap.png");
	trapDark = new Sprite();
	trapDark = m_pBackBuffer->CreateSprite("assets\\trapDark.png");

	ladder = new Sprite();
	ladder = m_pBackBuffer->CreateSprite("assets\\ladder.png");
	ladderDark = new Sprite();
	ladderDark = m_pBackBuffer->CreateSprite("assets\\ladderDark.png");

	tileEndPoint = new Sprite();
	tileEndPoint = m_pBackBuffer->CreateSprite("assets\\EndPoint\\1 (1).png");
	tileStartPoint = new Sprite();
	tileStartPoint = m_pBackBuffer->CreateSprite("assets\\EndPoint\\1 (1).png");

	playerSpriteFR = m_pBackBuffer->CreateSprite("assets\\playerIdleFacingRight.png");
	playerSpriteDarkFR = m_pBackBuffer->CreateSprite("assets\\playerIdleDarkFacingRight.png");
	playerSpriteFL = m_pBackBuffer->CreateSprite("assets\\playerIdleFacingLeft.png");
	playerSpriteDarkFL = m_pBackBuffer->CreateSprite("assets\\playerIdleDarkFacingLeft.png");

	playerRunSrpiteFR = m_pBackBuffer->CreateAnimatedSprite("assets\\playerRunFacingRight.png");

	for (int i = 0; i < 8; i++)
	{
		playerRunSrpiteFR->AddFrame(i*64);
	}
	playerRunSrpiteFR->SetFrameWidth(64);
	playerRunSrpiteFR->SetFrameSpeed(0.25f);
	playerRunSrpiteFR->SetLooping(true);

	playerRunSrpiteDarkFR = m_pBackBuffer->CreateAnimatedSprite("assets\\playerRunDarkFacingRight.png");
	for (int i = 0; i < 8; i++)
	{
		playerRunSrpiteDarkFR->AddFrame(i* 64);
	}
	playerRunSrpiteDarkFR->SetFrameWidth(64);
	playerRunSrpiteDarkFR->SetFrameSpeed(0.25f);
	playerRunSrpiteDarkFR->SetLooping(true);

	playerJumpSrpiteFR = m_pBackBuffer->CreateAnimatedSprite("assets\\playerJumpFacingRight.png");
	for (int i = 0; i < 8; i++)
	{
		playerJumpSrpiteFR->AddFrame(i* 64);
	}
	playerJumpSrpiteFR->SetFrameWidth(64);
	playerJumpSrpiteFR->SetFrameSpeed(0.25f);
	playerJumpSrpiteFR->SetLooping(true);

	playerJumpSrpiteDarkFR = m_pBackBuffer->CreateAnimatedSprite("assets\\playerJumpDarkFacingRight.png");
	for (int i = 0; i < 8; i++)
	{
		playerJumpSrpiteDarkFR->AddFrame(i* 64);
	}
	playerJumpSrpiteDarkFR->SetFrameWidth(64);
	playerJumpSrpiteDarkFR->SetFrameSpeed(0.25f);
	playerJumpSrpiteDarkFR->SetLooping(true);

	playerRunSrpiteFL = m_pBackBuffer->CreateAnimatedSprite("assets\\playerRunFacingLeft.png");
	for (int i = 0; i < 8; i++)
	{
		playerRunSrpiteFL->AddFrame(i * 64);
	}
	playerRunSrpiteFL->SetFrameWidth(64);
	playerRunSrpiteFL->SetFrameSpeed(0.25f);
	playerRunSrpiteFL->SetLooping(true);

	playerRunSrpiteDarkFL = m_pBackBuffer->CreateAnimatedSprite("assets\\playerRunDarkFacingLeft.png");
	for (int i = 0; i < 8; i++)
	{
		playerRunSrpiteDarkFL->AddFrame(i * 64);
	}
	playerRunSrpiteDarkFL->SetFrameWidth(64);
	playerRunSrpiteDarkFL->SetFrameSpeed(0.25f);
	playerRunSrpiteDarkFL->SetLooping(true);

	playerJumpSrpiteFL = m_pBackBuffer->CreateAnimatedSprite("assets\\playerJumpFacingLeft.png");
	for (int i = 0; i < 8; i++)
	{
		playerJumpSrpiteFL->AddFrame(i * 64);
	}
	playerJumpSrpiteFL->SetFrameWidth(64);
	playerJumpSrpiteFL->SetFrameSpeed(0.25f);
	playerJumpSrpiteFL->SetLooping(true);

	playerJumpSrpiteDarkFL = m_pBackBuffer->CreateAnimatedSprite("assets\\playerJumpDarkFacingLeft.png");
	for (int i = 0; i < 8; i++)
	{
		playerJumpSrpiteDarkFL->AddFrame(i * 64);
	}
	playerJumpSrpiteDarkFL->SetFrameWidth(64);
	playerJumpSrpiteDarkFL->SetFrameSpeed(0.25f);
	playerJumpSrpiteDarkFL->SetLooping(true);

	localPlayer = new Player();
	localPlayer->Initialise(playerSpriteFR);
	localPlayer->SetSprites(playerSpriteFR, playerSpriteDarkFR);
	torchList.push_back(localPlayer);

	enemySprite = new Sprite();
	enemySprite = m_pBackBuffer->CreateSprite("assets\\ghost1.png");
	darkEnemySprite = new Sprite();
	darkEnemySprite = m_pBackBuffer->CreateSprite("assets\\SlimeOrange\\SlimeOrangeDark.png");//just an invisible sprite
	shooterEnemySprite = new Sprite();
	shooterEnemySprite = m_pBackBuffer->CreateSprite("assets\\wizard.png");

	projectile = new Sprite();
	projectileInvis = new Sprite();
	projectile = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");
	projectileInvis = m_pBackBuffer->CreateSprite("assets\\invisibleBullet.png");

	torch = new Torch();
	torch->Initialise(torchSprite);
	torch->SetSprites(torchSprite, torchSpriteDark);
	torchList.push_back(torch);
	torchOn = false;

	m_pMap = new Map();
	std::vector<Tile*> tileMapScroller;
	std::vector<Tile*> tileMap;
	background = new Sprite;
	background = m_pBackBuffer->CreateSprite("assets\\backgrounddark.png");
	currentPlayerStatus = onAir;
	m_pMap->SetLevel(0);
	CreateLevel();

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this, *localPlayer);
	
	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		
		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);
		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}

		// DEBUG STUB:
//		char buffer[64];
//		sprintf(buffer, "%f", deltaTime);
//		LogManager::GetInstance().Log(buffer);
		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}

void
Game::InitializeSounds()
{
	// Create Fmod System
	result = FMOD::System_Create(&system);

	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("FMOD error! (%d) %s\n");
		exit(-1);
	}
	// Initialize Fmod System
	result = system->init(36, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("FMOD error! (%d) %s\n");
		exit(-1);
	}

	system->createSound("assets\\sounds\\torchOn.wav", FMOD_DEFAULT, 0, &soundTorchOn);
	system->createSound("assets\\sounds\\torchOff.wav", FMOD_DEFAULT, 0, &soundTorchOff);
	system->createSound("assets\\sounds\\jump.wav", FMOD_DEFAULT, 0, &soundJump);
	system->createSound("assets\\sounds\\trap.wav", FMOD_DEFAULT, 0, &soundTrap);
	system->createSound("assets\\sounds\\objective.wav", FMOD_DEFAULT, 0, &soundObjective);

	playJumpSound = false;
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	torch->Process(deltaTime);

	// Update the game world simulation:
	if (inMainMenu)
	{
		CreateButtons();
		gameOver = false;
		// Toggle Sprites When Hovered
		if (buttonPlay->IsCollidingWith(*torch))
		{
			buttonPlay->ChangeSprites(buttonPlay->GetLightSprite());
		}
		else if (buttonInstructions->IsCollidingWith(*torch))
		{
			buttonInstructions->ChangeSprites(buttonInstructions->GetLightSprite());
		}
		else if (buttonExit->IsCollidingWith(*torch))
		{
			buttonExit->ChangeSprites(buttonExit->GetLightSprite());
		}

		// Handle Menu Clicks
		if (menuClick)
		{
			menuClick = false;

			if (buttonPlay->IsCollidingWith(*torch))
			{
				inMainMenu = false;
				inGame = true;
			}
			else if (buttonInstructions->IsCollidingWith(*torch))
			{
				if (inInstructions)
				{
					inInstructions = false;
				}
				else
				{
					inInstructions = true;
				}
			}
			else if (buttonExit->IsCollidingWith(*torch))
			{
				Quit();
			}
		}
	}
	else if (inGame)
	{
		if (localPlayer->playerLive < 1)
		{
			GameOver();
		}
		if (isPaused)
		{
			CreatePauseButtons();

			// Toggle Sprites When Hovered
			if (buttonPlay->IsCollidingWith(*torch))
			{
				buttonPlay->ChangeSprites(buttonPlay->GetLightSprite());
			}
			else if (buttonExit->IsCollidingWith(*torch))
			{
				buttonExit->ChangeSprites(buttonExit->GetLightSprite());
			}

			// Handle Menu Clicks
			if (menuClick)
			{
				menuClick = false;

				if (buttonPlay->IsCollidingWith(*torch))
				{
					isPaused = false;
					inGame = true;
				}
				else if (buttonExit->IsCollidingWith(*torch))
				{
					inMainMenu = true;
					inGame = false;

					ResetGame();
				}
			}
		}
		else if (gameOver)
		{
			{
				// TODO: Game Over Buttons
				if (GetMenuClick())
				{
					SetMenuClick(false);

					if (buttonExit->IsCollidingWith(*torch))
					{
						// Reset Game
					}
				}
			}
		}
		else
		{
			for (size_t i = 0; i < tileMap.size(); i++)
			{
				tileMap[i]->Process(deltaTime);
			}
			ReadyNextLevel();

			// Process Torch
			ManageTorch(deltaTime);

			PlayerFall();

			
			if (playerClimbing)
			{
				if (CheckLadders())
				{
					PlayerClimbingUp(deltaTime);
				}
			}

			playerJumpSrpiteFL->Process(deltaTime);
			playerJumpSrpiteDarkFL->Process(deltaTime);
			playerJumpSrpiteFR->Process(deltaTime);
			playerJumpSrpiteDarkFR->Process(deltaTime);
			playerRunSrpiteFL->Process(deltaTime);
			playerRunSrpiteDarkFL->Process(deltaTime);
			playerRunSrpiteFR->Process(deltaTime);
			playerRunSrpiteDarkFR->Process(deltaTime);

			playerMovement(deltaTime);
			playerTouchEnemy();
			playerJump(deltaTime);
			
			worldPhysic();

			for (int i = 0; i < enemyList.size(); i++)
			{
				if (enemyList[i]->searchPlayer(deltaTime, localPlayer, 500))
				{
					enemyList[i]->Process(deltaTime, localPlayer);
				}
				
			}

			for (int i = 0; i < shooterEnemyList.size(); i++)
			{
				
				if (shooterEnemyList[i]->shootPlayer(deltaTime, localPlayer, 350))
				{
					Shoot();
					bullet->SetPosition(shooterEnemyList[i]->GetPositionX(), shooterEnemyList[i]->GetPositionY());
				}
			}

			for (int i = 0; i < bulletList.size(); i++)
			{
				if (bulletList[i]->IsDead())
				{
					bulletList.erase(bulletList.begin());
				}
				else
				{
					bulletList[i]->Process(deltaTime);
				}
			}

			// Check Trap Collisions
			CheckTraps();

			// Process Lightable Objects
			CheckTorchLight();

			// Check Debugging Features
			if (infiniteBattery)
			{
				torch->SetBatteryLevel(torch->GetMaxBattery());
			}

			setDeltaTime(deltaTime);

			groundCollisionCheck();
		}
		// this creates the game over screen with options to either exit the game or play again
	}
}

void Game::ManageTorch(float deltaTime)
{
	// Check Torch Battery Level
	if (torch->GetBatteryLevel() < 0)
	{
		torchOn = false;
		PlayTorchSound();
	}

	// Toggle Torch Based on Input Variable
	if (torchOn)
	{
		torch->SetTorchOn(true);
	}
	else
	{
		torch->SetTorchOn(false);
	}

	// Process Torch
	torch->Process(deltaTime);
}

void Game::CreateLevel() 
{
	m_pMap->LoadMap(&tileMap);

	for (size_t i = 0; i < tileMap.size(); i++)
	{
		Ladder* l;
		Trap* t;
		Enemy* e;
		switch (tileMap[i]->GetTileType())
		{
		case 0:
			break;
		case 1:
			tileMap.at(i)->Initialise(tileDark);
			tileMap.at(i)->SetSprites(tileLight, tileDark);
			torchList.push_back(tileMap.at(i));
			break;
		case 2:
			tileMap[i]->Initialise(tileStartPoint);
			currentStartPointPositionX = tileStartPoint->GetX();
			currentStartPointPositionY = tileStartPoint->GetY();
			break;
		case 3:
			tileMap[i]->Initialise(tileEndPoint);
			break;
		case 4:
			// Create Trap object on top of tile
			t = new Trap();
			t->Initialise(trap, tileMap.at(i)->GetPositionX(), tileMap.at(i)->GetPositionY() + 25);
			t->SetSprites(trap, trapDark);
			torchList.push_back(t);
			trapList.push_back(t);

			// Set tile to 0
			tileMap.at(i)->SetTileType(0);
			break;
		case 5:
			// Create Ladder object on top of tile
			l = new Ladder();
			l->Initialise(ladder, tileMap.at(i)->GetPositionX(), tileMap.at(i)->GetPositionY() + 25);
			l->SetSprites(ladder, ladderDark);
			torchList.push_back(l);
			ladderList.push_back(l);

			// Set tile to 0
			tileMap.at(i)->SetTileType(0);
			break;
		case 6:
			tileMap[i]->Initialise(tileCover);
			break;
		case 7:
			tileMap[i]->Initialise(tileLLight);
			tileMap[i]->SetSprites(tileLLight, tileLDark);
			torchList.push_back(tileMap[i]);
			break;
		case 8:
			tileMap[i]->Initialise(tileRLight);
			tileMap[i]->SetSprites(tileRLight, tileRDark);
			torchList.push_back(tileMap[i]);
			break;
		case 9:
			e = new MeleeEnemy(1, 25, 1, tileMap[i]->GetPositionX(), tileMap[i]->GetPositionY() + 25);
			e->Initialise(enemySprite);
			e->SetSprites(enemySprite, darkEnemySprite);
			enemyList.push_back(e);
			torchList.push_back(e);
			tileMap.at(i)->SetTileType(0);
			break;
		case 10:
			e = new ShooterEnemy(1, 0, 1, tileMap[i]->GetPositionX()+20, tileMap[i]->GetPositionY());
			e->Initialise(shooterEnemySprite);
			e->SetSprites(shooterEnemySprite, darkEnemySprite);
			shooterEnemyList.push_back(e);
			torchList.push_back(e);
			tileMap.at(i)->SetTileType(0);
			break;
		default:
			break;
		}
	}
}

void Game::DrawLevel()
{
	for (size_t i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i]->GetTileType() !=  0)
		{
			tileMap[i]->Draw(*m_pBackBuffer);
		}		
	}

	for (size_t i = 0; i < trapList.size(); i++)
	{
		if (!trapList.at(i)->IsDead())
		{
			trapList.at(i)->Draw(*m_pBackBuffer);
		}
	}

	for (size_t i = 0; i < ladderList.size(); i++)
	{
		if (!ladderList.at(i)->IsDead())
		{
			ladderList.at(i)->Draw(*m_pBackBuffer);
		}
	}
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList.at(i)->IsDead())
		{
			enemyList.at(i)->Draw(*m_pBackBuffer);
		}
	}
	for (size_t i = 0; i < shooterEnemyList.size(); i++)
	{
		if (!shooterEnemyList.at(i)->IsDead())
		{
			shooterEnemyList.at(i)->Draw(*m_pBackBuffer);
		}
	}
	for (size_t i = 0; i < bulletList.size(); i++)
	{
		if (!bulletList.at(i)->IsDead())
		{
			LogManager::GetInstance().Log("Bullet made!");
			bulletList.at(i)->Draw(*m_pBackBuffer);
		}
	}
}
// this method checks if collision with the endpoint happens it so copy next level to another vector and set all of its elements off screen to the right
void Game::ReadyNextLevel()
{
		if (tileEndPoint->GetX() != 0)
		{
			if (CheckEndPointCollision() == true)
			{
				scrollLevel = true;
			}
		}
}
//this method overrides the end of tileMap with the start of tileMapScroller to have a scrolling effect
void Game::NextLevelDraw()
{
	if (scrollLevel == true)
	{
		trapList.clear();
		ladderList.clear();
		enemyList.clear();
		shooterEnemyList.clear();
		bulletList.clear();
		tileMap.clear();
		m_pMap->SetLevel(m_pMap->GetLevel() + 1);
		scrollLevel = false;
		localPlayer->SetPosition(10, 0);
		CreateLevel();
	}
}
void Game::CheckTorchLight()
{
	for (size_t i = 0; i < torchList.size(); i++)
	{
		if (torchList.at(i)->GetIsLightable())
		{
			float entityX = torchList.at(i)->GetPositionX();
			float entityY = torchList.at(i)->GetPositionY();

			float torchX = torch->GetPositionX();
			float torchY = torch->GetPositionY();
			float radius = torch->GetRadius();

			if (((entityX - torchX)*(entityX - torchX) + (entityY - torchY)*(entityY - torchY)) < radius*radius)
			{
				if (torch->GetTorchOn())
				{
					torchList.at(i)->SetIsLit(true);
					torchList.at(i)->ChangeSprites(torchList.at(i)->GetLightSprite());
				}
				else
				{
					torchList.at(i)->SetIsLit(false);
					torchList.at(i)->ChangeSprites(torchList.at(i)->GetDarkSprite());
				}
			}
			else
			{
				torchList.at(i)->SetIsLit(false);
				torchList.at(i)->ChangeSprites(torchList.at(i)->GetDarkSprite());
			}
		}
	}
}

void Game::CheckTraps()
{

	for (size_t i = 0; i < trapList.size(); i++)
	{
		if (!trapList.at(i)->IsDead())
		{
			if (localPlayer->IsCollidingWith(*trapList.at(i)))
			{
				system->playSound(soundTrap, 0, false, &channel);
				localPlayer->SetPosition(tileStartPoint->GetX(), tileStartPoint->GetY());
				localPlayer->playerLive--;
				resetMap();
			}
		}
	}
}

bool Game::CheckLadders()
{
	bool onLadder = false;

	for (size_t i = 0; i < ladderList.size(); i++)
	{
		if (!ladderList.at(i)->IsDead())
		{
			if (localPlayer->IsCollidingWith(*ladderList.at(i)))
			{
				onLadder = true;
			}
		}
	}

	return (onLadder);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;
	
	backBuffer.Clear();
	SplashScreen(backBuffer);
	isGameActive = true;// temp
	//eManager[1].Draw(backBuffer);
	background->Draw(*m_pBackBuffer);
	//drawPlayerAnimation(playerRunSrpite,localPlayer, backBuffer);
	if (inMainMenu)
	{
		title->Draw(*m_pBackBuffer);
		buttonPlay->Draw(*m_pBackBuffer);
		buttonInstructions->Draw(*m_pBackBuffer);
		buttonExit->Draw(*m_pBackBuffer);


		if (inInstructions)
		{
			controls->Draw(*m_pBackBuffer);
		}
	}
	else if (inGame)
	{
		NextLevelDraw();
		DrawLevel();

		drawPlayerAnimation(backBuffer);

		// Display Battery Level
		char const* batteryHudText = "Battery:";
		char const* playerLiveHudText = "Lives:";
		m_pBackBuffer->DrawText(10, 10, batteryHudText);
		m_pBackBuffer->DrawText(10, 50, playerLiveHudText);

		std::string s = std::to_string((int)torch->GetBatteryLevel());
		std::string l = std::to_string((int)localPlayer->playerLive);
		char const* batteryLevelText = s.c_str();
		char const* playerLiveText = l.c_str();
		m_pBackBuffer->DrawText(120, 10, batteryLevelText);
		m_pBackBuffer->DrawText(120, 50, playerLiveText);

		if (isPaused)
		{
			pauseBackground->Draw(*m_pBackBuffer);
			buttonPlay->Draw(*m_pBackBuffer);
			buttonExit->Draw(*m_pBackBuffer);
		}
		torch->Draw(*m_pBackBuffer);
	}
	if (inGameOver)
	{
		m_pBackBuffer->Clear();
		inGameOver = false;
		gameOverSprite->Draw(*m_pBackBuffer);
		backBuffer.Present();
		SDL_Delay(1000);
		gameOverSprite->SetY(1500);
		gameOverSprite = NULL;
		ResetGame();
		
	}
	backBuffer.Present();
}
void
Game::drawPlayerAnimation(BackBuffer& backBuffer)
{
	switch (currentPlayerAction)
	{
	case Game::playerJumping:
		if (currentPlayerFacing == FacingLeft)
		{
			if (localPlayer->GetIsLit())
			{
				playerJumpSrpiteFL->SetX(localPlayer->GetPositionX());
				playerJumpSrpiteFL->SetY(localPlayer->GetPositionY());
				playerJumpSrpiteFL->Draw(backBuffer);
			}
			else
			{
				playerJumpSrpiteDarkFL->SetX(localPlayer->GetPositionX());
				playerJumpSrpiteDarkFL->SetY(localPlayer->GetPositionY());
				playerJumpSrpiteDarkFL->Draw(backBuffer);
			}
		}
		else if (currentPlayerFacing == FacingRight)
		{
			if (localPlayer->GetIsLit())
			{
				playerJumpSrpiteFR->SetX(localPlayer->GetPositionX());
				playerJumpSrpiteFR->SetY(localPlayer->GetPositionY());
				playerJumpSrpiteFR->Draw(backBuffer);
			}
			else
			{
				playerJumpSrpiteDarkFR->SetX(localPlayer->GetPositionX());
				playerJumpSrpiteDarkFR->SetY(localPlayer->GetPositionY());
				playerJumpSrpiteDarkFR->Draw(backBuffer);
			}
		}
		break;
	case Game::playerRun:
		if (currentPlayerFacing == FacingLeft)
		{
			if (localPlayer->GetIsLit())
			{
				playerRunSrpiteFL->SetX(localPlayer->GetPositionX());
				playerRunSrpiteFL->SetY(localPlayer->GetPositionY());
				playerRunSrpiteFL->Draw(backBuffer);
			}
			else
			{
				playerRunSrpiteDarkFL->SetX(localPlayer->GetPositionX());
				playerRunSrpiteDarkFL->SetY(localPlayer->GetPositionY());
				playerRunSrpiteDarkFL->Draw(backBuffer);
			}
		}
		else if (currentPlayerFacing == FacingRight)
		{
			if (localPlayer->GetIsLit())
			{
				playerRunSrpiteFR->SetX(localPlayer->GetPositionX());
				playerRunSrpiteFR->SetY(localPlayer->GetPositionY());
				playerRunSrpiteFR->Draw(backBuffer);
			}
			else
			{
				playerRunSrpiteDarkFR->SetX(localPlayer->GetPositionX());
				playerRunSrpiteDarkFR->SetY(localPlayer->GetPositionY());
				playerRunSrpiteDarkFR->Draw(backBuffer);
			}
		}
		break;
	case Game::playerIdle:
		if (currentPlayerFacing == FacingLeft)
		{
			if (localPlayer->GetIsLit())
			{
				playerSpriteFL->SetX(localPlayer->GetPositionX());
				playerSpriteFL->SetY(localPlayer->GetPositionY());
				playerSpriteFL->Draw(backBuffer);
			}
			else
			{
				playerSpriteDarkFL->SetX(localPlayer->GetPositionX());
				playerSpriteDarkFL->SetY(localPlayer->GetPositionY());
				playerSpriteDarkFL->Draw(backBuffer);
			}
		}
		else if (currentPlayerFacing == FacingRight)
		{
			localPlayer->Draw(backBuffer);
		}
		break;
	default:
		break;
	}
}

void 
Game::Quit()
{
	m_looping = false;
}

bool Game::CheckEndPointCollision()
{
		if ((localPlayer->GetPositionX() - tileEndPoint->GetX()) <= 80 && (localPlayer->GetPositionX() - tileEndPoint->GetX()) >= -80)// change to 50 when character gets resized.
		{
			if ((localPlayer->GetPositionY() - tileEndPoint->GetY()) <= 80 && (localPlayer->GetPositionY() - tileEndPoint->GetY()) >= -80)// change to 50 when character gets resized.
			{
				system->playSound(soundObjective, 0, false, &channel);
				return true;
			}
		}
		return false;
}
void
Game::worldPhysic()
{
	if (currentPlayerStatus == onAir)
	{
		localPlayer->SetPositionY(localPlayer->GetPositionY() + 8);
	}
}

bool
Game::sideBlockCollisionCheckLeft()
{
	for (size_t i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i]->GetIsSolid() == true)
		{
			if (localPlayer->IsCollidingWithYaxisLeft(*tileMap.at(i)) && localPlayer->IsCollidingWith(*tileMap.at(i)))
			{
				return true;
			}
		}
	}
	return false;
}

bool
Game::sideBlockCollisionCheckRight()
{
	for (size_t i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i]->GetIsSolid() == true)
		{
			if (localPlayer->IsCollidingWithYaxisRight(*tileMap.at(i)) && localPlayer->IsCollidingWith(*tileMap.at(i)))
			{
				return true;
			}
		}
	}
	return false;
}

void
Game::groundCollisionCheck()
{
	bool detectTouchGround = false;

	//actual block
	for (size_t i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i]->GetIsSolid() == true)
		{
			if (localPlayer->IsCollidingWith(*tileMap.at(i)))
			{
				detectTouchGround = true;
			}
		}
	}

	if (playerClimbing)
	{
		if (CheckLadders())
		{
			detectTouchGround = true;
		}
	}

	if (detectTouchGround)
	{
		currentPlayerStatus = onGround;
	}
	else
	{
		currentPlayerStatus = onAir;
	}

}

playerStatus
Game::getPlayerStatus()
{
	return currentPlayerStatus;
}

void 
Game::setPlayerStatus(playerStatus playerStatusInput)
{
	currentPlayerStatus = playerStatusInput;
}

void Game::PlayTorchSound()
{
	// Play torch sound based on current state
	if (torchOn)
	{
		system->playSound(soundTorchOn, 0, false, &channel);
	}
	else
	{
		system->playSound(soundTorchOff, 0, false, &channel);
	}
}

void Game::Shoot()
{
	LogManager::GetInstance().Log("Bullet made!");
	bullet = new Bullet(localPlayer->GetPositionX(), localPlayer->GetPositionY(), 50);
	bullet->Initialise(projectile);
	bullet->SetSprites(projectile, projectileInvis);
	torchList.push_back(bullet);
	bulletList.push_back(bullet);
}

void
Game::setDeltaTime(float deltaTime)
{
	tempdelta = deltaTime;
}

float
Game::getDeltaTime()
{
	return tempdelta;
}

void 
Game::playerMovement(float deltaTime)
{
	if (playerMoveLeft) 
	{
		if (!sideBlockCollisionCheckLeft())
		{
			currentPlayerAction = playerRun;
			currentPlayerFacing = FacingLeft;
			localPlayer->playerMoveLeft(deltaTime);
		}
	}
	else
	{
		currentPlayerAction = playerIdle;
	}

	if (playerMoveRight)
	{
		if (!sideBlockCollisionCheckRight())
		{
			currentPlayerAction = playerRun;
			currentPlayerFacing = FacingRight;
			localPlayer->playerMoveRight(deltaTime);
		}
	}
	else
	{
		currentPlayerAction = playerIdle;
	}
}

void
Game::PlayerClimbingUp(float deltaTime)
{
	if (playerClimbing)
	{
		localPlayer->playerMoveUp(deltaTime);
	}
}

void
Game::playerJump(float deltaTime)
{
	if (playJumpSound)
	{
		system->playSound(soundJump, 0, false, &channel);
		playJumpSound = false;
	}
	currentPlayerAction = playerJumping;
	localPlayer->playerJump(deltaTime);
}

bool
Game::checkCollision(Entity* collision1, Entity* collision2, float C1Left, float C1Right, float C1Top, float C1Bottom, float C2Left, float C2Right, float C2Top, float C2Bottom)
{
	if ((collision2->GetPositionX() - C2Left) - (collision1->GetPositionX() + C1Right) < 0 &&
		(collision1->GetPositionX() - C1Left) - (collision2->GetPositionX() + C2Right) < 0 &&
		(collision2->GetPositionY() - C2Bottom) - (collision1->GetPositionY() + C1Top) < 0 &&
		(collision1->GetPositionY() - C1Bottom) - (collision2->GetPositionY() + C2Top) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Game::PlayerFall() 
{
	if (localPlayer->GetPositionY() > 1080)
	{
		localPlayer->SetPosition(tileStartPoint->GetX(), tileStartPoint->GetY());
		localPlayer->playerLive--;
	}
}

void Game::CreateButtons()
{
	// Initialize Title
	title = new Button();
	title->Initialise(titleSprite);
	title->SetPositionX(420);
	title->SetPositionY(360);

	// Initialize Buttons
	buttonPlay = new Button();
	buttonPlay->Initialise(buttonSpritePlay);
	buttonPlay->SetSprites(buttonSpritePlay, buttonSpritePlayDark);
	buttonPlay->ChangeSprites(buttonPlay->GetDarkSprite());
	torchList.push_back(buttonPlay);
	buttonPlay->SetPositionX(300);
	buttonPlay->SetPositionY(520);

	buttonInstructions = new Button();
	buttonInstructions->Initialise(buttonSpriteInstructions);
	buttonInstructions->SetSprites(buttonSpriteInstructions, buttonSpriteInstructionsDark);
	buttonInstructions->ChangeSprites(buttonInstructions->GetDarkSprite());
	torchList.push_back(buttonInstructions);
	buttonInstructions->SetPositionX(775);
	buttonInstructions->SetPositionY(520);

	buttonExit = new Button();
	buttonExit->Initialise(buttonSpriteExit);
	buttonExit->SetSprites(buttonSpriteExit, buttonSpriteExitDark);
	buttonExit->ChangeSprites(buttonExit->GetDarkSprite());
	torchList.push_back(buttonExit);
	buttonExit->SetPositionX(1250);
	buttonExit->SetPositionY(520);

	// Initialize Controls/Instructions
	controls = new Button();
	controls->Initialise(controlsSprite);
	controls->SetPositionX(625);
	controls->SetPositionY(680);
}

void Game::CreatePauseButtons()
{
	// Initialize Pause Menu Background
	pauseBackground = new Button();
	pauseBackground->Initialise(pauseBackgroundSprite);
	pauseBackground->SetPositionX(350);
	pauseBackground->SetPositionY(150);

	// Initialize Pause Buttons
	buttonPlay = new Button();
	buttonPlay->Initialise(buttonSpritePlay);
	buttonPlay->SetSprites(buttonSpritePlay, buttonSpritePlayDark);
	buttonPlay->ChangeSprites(buttonPlay->GetDarkSprite());
	torchList.push_back(buttonPlay);
	buttonPlay->SetPositionX(470);
	buttonPlay->SetPositionY(400);

	buttonExit = new Button();
	buttonExit->Initialise(buttonSpriteExit);
	buttonExit->SetSprites(buttonSpriteExit, buttonSpriteExitDark);
	buttonExit->ChangeSprites(buttonExit->GetDarkSprite());
	torchList.push_back(buttonExit);
	buttonExit->SetPositionX(870);
	buttonExit->SetPositionY(400);
}
void Game::GameOverScreen() 
{
	gameOverSprite = new Sprite();
	gameOverSprite  = m_pBackBuffer->CreateSprite("assets\\Buttons\\gameOver.png");
	gameOverSprite->SetX(660);
	gameOverSprite->SetY(326);
}
void Game::ResetGame()
{
	// Initialize Debug Variables
	debugMode = false;
	infiniteBattery = false;

	InitializeSounds();

	inMainMenu = true;
	inInstructions = false;
	inGame = false;
	isPaused = false;

	gameOver = false;
	SetMenuClick(false);

	torch = new Torch();
	torch->Initialise(torchSprite);
	torch->SetSprites(torchSprite, torchSpriteDark);
	torchList.push_back(torch);
	torchOn = false;

	localPlayer = new Player();
	localPlayer->Initialise(playerRunSrpiteFR);
	localPlayer->SetSprites(playerRunSrpiteFR, playerRunSrpiteDarkFR);
	torchList.push_back(localPlayer);

	m_pMap = new Map();
	std::vector<Tile*> tileMapScroller;
	std::vector<Tile*> tileMap;
	background = new Sprite;
	background = m_pBackBuffer->CreateSprite("assets\\backgrounddark.png");
	currentPlayerStatus = onAir;
	m_pMap->SetLevel(0);
	CreateLevel();
}

void Game::SetMenuClick(bool m)
{
	menuClick = m;
}

bool Game::GetMenuClick()
{
	return menuClick;
}

void
Game::playerTouchEnemy()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (localPlayer->IsCollidingWith(*enemyList.at(i)))
		{
			//reset the map;
			system->playSound(soundTrap, 0, false, &channel);
			localPlayer->SetPosition(tileStartPoint->GetX(), tileStartPoint->GetY());
			localPlayer->playerLive--;
			resetMap();
		}
	}
	for (size_t i = 0; i < bulletList.size(); i++)
	{
		if (localPlayer->IsCollidingWith(*bulletList.at(i)))
		{
			//reset the map;
			system->playSound(soundTrap, 0, false, &channel);
			localPlayer->SetPosition(tileStartPoint->GetX(), tileStartPoint->GetY());
			localPlayer->playerLive--;
			resetMap();
		}
	}
	for (size_t i = 0; i < shooterEnemyList.size(); i++)
	{
		if (localPlayer->IsCollidingWith(*shooterEnemyList.at(i)))
		{
			//reset the map;
			system->playSound(soundTrap, 0, false, &channel);
			localPlayer->SetPosition(tileStartPoint->GetX(), tileStartPoint->GetY());
			localPlayer->playerLive--;
			resetMap();
		}
	}
}
void Game::resetMap() 
{
	enemyList.clear();
	shooterEnemyList.clear();
	bulletList.clear();
	trapList.clear();
	tileMap.clear();
	CreateLevel();
}

void Game::GameOver()
{
	GameOverScreen();
	inGameOver = true;
}