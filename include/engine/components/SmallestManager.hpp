// #pragma once
// // OBS -- COMPILE TIME CODE --- NOT PLAUSIBLE
// #include "engine/components/ComponentManager.hpp"
// #include <type_traits>
// template <typename A, typename B, typename Tuple> struct SmallerComponent
// {
//   using type = std::conditional_t<
//       (std::get<ComponentManager<A>>(std::declval<Tuple>()).size()) <
//           (std::get<ComponentManager<B>>(std::declval<Tuple()>).size()),
//       A, B>;
// };
//
// template <typename Tuple, typename T, typename... Rest>
// struct SmallestComponentHelper
// {
// private:
//   using SmallestRest = typename SmallestComponentHelper<Tuple, Rest...>::type;
//
// public:
//   using type = typename SmallerComponent<T, SmallestRest, Tuple>::type;
// };
//
// template <typename Tuple, typename T> struct SmallestComponentHelper<Tuple, T>
// {
//   using type = T;
// };
//
// // Entry point
// template <typename Tuple, typename... Ts> struct SmallestComponent
// {
//   using type = typename SmallestComponentHelper<Tuple, Ts...>::type;
// };
