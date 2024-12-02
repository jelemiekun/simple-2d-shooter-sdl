#include "InvokerPlaying.h"
#include "Command.h"
#include "Player.h"

InvokerPlaying::InvokerPlaying() {}

InvokerPlaying* InvokerPlaying::getInstance() {
	static InvokerPlaying instance;
	return &instance;
}

void InvokerPlaying::addPlayer(std::shared_ptr<Player> player) {
	players[player->getID()] = player;
}

void InvokerPlaying::assignKeyToCommand (
	SDL_Keycode keyCode,
	std::shared_ptr<Command> command,
	std::shared_ptr<Player> player
	) {
	keyBindings[keyCode] = std::make_pair(command, player);
}

void InvokerPlaying::pressButton(SDL_Keycode keyCode) {
	auto it = keyBindings.find(keyCode);
	if (it != keyBindings.end()) {
		auto& pair = it->second;
		auto command = pair.first;
		auto player = pair.second;
		if (command && player) {
			player->commandQueue.push(command);
		}
	}
}

void InvokerPlaying::updatePlayers() {
	for (auto& player : players) {
		player.second->update();
	}
}

void InvokerPlaying::renderPlayers() {
	for (auto& player : players) {
		player.second->render();
	}
}