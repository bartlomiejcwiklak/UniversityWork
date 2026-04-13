import { Routes } from '@angular/router';

import { Calculator } from './calculator/calculator';
import { Fibonacci } from './fibonacci/fibonacci';
import { Helloworld } from './helloworld/helloworld';
import { QuadraticEquation } from './quadratic-equation/quadratic-equation';

export const routes: Routes = [
  { path: '', pathMatch: 'full', redirectTo: 'hello' },
  { path: 'hello', component: Helloworld },
  { path: 'calculator', component: Calculator },
  { path: 'quadratic', component: QuadraticEquation },
  { path: 'fibonacci', component: Fibonacci },
  { path: '**', redirectTo: 'hello' },
];
