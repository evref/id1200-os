output = open("output.txt", "r")
correct = open("correct.txt", "r")

output_text = output.read().split()
correct_text = correct.read().split()

if(len(output_text) == len(correct_text)):
    print("SUCCESS: Number of rows are the same")
else:
    print("ERROR: Number of rows are not the same")

no_correct = 0
for i in range(len(correct_text)):
    if output_text[i] == correct_text[i]:
        no_correct += 1

print(f"{100 * no_correct / len(correct_text)}% of rows were correct!")

