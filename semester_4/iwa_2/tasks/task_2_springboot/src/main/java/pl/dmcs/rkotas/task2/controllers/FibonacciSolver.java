package pl.dmcs.rkotas.task2.controllers;

import org.springframework.stereotype.Controller;

@Controller
public class FibonacciSolver {
    public String calculate(long n) {
        if (n <= 0) return "0";
        long a = 0, b = 1;
        for (long i = 2; i <= n; i++) {
            long temp = a + b;
            a = b;
            b = temp;
        }
        return String.valueOf(b);
    }
}