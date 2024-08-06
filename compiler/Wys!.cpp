#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <cstdlib>

// Inclure les autres fichiers nécessaires
#include "fstring.hpp"
#include "handles.hpp"
#include "strings.hpp"
#include "includes.hpp"
#include "filesystem.hpp"

void copy_file(const std::string &source_path, const std::string &destination_path)
{
  if (std::filesystem::exists(destination_path))
  {
    std::filesystem::remove(destination_path);
  }
  std::filesystem::copy(source_path, destination_path);
}

void replace_logical_operators(std::ifstream &in, std::ofstream &out)
{
  std::unordered_map<std::string, std::string> replacements = {
      {"or", "||"},
      {"not", "!"},
      {"and", "&&"},
      {"xor", "^"}};

  std::string word;
  while (in >> word)
  {
    if (replacements.find(word) != replacements.end())
    {
      out << replacements[word];
    }
    else
    {
      out << word;
    }

    char next_char = in.peek();
    if (next_char == ' ' || next_char == '\n' || next_char == '\t')
    {
      out << next_char;
      in.get();
    }
    else if (next_char == EOF)
    {
      break;
    }
  }
}

int main(int argc, char *const argv[])
{
  if (argc < 2)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <error>: No input file given\n";
    return 1;
  }

  std::string input_filename = argv[1];
  std::string output_filename = (argc >= 3 ? argv[2] : "output");
  std::string bin_dir = filesystem::getExecutableDirectory();
  std::string inter_file_path = bin_dir + "/temporal/inter.i";
  std::string final_file_path = bin_dir + "/temporal/final.cpp";
  std::string result_dll_path = bin_dir + "/temporal/result.dll";
  std::string output_dll_path = output_filename + ".dll";

  std::filesystem::create_directories(bin_dir);

  std::ofstream inter_file(inter_file_path);
  if (!inter_file)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <filesystem>: <error>: Error opening intermediate file: " << inter_file_path << std::endl;
    return 1;
  }

  Loader ld(input_filename, inter_file);
  inter_file.close();

  std::ofstream final_file(final_file_path);
  if (!final_file)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <filesystem>: <error>: Error opening final file: " << final_file_path << std::endl;
    return 1;
  }

  includes(final_file);
  blank++;

  std::ifstream input_file(inter_file_path);
  if (!input_file)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <filesystem>: <error>: Error opening input file: " << inter_file_path << std::endl;
    return 1;
  }

  std::unordered_map<std::string, std::function<void(std::istringstream &, std::ofstream &)>> handlers;
  def_handles(handlers);

  std::string line;
  while (std::getline(input_file, line))
  {
    std::istringstream iss(line);
    std::string keyword;
    iss >> keyword;

    auto it = handlers.find(keyword);
    if (it != handlers.end())
    {
      it->second(iss, final_file);
    }
    else
    {
      if (trim_copy(keyword).empty())
      {
        continue;
      }
      final_file << Blank() << keyword;
      std::string local_line;
      std::getline(iss, local_line);
      final_file << local_line << ";\n";
    }
  }

  blank--;
  final_file << Blank() << "}";

  input_file.close();
  replace_logical_operators(input_file, final_file);

  final_file.close();

  // Compilation
  wys::fstring str =
      "g++ -x c++ -shared -I{bin_dir}/res/include/ -I{bin_dir}/res/api/ -static-libgcc -static-libstdc++ -o  {result_dll_path} {final_file_path}";

  str.add_variable("bin_dir", bin_dir);
  str.add_variable("result_dll_path", result_dll_path);
  str.add_variable("final_file_path", final_file_path);

  std::system(str.format().c_str());

  copy_file(result_dll_path, output_dll_path);

  return 0;
}
