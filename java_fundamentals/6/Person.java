public class Person extends TelephoneEntry {
    private String firstName;
    private String lastName;

    public Person(String firstName, String lastName, Address address, TelephoneNumber telephoneNumber) {
        super(address, telephoneNumber);
        this.firstName = firstName;
        this.lastName = lastName;
    }

    @Override
    public String description() {
        return "Person: " + firstName + " " + lastName + 
               " | Address: " + getAddress() + 
               " | Phone: " + getTelephoneNumber();
    }
}