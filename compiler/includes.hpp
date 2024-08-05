#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> file_f;

class Loader
{
private:
  std::vector<std::string> Errors;
  std::unordered_map<std::string, bool> IsIncluded;

  void IncludeFile(const std::string &file_path, std::ofstream &out_stream)
  {
    std::ifstream ifile(file_path);
    if (!ifile.is_open())
    {
      if (file_f[file_path] != "")
      {
        out_stream << file_f[file_path] << '\n';
      }
      else
      {
        Errors.push_back("[wys]: > Wys! <loader>: <error>: " + file_path +
                         " : No such file\n");
        return;
      }
    }

    std::string line;
    while (std::getline(ifile, line))
    {
      std::istringstream iss(line);
      std::string word;
      iss >> word;
      if (word == "import")
      {
        std::string next;
        iss >> next;
        size_t pos = line.find('\'');
        size_t end = line.find('\'', pos + 1);
        if (pos == std::string::npos || end == std::string::npos)
        {
          Errors.push_back("[wys]: > Wys! <loader>: <error> : Expected \\' "
                           "token before and after import\n  | line: " +
                           line);
          continue;
        }
        std::string path = line.substr(pos + 1, end - (pos + 1));
        if (!IsIncluded[path])
        {
          IsIncluded[path] = true;
          IncludeFile(path, out_stream);
          std::cout << "[wys]: <loader>: > Wys! file included:\t" << path
                    << '\n';
        }
      }
      else
      {
        out_stream << line << '\n';
      }
    }
    ifile.close();
  }

public:
  Loader(const std::string &file_name, std::ofstream &ofile)
  {
    IncludeFile(file_name, ofile);
  }

  const std::vector<std::string> &getErrors() const { return Errors; }
};
