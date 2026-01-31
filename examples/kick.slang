//your slang script goes here! :D
trig = stepsequencer([1], 120);
env = linenvelope(trig, 0.001, 0.15, 0.001, 0.15);
out = truesineosc(env * 120);
//outs = squareosc(env * 110);