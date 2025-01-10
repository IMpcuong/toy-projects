#include <cxxabi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// clang++ -std=c++ 20 -O2 03.cpp -o out

class Person
{
private:
  std::string _addr;

public:
  int age;
  std::string name;

  Person() = default;
  Person(int age) : age(age) {};
  Person(int age, std::string name) : age(age), name(std::move(name)) {};
};

class FileProducer
{
private:
  FILE *_unchained;

public:
  FileProducer(const std::string &full_path, const std::string &granted_mode)
  {
    _unchained = fopen(full_path.c_str(), granted_mode.c_str());
    if (!_unchained)
    {
      std::ofstream _avoid_non_exist_state_file(full_path);
      _avoid_non_exist_state_file << "you're doin' great, my friendo!" << std::endl;
      _avoid_non_exist_state_file.close();
    }
  }

  ~FileProducer()
  {
    fclose(_unchained);
  }

  /*
   * @brief DEPRECATED.
   */
  FILE examine_rvalue() const
  {
    FILE copied_file = *_unchained;
    return copied_file;
  }

  template <typename GenericType>
  static std::string time_to_str(const GenericType &stat_time)
  {
    // NOTE: https://stackoverflow.com/a/69499089/12535617
    std::ostringstream oss;
    oss << stat_time;
    return oss.rdbuf()->str();
  }
};

int main()
{
  Person person = Person(50, "John Cena"); // or: `person(50, "John Cena")`.
  std::cout << person.name << " is " << person.age << "\n";

  std::array<std::string_view, 2> filenames = {"non_existence_dude_path", "README.md"};
  std::vector<FileProducer> list_file;
  [&](std::string _r = "r")
  {
    for (const auto &_fname : filenames)
    {
      try
      {
        FileProducer cfh(/* file_path */ std::string(_fname.data(), _fname.size()),
                         /* file_mode */ _r);
        list_file.push_back(cfh);
        if (_fname.find_first_of("non") != std::string::npos)
          std::cout << _fname.data() << std::endl;
      }
      catch (const std::exception &e)
      {
        std::cout << e.what();
      }
    }
  }();
  std::for_each(filenames.cbegin(),
                filenames.cend(),
                [=](const std::string_view &_file_name_view)
                {
                  std::string _file_name = std::string(_file_name_view.data(), _file_name_view.size());
                  struct stat _file_buf_stat;
                  if (stat(/* file_path */ _file_name.c_str(),
                           /* sys/stat buffer */ &_file_buf_stat))
                    perror("Oops");

                  FILE *_file_closure = fopen(_file_name.c_str(), "r");
                  long _file_pos = std::ftell(_file_closure);
                  fclose(_file_closure);
                  long long _file_size = _file_buf_stat.st_size;
                  std::string _file_creation_date = FileProducer::time_to_str(_file_buf_stat.st_birthtimespec.tv_sec);
                  std::cout << _file_pos << " " << _file_size << " "
                            << _file_buf_stat.st_mode << " " << _file_creation_date << "\n";
                });
  return 0;
}