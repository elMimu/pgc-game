#pragma once

#include <algorithm>

struct UserStateBase
{
  virtual ~UserStateBase() = default;
};

template <typename T> struct UserStateHolder : UserStateBase
{
  T data;
  UserStateHolder(T &&data) : data(std::move(data)) {}
};
