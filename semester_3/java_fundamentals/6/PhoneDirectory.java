import java.util.TreeMap;
import java.util.Iterator;
import java.util.Map;

public class PhoneDirectory {
    public static void main(String[] args) {
        TreeMap<TelephoneNumber, TelephoneEntry> directory = new TreeMap<>();

        Address address1 = new Address("Wolczanska 12", "Lodz", "90500");
        Address address2 = new Address("Jesienna 99", "Warszawa", "10000");
        Address address3 = new Address("Fioletowa 192", "Poznan", "53541");
        Address address4 = new Address("Paddington Street", "Londyn", "67000");

        TelephoneNumber num1 = new TelephoneNumber(1, 5550000);
        TelephoneNumber num2 = new TelephoneNumber(1, 5550001);
        TelephoneNumber num3 = new TelephoneNumber(48, 123456789);
        TelephoneNumber num4 = new TelephoneNumber(48, 987654321);

        Person person1 = new Person("Jan", "Kowalski", address1, num1);
        Person person2 = new Person("Andrzej", "Konieczny", address2, num2);

        Company company1 = new Company("Samsung", address4, num3);
        Company company2 = new Company("Google", address3, num4);

        directory.put(num1, person1);
        directory.put(num2, person2);
        directory.put(num3, company1);
        directory.put(num4, company2);

        Iterator<Map.Entry<TelephoneNumber, TelephoneEntry>> iterator = directory.entrySet().iterator();

        while (iterator.hasNext()) {
            Map.Entry<TelephoneNumber, TelephoneEntry> entry = iterator.next();
            System.out.println(entry.getValue().description());
        }
    }
}