from PIL import Image
import numpy as np

def equalize_histogram(image_path, output_path):
    img = Image.open(image_path).convert('L')
    arr = np.array(img)

    hist, bins = np.histogram(arr.flatten(), 256, [0,256]) # bins will not be used

    cdf = hist.cumsum() # for each pixel value, how many pixels have intensity up to that value
    cdf_masked = np.ma.masked_equal(cdf, 0) # skip the zero values

    cdf_masked = (cdf_masked - cdf_masked.min()) * 255 / (cdf_masked.max() - cdf_masked.min()) # normalize
    cdf = np.ma.filled(cdf_masked, 0).astype('uint8') # set any masked values to 0, avoiding division by zero

    equalized = cdf[arr] # map the original pixel values to the new values
    out_img = Image.fromarray(equalized)
    out_img.save(output_path)

if __name__ == "__main__":
    equalize_histogram("yoda.jpg", "yodaEqualized.jpg")