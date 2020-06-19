#include "boost/program_options.hpp"

#include "converter.hpp"

#define VERSION PNG2PDF_VERSION
#define EXECUTABLE PNG2PDF_EXECUTABLE

std::string input_file, output_file;
int dpi;

int ParseOptions(int argc, char* argv[])
{
  boost::program_options::options_description desc("Options");

  desc.add_options()
    ("help,h", "print program options")
    ("input-file,i", boost::program_options::value<std::string>(), "PNG file to be converted")
    ("output-file,o", boost::program_options::value<std::string>(), "PDF file to be generated")
    ("dpi,d", boost::program_options::value<int>(&dpi)->default_value(72),
      "DPI of PNG provided, defaults to 72")
  ;

  boost::program_options::variables_map var;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), var);
  boost::program_options::notify(var);

  if (var.size() == 1 || var.count("help")) {
    std::cout << "Version: " << VERSION << "\n";
    std::cout << "Usage: " << EXECUTABLE << " [options ...]\n";
    std::cout << "\n" << desc << "\n";

    return 1;
  }

  if (var.count("input-file")) {
    input_file = var["input-file"].as<std::string>();
  } else {
    std::cout << "input-file must be specified" << "\n";

    return 1;
  }

  if (var.count("output-file")) {
    output_file = var["output-file"].as<std::string>();
  } else {
    std::cout << "output-file must be specified" << "\n";

    return 1;
  }

  if (var.count("dpi"))
    dpi = var["dpi"].as<int>();

  return 0;
}

int main(int argc, char* argv[])
{
  int parsed(ParseOptions(argc, argv));

  if (parsed > 0)
    return parsed;

  png2pdf::Converter converter(input_file, output_file, dpi);

  converter.Convert();

  return 0;
}
