from PIL import Image

def single_threshold(image_path, threshold, output_path):
    img = Image.open(image_path).convert('L')
    def thr1(p):
        if p < threshold:
            return 0
        else:
            return 255
    bw = img.point(thr1)
    bw.save(output_path)

def double_threshold(image_path, low, high, output_path):
    img = Image.open(image_path).convert('L')
    def thr2(p):
        if low < p < high:
            return 0
        else:
            return 255
    bw = img.point(thr2)
    bw.save(output_path)

if __name__ == "__main__":
    img_path = "yoda.jpg"
    single_threshold(img_path, 128, "yodaSingleThreshold.jpg")
    double_threshold(img_path, 100, 150, "yodaDoubleThreshold.jpg")