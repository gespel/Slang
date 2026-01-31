//your slang script goes here! :D
trig = stepsequencer([0, 1], 240);
env = linenvelope(trig, 0.001, 0.15, 0.001, 0.15);
//out = truesineosc(env * 110);
outs = squareosc(env * 110);