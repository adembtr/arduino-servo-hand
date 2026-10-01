# arduino-servo-hand

**An Arduino sketch for a four-finger robotic hand. Each finger is driven by a hobby servo and moves smoothly between poses.**

## What it does

`kol1/kol1.ino` (*kol* means "arm" in Turkish) drives 4 servos, one per finger, through
the standard `Servo` library. Each finger's pose is a value between `0` (fully closed) and
`1` (fully open), which is mapped linearly onto that finger's angle range (default
0–170°). The sketch then runs a demo loop:

1. all fingers closed
2. all fingers open
3. fingers 1–2 open, fingers 3–4 closed
4. fingers 1–2 closed, fingers 3–4 open

Each transition is interpolated over 100 small steps 20 ms apart, so a move takes about
2 seconds. All 4 servos move together.

## How it works

- `range[i] = {min, max}` holds the angle limits of finger `i`.
  `steps[i] = (max − min) / 100` is the per-step increment.
- `CmdSet(a, b, c, d)` sets the target pose of the four fingers.
- `dynamicPos()` inverts the pose (`1 − cmd`), converts it to a target angle and, on each
  step, moves every servo one increment toward its target.

## Hardware

| Finger | Arduino pin |
|---|---|
| 1 | D10 |
| 2 | D9 |
| 3 | D6 |
| 4 | D5 |

You need an Arduino Uno (or a compatible board) and 4 hobby servos. Tip: power the servos
from an external 5–6 V supply and connect its ground to the Arduino's GND. Four servos can
draw more current than the board's 5 V pin can supply.

## Build and upload

Arduino IDE: open `kol1/kol1.ino`, select **Arduino Uno**, then click **Upload**.

Or with `arduino-cli`:

```bash
arduino-cli compile --fqbn arduino:avr:uno kol1
arduino-cli upload  --fqbn arduino:avr:uno -p /dev/ttyACM0 kol1
```

With AVR core 1.8.7 the sketch compiles to about 5.2 KB of flash (16%) and 306 bytes of
RAM on an Uno.

## Project status

Early prototype: a first motion test for the hand.

- The serial port is opened (`9600` baud) but no commands are read yet. The poses are
  hard-coded in `loop()`.
- `Servo::write()` takes an `int`, so `nPos ± 1.7` is truncated. Moves toward larger
  angles (closing) advance only 1° per step, so one 2-second transition covers at most
  about 100° and a full 0 → 170° close does not finish. Opening moves advance 2° per
  step. Rounding the value, or keeping positions in a `double` array, would fix this.
- The `dir[]` array is not used yet.

## License

[MIT](LICENSE)

---

Built by [Adem Batur](https://github.com/adembtr)
