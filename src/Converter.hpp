#include "podofo/podofo.h"
#include "png++/png.hpp"
#include "boost/filesystem.hpp"

using namespace png;
using namespace PoDoFo;

namespace png2pdf {

class Converter {
 public:
  Converter(std::string in, std::string out, int dpi_value);

  void Convert();
 private:
  std::string input;
  std::string output;
  uint_32 width, height, dpi;
  std::string rgb_file, alpha_file;

  std::string GenerateTempFilePath();
  void SplitPng();
  void EmbedPngs();
  void CleanUp();
};

} // namespace png2pdf
