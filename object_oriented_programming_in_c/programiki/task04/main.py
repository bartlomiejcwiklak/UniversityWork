import heapq

# exercise 1
def levenshtein_distance(s, t, subs_cost=None):
    m, n = len(s), len(t)
    dp = [[0]*(n+1) for _ in range(m+1)]
    for i in range(m+1): dp[i][0] = i
    for j in range(n+1): dp[0][j] = j

    for i in range(1, m+1):
        for j in range(1, n+1):
            if s[i-1] == t[j-1]:
                cost = 0
            else:
                cost = subs_cost.get((s[i-1], t[j-1]), 1) if subs_cost else 1
            dp[i][j] = min(
                dp[i-1][j] + 1,       # deletion
                dp[i][j-1] + 1,       # insertion
                dp[i-1][j-1] + cost   # substitution
            )
    return dp[m][n]

def hamming_distance(s, t, subs_cost=None):
    # allows only for character switches
    if len(s) != len(t):
        raise ValueError("Hamming requires equal-length strings")
    if subs_cost:
        return sum(subs_cost.get((a, b), 1) for a, b in zip(s, t) if a != b)
    else:
        return sum(a != b for a, b in zip(s, t))

def indel_distance(s, t):
    # allows only for insertions & deletions (substitutions count as del+ins).
    m, n = len(s), len(t)
    dp = [[0]*(n+1) for _ in range(m+1)]
    for i in range(m+1): dp[i][0] = i
    for j in range(n+1): dp[0][j] = j
    for i in range(1, m+1):
        for j in range(1, n+1):
            if s[i-1] == t[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                # deletion or insertion
                dp[i][j] = min(dp[i-1][j] + 1,
                               dp[i][j-1] + 1)
    return dp[m][n]

def load_dictionary(dict_file):
    buckets = {}
    with open(dict_file, 'r') as f:
        for line in f:
            w = line.strip().lower()
            if w:
                buckets.setdefault(len(w), []).append(w)
    return buckets

def suggest(word, buckets, dist_fn, **kwargs):  # kwargs = optional keyword argument
    L = len(word)
    candidates = []
    for l in range(L-1, L+2):
        candidates += buckets.get(l, [])
    best, best_d = None, float('inf')
    for w in candidates:
        d = dist_fn(word, w, **kwargs) if kwargs else dist_fn(word, w)
        if d < best_d or (d == best_d and w < best):
            best, best_d = w, d
    return best, best_d

def correct_text_file(input_file, dict_file, output_file):
    buckets = load_dictionary(dict_file)
    subs_cost = {('o','p'): 0.5, ('p','o'): 0.5, ('a','s'): 0.5, ('s','a'): 0.5, ('x','z'): 0.5, ('z','x'): 0.5}

    with open(input_file, 'r') as fin, open(output_file, 'w') as fout:
        for line in fin:
            # keep only letters & spaces, lowercase
            clean = ''.join(ch.lower() if ch.isalpha() or ch.isspace() else ' '
                            for ch in line)
            tokens = clean.split()
            fixed = []
            for w in tokens:
                if w in buckets.get(len(w), []):
                    fixed.append(w)
                else:
                    corr, d = suggest(w, buckets,
                                      dist_fn=levenshtein_distance,
                                      subs_cost=subs_cost)
                    fixed.append(corr)
            fout.write(' '.join(fixed) + '\n')

# exercise 2
def build_frequency_heap(data):
    freq = {}
    for ch in data:
        freq[ch] = freq.get(ch, 0) + 1
    counter = 0
    heap = []
    for ch, f in freq.items():
        heap.append((f, counter, {'symbol': ch}))
        counter += 1
    heapq.heapify(heap)
    return heap

def build_huffman_tree(heap):
    # start with the rarest characters
    while len(heap) > 1:
        f1, _, left = heapq.heappop(heap)
        f2, _, right = heapq.heappop(heap)
        merged = {'left': left, 'right': right}
        heapq.heappush(heap, (f1 + f2, id(merged), merged))
    return heap[0][2] if heap else None

def build_codes_dict(node, prefix='', codes=None):
    if codes is None:
        codes = {}
    if 'symbol' in node:
        codes[node['symbol']] = prefix or '0'
    else:
        build_codes_dict(node['left'], prefix + '0', codes)
        build_codes_dict(node['right'], prefix + '1', codes)
    return codes

def huffman_encode(text, codes):
    return ''.join(codes[ch] for ch in text)

def huffman_decode(bits, tree):
    out, node = [], tree
    for b in bits:
        node = node['left'] if b == '0' else node['right']
        if 'symbol' in node:
            out.append(node['symbol'])
            node = tree
    return ''.join(out)

def compression_ratio(original, encoded):
    return (len(original) * 8) / len(encoded) if encoded else float('inf')

def test_huffman():
    s = "I love data structures"
    heap = build_frequency_heap(s)
    tree = build_huffman_tree(heap)
    codes = build_codes_dict(tree)
    print("Huffman Codes:")
    for sym in sorted(codes):
        print(f"  {repr(sym)}: {codes[sym]}")
    enc = huffman_encode(s, codes)
    print(f"\nEncoded string:\n{enc}")
    ratio = compression_ratio(s, enc)
    print(f"\nCompression ratio: {ratio:.2f}")

if __name__ == '__main__':
    INPUT_FILE  = 'input.txt'
    DICT_FILE   = 'words_alpha.txt'
    OUTPUT_FILE = 'corrected.txt'
    print("Running Exercise 1: spell checking…")
    correct_text_file(INPUT_FILE, DICT_FILE, OUTPUT_FILE)
    print(f"Corrected text written to {OUTPUT_FILE}\n")
    print("Running Exercise 2: Huffman coding demo…\n")
    test_huffman()