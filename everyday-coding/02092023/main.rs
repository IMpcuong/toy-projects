use std::fmt::*;
use std::mem;

// Can use Copy, Clone traits to avoid unclonable behaviour.
#[derive(Debug)]
struct Test(i32);

impl Display for Test {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "{}", self.0)
    }
}

impl Test {
    fn new(val: i32) -> Self {
        Self(val)
    }

    fn borrow_understood(&mut self, extra: f32) -> &mut Self {
        self.0 += extra as i32;
        self
    }

    fn divide_by(&self, divisor: i32) -> i32 {
        if self.0 > 2 && divisor != 2 {
            self.0 / divisor
        } else {
            self.0 + divisor
        }
    }
}

#[derive(Copy, Clone, Debug, Eq, PartialEq)]
enum Hobby {
    SuperStupid,
    ReallyStupid,
    ReallySmart,
}

// NOTE: Generic type `Human` or `T` are both accepted.
pub trait Action {
    fn is_stupid(&self) -> bool;

    fn adult_enough(&self) -> Box<Self>;
}

#[derive(Copy, Clone, Debug)]
pub struct Noobie {
    age: i8,
    need: i8,
    fav: Hobby,
}

impl Action for Noobie {
    fn is_stupid(&self) -> bool {
        // NOTE: Custom enum requires to derive `Partial_Eq` traits to use any
        //  condition operator.
        match self.fav {
            Hobby::ReallyStupid | Hobby::SuperStupid => return true,
            Hobby::ReallySmart => return false,
        }
    }

    fn adult_enough(&self /* self: Noobie */) -> Box<Self> {
        let under_adult_age: i8 = 18;
        if self.age < under_adult_age {
            if self.need == 0 {
                println!("Oiiis, you need {} more years", under_adult_age - self.age);
            } else {
                println!("Oiiis, you need {} more years", self.need);
            }
        }
        // NOTE: Moving `self` out of the function's scope or binding with the
        //  return statement demands the `Copy, Clone` traits.
        Box::new(*self)
    }
}

impl Noobie {
    fn new_noob(fav: Hobby, age: i8) -> Self {
        let need = 18 - age;
        // NOTE: The order of struct's fields are trivial.
        Self{fav, age, need}
    }
}

fn main() {
    let x: i32 = 12; // By default this is i32.

    let t: Test = Test::new(x);
    println!("{:}", t);

    let mut t1 = Test::new(&x+1);
    println!("{:#?}", &t1.borrow_understood(12.0));
    println!("{:#?}", t1);

    let t2 = &t1;
    println!("{:#?}", t2);

    println!("{:#?}", t1.divide_by(t.0));

    let cur_age: i8 = 18;
    let noob = Noobie::new_noob(Hobby::ReallyStupid, cur_age);
    println!("{:#?}", noob);
    println!("{:#?}", noob.is_stupid());

    // NOTE: Shadowing variable (`noob`) is valid here because of the
    //  `Copy, Clone` traits implementation in both enum `Hobby` and
    //  `Noobie` struct.
    let adult_noob: Box<Noobie> = noob.adult_enough();
    println!("{:#?}", adult_noob);

    // ERROR: https://github.com/rust-lang/rust/issues/80437
    // let mut unboxed_adult_noob: Noobie = Box::<Noobie>::into_inner(adult_noob);

    // NOTE: Dereference a raw pointer (maybe null, dangling or unaligned; they
    //  can violate aliasing rules and cause data races) is unsafe and requires
    //  unsafe function block.
    unsafe {
        let mut unboxed_adult_noob: Noobie = *Box::into_raw(adult_noob.clone());
        unboxed_adult_noob.fav = Hobby::ReallySmart;
        unboxed_adult_noob.age = 12;
        println!("{:#?}", unboxed_adult_noob.adult_enough());
    }

    let other_adult_noob: Box<Noobie> = Noobie::adult_enough(&adult_noob);
    println!("{:#?}", other_adult_noob);

    let stupid_in_heap = mem::size_of_val(&other_adult_noob);
    println!("{:#?}", stupid_in_heap);

    // Output:
    // 12
    // Test(
    //    25,
    // )
    // Test(
    //    25,
    // )
    // Test(
    //    25,
    // )
    // 2
    // Noobie {
    //     age: 18,
    //     need: 0,
    //     fav: ReallyStupid,
    // }
    // true
    // Noobie {
    //     age: 18,
    //     need: 0,
    //     fav: ReallyStupid,
    // }
    // Oiiis, you need 6 more years
    // Noobie {
    //     age: 12,
    //     need: 0,
    //     fav: ReallySmart,
    // }
    // Noobie {
    //     age: 18,
    //     need: 0,
    //     fav: ReallyStupid,
    // }
    // 8
}