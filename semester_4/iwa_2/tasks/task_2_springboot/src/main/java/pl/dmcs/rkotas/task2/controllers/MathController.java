package pl.dmcs.rkotas.task2.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import pl.dmcs.rkotas.task2.model.Mathematics;

@Controller
public class MathController {
    private final QuadraticSolver quadraticSolver;
    private final FibonacciSolver fibonacciSolver;

    public MathController(QuadraticSolver quadraticSolver, FibonacciSolver fibonacciSolver) {
        this.quadraticSolver = quadraticSolver;
        this.fibonacciSolver = fibonacciSolver;
    }

    @RequestMapping("/math")
    public String math(Model model) {
        model.addAttribute("math", new Mathematics());
        return "math";
    }

    @RequestMapping(value = "/calculatex1x2.html", method = RequestMethod.POST)
    public String calculatex1x2(@ModelAttribute("math") Mathematics mathematics, Model model) {
        String result = quadraticSolver.calculate(mathematics);
        model.addAttribute("calculationResult", result);
        return "math";
    }

    @RequestMapping(value = "/calculatefibonacci.html", method = RequestMethod.POST)
    public String calculatefibonacci(@ModelAttribute("math") Mathematics mathematics, Model model) {
        String result = fibonacciSolver.calculate(mathematics.getFibonacciN());
        model.addAttribute("calculationResult", "Fibonacci result: " + result);
        return "math";
    }
}