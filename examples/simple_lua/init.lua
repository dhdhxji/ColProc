Font = v("3_by_57")

Hrs = GeneratorText:new(vcasts(hrs),Font)
Mins = Move:new(GeneratorText:new(vcasts(mins),Font), v(10), v(0))
Dash = Move:new(GeneratorText:new(v(":"), Font), v(7), v(0))

Tmp = Concat:new(colprocVec(Hrs, Dash, Mins))
ClockText = Move:new(Tmp, v(1), v(1))
Rainbow = GeneratorRainbow:new(v(50), v(10), v(5000))

ClockMixed = Mixer:new(Rainbow, ClockText)

RenderTree = BrightnessScale:new(ClockMixed, v(1.0))