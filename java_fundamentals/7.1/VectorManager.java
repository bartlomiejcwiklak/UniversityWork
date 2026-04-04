import java.util.ArrayList;
import java.util.List;

public class VectorManager {

    public VectorManager() {
        System.out.println("Vector Addition Program (with Exception Handling)");
        System.out.println("Enter vector components one by one. Type 'calculate' to sum them.");

        VectorConsoleReader reader = new VectorConsoleReader();
        VectorAdder adder = new VectorAdder();

        while (true) {
            
            List<MathVector> vectorsToSum = new ArrayList<>();
            System.out.println("\n--- New Calculation ---");

            while (true) {
                MathVector v = reader.readVector(vectorsToSum.size() + 1);
                if (v == null) {
                    break; 
                }
                vectorsToSum.add(v);
            }

            if (vectorsToSum.size() < 2) {
                System.out.println("Addition requires at least 2 vectors. Please try again.");
                continue; 
            }

            try {
                System.out.println("\nCalculating sum of " + vectorsToSum.size() + " vectors...");
                
                MathVector totalResult = vectorsToSum.get(0);
                for (int i = 1; i < vectorsToSum.size(); i++) {
                    MathVector vNext = vectorsToSum.get(i);
                    totalResult = adder.addVectors(totalResult, vNext);
                }

                System.out.println("\nSuccess! All " + vectorsToSum.size() + " vectors had equal length.");
                System.out.println("Resulting Vector: " + totalResult);

            } catch (DifferentVectorsLengthsException e) {
                ArrayList<Integer> allLengths = new ArrayList<>();
                for (MathVector v : vectorsToSum) {
                    allLengths.add(v.getLength());
                }

                DifferentVectorsLengthsException fullInfo = new DifferentVectorsLengthsException("Some lengths mismatched", allLengths);
                
                System.out.println("\nAddition Failed!");
                System.out.println(fullInfo.getMessage());
                System.out.println("Please re-enter the vectors with equal length.\n");
            }
        }
    }

    public static void main(String[] args) {
        new VectorManager();
    }
}