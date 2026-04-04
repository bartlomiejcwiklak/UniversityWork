import java.util.ArrayList;
import java.util.List;

class VectorComponentParser {
    private static final String DELIMITER = ",";

    public static List<Double> parse(String rawInput) {
        List<Double> components = new ArrayList<>();

        if (rawInput == null || rawInput.trim().isEmpty()) {
            return components;
        }

        String[] parts = rawInput.split(DELIMITER);

        for (String part : parts) {
            String trimmedPart = part.trim();
            if (trimmedPart.isEmpty()) {
                continue;
            }
            
            try {
                double value = Double.parseDouble(trimmedPart);
                components.add(value);
            } catch (NumberFormatException e) {
            }
        }

        return components;
    }
}