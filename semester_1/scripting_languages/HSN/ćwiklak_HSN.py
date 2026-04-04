def hsn(c):
    sequence = [c]
    while c > 1:
        c = next_hsn(c)
        sequence.append(c)
    return sequence


def next_hsn(c):
    if c % 2 == 0:
        return c//2
    else:
        return 3*c+1


longestSeq = 0
longestIndex = 0
highestValue = 0
numOfOccur = 0
indexHighest = []
lenOfSeq = {}
idsOfSequences = {}
index = 0
for x in range(0, 1000):
    for y in (hsn(x)):
        if y > highestValue:
            highestValue = y
            numOfOccur = 0
            indexHighest = []
        if y == highestValue:
            numOfOccur += 1
            indexHighest.append(x)
    if len(hsn(x)) > longestSeq:
        longestSeq = len(hsn(x))
        longestIndex = x
    if str(len(hsn(x))) in lenOfSeq:
        lenOfSeq[str(len(hsn(x)))] = lenOfSeq.get(str(len(hsn(x))), 0) + 1
        idsOfSequences[str(len(hsn(x)))] = [].append(1)
    else:
        lenOfSeq[str(len(hsn(x)))] = 1
    print(hsn(x), "\n")

print("\nProblem 1 (for range 1-1000):")
print("- longest sequence contains", longestSeq, "elements")
print("- starts from seed:", longestIndex)

print("\nProblem 2 (for range 1-1000):")
print("- highest element value is", highestValue)
print("- found", numOfOccur, "times")
print("- in sequences starting from seeds: ", indexHighest)

print("\nProblem 3 (for range 1-1000):")
print("- most common sequence length is", max(lenOfSeq, key=lenOfSeq.get))
print("- found", lenOfSeq[max(lenOfSeq, key=lenOfSeq.get)], "times")
print("- in sequences starting from seeds:",)
