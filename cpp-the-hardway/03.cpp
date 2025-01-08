#include <cxxabi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
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

class CustomFileHandler
{
private:
  FILE *_unchained;

public:
  CustomFileHandler(const std::string &full_path, const std::string &granted_mode)
  {
    _unchained = fopen(full_path.c_str(), granted_mode.c_str());
    if (!_unchained)
    {
      std::ofstream _avoid_non_exist_state_file(full_path);
      _avoid_non_exist_state_file << "you're doin' great, my friendo!" << std::endl;
    }
  }

  ~CustomFileHandler()
  {
    fclose(_unchained);
  }

  FILE examine_rvalue() const
  {
    FILE copied_file = *_unchained;
    return copied_file;
  }

  int obtain_file_descriptor() const
  {
    return fileno(_unchained);
  }
};

int main()
{
  Person person = Person(50, "John Cena"); // or: `person(50, "John Cena")`.
  std::cout << person.name << " is " << person.age << "\n";

  std::array<std::string_view, 2> filenames = {"non_existence_dude_path", "README.md"};
  std::vector<CustomFileHandler> list_file;
  [&](std::string _r = "r")
  {
    for (const auto &_fname : filenames)
    {
      try
      {
        CustomFileHandler cfh(/* file_path */ std::string(_fname.data(), _fname.size()),
                              /* file_mode */ _r);
        list_file.push_back(cfh);
        // if (_fname.find_first_of("non") != std::string::npos)
        //   std::remove(_fname.data());
      }
      catch (const std::exception &e)
      {
        std::cout << e.what();
      }
    }
  }();
  std::for_each(list_file.cbegin(),
                list_file.cend(),
                [&](const CustomFileHandler &f)
                {
                  int fd = f.obtain_file_descriptor();

                  // struct stat _file_stat;
                  // if (fstat(fd, &_file_stat))
                  //   perror("Oops");

                  // long _file_pos = std::ftell(&_file_closure);
                  // long long _file_size = _file_stat.st_size;
                  // std::cout << _file_pos << _file_size << "\n";
                  std::cout << fd << std::endl;
                });
}