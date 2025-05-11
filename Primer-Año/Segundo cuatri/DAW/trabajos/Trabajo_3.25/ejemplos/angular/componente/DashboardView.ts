import { Component, OnInit, Type } from '@angular/core';
import { Router } from '@angular/router';

import { ReservaPistaComponent } from './reserva-pista/reserva-pista.component';
import { ReseniasComponent }   from './resenias/resenias.component';
import { AdminComponent }      from './admin/admin.component';
import { AdminPistasComponent }from './admin-pistas/admin-pistas.component';
import { AdminUsersComponent } from './admin-users/admin-users.component';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']  
})
export class AppComponent implements OnInit {
  userRole: 'DEPORTISTA' | 'ADMINISTRADOR' = 'DEPORTISTA';
  currentComponentName = 'ReservaPista';
  currentComponentInstance!: Type<any>;

  // Mapa de nombres a clases de componente
  private componentsMap: Record<string, Type<any>> = {
    ReservaPista:   ReservaPistaComponent,
    Resenias:       ReseniasComponent,
    Admin:          AdminComponent,
    AdminPistas:    AdminPistasComponent,
    AdminUsers:     AdminUsersComponent
  };

  constructor(private router: Router) {}

  ngOnInit(): void {
    const userStr = localStorage.getItem('user');
    if (userStr) {
      const user = JSON.parse(userStr);
      this.userRole = user.tipo;
    }
    this.loadCurrentComponent();
  }

  private loadCurrentComponent() {
    this.currentComponentInstance =
      this.componentsMap[this.currentComponentName] ||
      ReservaPistaComponent;
  }

  changeComponent(componentName: string) {
    this.currentComponentName = componentName;
    this.loadCurrentComponent();
  }

  handleLogout() {
    localStorage.removeItem('token');
    localStorage.removeItem('user');
    this.router.navigate(['/login']);
  }
}
