// class RenderSystem
// {
// public:
//   RenderSystem(ComponentManager<TransformComponent> &transformManager,
//                ComponentManager<RenderComponent> &renderManager)
//       :
//
//         transformManager(transformManager), renderManager(renderManager)
//   {
//   }
//
//   void draw()
//   {
//     for (auto &[e, d] : renderManager.getAll())
//     {
//       if (d.active)
//       {
//         auto &t = transformManager.get(e);
//         std::cout << t.position.x << std::endl;
//         DrawRectanglePro(
//             Rectangle{t.position.x, t.position.y, t.size.x, t.size.y},
//             Vector2{t.size.x * t.origin.x, t.size.y * t.origin.y}, t.rotation,
//             ColorFromNormalized(d.color));
//       }
//     }
//   }
//
// private:
//   ComponentManager<TransformComponent> &transformManager;
//   ComponentManager<RenderComponent> &renderManager;
// };
