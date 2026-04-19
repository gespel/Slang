r = randomstepsequencer([1, 2, 3.33, 1.666, 1.33, 5.66, 2.33, 1.76], [0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5], 480);
l = linenvelope(r, 0.001, 0.1, 0.1, 0.01);
x = sawtoothosc(r * 110);
a = sawtoothosc(r * 55);
y = sawtoothosc(r * 771);
z = sawtoothosc(r * 769);
lowpassfilter(MAIN, 300 * l);
springreverb(0.005, 0.95, 0.04, 0.1);