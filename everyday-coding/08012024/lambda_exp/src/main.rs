#![feature(new_uninit)]

use std::mem::MaybeUninit;

fn exp1() {
  let vec1 = [1, 2, 3, 4, 5];
  let square = vec1.into_iter().map(|e| e * e).collect::<Vec<_>>();
  println!("Exp1: {:?}", square);
}

fn exp2() {
  let vec1 = [1, 2, 3, 4, 5, 6, 7, 8];
  let square = vec1.into_iter().filter(|e| e % 2 == 0).collect::<Vec<_>>();
  println!("Exp2: {:?}", square);
}

fn exp3() {
  let vec1 = [1, 2, 3, 4, 5, 6, 7, 8];
  let accumulate = vec1.into_iter().fold(1, |acc, e| acc * e);
  println!("Exp3: {:?}", accumulate);
}

fn exp4() {
  let vec1 = [1, 2, 3, 4, 5, 6, 7, 8];
  let vec2 = [9, 10, 11, 12];
  for (e1, e2) in vec1.iter().zip(vec2.iter()) {
    println!("Exp4: e1~{e1}, e2~{e2}");
  }
}

fn exp5() {
  let vec1 = [1, 2, 3, 4, 5, 6, 7, 8, 9];
  for (idx, chunk) in vec1.chunks(3).enumerate() {
    println!("Exp5: {idx}~{chunk:?}");
  }
}

fn exp6() -> bool {
  let zero = MaybeUninit::<u32>::zeroed();
  let zero = unsafe { zero.assume_init() };
  let triple_zeroes = Box::<[u32]>::new_zeroed_slice(3);
  let triple_zeroes = unsafe { triple_zeroes.assume_init() };
   *triple_zeroes == [zero, zero, zero]
}

fn exp7() {
  let vec1 = [1, 2, 3];
  let vec2 = [4, 5, 6];
  let vec3 = [7, 8, 9];
  let chained = vec1.iter().chain(vec2.iter()).chain(vec3.iter()).collect::<Vec<_>>();
  println!("Exp7: {chained:?}");
}

fn exp8() -> bool {
  [2, 4, 6, 8].iter().all(|e| *e % 2 == 0) && [2, 4, 6, 8].iter().any(|e| *e > 7)
}

fn exp9() -> bool {
  let vec1 = [2, 4, 6, 8, 10, 12];
  // NOTE: `slice.windows()` not `iterator.windows()`!
  vec1.windows(2).all(|chunk| chunk[0] < chunk[1])
}

fn exp10() {
  let vec1 = [5, 10, 15];
  let cycle = vec1.iter().cycle().take(10).collect::<Vec<_>>();
  println!("Exp10: {cycle:?}");
}

// cargo +nightly run

fn main() {
  println!("Hello, world!");
  exp1();
  exp2();
  exp3();
  exp4();
  exp5();
  let is_equal = exp6();
  println!("{is_equal}");
  exp7();
  let silly_condition = exp8();
  println!("{silly_condition:?}");
  let is_ascending = exp9();
  println!("{is_ascending:?}");
  exp10();
}
