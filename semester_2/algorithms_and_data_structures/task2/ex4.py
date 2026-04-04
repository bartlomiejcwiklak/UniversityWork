from PIL import Image
import numpy as np
import time

def naive_mean_filter(arr, k):
    pad = k // 2
    padded = np.pad(arr, pad, mode='constant', constant_values=0)
    h, w = arr.shape
    out = np.zeros_like(arr, dtype=np.uint8)

    for i in range(h):
        for j in range(w):
            window = padded[i : i + k, j : j + k]
            m = window.mean()
            out[i, j] = int(m)
    return out

def sat_mean_filter(arr, k):
    h, w = arr.shape
    pad = k // 2

    sat = np.zeros((h + 1, w + 1), dtype=np.uint32)
    sat[1:, 1:] = arr.cumsum(axis=0).cumsum(axis=1)

    out = np.zeros_like(arr, dtype=np.uint8)

    for i in range(h):
        for j in range(w):
            y1 = max(i - pad, 0)
            x1 = max(j - pad, 0)
            y2 = min(i + pad, h - 1)
            x2 = min(j + pad, w - 1) # clamp the pixels near the edges

            Y1, X1 = y1, x1
            Y2, X2 = y2 + 1, x2 + 1 # correction for the padding in line 23

            total = sat[Y2, X2] - sat[Y1, X2] - sat[Y2, X1] + sat[Y1, X1] # formula for the summed-area table
            area = (y2 - y1 + 1) * (x2 - x1 + 1) # number of pixels in the window
            out[i, j] = total // area

    return out

if __name__ == "__main__":
    INPUT_FILE  = "road.jpg"
    KERNEL_SIZE = 71

    img = Image.open(INPUT_FILE).convert('L')
    arr = np.array(img)

    t0 = time.time()
    naive_out = naive_mean_filter(arr, KERNEL_SIZE)
    t1 = time.time()

    sat_out = sat_mean_filter(arr, KERNEL_SIZE)
    t2 = time.time()

    print(f"Naive filter time: {t1 - t0:.2f} s")
    print(f"Summed-area table filter time: {t2 - t1:.2f} s")

    Image.fromarray(naive_out).save("road_naive.jpg")
    Image.fromarray(sat_out).save("road_sat.jpg")