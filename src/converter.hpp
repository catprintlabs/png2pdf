#include "podofo/podofo.h"
#include "png++/png.hpp"
#include "boost/filesystem.hpp"

using namespace png;
using namespace PoDoFo;

namespace png2pdf {

class Converter {
 public:
  Converter(std::string input_file, std::string output_file, int dpi);

  void Convert();
 private:
  std::string input_file_;
  std::string output_file_;
  std::string rgb_file_, alpha_file_;
  uint_32 width_, height_, dpi_;

  std::string GenerateTempFilePath();
  void SplitPng();
  void EmbedPngs();
  void CleanUp();
};

} // namespace png2pdf
