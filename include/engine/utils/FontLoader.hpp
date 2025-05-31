#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>

class FontLoader
{
public:
  void registerFont(std::string key, const Font &f) { loaded[key] = f; }

  void loadFontEx(std::string key, const char *fileName)
  {
    loaded[key] = LoadFontEx(fileName, 64, nullptr, 0);
  };

  Font &get(const std::string key) { return loaded.at(key); }

  void unload(std::string key)
  {
    Font &font = get(key);
    UnloadFont(font);
    loaded.erase(key);
  }

  void unloadAll()
  {
    for (auto &[key, font] : loaded)
    {
      UnloadFont(font);
    }
    loaded.clear();
  };

  void getBaseTextWidth(std::string text, Font font, float testFontSize)
  {
    float textAdvance = 0.0f;
    // if (!font.glyphs || font.glyphCount <= 0)
    // {
    //   TraceLog(LOG_ERROR, "Font not valid for glyph indexing.");
    //   return;
    // }
    for (char c : text)
    {

      // int index = GetGlyphIndex(font, c);
      // std:: cout << index << " " ;
      // GlyphInfo glyph = font.glyphs[index];
      // textAdvance += glyph.advanceX;
    }
    // std::cout << "########" << "\n";
    // std::cout << textAdvance << " - " << font.baseSize << "\n";
    // float baseWidth = textAdvance * (testFontSize / font.baseSize);
  }

private:
  std::unordered_map<std::string, Font> loaded;
};
