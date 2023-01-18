use std::fmt::*;

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

fn main() {
    let x: i32 = 12; // by default this is i32
    
    let t: Test = Test::new(x);
    println!("{:}", t);
    
    let mut t1 = Test::new(&x+1);
    println!("{:#?}", &t1.borrow_understood(12.0));
    println!("{:#?}", t1);
    
    let t2 = &t1;
    println!("{:#?}", t2);
    
    println!("{:#?}", t1.divide_by(t.0))
}
