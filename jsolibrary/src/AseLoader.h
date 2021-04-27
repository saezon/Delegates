#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace jso
{
  struct AseOut
  {
    struct Frame
    {
      struct Chunk
      {
        uint32_t size = 0;
        uint16_t type = 0;
        std::vector<uint8_t> data{};
      };

      uint32_t bytes = 0;
      uint16_t oldField = 0;
      uint16_t duration = 0;
      uint32_t newField = 0;
      std::vector<Chunk> chunks{};
    };

    uint32_t fileSize = 0;
    uint16_t frames = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t colorDepth = 0;
    uint32_t flags = 0;
    uint16_t speed = 0;
    uint8_t paletteEntry = 0;
    uint16_t numColors = 0;
    uint8_t pixelWidth = 0;
    uint8_t pixelHeight = 0;
    int16_t pivotX = 0;
    int16_t pivotY = 0;
    uint16_t gridWidth = 0;
    uint16_t gridHeight = 0;
    std::vector<Frame> frameData{};
  };

  class AseLoader
  {
  public:
    enum class Chunks
    {
      OldPaletteA = 0x0004,
      OldPaletteB = 0x0011,
      Layer = 0x2004,
      Cel = 0x2005,
      CelExtra = 0x2006,
      Mask = 0x2016,
      Path = 0x2017,
      FrameTags = 0x2018,
      Palette = 0x2019,
      UserData = 0x2020,
      Slice = 0x2022
    };
    struct Layer
    {
      uint16_t flags =0;
      uint16_t type=0;
      uint16_t childLevel=0;
      uint16_t blendMode=0;
      uint8_t opacity=0;
      std::string name;
    };

    
    void initialize(const std::string folder_path);
    bool load_ase(const std::string name, AseOut& aseOut);

    std::vector<Layer> _layers;
  private:
    void parse_layer(FILE* stream, const uint32_t frame);
    void parse_cel(FILE* stream, const uint32_t frame);
  };
}
