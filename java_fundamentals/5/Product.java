public record Product(Category category, String name){
    @Override
    public String toString(){
        return name + " (" + category.name() + ")";
    }
}