import java.util.ArrayList;

public class DifferentVectorsLengthsException extends Exception {

	private final ArrayList<Integer> length;

    public DifferentVectorsLengthsException(String message, ArrayList<Integer> length) {
        super(message);
        this.length = length;
    }
	
	public ArrayList getLengths(){
		return length;
	}
}