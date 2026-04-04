public abstract class TelephoneEntry {
    private Address address;
    private TelephoneNumber telephoneNumber;

    public TelephoneEntry(Address address, TelephoneNumber telephoneNumber) {
        this.address = address;
        this.telephoneNumber = telephoneNumber;
    }

    public Address getAddress() {
        return address;
    }

    public TelephoneNumber getTelephoneNumber() {
        return telephoneNumber;
    }

    public abstract String description();
}