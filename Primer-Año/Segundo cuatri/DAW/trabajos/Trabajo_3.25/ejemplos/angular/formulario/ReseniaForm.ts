import { Component, Input, Output, EventEmitter, OnChanges, SimpleChanges } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { finalize } from 'rxjs/operators';
import { AuthService } from '../services/auth.service';
import { Resenia } from '../models/resenia.model';

@Component({
  selector: 'app-resenia-form',
  templateUrl: './resenia-form.component.html',
  styles: [`
    .resenia-form {
      max-width: 500px;
      margin: 1rem auto;
    }
  `]
})
export class ReseniaFormComponent implements OnChanges {
  @Input() pista!: { id: number; nombre: string };
  @Output() created = new EventEmitter<Resenia>();

  form: FormGroup;
  loading = false;
  submitError: string | null = null;

  constructor(
    private fb: FormBuilder,
    private http: HttpClient,
    private authService: AuthService,
    private router: Router
  ) {
    this.form = this.fb.group({
      puntuacion: [1, [Validators.required, Validators.min(1), Validators.max(5)]],
      comentario: ['', [Validators.required, Validators.maxLength(200)]]
    });
  }

  ngOnChanges(changes: SimpleChanges): void {
    if (changes.pista && !changes.pista.firstChange) {
      this.form.reset({ puntuacion: 1, comentario: '' });
      this.submitError = null;
    }
  }

  handleSubmit(): void {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      return;
    }

    this.submitError = null;
    this.loading = true;

    const payload = {
      pistaId: this.pista.id,
      puntuacion: this.form.value.puntuacion,
      comentario: this.form.value.comentario
    };

    this.http.post<Resenia>('/resenias', payload)
      .pipe(finalize(() => this.loading = false))
      .subscribe({
        next: (res) => {
          this.created.emit(res);
          const tipo = this.authService.user?.tipo;
          const destino = tipo === 'ADMINISTRADOR' ? 'ReseniaAdmin' : 'ReseniaCliente';
          this.router.navigateByUrl(`/${destino}`);
          this.form.reset({ puntuacion: 1, comentario: '' });
        },
        error: (err) => {
          console.error('Error creando reseña:', err);
          if (err.error?.message) {
            this.submitError = err.error.message;
          } else {
            this.submitError = 'Error al crear reseña: ' + (err.message || 'desconocido');
          }
        }
      });
  }
}