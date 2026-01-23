ss = stepsequencer([1, 2, 3, 4], 240); 
lin = linenvelope(ss, 0.001, 0.05, 0.001, 0.25);
c = sawtoothosc(ss * 110); 
e = sawtoothosc(ss * 55); 
f = sawtoothosc(ss * 109); 
g = sawtoothosc(ss * 111);
lowpassfilter(2000 * lin);
lowpassfilter(2000 * lin);