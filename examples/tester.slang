ss = stepsequencer([1, 1.2, 1.33333, 1.5,  1.6, 1.5, 1.3333, 1.6], 240); 
lin = linenvelope(ss, 0.001, 0.05, 0.001, 0.25);
c = sawtoothosc(ss * 110); 
e = sawtoothosc(ss * 55); 
f = sawtoothosc(ss * 110.2); 
g = sawtoothosc(ss * 220);
lowpassfilter(1500 * lin);
lowpassfilter(1500 * lin);