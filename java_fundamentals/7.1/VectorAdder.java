import java.util.ArrayList;
import java.util.List;

public class VectorAdder {

    public MathVector addVectors(MathVector v1, MathVector v2) {
        
        int length1 = v1.getLength();
        int length2 = v2.getLength();

        if (length1 != length2) {
            ArrayList<Integer> lengths = new ArrayList<>();
            lengths.add(length1);
            lengths.add(length2);
            
            throw new DifferentVectorsLengthsException("Vectors lenghts mismatch", lengths);
        }

        List<Double> resultComponents = new ArrayList<>();
        
        for (int i = 0; i < length1; i++) {
            double sum = v1.getComponent(i) + v2.getComponent(i);
            resultComponents.add(sum);
        }

        return new MathVector(resultComponents);
    }
}