#![no_std]
#![no_main]

use arduino_hal::prelude::*;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let peripherals = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(peripherals);
    let mut serial = arduino_hal::default_serial!(peripherals, pins, 57600);

    let mut led_pin = pins.d13.into_output();
    let button_pin = pins.d2.into_pull_up_input();

    ufmt::uwriteln!(&mut serial, "Hello, World!/r").void_unwrap();

    loop {
        if button_pin.is_high() {
            led_pin.set_high()
        } else {
            led_pin.set_low()
        }
    }
}
