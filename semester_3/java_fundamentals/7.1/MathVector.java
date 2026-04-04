import java.util.List;

public class MathVector {

    private final List<Double> components;

    public MathVector(List<Double> components) {
        this.components = components;
    }

    public int getLength() {
        return components.size();
    }

    public double getComponent(int index) {
        if (index < 0 || index >= components.size()) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for vector length " + components.size());
        }
        return components.get(index);
    }
    
    @Override
    public String toString() {
        return components.toString();
    }
}