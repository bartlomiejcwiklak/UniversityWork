import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class InputReader {
    private final Scanner scanner;

    public InputReader() {
        this.scanner = new Scanner(System.in);
    }

    public int parseVectorCountArgument(String[] args) {
        if (args.length > 0) {
            try {
                return Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                return -1;
            }
        }
        return -1;
    }

    public List<Vector> readVectors(int count) {
        List<Vector> vectors = new ArrayList<>();
        for (int i = 0; i < count; i++) {
            if (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                vectors.add(Vector.fromString(line));
            }
        }
        return vectors;
    }

    public void close() {
        scanner.close();
    }
}