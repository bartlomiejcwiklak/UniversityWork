import java.util.List;

public class VectorCalculator {

    public Vector sumVectors(List<Vector> vectors) throws DifferentVectorsLengthsException {
        if (vectors == null || vectors.isEmpty()) {
            return new Vector(new java.util.ArrayList<>());
        }

        Vector sum = vectors.get(0);
        int expectedLength = sum.getDimension();

        for (int i = 1; i < vectors.size(); i++) {
            Vector current = vectors.get(i);
            if (current.getDimension() != expectedLength) {
                throw new DifferentVectorsLengthsException(expectedLength, current.getDimension(), i);
            }
            sum = sum.add(current);
        }

        return sum;
    }
}