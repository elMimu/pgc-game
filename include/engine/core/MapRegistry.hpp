// #pragma once
// #include <functional>
// #include <iostream>
// #include <memory>
// #include <typeindex>
// #include <unordered_map>
//
// template <typename KeyType, typename ValueType> class MapRegistry
// {
// public:
//   template <typename... Args> ValueType &create(KeyType key, Args &&...args);
//   template <typename... Args> ValueType &create(Args &&...args);
//   // std::unordered_map<KeyType, std::unique_ptr<ValueType>> &getAll();
//   // void forEach(std::function<void(ValueType &, int)>);
//   // void add(KeyType key, ValueType &item);
//   ValueType *get(KeyType key);
//   // bool remove(KeyType key);
//   bool has(KeyType key);
//
// private:
//   std::unordered_map<KeyType, std::unique_ptr<ValueType>> itemsList;
// };
//
// // template <typename KeyType, typename ValueType>
// // std::unordered_map<KeyType, std::unique_ptr<ValueType>> &
// // MapRegistry<KeyType, ValueType>::getAll()
// // {
// //   return itemsList;
// // };
// //
// template <typename KeyType, typename ValueType>
// template <typename... Args>
// ValueType &MapRegistry<KeyType, ValueType>::create(Args &&...args)
// {
//   auto itemPtr = std::make_unque<ValueType>(std::forward<Args>(args)...);
//   ValueType &itemRef = *itemPtr;
//   itemsList[std::type_index(typeid(KeyType))] = std::move(itemPtr);
//
//   return &itemRef;
// };
//
// template <typename KeyType, typename ValueType>
// template <typename... Args>
// ValueType &MapRegistry<KeyType, ValueType>::create(KeyType key, Args &&...args)
// {
//   auto itemPtr = std::make_unique<ValueType>(std::forward<Args>(args)...);
//   ValueType &itemRef = *itemPtr;
//   itemsList[key] = std::move(itemPtr);
//
//   return &itemRef;
// };
// //
// // template <typename KeyType, typename ValueType>
// // bool MapRegistry<KeyType, ValueType>::has(KeyType key)
// // {
// //   if (itemsList.find(key) != itemsList.end())
// //   {
// //     return true;
// //   }
// //   return false;
// // };
// //
// // template <typename KeyType, typename ValueType>
// // bool MapRegistry<KeyType, ValueType>::remove(KeyType key)
// // {
// //   if (this->has(key))
// //   {
// //     itemsList.erase(key);
// //     return true;
// //   }
// //   return false;
// // }
// //
// template <typename KeyType, typename ValueType>
// ValueType *MapRegistry<KeyType, ValueType>::get(KeyType key)
// {
//   if (itemsList.find(key))
//   {
//     std::cout << "NOT FOUND" << "\n";
//     return nullptr;
//   };
//   return itemsList.at(key);
// };
// //
// // template <typename KeyType, typename ValueType>
// // void MapRegistry<KeyType, ValueType>::add(KeyType key, ValueType &item)
// // {
// //   itemsList[key] = std::make_unique<ValueType>(item);
// // };
//
// // template <typename KeyType, typename ValueType>
// // void MapRegistry<KeyType, ValueType>::forEach(
// //     std::function<void(ValueType &, int)> f)
// // {
// //   int i = 0;
// //   for (auto [k, v] : itemsList)
// //   {
// //     f(*v, i);
// //   }
// // };
