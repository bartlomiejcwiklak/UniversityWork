import java.util.List;

public class VectorApp {
    private final InputReader input;
    private final ResultPrinter output;
    private final VectorCalculator calculator;

    public VectorApp() {
        this.input = new InputReader();
        this.output = new ResultPrinter();
        this.calculator = new VectorCalculator();
    }

    public static void main(String[] args) {
        VectorApp app = new VectorApp();
        app.run(args);
    }

    public void run(String[] args) {
        int numberOfVectors = input.parseVectorCountArgument(args);

        if (numberOfVectors <= 0) {
            output.printArgumentError();
            return;
        }

        boolean success = false;
        while (!success) {
            output.printWelcome(numberOfVectors);
            List<Vector> vectors = input.readVectors(numberOfVectors);

            try {
                Vector result = calculator.sumVectors(vectors);
                output.printSuccess(result);
                success = true;
            } catch (DifferentVectorsLengthsException e) {
                output.printExceptionDetails(e);
            }
        }
        input.close();
    }
}