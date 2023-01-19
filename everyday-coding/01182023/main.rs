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
        if self.age < 18 {
            println!("Oiiis, you need {} more years", self.need);
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
    let adult_noob = noob.adult_enough();
    let adult_noob = Noobie::adult_enough(&noob);
    let stupid_in_heap = mem::size_of_val(&adult_noob);
    println!("{:#?}", stupid_in_heap);

    // Output:
    // 12
    // test(
    //     25,
    // )
    // test(
    //     25,
    // )
    // test(
    //     25,
    // )
    // 2
    // noobie {
    //     age: 18,
    //     need: 0,
    //     fav: ReallyStupid,
    // }
    // true
    // 8
}