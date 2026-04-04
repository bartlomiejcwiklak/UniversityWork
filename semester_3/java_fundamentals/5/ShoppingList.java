import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class ShoppingList {
    private final List<Product> items;

    public ShoppingList() {
        this.items = new ArrayList<>();
    }

    public void addProduct(Product product) {
        items.add(product);
        System.out.println("\n\n\n  [+]   " + product.name() + " has been added to your list.");
    }

    public void removeProduct(Product product) {
        if (items.remove(product)) {
            System.out.println("\n\n\n[-]   " + product.name() + " has been removed from your list.");           
        } else {
            System.out.println("\n\n\n[!]   " + "Product not found in the list.");     
        }
    }

    public void displayProducts() {
        if (items.isEmpty()) {
            System.out.println("\n\n\n[!]   " + "Your shopping list is currently empty.");
            return ;
        }

        System.out.println("\n\n\n======== Your shopping list ========");
        Map<Category, List<Product>> groupedItems = this.getItemsByCategory();

        groupedItems.forEach((category, products) -> {
            System.out.println("# " + category + ":");
            products.forEach(product -> System.out.println("   - " + product.name()));
        });
        System.out.println("====================================");
    }

    public void saveToFile(String filePath) {
        if (items.isEmpty()) {
            System.out.println("\n\n\n[!]   " + "Your shopping list is currently empty.");
            return ;
        }

        Path path = Paths.get(filePath);
        List<String> lines = new ArrayList<>();
        lines.add("======== My shopping list ========");
        
        Map<Category, List<Product>> groupedItems = this.getItemsByCategory();
        
        groupedItems.forEach((category, products) -> {
            lines.add("\n# " + category + ":");
            products.forEach(product -> lines.add("   - " + product.name()));
        });

        try {
            Files.write(path, lines);
            System.out.println("Shopping list successfully saved to " + filePath + ".");
        } catch (IOException e) {
            System.err.println("Could not save the shopping list to file: " + e.getMessage());
        }

    }
    
    public Map<Category, List<Product>> getItemsByCategory() {
        return items.stream()
                .collect(Collectors.groupingBy(Product::category, TreeMap::new, Collectors.toList()));
    }
}