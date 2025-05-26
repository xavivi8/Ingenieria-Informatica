import { BASE_URL } from "@/environments/environments.js";

export class PayslipDAOfetch {
  constructor(apiurl = BASE_URL) {
    this.srvUrl = apiurl;
    this.respuestaValida = false;
  }

  // Obtener todas las nóminas
  readAll() {
    return fetch(`${this.srvUrl}/payslip`)
      .then(response => this.comprobarRespuesta(response))
      .then(response => this.devolverRespuesta(response));
  }

  // Obtener una nómina por ID
  readById(id = 0) {
    return fetch(`${this.srvUrl}/payslip/${id}`)
      .then(response => this.comprobarRespuesta(response))
      .then(response => this.devolverRespuesta(response));
  }

  // Crear una nómina
  create(payslip) {
    return fetch(`${this.srvUrl}`, {
      method: "POST",
      body: JSON.stringify(payslip),
      headers: {
        "Content-Type": "application/json",
        Accept: "application/json",
      },
    })
      .then(response => this.comprobarRespuesta(response))
      .then(response => this.devolverRespuesta(response));
  }

  // Actualizar una nómina
  save(payslip) {
    return fetch(`${this.srvUrl}/payslip/${payslip.id}`, {
      method: "PUT",
      body: JSON.stringify(payslip),
      headers: {
        "Content-Type": "application/json",
        Accept: "application/json",
      },
    })
      .then(response => this.comprobarRespuesta(response))
      .then(response => this.devolverRespuesta(response));
  }

  // Eliminar una nómina
  delete(id = 0) {
    return fetch(`${this.srvUrl}/payslip/${id}`, {
      method: "DELETE",
    })
      .then(response => this.comprobarRespuesta(response))
      .then(response => this.devolverRespuesta(response));
  }

  // Comprueba si la respuesta es válida
  comprobarRespuesta(response) {
    this.respuestaValida = response.ok;
    return response.json();
  }

  // Maneja la respuesta (éxito o error)
  devolverRespuesta(json) {
    if (!this.respuestaValida) {
      return Promise.reject(json);
    }
    return json;
  }
}