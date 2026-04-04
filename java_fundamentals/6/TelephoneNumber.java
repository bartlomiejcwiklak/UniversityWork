import java.util.Objects;

public class TelephoneNumber implements Comparable<TelephoneNumber> {
    private int countryCode;
    private long localNumber;

    public TelephoneNumber(int countryCode, long localNumber) {
        this.countryCode = countryCode;
        this.localNumber = localNumber;
    }

    public int getCountryCode() {
        return countryCode;
    }

    public long getLocalNumber() {
        return localNumber;
    }

    @Override
    public int compareTo(TelephoneNumber other) {
        if (this.countryCode != other.countryCode) {
            return Integer.compare(this.countryCode, other.countryCode);
        }
        return Long.compare(this.localNumber, other.localNumber);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TelephoneNumber that = (TelephoneNumber) o;
        return countryCode == that.countryCode && localNumber == that.localNumber;
    }

    @Override
    public int hashCode() {
        return Objects.hash(countryCode, localNumber);
    }

    @Override
    public String toString() {
        return "+" + countryCode + " " + localNumber;
    }
}