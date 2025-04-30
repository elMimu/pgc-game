#pragma once

class IScene
{
public:
  virtual void inputHandler() = 0;
  virtual void onLoad() = 0;
  virtual void onUpdate(float dt);
  virtual void onFinish() = 0;
  virtual ~IScene() = default;
};
