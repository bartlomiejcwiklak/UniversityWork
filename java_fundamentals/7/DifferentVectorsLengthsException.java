public class DifferentVectorsLengthsException extends Exception {
    private final int expectedLength;
    private final int actualLength;
    private final int vectorIndex;

    public DifferentVectorsLengthsException(int expectedLength, int actualLength, int vectorIndex) {
        this.expectedLength = expectedLength;
        this.actualLength = actualLength;
        this.vectorIndex = vectorIndex;
    }

    public int getExpectedLength() {
        return expectedLength;
    }

    public int getActualLength() {
        return actualLength;
    }

    public int getVectorIndex() {
        return vectorIndex;
    }
}