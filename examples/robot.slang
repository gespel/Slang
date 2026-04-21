r = randomstepsequencer([1, 2, 3.33, 1.666, 1.33, 5.66, 2.33, 1.76], [0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5], 480);
l = linenvelope(r, 0.001, 0.1, 0.1, 0.01);

x = truesineosc(r * 110);
a = truesineosc(r * 55);
y = truesineosc(r * 771);
z = truesineosc(r * 769);
xa = sawtoothosc(r * 110);
aa = sawtoothosc(r * 55);
ya = sawtoothosc(r * 771);
za = sawtoothosc(r * 769);

lowpassfilter(MAIN, 300 * l);
springreverb(0.005, 0.95, 0.04, 0.1);