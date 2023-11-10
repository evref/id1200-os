output = open("output.txt", "r")
correct = open("correct.txt", "r")

if(output.read() == correct.read()):
    print("Output is correct")
else:
    print("Output does not match")
