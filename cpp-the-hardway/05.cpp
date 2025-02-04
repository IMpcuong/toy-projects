#include <cassert>
#include <functional>
#include <iostream>
#include <string>

//
// Convenient IO functions.
//

template <typename... Args>
void print(const Args &...args)
{
  (std::cout << ... << args);
}

template <typename... Args>
void println(const Args &...args)
{
  (std::cout << ... << args) << "\n";
}

//
// Member-func/method demystification.
//

class Animal
{
public:
  // Pure virtual (abstract) method forces the deprived/inherited sub-class
  // to define this method's body (behaviour) explicitly.
  virtual int report_pure_amount_of_limb() const = 0;

  virtual int report_amount_of_limb() const
  {
    return 0 /* zero-legs */;
  }

  virtual void give_name_to_animal(std::string name)
  {
    this->distinct_name = std::move(name);
  }

  virtual std::string report_animal_name() const
  {
    return distinct_name;
  }

private:
  std::string distinct_name;
};

class Fox : public Animal
{
public:
  Fox()
  {
    quantity++;
  }

  ~Fox()
  {
    quantity--;
  }

  int report_pure_amount_of_limb() const override
  {
    return 4 /* fox-legs */;
  }

  void give_name_to_animal(std::string name) override
  {
    this->distinct_name = std::move(name);
  }

  std::string report_animal_name() const override
  {
    return distinct_name;
  }

  static int report_fox_instances()
  {
    return quantity;
  }

private:
  static int quantity;
  int legs = 4;
  std::string distinct_name;
};

int Fox::quantity = 8;

namespace Math_Executor
{
  constexpr int add(int first, int second)
  {
    return first + second;
  }
}

//
// Namespace and namespace-aliases:
//

namespace Math_Simulator
{
  constexpr int add(int first, int second)
  {
    return first + second;
  }
}

namespace ME = Math_Executor;
namespace MS = Math_Simulator;

//
// Ordered map.
//

template <typename Param_Type, typename Comparison = std::less<>>
constexpr bool collate_first_char_from_str(Param_Type lhs, Param_Type rhs,
                                           Comparison comp_func = Comparison{})
{
  return comp_func(lhs, rhs);
}

int main()
{
  print("Mars is ", 1.5, "AU from the Sun.\n");
  println("Venus is ", 0.7, "AU from the Sun.");

  // ----- //

  Fox f;
  f.give_name_to_animal("Nine-tails");
  println(f.report_animal_name());
  println(f.report_amount_of_limb());
  println(f.report_pure_amount_of_limb());
  println(Fox::report_fox_instances());

  f.~Fox(); // Explicitly invokes/triggers destructor.
  println(Fox::report_fox_instances());

  // ----- //

  println(Math_Executor::add(1, 2) == Math_Simulator::add(1, 2));
  println(ME::add(132, 424) == MS::add(778, 681));

  // ----- //

  std::string s1 = "something";
  std::string s2 = "right";
  assert(collate_first_char_from_str(s1.at(0), s2.at(0)) == false); // If `false` -> throws exception -> abort process.
}
