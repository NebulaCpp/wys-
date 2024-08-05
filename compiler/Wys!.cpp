#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "fstring.hpp"
#include "handles.hpp"
#include "strings.hpp"
#include "includes.hpp"

int main(int argc, char *const argv[])
{
  if (argc < 2) 
  {
    std::cerr << "[wys]: > Wys! <compiler>: <error>: No input file given\n";
    return 1;
  }

  std::unordered_map<std::string, std::function<void(std::istringstream &, std::ofstream &)>> handlers;

  handlers["var"] = handle_var;
  handlers["function"] = handle_func;
  handlers["struct"] = handle_struct;
  handlers["end"] = handle_end;
  handlers["if"] = handle_if;
  handlers["elif"] = handle_elif;
  handlers["else"] = handle_else;
  handlers["else:"] = handle_else;
  handlers["include"] = handle_include;
  handlers["throw"] = handle_throw;
  handlers["for"] = handle_for;
  handlers["while"] = handle_while;
  handlers["try"] = handle_try;
  handlers["try:"] = handle_try;
  handlers["catch"] = handle_catch;
  handlers["catch:"] = handle_catch;

  std::string input_filename = argv[1];
  std::string output_filename = (argc >= 3 ? argv[2] : input_filename);

  std::ofstream output_file(output_filename + ".cpp");
  std::ofstream inter_file(output_filename + ".i");

  Loader ld(input_filename, inter_file);

  inter_file.close();

  if (!output_file)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <filesystem>: <error>: Error opening output file: " << output_filename << std::endl;
    return 1;
  }

  output_file
      << "#include \"wlerror.hpp\"\n"
      << "#include \"wlio.hpp\"\n"
      << "#include \"wlvector.hpp\"\n"
      << "#include \"wlmemory.hpp\"\n"
      << "#include \"wlstring.hpp\"\n"
      << "#include \"wlstringfmt.hpp\"\n"
      << "#include \"wltype.hpp\"\n"
      << "#include \"wlutiles.hpp\"\n"
      << "using namespace wys;\n"
      << "extern \"C\" {\n";
  blank++;

  std::ifstream input_file(output_filename + ".i");

  std::string line;
  while (std::getline(input_file, line))
  {
    std::istringstream iss(line);
    std::string keyword;
    iss >> keyword;

    auto it = handlers.find(keyword);
    if (it != handlers.end())
    {
      it->second(iss, output_file);
    }
    else
    {
      if (trim_copy(keyword).empty())
      {
        continue;
      }
      output_file << Blank() << keyword; 
      std::string local_line;
      std::getline(iss, local_line);
      output_file << local_line << ";\n";
    }
  }

  blank--;
  output_file << Blank() << "}";
  input_file.close();
  output_file.close();

  wys::fstring str = 
  "g++ -x c++ -shared -I./res/include/ -I./res/api/ -static-libgcc -static-libstdc++ -o {output_filename}.dll {output_filename}.cpp";

  str.add_variable("output_filename", output_filename);

  std::system(str.format().c_str());

  std::cout << output_filename << ' ' << input_filename << '\n';

  return 0;
}
