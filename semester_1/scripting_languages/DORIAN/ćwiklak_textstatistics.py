file = open("dorian.txt", 'r')

locc = {}  # letter occurrences: stores counts of each letter
for line in file:
    line = line.strip().lower()
    for locckey in line:  # iterating over each character, renamed from 'l'
        if locckey.isalpha():
            if locckey not in locc:
                locc[locckey] = 1
            else:
                locc[locckey] += 1
file.close()

rlocc = {}  # reversed letter occurrences: groups letters by their counts
for locckey, n in locc.items():
    if n not in rlocc:
        rlocc[n] = [locckey]
    else:
        rlocc[n].append(locckey)

sorted_rlocc = sorted(rlocc.items(), reverse=True)
print("Letters statistics:\n- 5 most common letters:")
for count, letters in sorted_rlocc[:5]:
    for letter in letters:
        print("letter/char '", letter, "' found", count, "times")

print("\n- 5 least common letters:")
for count, letters in sorted_rlocc[-5:]:
    for letter in letters:
        print("letter/char '", letter, "' found", count, "times")

file = open("dorian.txt", 'r')

wocc = {}  # word occurrences: stores counts of each unique word
wlen = {}  # word length: stores the length of each unique word

for line in file:
    words = line.strip().lower().split()
    for w in words:
        w = w.strip(".,;:-'`\"?!()")
        if w:
            if w not in wocc:
                wocc[w] = 1
                wlen[w] = len(w)
            else:
                wocc[w] += 1
file.close()

rwocc = {}  # reversed word occurrences: groups words by their counts
for word, count in wocc.items():
    if count not in rwocc:
        rwocc[count] = [word]
    else:
        rwocc[count].append(word)

rwlen = {}  # reversed word lengths: groups words by their lengths
for word, length in wlen.items():
    if length not in rwlen:
        rwlen[length] = [word]
    else:
        rwlen[length].append(word)

sorted_rwocc = sorted(rwocc.items(), reverse=True)
print("\nWords statistics:\n- 5 most common words:")
for count, words in sorted_rwocc[:5]:
    for word in words:
        print("word '", word, "' found", count, "times")

print("\n- Number of unique words:", len(wocc))

sorted_rwlen = sorted(rwlen.items(), reverse=True)
print("\n- 5 longest words:")
for length, words in sorted_rwlen[:5]:
    print("words of length", length, "are:", ", ".join(words[:5]))
