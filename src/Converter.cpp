#include "Converter.hpp"

namespace png2pdf {

Converter::Converter(std::string in, std::string out, int dpi_value)
{
  input = in;
  output = out;
  dpi = dpi_value;
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
  image<rgba_pixel> png(input);

  width = png.get_width();
  height = png.get_height();

  image<rgb_pixel> rgb_png(width, height);
  image<gray_pixel> alpha_png(width, height);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
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

  rgb_file = GenerateTempFilePath();
  alpha_file = GenerateTempFilePath();

  rgb_png.write(rgb_file);
  alpha_png.write(alpha_file);
}

void Converter::EmbedPngs()
{
  PdfStreamedDocument document(output.c_str());
  PdfPage *page;
  PdfPainter painter;
  PdfRect rect(0.0, 0.0, (width / dpi) * 72, (height / dpi) * 72);
  PdfImage image(&document);
  PdfImage mask(&document);
  double scale(72.0 / dpi);

  page = document.CreatePage(rect);
  painter.SetPage(page);

  mask.LoadFromPng(alpha_file.c_str());
  image.SetImageSoftmask(&mask);

  image.LoadFromPng(rgb_file.c_str());
  painter.DrawImage(0.0, 0.0, &image, scale, scale);

  painter.FinishPage();
  document.Close();
}

void Converter::CleanUp()
{
  std::remove(rgb_file.c_str());
  std::remove(alpha_file.c_str());
}

} // namespace png2pdf
