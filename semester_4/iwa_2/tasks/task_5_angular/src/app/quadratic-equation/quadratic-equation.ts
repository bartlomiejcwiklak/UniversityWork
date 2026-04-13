import { Component, computed, signal } from '@angular/core';
import { form, FormField } from '@angular/forms/signals';
import { MatCard, MatCardContent, MatCardHeader, MatCardTitle } from '@angular/material/card';
import { MatFormField, MatLabel } from '@angular/material/form-field';
import { MatInput } from '@angular/material/input';

@Component({
  selector: 'app-quadratic-equation',
  imports: [
    FormField,
    MatCard,
    MatCardContent,
    MatCardHeader,
    MatCardTitle,
    MatFormField,
    MatInput,
    MatLabel,
  ],
  templateUrl: './quadratic-equation.html',
  styleUrl: './quadratic-equation.css',
})
export class QuadraticEquation {
  protected readonly coeffsModel = signal({ a: 1, b: 0, c: 0 });
  protected readonly coeffsForm = form(this.coeffsModel);

  protected readonly analysis = computed(() => {
    const { a, b, c } = this.coeffsModel();

    if (a === 0 && b === 0 && c === 0) {
      return {
        kind: 'identity' as const,
        summary: 'Identity 0 = 0 — infinitely many solutions (any x).',
      };
    }
    if (a === 0 && b === 0) {
      return {
        kind: 'contradiction' as const,
        summary: 'Contradiction — no solutions.',
      };
    }
    if (a === 0) {
      const x = -c / b;
      return {
        kind: 'linear' as const,
        summary: `Linear equation bx + c = 0 ⇒ x = ${formatNum(x)}`,
      };
    }

    const delta = b * b - 4 * a * c;
    if (delta < 0) {
      return {
        kind: 'none' as const,
        summary: `Δ = ${formatNum(delta)} < 0 — no real roots.`,
      };
    }
    if (delta === 0) {
      const x = -b / (2 * a);
      return {
        kind: 'one' as const,
        summary: `Δ = 0 — one double root: x = ${formatNum(x)}`,
      };
    }
    const s = Math.sqrt(delta);
    const x1 = (-b - s) / (2 * a);
    const x2 = (-b + s) / (2 * a);
    return {
      kind: 'two' as const,
      summary: `Δ = ${formatNum(delta)} — x₁ = ${formatNum(x1)}, x₂ = ${formatNum(x2)}`,
    };
  });
}

function formatNum(n: number): string {
  if (!Number.isFinite(n)) {
    return String(n);
  }
  return Number.isInteger(n) ? String(n) : n.toFixed(6).replace(/\.?0+$/, '');
}
