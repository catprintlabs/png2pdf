#include "podofo/podofo.h"
#include "png++/png.hpp"
#include "boost/filesystem.hpp"

using namespace png;
using namespace PoDoFo;

namespace png2pdf {

class Converter {
 public:
  static const double kPointsPerInch;

  Converter(const std::string& i, const std::string& o, const int& d);

  void Convert();
 private:
  std::string input_file_, output_file_, image_file_, mask_file_;
  uint_32 width_, height_, dpi_;
  double scale_;
  bool transparency_;
  image_info image_info_;

  void set_image_info();
  void set_dimensions();
  void set_transparency();

  std::string GenerateTempFilePath();
  void SplitRGBAChannels();
  void SplitGAChannels();
  void RenderPDF();
  void CleanUp();
};

} // namespace png2pdf
