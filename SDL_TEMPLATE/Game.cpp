#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "GameState.h"
#include "AppInfo.h"
#include "InvokerPlaying.h"
#include "Prototype.h"
#include "PrototypeRegistry.h"
#include "TextureType.h"
#include "Command.h"
#include "Background.h"
#include "Bullet.h"





Game::Game() : gWindow(nullptr), gRenderer(nullptr), gameState(std::make_unique<GamePlaying>()),
				running(false), gFont(nullptr) {}

void Game::initSDLSubsystems() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Failed to initialize SDL subsystems." << SDL_GetError() << '\n';
	else
		std::cout << "Initialized SDL subsystems." << '\n';
}

void Game::initWindowCreation() {
	gWindow = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!gWindow) std::cout << "Failed to create window: " << SDL_GetError() << '\n';
	else std::cout << "Window created." << '\n';
}

void Game::initRendererCreation() {
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!gRenderer) std::cout << "Failed to create renderer: " << SDL_GetError() << '\n';
	else std::cout << "Renderer created." << '\n';
}

void Game::initSDL_image() {
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags)) std::cout << "Warning: SDL_image could not initialize: " << IMG_GetError() << '\n';
	else std::cout << "SDL_image initialized." << '\n';
}

void Game::initSDL_ttf() {
	if (TTF_Init() == -1) std::cout << "SDL_TTF could not initialize: " << TTF_GetError() << '\n';
	else std::cout << "SDL_TTF initialized." << '\n';
}

void Game::initGFont() {
	//TODO
	gFont = TTF_OpenFont("path", 28);

	if (!gFont) std::cout << "Failed to load font: " << TTF_GetError() << '\n';
	else std::cout << "Font loaded." << '\n';
}

void Game::setRunningToTrue() {
	running = true;
}

void Game::setRunningToFalse() {
	running = false;
}

void Game::initBackground() {
	Background::getInstance()->init();
}

void Game::initPlayer() {
	// Initialize main prototype of Player
	SDL_Point position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	TextureType* playerTexture = new TextureType(Prototype_Type::PLAYER);
	std::shared_ptr<Player> playerPrototype = std::make_shared<Player>(5, playerTexture, position, 4.0f, 30.0f);

	// Add main prototype player to Prototype Registry
	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::PLAYER, std::static_pointer_cast<Prototype>(playerPrototype)
	);

	// Clone a player
	std::shared_ptr<Player> player1 = std::dynamic_pointer_cast<Player>(
		PrototypeRegistry::getInstance()->getPrototype(Prototype_Type::PLAYER)
	);

	// Add player to invoker
	InvokerPlaying::getInstance()->addPlayer(player1);

	// Set commands
	auto moveLeftCommand = std::make_shared<MoveLeftCommand>();
	auto moveUpLeftCommand = std::make_shared<MoveUpLeftCommand>();
	auto moveUpCommand = std::make_shared<MoveUpCommand>();
	auto moveUpRightCommand = std::make_shared<MoveUpRightCommand>();
	auto moveRightCommand = std::make_shared<MoveRightCommand>();
	auto moveDownRightCommand = std::make_shared<MoveDownRightCommand>();
	auto moveDownCommand = std::make_shared<MoveDownCommand>();
	auto moveDownLeftCommand = std::make_shared<MoveDownLeftCommand>();

	auto faceLeftCommand = std::make_shared<FaceLeftCommand>();
	auto faceUpLeftCommand = std::make_shared<FaceUpLeftCommand>();
	auto faceUpCommand = std::make_shared<FaceUpCommand>();
	auto faceUpRightCommand = std::make_shared<FaceUpRightCommand>();
	auto faceRightCommand = std::make_shared<FaceRightCommand>();
	auto faceDownRightCommand = std::make_shared<FaceDownRightCommand>();
	auto faceDownCommand = std::make_shared<FaceDownCommand>();
	auto faceDownLeftCommand = std::make_shared<FaceDownLeftCommand>();

	auto keyUpFaceLeftCommand = std::make_shared<KeyUpMoveLeftCommand>();
	auto keyUpFaceUpLeftCommand = std::make_shared<KeyUpMoveUpLeftCommand>();
	auto keyUpFaceUpCommand = std::make_shared<KeyUpMoveUpCommand>();
	auto keyUpFaceUpRightCommand = std::make_shared<KeyUpMoveUpRightCommand>();
	auto keyUpFaceRightCommand = std::make_shared<KeyUpMoveRightCommand>();
	auto keyUpFaceDownRightCommand = std::make_shared<KeyUpMoveDownRightCommand>();
	auto keyUpFaceDownCommand = std::make_shared<KeyUpMoveDownCommand>();
	auto keyUpFaceDownLeftCommand = std::make_shared<KeyUpMoveDownLeftCommand>();

	std::shared_ptr<SprintCommand> sprintCommand = std::make_shared<SprintCommand>();
	std::shared_ptr<RemoveSprintCommand> removeSprintCommand = std::make_shared<RemoveSprintCommand>();

	std::shared_ptr<FireCommand> fireCommand = std::make_shared<FireCommand>();

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_w, moveUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_a, moveLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_s, moveDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_d, moveRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_q, moveUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_e, moveUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_z, moveDownLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_c, moveDownRightCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_f, faceLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_r, faceUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_t, faceUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_y, faceUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_h, faceRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_n, faceDownRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_b, faceDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_v, faceDownLeftCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_j, keyUpFaceLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_u, keyUpFaceUpLeftCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_i, keyUpFaceUpCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_o, keyUpFaceUpRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_l, keyUpFaceRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_g, keyUpFaceDownRightCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_k, keyUpFaceDownCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_m, keyUpFaceDownLeftCommand, player1);

	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_LSHIFT, sprintCommand, player1);
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_CAPSLOCK, removeSprintCommand, player1);
	
	InvokerPlaying::getInstance()->assignKeyToCommand(SDLK_x, fireCommand, player1);
}

void Game::initBullet() {
	std::shared_ptr<Bullet> bulletPrototype = std::make_shared<Bullet>();

	PrototypeRegistry::getInstance()->addPrototype(
		Prototype_Type::BULLET, std::static_pointer_cast<Prototype>(bulletPrototype)
	);
}

Game* Game::getInstance() {
	static Game instance;
	return &instance;
}

void Game::init() {
	initSDLSubsystems();
	initWindowCreation();
	initRendererCreation();
	initSDL_image();
	initSDL_ttf();
	initGFont();
	setRunningToTrue();
	initBackground();
	initPlayer();
	initBullet();
}

void Game::input() {
	while (SDL_PollEvent(&gEvent)) {
		if (gEvent.type == SDL_QUIT) {
			setRunningToFalse();
		}

		gameState->input();
	}
}

void Game::update() {
	gameState->update();
}

void Game::render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	Background::getInstance()->render();
	gameState->render();

	SDL_RenderPresent(gRenderer);
}

SDL_Renderer* Game::getRenderer() {
	return gRenderer;
}

const SDL_Event& Game::getEvent() const {
	return gEvent;
}

const bool& Game::isRunning() const {
	return running;
}