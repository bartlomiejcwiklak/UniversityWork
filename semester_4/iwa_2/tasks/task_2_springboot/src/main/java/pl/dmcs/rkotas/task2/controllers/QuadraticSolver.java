package pl.dmcs.rkotas.task2.controllers;

import org.springframework.stereotype.Controller;
import pl.dmcs.rkotas.task2.model.Mathematics;
import static java.lang.Math.sqrt;

@Controller
public class QuadraticSolver {
    public String calculate(Mathematics math) {
        double a = math.getCoeffa();
        double b = math.getCoeffb();
        double c = math.getCoeffc();

        if (a == 0) return "This is a linear function.";

        math.setDelta((b * b) - (4 * a * c));
        double delta = math.getDelta();
        math.setx1(((b * -1) - sqrt(delta)) / (2 * a));

        if (delta < 0) {
            return "There are no real roots.";
        } else if (delta == 0) {
            return "One root, x1 = " + math.getx1();
        } else {
            math.setx2(((b * -1) + sqrt(delta)) / (2 * a));
            return String.format("Two roots, x1 = %.2f, x2 = %.2f", math.getx1(), math.getx2());
        }
    }
}