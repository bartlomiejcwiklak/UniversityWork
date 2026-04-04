import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Vector {
    private final List<Double> elements;

    public Vector(List<Double> elements) {
        this.elements = new ArrayList<>(elements);
    }

    public static Vector fromString(String input) {
        List<Double> parsedElements = new ArrayList<>();
        Scanner scanner = new Scanner(input);
        scanner.useDelimiter(",");

        while (scanner.hasNext()) {
            String token = scanner.next();
            try {
                parsedElements.add(Double.parseDouble(token));
            } catch (NumberFormatException ignored) {
            }
        }
        scanner.close();
        return new Vector(parsedElements);
    }

    public int getDimension() {
        return elements.size();
    }

    public List<Double> getElements() {
        return elements;
    }

    public Vector add(Vector other) {
        List<Double> result = new ArrayList<>();
        for (int i = 0; i < elements.size(); i++) {
            result.add(this.elements.get(i) + other.getElements().get(i));
        }
        return new Vector(result);
    }

    @Override
    public String toString() {
        return elements.toString();
    }
}