#pragma once

#include <string>

struct SceneRequest
{
  enum class RequestType
  {
    REPLACE,
    STACK,
    POP,
    NONE
  };
  RequestType type = RequestType::NONE;
  std::string sceneName = "";
};
