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

  static float getBaseTextWidth(const std::string &text, Font font)
  {
    if (!font.glyphs || font.glyphCount <= 0)
    {
      TraceLog(LOG_ERROR, "Font not valid for glyph indexing.");
      return 0.0f;
    }

    float totalAdvance = 0.0f;
    for (char c : text)
    {
      int index = GetGlyphIndex(font, c);
      GlyphInfo glyph = (index >= 0 && index < font.glyphCount)
                            ? font.glyphs[index]
                            : font.glyphs[0];
      totalAdvance += glyph.advanceX;
    }
    return totalAdvance; //
  }

private:
  std::unordered_map<std::string, Font> loaded;
};
