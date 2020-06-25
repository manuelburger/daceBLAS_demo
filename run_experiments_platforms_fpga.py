#!/usr/bin/env python3
# coding: utf-8

import subprocess
import re
import json
import os
import numpy as np
from tqdm import tqdm
from datetime import datetime
import argparse



# ---------- ---------- ----------
# PREPARE results
# ---------- ---------- ----------
def runExperiment(
        algorithm,
        implementation,
        platform,
        vendor,
        mode,
        precision,
        experimentSizes,
        repetitions,
        callstring,
        info
    ):
    experiment = {}

    experiment['algo'] = algorithm
    experiment['implementation'] = implementation
    experiment['precision'] = precision
    experiment['platform'] = platform
    experiment['vendor'] = vendor
    experiment['repetitions'] = repetitions
    experiment['n'] = experimentSizes
    experiment['callstring'] = callstring
    experiment['info'] = info

    now = datetime.now()
    experiment['date'] = now.strftime("%d/%m/%Y %H:%M:%S")

    timingsAll = []
    runtimeAll = []
    passedAll = []

    print("\n----- EXPERIMENT -----")
    print("Running", algorithm, ": ", implementation," on ", platform, " in ", mode, ", #sizes:", len(experimentSizes))

    for size in experimentSizes:

        print("Size:", size, end='\n')

        timings = []
        runtimes = []
        passed = []

        for i in tqdm(range(0, repetitions)):

            runString = "" + callstring + " " + str(size) + " "
            runString += "-p " + platform + " "
            runString += "-v " + vendor + " "
            runString += "-m " + mode + " "
            runString += "-t " + precision + " "
            runString += "-c " + " "
            runProc = subprocess.run(runString, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output = runProc.stdout.decode('utf-8')

            # kernelTimeString = re.findall('Kernel executed in \d+\.\d+ seconds.', output)[0]
            # kernelTime = float(re.findall('\d+\.\d+', kernelTimeString)[0])

            runtimeString = re.findall('Runtime: \d+\.\d+', output)[0]
            runtime = float(re.findall('\d+\.\d+', runtimeString)[0])

            # print("Kernel: ", kernelTime)
            # print("Total: ", runtime)

            kernelPassed = bool(re.findall('Passed Test:  True', output))

            if not kernelPassed:
                print("\n\t--> ATTENTION, found failed experiment at N=", size)
                print(output)

            # timings.append(kernelTime)
            runtimes.append(runtime)
            passed.append(kernelPassed)

        # print("\tMedian runtime for N=", size, " > ", np.median(timings), "seconds")    

        runtimeAll.append(runtimes)
        # timingsAll.append(timings)
        passedAll.append(passed)

    print("Finished, median runtimes:")
    for runtime, timing, size in zip(runtimeAll, timingsAll, experimentSizes):
        print("N=", "{0:>14}".format(str(size)), " > ", -1, " seconds; total >", np.median(runtime))

    print("----- DONE -----\n")

    # experiment['timings'] = timingsAll
    experiment['runtimes'] = runtimeAll
    experiment['passed'] = passedAll

    return experiment


def getNextFileName(filename):

    i = 0
    while os.path.exists(filename + "_" + str(i)):
        i += 1

    return filename + "_" + str(i)


def main(vendor):
    # ---------- ---------- ----------
    # EXPERIMENT RUNS
    # ---------- ---------- ----------
    experiments = []

    # Cannot run GPU implementation for these larger sizes
    # Comment out GPU version if running with these sizes
    Ns = [int(2**13), int(2**14), int(24576), int(2**15), int(40960)]

    # If running with GPU implementation
    # Ns = [int(2**13), int(2**14), int(24576)]

    print("\n----- RUNNING: {} -----".format(vendor))





    # SYNTHETIC BENCHMARK
    # FPGA
    # ---------- ---------- ----------
    algorithm = "synthetic1Bench"
    implementation = "fpga-stream"
    platform = "FPGA"
    mode = "hardware"
    repetitons = 10
    callstring = "./performance_synthetic1.py"
    precision = "single"
    experimentSizes = Ns
    info = "Synthetic benchmark synthetic1, FPGA"

    res = runExperiment(
        algorithm,
        implementation,
        platform,
        vendor,
        mode,
        precision,
        experimentSizes,
        repetitons,
        callstring,
        info
    )

    experiments.append(res)




    # # GPU
    # # ---------- ---------- ----------
    # algorithm = "synthetic1Bench"
    # implementation = "cublas"
    # platform = "GPU"
    # mode = "hardware"
    # repetitons = 10
    # callstring = "./performance_synthetic1_gpu.py"
    # precision = "single"
    # experimentSizes = Ns
    # info = "Synthetic benchmark synthetic1, GPU"

    # res = runExperiment(
    #     algorithm,
    #     implementation,
    #     platform,
    #     vendor,
    #     mode,
    #     precision,
    #     experimentSizes,
    #     repetitons,
    #     callstring,
    #     info
    # )

    # experiments.append(res)



    # # CPU
    # # ---------- ---------- ----------
    # algorithm = "synthetic1Bench"
    # implementation = "openblas"
    # platform = "CPU"
    # mode = "hardware"
    # repetitons = 10
    # callstring = "./performance_synthetic1_cpu.py"
    # precision = "single"
    # experimentSizes = Ns
    # info = "Synthetic benchmark synthetic1, CPU"

    # res = runExperiment(
    #     algorithm,
    #     implementation,
    #     platform,
    #     vendor,
    #     mode,
    #     precision,
    #     experimentSizes,
    #     repetitons,
    #     callstring,
    #     info
    # )

    # experiments.append(res)
















    # ---------- ---------- ----------
    # DUMP all runs to file
    # ---------- ---------- ----------
    outfile = 'largeBench_single_fpga'
    outfile = getNextFileName(outfile)
    with open(outfile + ".json", 'w') as f:
        f.write(json.dumps(experiments))


# ---------- ---------- ----------
# PROGRAM START
# ---------- ---------- ----------
if __name__ == "__main__":

    cmdParser = argparse.ArgumentParser()

    cmdParser.add_argument("-v", "--vendor", dest="vendor", default="xilinx", help="FPGA Vendor (xilinx, intel_fpga)")

    args = cmdParser.parse_args()
    vendor = args.vendor

    main(vendor)
