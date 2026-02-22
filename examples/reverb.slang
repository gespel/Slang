ss = stepsequencer([1, 2, 3, 4], 240); 
lin = linenvelope(ss, 0.001, 0.05, 0.001, 0.25);
c = sawtoothosc(ss * 110); 
lowpassfilter(MAIN, 1500 * lin);

springreverb(0.05, 0.7, 0.8, 0.3);