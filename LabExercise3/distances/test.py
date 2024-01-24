from subprocess import PIPE, Popen

for n in range(1,10):
    inputFile = "/home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/test/distances/input/input"+str(n)+".txt"
    outputFile = "/home/piyi/Documents/NTUA/ALGORITHMS/LabExercise3/test/distances/output/output"+str(n)+".txt"
    f = open(outputFile)
    output = f.read()
    command = "./a.out < " + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output == producedOutput.decode("utf-8"):
        print("+++ Testcase {} passed!".format(n))
    else:
        print("--- Testcase {} failed!\nExpected Output:\n{}\nProduced Output:\n{}\n"
        .format(n,output,producedOutput.decode("utf-8")
        ))
