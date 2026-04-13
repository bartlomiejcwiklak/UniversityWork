import { Component, computed, signal } from '@angular/core';
import { form, FormField } from '@angular/forms/signals';
import { MatCard, MatCardContent, MatCardHeader, MatCardTitle } from '@angular/material/card';
import { MatFormField, MatLabel } from '@angular/material/form-field';
import { MatInput } from '@angular/material/input';

const MAX_N = 50;

@Component({
  selector: 'app-fibonacci',
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
  templateUrl: './fibonacci.html',
  styleUrl: './fibonacci.css',
})
export class Fibonacci {
  protected readonly maxN = MAX_N;

  protected readonly settings = signal({ n: 10 });
  protected readonly settingsForm = form(this.settings);

  protected readonly sequence = computed(() => {
    const raw = Math.round(this.settings().n);
    const n = Math.min(MAX_N, Math.max(1, Number.isFinite(raw) ? raw : 1));
    const out: number[] = [];
    let a = 0;
    let b = 1;
    for (let i = 0; i < n; i++) {
      if (i === 0) {
        out.push(a);
      } else {
        out.push(b);
        const next = a + b;
        a = b;
        b = next;
      }
    }
    return { terms: out, usedN: n, capped: n !== raw };
  });
}
