#include "engine/shaders/basic2d.hpp"
#include "engine/utils/PrintMatrix.hpp"
#include "raylib.h"
#include "raymath.h"

namespace Basic2DShader
{
Shader shader;
int projLoc;
bool loaded = false;
// bool once = false;

void init()
{
  if (loaded)
    return;

  shader = LoadShader(RESOURCES_PATH "shaders/basic2d/basic2d.vs",
                      RESOURCES_PATH "shaders/basic2d/basic2d.fs");

  projLoc = GetShaderLocation(shader, "matrix");
  loaded = true;
}

void draw(const Matrix &projection, const Matrix &transform,
          const RenderRectangle &r)
{
  if (!loaded)
    init();

  // if (!once)
  // {
  //   PrintMatrix(transform);
  //   PrintMatrix(projection);
  //   once = true;
  // }

  BeginShaderMode(shader);
  SetShaderValueMatrix(shader, projLoc, MatrixMultiply(transform, projection));

  rlBegin(RL_QUADS);

  rlColor4ub(r.color.r, r.color.g, r.color.b, r.color.a);
  // rlVertex3f(0.0f, 0.0f, 0.0f);
  // rlVertex3f(1.0f, 0.0f, 0.0f);
  // rlVertex3f(1.0f, 1.0f, 0.0f);
  // rlVertex3f(0.0f, 1.0f, 0.0f);

  rlVertex3f(0.0f, 0.0f, 0.0f);
  rlVertex3f(0.0f, 1.0f, 0.0f);
  rlVertex3f(1.0f, 1.0f, 0.0f);
  rlVertex3f(1.0f, 0.0f, 0.0f);

  rlEnd();

  EndShaderMode();
}
} // namespace Basic2DShader
