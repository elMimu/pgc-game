#include "engine/utils/TransformUtils.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "raylib.h"
#include "raymath.h"

namespace TransformUtils {

float getAspect(Entity e, World &w) {
  float aspect = 1.0f;
  Entity current = e;

  while (true) {
    auto &t = w.get<Transformable>(current);
    aspect *= t.size.x / t.size.y;

    if (t.parent == 0)
      break;

    current = t.parent;
  }

  return aspect;
}

Matrix getLocalMatrix(const Transformable &t) {
  Matrix anchor = MatrixTranslate(-t.origin.x, -t.origin.y, 0.0f);
  Matrix scale = MatrixScale(t.size.x, t.size.y, 1.0f);
  Matrix rotation = MatrixRotateZ(t.rotation);
  Matrix translation = MatrixTranslate(t.position.x, t.position.y, 0.0f);

  Matrix model = MatrixMultiply(anchor, scale); // S * A
  model = MatrixMultiply(model, rotation);      // R * (S * A)
  model = MatrixMultiply(model, translation);
  return model;
};

float getRotationFromMatrix(const Matrix &m) { return atan2f(m.m1, m.m0); }

float getDegRotationFromMatrix(const Matrix &m) {
  return getRotationFromMatrix(m) * RAD2DEG;
}

Vector2 getScaleFromMatrix(const Matrix &m) {
  float scaleX = sqrtf(m.m0 * m.m0 + m.m1 * m.m1);
  float scaleY = sqrtf(m.m4 * m.m4 + m.m5 * m.m5);
  return {scaleX, scaleY};
}

Matrix getParentMatrix(World &w, Entity e) {
  auto &t = w.get<Transformable>(e);

  if (t.parent == 0) {
    return getLocalMatrix(t);
  }

  return MatrixMultiply(getLocalMatrix(t),
                        getParentMatrix(w,t.parent));
}

WorldMatrixResult getSafeWorldMatrix(World &w, Entity e, Transformable &t) {
  auto &gt = w.get<GlobalTransformable>(e);
  bool recalculate = false;

  if (t.parent == 0) {
    if (gt.dirty) {
      gt.worldMatrix = getLocalMatrix(t);
      gt.dirty = false;
      recalculate = true;
    }
    return {std::ref(gt.worldMatrix), recalculate};
  }

  auto &parentT = w.get<Transformable>(t.parent);
  auto [parentMatrix, parentChanged] = getSafeWorldMatrix(w, t.parent, parentT);

  if (gt.dirty || parentChanged) {
    gt.worldMatrix = MatrixMultiply(getLocalMatrix(t), parentMatrix);
    gt.dirty = false;
    recalculate = true;
  }

  return {std::ref(gt.worldMatrix), recalculate};
}

Matrix &getWorldMatrix(World &w, Entity e, Transformable &t) {
  return getSafeWorldMatrix(w, e, t).matrix;
}

}; // namespace TransformUtils
