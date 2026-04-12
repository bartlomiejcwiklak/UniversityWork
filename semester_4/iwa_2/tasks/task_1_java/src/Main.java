import java.util.Scanner;
import java.util.regex.Pattern;
import static java.lang.Math.sqrt;

public class Main {
    static boolean isNumber(String Number){
        Pattern pattern = Pattern.compile("-?\\d+(\\.\\d+)?");
        if (Number == null) return false;
        else return pattern.matcher(Number).matches();
    }

    static boolean isInteger(String number) {
        Pattern pattern = Pattern.compile("-?\\d+");
        if (number == null) return false;
        else return pattern.matcher(number).matches();
    }

    static void quadratic(double a, double b, double c) {
        double delta = (b * b) - (4 * a * c);
        double x1 = ((b * -1) - sqrt(delta)) / (2 * a);
        if (delta < 0) {
            System.out.println("There are no real roots.");
        } else if (delta == 0) {
            System.out.println("One root, x1 = " + x1);
        } else {
            double x2 = ((b * -1) + sqrt(delta)) / (2 * a);
            System.out.printf("Two roots, x1 = %f, x2 = %f%n", x1, x2);
        }
    }

    static long fibonacci(long n) {
        if (n <= 0) return 0;
        long a = 0, b = 1;
        for (long i = 2; i <= n; i++) {
            long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

    public static void main(String[] args) {
        System.out.println("Choose the action you would like to perform: ");
        System.out.println("1. Calculate quadratic formula");
        System.out.println("2. Calculate n-th Fibonacci sequence element");

        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

        if (isInteger(input)) {
            int choice = Integer.parseInt(input);
            switch (choice){
                case 1:
                    System.out.println("Please provide the a, b and c values for the quadratic formula: ");
                    String[] vars = new String[3];
                    for (int i = 0; i < vars.length; i++) vars[i] = scanner.nextLine();
                    if (isNumber(vars[0]) && isNumber(vars[1]) && isNumber(vars[2])){
                        double[] coeff = new double[3];
                        for (int i = 0; i < coeff.length; i++) coeff[i] = Double.parseDouble(vars[i]);
                        if (coeff[0] == 0) {
                            System.out.println("This is not a quadratic equation.");
                        } else {
                            quadratic(coeff[0], coeff[1], coeff[2]);
                        }
                    } else {
                        System.out.println("Invalid input for the coefficients.");
                    }
                    break;
                case 2:
                    System.out.println("Please provide which element of the Fibonacci sequence to print (one by one): ");
                    String n = scanner.nextLine();
                    if (isInteger(n)) {
                        System.out.println("The element is equal to: " + fibonacci(Long.parseLong(n)));
                    } else {
                        System.out.println("Invalid input for the index. Please enter a whole number.");
                    }
                    break;
                default:
                    System.out.println("Invalid input choice.");
                    break;
            }
        } else {
            System.out.println("Invalid input choice.");
        }
    }
}