#pragma once

#include <functional>

// FORWARD DECLARATION
class ComponentRegistry;

class RenderSystem
{
public:
  virtual ~RenderSystem() = default;
  virtual void registerAllSystemJobs(ComponentRegistry &components) = 0;

protected:
  RenderSystem(std::function<void()> drawFn) : drawFn(drawFn) {};
  std::function<void()> drawFn;
};
