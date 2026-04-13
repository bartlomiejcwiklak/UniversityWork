import { Component, signal } from '@angular/core';
import { RouterLink, RouterLinkActive, RouterOutlet } from '@angular/router';
import { MatButton } from '@angular/material/button';
import { MatIcon } from '@angular/material/icon';
import { MatToolbar } from '@angular/material/toolbar';

@Component({
  selector: 'app-root',
  imports: [RouterOutlet, RouterLink, RouterLinkActive, MatToolbar, MatButton, MatIcon],
  templateUrl: './app.html',
  styleUrl: './app.css',
})
export class App {
  protected readonly title = signal('task5_Angular');

  protected readonly navLinks = [
    { path: '/hello', label: 'Main', icon: 'waving_hand' },
    { path: '/calculator', label: 'Calculator', icon: 'calculate' },
    { path: '/quadratic', label: 'Quadratic', icon: 'functions' },
    { path: '/fibonacci', label: 'Fibonacci', icon: 'timeline' },
  ] as const;
}
