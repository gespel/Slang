a = 3; 
b = 2; 

fn freqcalc(x, y) {
    return x * y * 10;
}

freq = freqcalc(a, b);

x = sawtoothosc(1)+;
s = stepsequencer([3, 2.5, 1, 6], 300); 
ss = stepsequencer([2, 8, 16, 32], 300); 
c = squareosc(s * 110 * a); 
d = sawtoothosc(8)+; 
lowpassfilter(ss * freqcalc(4, 2)); 
e = squareosc(s * 55); 
f = squareosc(s * 109); 
g = squareosc(s * 111);
lowpassfilter(2200 * x);