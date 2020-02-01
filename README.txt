----------------------------- Description -----------------------------
Naive implementation of a correlation power analysis side channel attack on AES-128 in C language.
Files in file/ are available to test the program, they can be replaced by your own.
A chipWhisperer has been used to capture traces. 
Trace values are stored in traces.raw and the corresponding input text in input.raw.
Remember to update my.h NB_SAMPLES and NB_TRACES accordingly to the values you chose to capture your traces

----------------------------- Usage -----------------------------
Compile with -lm flag
Use example files or try with your own.

#-------------- Python script to create your own traces ------------
# Capture Trace
import numpy as np
import os
import time

ktp = cw.ktp.Basic()
key, text = ktp.next()
traces = []

#values for our chipWhisperer, can vary a little between chips
scope.adc.samples = 980
scope.adc.offset = 1476
nb_trace = 2000

# Write trace to file
traces_dir = 'traces'
f = open(os.path.join(traces_dir, 'traces.raw'), "w")
f2 = open(os.path.join(traces_dir, 'input.raw'), "w")

for n_trace in range(0,nb_trace) :
    key, text = ktp.next()
    trace = cw.capture_trace(scope, target, text, key)
    traces.append(trace)

    trace_array = np.asarray([trace.wave for trace in traces])
    data = []
    data = trace_array.astype('float64')
    f.write("\n".join(str(e) for e in data[n_trace]))

    textin = list(trace.textin)
    for char in textin:
        f2.write(str(char) + "\n")

    n_trace+=1
    f.write("\n")

f.close()
f2.close()
#------------------------------------------------
