//your slang script goes here! :D
r = randomstepsequencer([1, 2], [0.5, 0.5], 120);
l = linenvelope(r, 0.01, 0.1, 0.1, 0.1);
x = sawtoothosc(r * 110);
lowpassfilter(MAIN, 250 * l);