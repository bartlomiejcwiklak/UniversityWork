public record Category(String name) implements Comparable<Category> {

    @Override
    public String toString() {
        return name;
    }

    @Override
    public int compareTo(Category other) {
        return this.name.compareTo(other.name);
    }
}