#![feature(new_uninit)]
fn main() {
    let mut five = Box::new_uninit();

    let five = unsafe {
        // Deferred initialization:
        // Error: &5 as *const i64 (https://doc.rust-lang.org/nightly/error_codes/E0606.html).
        let raw_ptr = 5 as *mut i64;
        // Error: five.as_raw_ptr().write(raw_ptr) (https://doc.rust-lang.org/nightly/error_codes/E0699.html).
        five.write(raw_ptr);

        five.assume_init()
    };

    assert_eq!(*five, 5 as *mut i64);
    println!("{:#?}", *five);
}
