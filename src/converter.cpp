#include "converter.hpp"

namespace png2pdf {

const double Converter::kPointsPerInch = 72;

Converter::Converter(const std::string& i, const std::string& o, const int& d)
    : input_file_(i), output_file_(o), dpi_(d) {
  set_image_info();
  set_dimensions();
  set_transparency();
};

void Converter::Convert() {
  if (transparency_) {
    if (image_info_.get_color_type() == color_type::color_type_ga)
      SplitGAChannels();
    else
      SplitRGBAChannels();
  } else {
    image_file_ = input_file_;
  }

  RenderPDF();
}

void Converter::set_image_info() {
  std::ifstream stream(input_file_.c_str(), std::ifstream::binary);
  reader<std::istream> reader(stream);

  reader.read_info();

  image_info_ = reader.get_info();
}

void Converter::set_dimensions() {
  width_ = image_info_.get_width();
  height_ = image_info_.get_height();
  scale_ = kPointsPerInch / dpi_;
}

void Converter::set_transparency() {
  transparency_ = false;

  color_type c_type(image_info_.get_color_type());
  tRNS trns(image_info_.get_tRNS());

  if (c_type == color_type::color_type_rgba || c_type == color_type::color_type_ga)
    transparency_ = true;
  else if (!trns.empty())
    transparency_ = true;
}

std::string Converter::GenerateTempFilePath() {
  boost::filesystem::path path(boost::filesystem::temp_directory_path());

  path.append(boost::filesystem::unique_path().string());

  return path.string();
}

void Converter::SplitRGBAChannels() {
  image<rgba_pixel> input_png(input_file_);
  image<rgb_pixel> image_png(width_, height_);
  image<gray_pixel> mask_png(width_, height_);

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      rgba_pixel pixel(input_png.get_pixel(x, y));
      rgb_pixel new_pixel;

      if (pixel.alpha == 0)
        new_pixel = rgb_pixel(255, 255, 255);
      else
        new_pixel = rgb_pixel(pixel.red, pixel.green, pixel.blue);

      image_png.set_pixel(x, y, new_pixel);
      mask_png.set_pixel(x, y, gray_pixel(pixel.alpha));
    }
  }

  image_file_ = GenerateTempFilePath();
  mask_file_ = GenerateTempFilePath();

  image_png.write(image_file_);
  mask_png.write(mask_file_);
}

void Converter::SplitGAChannels() {
  image<ga_pixel> input_png(input_file_);
  image<gray_pixel> image_png(width_, height_), mask_png(width_, height_);

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      ga_pixel pixel(input_png.get_pixel(x, y));
      gray_pixel new_pixel;

      if (pixel.alpha == 0)
        new_pixel = gray_pixel(255);
      else
        new_pixel = gray_pixel(pixel.value);

      image_png.set_pixel(x, y, new_pixel);
      mask_png.set_pixel(x, y, gray_pixel(pixel.alpha));
    }
  }

  image_file_ = GenerateTempFilePath();
  mask_file_ = GenerateTempFilePath();

  image_png.write(image_file_);
  mask_png.write(mask_file_);
}

void Converter::RenderPDF() {
  PdfStreamedDocument document(output_file_.c_str());
  PdfPage *page;
  PdfPainter painter;
  PdfRect rect(0.0, 0.0, width_ * scale_, height_ * scale_);

  PdfImage image(&document);

  page = document.CreatePage(rect);
  painter.SetPage(page);

  if (transparency_) {
    PdfImage mask(&document);

    mask.LoadFromPng(mask_file_.c_str());
    image.SetImageSoftmask(&mask);
  }

  image.LoadFromPng(image_file_.c_str());
  painter.DrawImage(0.0, 0.0, &image, scale_, scale_);

  painter.FinishPage();
  document.Close();
}

void Converter::CleanUp() {
  if (!transparency_) return;

  std::remove(image_file_.c_str());
  std::remove(mask_file_.c_str());
}

} // namespace png2pdf
