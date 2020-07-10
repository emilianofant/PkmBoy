#include "GUIManager.h"
#include "Game.h"
#include "ECS/Components.h"

GUIManager::GUIManager() {
  _isActive = false;
}

int _scale = 2;

void GUIManager::SetActive()
{
  _isActive = true;
}

void GUIManager::SetInactive()
{
  _isActive = false;
  Game::_controlFocus = Game::CONTROL_PLAYER;
}

bool GUIManager::IsActive()
{
  return _isActive;
}

// @todo: is not used
void GUIManager::SetGUIEntity(Entity* e)
{
  _guiLayer = e;
}

void GUIManager::OpenDialogBox()
{
  if(!IsActive()) {
    Game::assets->CreateDialogBox(_scale);
    SetActive();
    Game::_controlFocus = Game::CONTROL_GUI;
  }
}

void GUIManager::CloseDialogBox()
{
  // @todo: toggle the active flag
  // _guiLayer->destroy();
  SetInactive();
  Game::_controlFocus = Game::CONTROL_PLAYER;
}

// @todo: is not used
void GUIManager::drawGui()
{
  _guiLayer->draw();
}
