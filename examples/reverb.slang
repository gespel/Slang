s = stepsequencer([1, 1.333], 12);
ss = stepsequencer([1, 2, 3, 4], 480); 
lin = linenvelope(ss, 0.001, 0.05, 0.001, 0.07);
c = sawtoothosc(s * ss * 110); 
lowpassfilter(MAIN, 1000 * lin);

springreverb(0.05, 0.8, 0.4, 0.5);