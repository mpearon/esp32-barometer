# esp32-barometer

## The Idea
I was gifted a few old barometers and one of them was broken beyond repair, so
after many months of staring at what was essentially a neat looking paper weight
I decided to make it useful again.

If you've perused my repositories, you might have notice an aviation theme to
some of them - well, surprise!  This one is too.  I'll be polling [the aviation 
weather API offered by aviationweather.gov][WxApi] and using the data to drive
physical needles on the barometer.

I'm not familiar with the beat that is `C++`, so please don't make fun of any of
the incredibly stupid and/or inefficient mistakes I'm going to make.  We all
benefit from someone else learning out loud.  Wheels up!

## The Parts List
- ESP32
- (3) 28BYJ-48 Stepper Motors
- (3) ULN-2003 Stepper Motor Controllers
- An old barometer

## The Execution

## The To-do List
- [X] Acquire METAR
- [X] Parse METAR
- [X] Process `altim`
- [X] Drive barometer stepper to position using `altim`
- [X] Build barometer stepper homing mechanism
- [ ] Commit last barometer stepper position to permanent storage
- [ ] Drive temperature stepper to position using `temp`
- [ ] Build temperature stepper homing mechanism
- [ ] Commit last temperature stepper position to permanent storage
- [ ] Drive humidity stepper to position using `temp` and `dewp`
	- [Meterological Calculator][metCalc]
- [ ] Build humidity stepper homing mechanism
- [ ] Commit last humidity stepper position to permanent storage
- [ ] Build web-based configuration options
	- [ ] Airport selection
	- [ ] Consolidated Stepper Homing
- [ ] Add [BME 280 Environment Sensor][bme] for local data
- [ ] Build automatic or manual toggle for switching between local/remote data


[WxApi]: https://aviationweather.gov/data/api/#/Data/dataMetars
[metCalc]: https://www.weather.gov/lzk/metcalc.htm
[bme]: https://www.adafruit.com/product/2652