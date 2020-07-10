#pragma once

class Entity;

class GUIManager
{
private:
    Entity* _guiLayer;
    bool _isActive;
public:
  GUIManager();
  ~GUIManager();

  void SetActive();
  void SetInactive();
  bool IsActive();
  void SetGUIEntity(Entity* e);
  void OpenDialogBox();
  void CloseDialogBox();
  void drawGui();
};