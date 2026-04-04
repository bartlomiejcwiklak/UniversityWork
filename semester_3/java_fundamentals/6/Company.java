public class Company extends TelephoneEntry {
    private String companyName;

    public Company(String companyName, Address address, TelephoneNumber telephoneNumber) {
        super(address, telephoneNumber);
        this.companyName = companyName;
    }

    @Override
    public String description() {
        return "Company: " + companyName + 
               " | Address: " + getAddress() + 
               " | Phone: " + getTelephoneNumber();
    }
}