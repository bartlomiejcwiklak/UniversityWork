import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class ProductCatalog {
    private final Map<Category, List<Product>> productsByCategory;

    public ProductCatalog(String filePath) {
        this.productsByCategory = new TreeMap<>();
        loadProducts(filePath);
    }

    private void loadProducts(String filePath) {
        Path path = Paths.get(filePath);
        try {
            List<String> lines = Files.readAllLines(path);
            for (String line : lines) {
                if (line.trim().isEmpty()) continue;
                String[] parts = line.split(",");
                if (parts.length == 2) {
                    String categoryName = parts[0].trim();
                    Category category = new Category(categoryName);
                    String name = parts[1].trim();
                    Product product = new Product(category, name);
                    productsByCategory.computeIfAbsent(category, k -> new ArrayList<>()).add(product);
                }
            }
        } catch (IOException e) {
            System.err.println("Error: Could not read the product catalog file: " + filePath);
        }
    }

    public List<Category> getCategoryNames() {
        return new ArrayList<>(productsByCategory.keySet());
    }

    public List<Product> getProductsForCategory(Category category) {
        return Collections.unmodifiableList(productsByCategory.getOrDefault(category, new ArrayList<>()));
    }
}