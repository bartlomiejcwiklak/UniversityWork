import { Component, computed, signal } from '@angular/core';
import { form, FormField } from '@angular/forms/signals';
import { MatButton } from '@angular/material/button';
import { MatCard, MatCardContent, MatCardHeader, MatCardTitle } from '@angular/material/card';
import { MatDivider } from '@angular/material/divider';
import { MatFormField, MatLabel } from '@angular/material/form-field';
import { MatInput } from '@angular/material/input';
import { MatOption } from '@angular/material/core';
import { MatSelect, MatSelectChange } from '@angular/material/select';

export type CalculatorOperation = 'add' | 'subtract' | 'multiply' | 'divide';

@Component({
  selector: 'app-calculator',
  imports: [
    FormField,
    MatButton,
    MatCard,
    MatCardContent,
    MatCardHeader,
    MatCardTitle,
    MatDivider,
    MatFormField,
    MatInput,
    MatLabel,
    MatOption,
    MatSelect,
  ],
  templateUrl: './calculator.html',
  styleUrl: './calculator.css',
})
export class Calculator {
  protected readonly operandsModel = signal({ a: 0, b: 0 });
  protected readonly operandsForm = form(this.operandsModel);

  protected readonly operation = signal<CalculatorOperation>('add');

  protected readonly operations: { value: CalculatorOperation; label: string }[] = [
    { value: 'add', label: 'Addition (+)' },
    { value: 'subtract', label: 'Subtraction (−)' },
    { value: 'multiply', label: 'Multiplication (×)' },
    { value: 'divide', label: 'Division (/)' },
  ];

  protected readonly result = computed(() => {
    const { a, b } = this.operandsModel();
    const op = this.operation();
    switch (op) {
      case 'add':
        return { ok: true as const, value: a + b };
      case 'subtract':
        return { ok: true as const, value: a - b };
      case 'multiply':
        return { ok: true as const, value: a * b };
      case 'divide':
        if (b === 0) {
          return { ok: false as const, error: 'Division by zero' };
        }
        return { ok: true as const, value: a / b };
    }
  });

  protected rxResult?: number;

  protected rxAddition(c: number, d: number): void {
    this.rxResult = c + d;
    console.log('Template method: addition result =', this.rxResult);
  }

  protected onOperationChange(event: MatSelectChange): void {
    this.operation.set(event.value as CalculatorOperation);
  }
}
