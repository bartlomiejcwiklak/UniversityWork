public class ResultPrinter {

    public void printWelcome(int count) {
        System.out.println("Enter " + count + " vectors:");
    }

    public void printSuccess(Vector result) {
        System.out.println("Result of addition: " + result);
    }

    public void printArgumentError() {
        System.out.println("Please provide a valid integer for the number of vectors as an argument.");
    }

    public void printExceptionDetails(DifferentVectorsLengthsException e) {
        System.out.println("Error: Vectors have different lengths.");
        String ordinal = getOrdinal(e.getVectorIndex() + 1);
        System.out.println("The " + ordinal + " vector length is " + e.getActualLength() + ".");
        String comparison = (e.getActualLength() < e.getExpectedLength()) ? "lower" : "bigger";
        System.out.println("The " + ordinal + " vector length is " + comparison + " than the 1st vector length.");
        System.out.println("Please re-enter the vectors.");
    }

    private String getOrdinal(int i) {
        String[] suffixes = new String[] { "th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th" };
        switch (i % 100) {
        case 11:
        case 12:
        case 13:
            return i + "th";
        default:
            return i + suffixes[i % 10];
        }
    }
}