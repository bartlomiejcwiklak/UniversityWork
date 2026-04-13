import { Component } from '@angular/core';
import { MatCard, MatCardContent, MatCardHeader, MatCardTitle } from '@angular/material/card';

@Component({
  selector: 'app-helloworld',
  imports: [MatCard, MatCardContent, MatCardHeader, MatCardTitle],
  templateUrl: './helloworld.html',
  styleUrl: './helloworld.css',
})
export class Helloworld {}
