// COMP710 GP 2D Framework 2020
#ifndef __GAME_H__
#define __GAME_H__

// Includes
#include <vector>
#include "entity.h"
#include "fmod.hpp" 
#include "fmod_errors.h" 
#include <SDL_ttf.h>

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Map;
class Tile;
class Player;
class Torch;
class Enemy;
class MeleeEnemy;
class ShooterEnemy;
class Entity;
class AnimatedSprite;
class Button;
class Trap;
class Bullet;
class Ladder;

enum playerStatus
{
	onGround, onAir
};

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void InitializeSounds();
	void Quit();
	void DrawLevel();
	void CreateLevel();
	void ReadyNextLevel();
	void NextLevelDraw();
	void SplashScreen(BackBuffer& backBuffer);

	void CheckTorchLight();
	void CheckTraps();
	bool CheckLadders();
	void worldPhysic();
	void groundCollisionCheck();
	bool sideBlockCollisionCheckLeft();
	bool sideBlockCollisionCheckRight();

	playerStatus getPlayerStatus();
	void setPlayerStatus(playerStatus playerStatusInput);

	void PlayTorchSound();

	void Shoot();
	void setDeltaTime(float deltaTime);
	float getDeltaTime();
	void PlayerFall();
	void CreateButtons();
	void CreatePauseButtons();
	void ResetGame();
	void playerMovement(float deltaTime);
	void PlayerClimbingUp(float deltaTime);
	void playerJump(float deltaTime);
	bool checkCollision(Entity* collision1, Entity* collision2, float C1Left, float C1Right, float C1Top, float C1Bottom, float C2Left, float C2Right, float C2Top, float C2Bottom);
	bool CheckEndPointCollision();
	void GameOverScreen();
	void drawPlayerAnimation(BackBuffer& backBuffer);
	void SetMenuClick(bool m);
	bool GetMenuClick();
	void playerTouchEnemy();
	void GameOver();
	void resetMap();

protected:
	void Process(float deltaTime);
	void ManageTorch(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	// Control Variables
	bool playerMoveLeft;
	bool playerMoveRight;
	bool playerClimbing;
	bool torchOn;
	bool playJumpSound;
	bool menuClick;
	bool GameOverClick;

	// Game States
	bool inMainMenu;
	bool inInstructions;
	bool inGame;
	bool isPaused;
	bool gameOver;
	bool inGameOver;

	// Debug Variables
	bool debugMode;
	bool infiniteBattery;

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;
	bool isGameActive;
	bool levelLoaded;
	bool scrollLevel;
	bool displaySplash;
	bool playPlayerRunAnimation;
	bool playPlayerJumpAnimation;

	// Sprites:
	Sprite* splashSprite;
	Sprite* torchSprite;
	Sprite* torchSpriteDark;
	Sprite* background;
	Sprite* tileLight;
	Sprite* tileDark;
	Sprite* tileLLight;
	Sprite* tileLDark;
	Sprite* tileRLight;
	Sprite* tileRDark;
	Sprite* tileCover;
	Sprite* enemySprite;
	Sprite* darkEnemySprite;
	Sprite* shooterEnemySprite;
	Sprite* projectile;
	Sprite* projectileInvis;
	Sprite* playerSpriteFR;
	Sprite* playerSpriteDarkFR;
	Sprite* playerSpriteFL;
	Sprite* playerSpriteDarkFL;	Sprite* tileEndPoint;
	Sprite* trap;
	Sprite* trapDark;
	Sprite* ladder;
	Sprite* ladderDark;
	Sprite* tileStartPoint;
	Sprite* gameOverSprite;

	//animated sprite
	AnimatedSprite* playerRunSrpiteFR;
	AnimatedSprite* playerRunSrpiteDarkFR;
	AnimatedSprite* playerJumpSrpiteFR;
	AnimatedSprite* playerJumpSrpiteDarkFR;
	AnimatedSprite* playerRunSrpiteFL;
	AnimatedSprite* playerRunSrpiteDarkFL;
	AnimatedSprite* playerJumpSrpiteFL;
	AnimatedSprite* playerJumpSrpiteDarkFL;

	// Game Objects:
	std::vector<Tile*> tileMap;
	std::vector<Entity*> torchList;
	std::vector<Trap*> trapList;
	std::vector<Ladder*> ladderList;
	std::vector<Enemy*> enemyList;
	std::vector<Enemy*> shooterEnemyList;
	std::vector<Bullet*> bulletList;
	Map * m_pMap;
	std::vector<Tile*> tileMapScroller;
	Player* localPlayer;
	Torch* torch;
	Enemy* enemy;
	ShooterEnemy* shooterEnemy;
	MeleeEnemy* meleeEnemy;
	playerStatus currentPlayerStatus;
	Bullet* bullet;

	// Fmod
	FMOD_RESULT result;
	FMOD::System* system = 0;
	FMOD::Channel* channel = 0;

	// Sound Effects
	FMOD::Sound* soundTorchOn;
	FMOD::Sound* soundTorchOff;
	FMOD::Sound* soundJump;
	FMOD::Sound* soundTrap;
	FMOD::Sound* soundObjective;

	//animation
	enum playerFacing
	{
		FacingLeft, FacingRight
	};
	playerFacing currentPlayerFacing;
	enum playerAction
	{
		playerJumping, playerRun, playerIdle
	};
	playerAction currentPlayerAction;	// Buttons
	Sprite* buttonSpritePlay;
	Sprite* buttonSpritePlayDark;
	Sprite* buttonSpriteInstructions;
	Sprite* buttonSpriteInstructionsDark;
	Sprite* buttonSpriteExit;
	Sprite* buttonSpriteExitDark;
	Sprite* pauseBackgroundSprite;
	Sprite* titleSprite;
	Sprite* controlsSprite;

	Button* buttonPlay;
	Button* buttonInstructions;
	Button* buttonExit;
	Button* pauseBackground;
	Button* title;
	Button* controls;

	float currentStartPointPositionX;
	float currentStartPointPositionY;

float tempdelta;
private:

};

#endif // __GAME_H__
