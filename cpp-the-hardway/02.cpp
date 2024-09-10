#include <cxxabi.h>

#include <iostream>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>

// clang++ -std=c++17 -o out 02.cpp
// clang++ -std=c++20 -o out 02.cpp

namespace Investigator
{
  template <typename NT>
  struct GenericTypeHelper
  {
    static std::string_view get_name()
    {
      const std::type_info &info = typeid(NT);
      int status;
      // NOTE: https://www.geeksforgeeks.org/reflection-in-cpp.
      char *demangled_name = abi::__cxa_demangle(info.name(), nullptr, nullptr, &status);
      static std::string_view t = (status == 0) ? std::string_view(demangled_name) : info.name();
      std::cout << t << std::endl;
      return t;
    }
  };

  template <typename S = std::size_t>
  class Vector
  {
  private:
    constexpr static bool verify_vector_type()
    {
      std::string vtype_as_str(GenericTypeHelper<S>::get_name());
      return vtype_as_str.find("signed") != std::string::npos;
    }

    constexpr static std::string
    convert_num_to_string(S num)
    {
      // if (!std::same(S, std::size_t))
      return std::to_string(num);
    }

  public:
    Vector() = default;
    virtual ~Vector() {};

    template <typename T>
    static void ptr_func(const T *ptr, S size)
    {
      std::string data;
      if (verify_vector_type())
        data = "data-" + convert_num_to_string(size) + " = ";
      std::cout << data;
      for (S i = 0; i < size; ++i)
        std::cout << ptr[i] << " ";
      std::cout << "\n";
    }
  };
}

int main()
{
  std::vector<int> vec1_;
  vec1_.push_back(12345);
  std::cout << vec1_.size() << "\n"; // 1
  std::cout << vec1_.back() << "\n"; // 12345

  std::vector<uint16_t> vec2_(5, 100);
  vec2_.push_back((uint16_t)12345);
  vec2_.push_back((uint16_t)12345);
  vec2_.pop_back();
  std::cout << vec2_.size() << "\n"; // 6
  std::cout << vec2_.back() << "\n"; // 12345

  std::vector<int> vec3_{1, 2, 3, 4};
  std::vector<int> vec4_(vec3_.begin(), vec3_.end());
  std::cout << vec4_.at(1) << "\n";                                  // 2
  Investigator::Vector<>::ptr_func<int>(vec4_.data(), vec4_.size()); // data-4 = 1 2 3 4

  int arr[] = {1, 2, 3, 4, 5};
  std::vector<int> vec5_(arr, arr + sizeof(arr) / sizeof(int));
  std::cout << vec5_.at(3) << "\n";
  Investigator::Vector<uint8_t>::ptr_func<int>(vec5_.data(), (uint8_t)vec5_.size()); // data-5 = 1 2 3 4 5

  std::vector<int> vec6_(6);
  fill(vec6_.begin(), vec6_.end(), 5);
  Investigator::Vector<>::ptr_func<int>(vec6_.data(), vec6_.size()); // data-6 = 5 5 5 5 5 5

  std::vector<int> vec7_(7);
  iota(vec7_.begin(), vec7_.end(), 8);
  Investigator::Vector<>::ptr_func<int>(vec7_.data(), vec7_.size()); // data-7 = 8 9 10 11 12 13 14

  return 0;
}
