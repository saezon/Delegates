#include "AseLoader.h"

#include <iostream>
using namespace std;

namespace
{
  std::string sFolderPath;

  void FileReadData(void* buffer, size_t elementSize, FILE* stream)
  {
    fread(buffer, elementSize, 1, stream);
  }



  void FileJumpSize(size_t elementSize, FILE* stream)
  {
    fseek(stream, elementSize, SEEK_CUR);
  }
  void FileJumpTo(size_t pos, FILE* stream)
  {
    fseek(stream, pos, SEEK_SET);
  }
  size_t FilePos( FILE* stream)
  {
    return ftell(stream);
  }
}

void jso::AseLoader::initialize(const std::string folder_path)
{
  sFolderPath = folder_path;
}

bool jso::AseLoader::load_ase(const std::string name, AseOut& aseOut)
{
  aseOut = AseOut();
  const auto extension = name.substr(name.find_last_of("."));
  if (!(extension == ".ase" || extension == ".aseprite"))
  {
    cout << "File is not .ase or .aseprite" << endl;
    return false;
  }
  FILE* stream = fopen((sFolderPath + "/" + name).c_str(), "rb");
  if (stream == nullptr)
  {
    cout << "File does not exist" << endl;
    return false;
  }
  //HEADER
  FileReadData(&aseOut.fileSize, sizeof(uint32_t), stream);
  FileJumpSize(sizeof(uint16_t), stream);
  FileReadData(&aseOut.frames, sizeof(uint16_t), stream);
  FileReadData(&aseOut.width, sizeof(uint16_t), stream);
  FileReadData(&aseOut.height, sizeof(uint16_t), stream);
  FileReadData(&aseOut.colorDepth, sizeof(uint16_t), stream);
  FileReadData(&aseOut.flags, sizeof(uint32_t), stream);
  FileReadData(&aseOut.speed, sizeof(uint16_t), stream);
  FileJumpSize(sizeof(uint64_t), stream);
  FileReadData(&aseOut.paletteEntry, sizeof(uint8_t), stream);
  FileJumpSize(sizeof(uint8_t) * 3, stream);
  FileReadData(&aseOut.numColors, sizeof(uint16_t), stream);
  FileReadData(&aseOut.pixelWidth, sizeof(uint8_t), stream);
  FileReadData(&aseOut.pixelHeight, sizeof(uint8_t), stream);
  FileReadData(&aseOut.pivotX, sizeof(int16_t), stream);
  FileReadData(&aseOut.pivotY, sizeof(int16_t), stream);
  FileReadData(&aseOut.gridWidth, sizeof(uint16_t), stream);
  FileReadData(&aseOut.gridHeight, sizeof(uint16_t), stream);
  FileJumpSize(sizeof(uint8_t) * 84, stream);

  //FRAME DATA
  aseOut.frameData.reserve(aseOut.frames);
  for (uint32_t i = 0; i < aseOut.frames; i++)
  {
    AseOut::Frame frame{};
    //HEADER
    FileReadData(&frame.bytes, sizeof(uint32_t), stream);
    FileJumpSize(sizeof(uint16_t), stream);
    FileReadData(&frame.oldField, sizeof(uint16_t), stream);
    FileReadData(&frame.duration, sizeof(uint16_t), stream);
    FileJumpSize(sizeof(uint8_t) * 2, stream);
    FileReadData(&frame.newField, sizeof(uint32_t), stream);
    //CHUNK
    auto size = frame.oldField == 0xFFFF ? frame.newField : frame.oldField;
    frame.chunks.reserve(size);
    for (uint32_t j = 0; j < size; j++)
    {
      AseOut::Frame::Chunk chunk{};
      auto start = FilePos(stream);
      FileReadData(&chunk.size, sizeof(uint32_t), stream);
      auto end = start + chunk.size;
      FileReadData(&chunk.type, sizeof(uint16_t), stream);
      //CHUNK DATA
      auto chunkType = static_cast<Chunks>(chunk.type);
      switch (chunkType) {
      case Chunks::OldPaletteA:
        break;
      case Chunks::OldPaletteB:
        break;
      case Chunks::Layer:
        parse_layer(stream, i);
        break;
      case Chunks::Cel:
        break;
      case Chunks::CelExtra:
        break;
      case Chunks::Mask:
        break;
      case Chunks::Path:
        break;
      case Chunks::FrameTags:
        break;
      case Chunks::Palette:
        break;
      case Chunks::UserData:
        break;
      case Chunks::Slice:
        break;
      default: ;
      }
      FileJumpTo(end, stream);
      frame.chunks.push_back(chunk);
    }
    aseOut.frameData.push_back(frame);
  }

  return true;
}

void jso::AseLoader::parse_layer(FILE* stream, const uint32_t frame)
{
  Layer layer{};
  FileReadData(&layer.flags, sizeof(uint16_t), stream);
  FileReadData(&layer.type, sizeof(uint16_t), stream);
  FileReadData(&layer.childLevel, sizeof(uint16_t), stream);
  FileJumpSize(sizeof(uint16_t) * 2, stream);
  FileReadData(&layer.blendMode, sizeof(uint16_t), stream);
  FileReadData(&layer.opacity, sizeof(uint8_t), stream);
  FileJumpSize(sizeof(uint8_t) * 3, stream);
  uint16_t length;
  FileReadData(&length, sizeof(uint16_t), stream);
  char* name = new char[length + 1];
  name[length]='\0';
  FileReadData(name, sizeof(uint8_t) * length, stream);
  layer.name = name;
  delete[] name;
  _layers.push_back(layer);
}

void jso::AseLoader::parse_cel(FILE* stream, const uint32_t frame)
{
}
