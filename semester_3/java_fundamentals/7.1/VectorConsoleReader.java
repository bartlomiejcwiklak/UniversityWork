import java.util.List;
import java.util.Scanner;

public class VectorConsoleReader {

    private final Scanner scanner;
    private static final String CALCULATE_KEYWORD = "calculate";

    public VectorConsoleReader() {
        this.scanner = new Scanner(System.in);
    }

    public MathVector readVector(int index) {
        
        while (true) {
            System.out.println("-----------------------------------------------------");
            System.out.print("Enter components for vector #" + index + " (or '" + CALCULATE_KEYWORD + "' to sum): ");
            
            String rawInput = this.scanner.nextLine().trim();

            if (rawInput.equalsIgnoreCase(CALCULATE_KEYWORD)) {
                return null;
            }

            List<Double> cleanComponents = VectorComponentParser.parse(rawInput);

            if (cleanComponents.isEmpty()) {
                System.out.println("-> Invalid input. Please enter numeric components (e.g., 1, 2, 3)");
                continue; 
            }
            
            System.out.println("-> Successfully parsed " + cleanComponents.size() + " valid component(s).");
            return new MathVector(cleanComponents);
        }
    }
}