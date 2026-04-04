from PIL import Image

def read_image_rgb(path):
    img = Image.open(path).convert('RGB')
    width, height = img.size
    pixels = list(img.getdata())
    rgb_pixels = []
    for i in range(height):
        start = i * width
        end = start + width
        row = pixels[start:end]
        rgb_pixels.append(row)
    return rgb_pixels

if __name__ == "__main__":
    img_path = "yoda.jpg"
    rgb_data = read_image_rgb(img_path)
    print(rgb_data)
    print(f"Read image '{img_path}' with dimensions: {len(rgb_data[0])}x {len(rgb_data)}")