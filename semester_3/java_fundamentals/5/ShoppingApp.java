import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class ShoppingApp {
    private final String CATALOG_FILE = "products.csv";
    private final String OUTPUT_FILE = "mylist.txt";

    private final Scanner scanner;
    private final ProductCatalog catalog;
    private final ShoppingList shoppingList;

    public ShoppingApp() {
        this.scanner = new Scanner(System.in);
        this.catalog = new ProductCatalog(CATALOG_FILE);
        this.shoppingList = new ShoppingList();
    }
    
    public void run() {
        while (true) {
            displayMenu();
            int choice = getUserChoice(0,4);

            switch (choice) {
                case 1:
                    handleAddingProducts();
                    break;
                case 2:
                    shoppingList.displayProducts();
                    break;
                case 3:
                    handleRemovingProducts();
                    break;
                case 4:
                    shoppingList.saveToFile(OUTPUT_FILE);
                    break;
                case 0:
                    System.out.println("Closing...");
                    return ;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void displayMenu() {
        System.out.println("\n\n\n====================================");
        System.out.println("        SHOPPING LIST MANAGER       ");
        System.out.println("====================================");
        System.out.println("1. Add product to list");
        System.out.println("2. Display list");
        System.out.println("3. Remove product from list");
        System.out.println("4. Save shopping list to file");
        System.out.println("0. Exit");
        System.out.println("====================================");
        System.out.print("Enter your choice: ");
    }

    private void handleAddingProducts() {
        System.out.println("\n===   Select a category:");
        List<Category> categories = catalog.getCategoryNames();
        if (categories.isEmpty()) {
            System.out.println("\n\n\nNo product categories available. Check the catalog file.");
            return ;
        }
        displayOptions(categories);
        int categoryIndex = getUserChoice(1, categories.size());
        Category selectedCategory = categories.get(categoryIndex - 1);

        System.out.println("\n===   Select a product from " + selectedCategory + ":"); 
        
        List<Product> products = catalog.getProductsForCategory(selectedCategory);
        displayOptions(products);
        int productIndex = getUserChoice(1, products.size());
        Product selectedProduct = products.get(productIndex - 1);

        shoppingList.addProduct(selectedProduct);
    }

    private void handleRemovingProducts() {
        System.out.println("\n===   Select a category:");
        List<Category> categories = catalog.getCategoryNames();
        if (categories.isEmpty()) {
            System.out.println("\n\n\nNo product categories available. Check the catalog file.");
            return ;
        }
        displayOptions(categories);
        int categoryIndex = getUserChoice(1, categories.size());
        Category selectedCategory = categories.get(categoryIndex - 1);

        System.out.println("\n===   Select a product from " + selectedCategory + ":");
        
        List<Product> products = catalog.getProductsForCategory(selectedCategory);
        displayOptions(products);
        int productIndex = getUserChoice(1, products.size());
        Product selectedProduct = products.get(productIndex - 1);

        shoppingList.removeProduct(selectedProduct);
    }

    private void displayOptions(List<?> options) {
        for (int i = 0; i < options.size(); i++) {
            Object item = options.get(i);
            String displayName = (item instanceof Product) ? ((Product) item).name() : item.toString();
            System.out.printf("%d. %s%n", i + 1, displayName);
        }
    }

    private int getUserChoice(int min, int max) {
        int choice = -1;
        while (true) {
            try {
                choice = scanner.nextInt();
                if (choice >= min && choice <= max) {
                    break;
                } else {
                    System.out.printf("\n\n\nInvalid input. Please enter a number between %d and %d: ", min, max);
                }
            } catch (InputMismatchException e) {
                System.out.printf("\n\n\nInvalid input. Please enter a whole number between %d and %d: ", min, max);
                scanner.next();
            }
        }
        return choice;
    }

    public static void main(String[] args) {
        ShoppingApp app = new ShoppingApp();
        app.run();
    }
}