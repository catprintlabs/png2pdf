#include "converter.hpp"

namespace png2pdf {

Converter::Converter(std::string input_file, std::string output_file, int dpi)
{
  input_file_ = input_file;
  output_file_ = output_file;
  dpi_ = dpi;
};

void Converter::Convert()
{
  SplitPng();
  EmbedPngs();
}

std::string Converter::GenerateTempFilePath()
{
  boost::filesystem::path path(boost::filesystem::temp_directory_path());

  path.append(boost::filesystem::unique_path().string());

  return path.string();
}

void Converter::SplitPng()
{
  image<rgba_pixel> png(input_file_);

  width_ = png.get_width();
  height_ = png.get_height();

  image<rgb_pixel> rgb_png(width_, height_);
  image<gray_pixel> alpha_png(width_, height_);

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      rgba_pixel pixel(png.get_pixel(x, y));
      rgb_pixel new_pixel;

      if (pixel.alpha == 0)
        new_pixel = rgb_pixel(255, 255, 255);
      else
        new_pixel = rgb_pixel(pixel.red, pixel.green, pixel.blue);

      rgb_png.set_pixel(x, y, new_pixel);
      alpha_png.set_pixel(x, y, gray_pixel(pixel.alpha));
    }
  }

  rgb_file_ = GenerateTempFilePath();
  alpha_file_ = GenerateTempFilePath();

  rgb_png.write(rgb_file_);
  alpha_png.write(alpha_file_);
}

void Converter::EmbedPngs()
{
  PdfStreamedDocument document(output_file_.c_str());
  PdfPage *page;
  PdfPainter painter;
  PdfRect rect(0.0, 0.0, (width_ / dpi_) * 72, (height_ / dpi_) * 72);
  PdfImage image(&document);
  PdfImage mask(&document);
  double scale(72.0 / dpi_);

  page = document.CreatePage(rect);
  painter.SetPage(page);

  mask.LoadFromPng(alpha_file_.c_str());
  image.SetImageSoftmask(&mask);

  image.LoadFromPng(rgb_file_.c_str());
  painter.DrawImage(0.0, 0.0, &image, scale, scale);

  painter.FinishPage();
  document.Close();
}

void Converter::CleanUp()
{
  std::remove(rgb_file_.c_str());
  std::remove(alpha_file_.c_str());
}

} // namespace png2pdf
