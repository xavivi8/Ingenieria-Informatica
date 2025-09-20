import { BASE_URL } from "@/environments/environments.js";

export class ProductDAOfetch {

    constructor(apiurl = BASE_URL) {
        this.srvUrl = apiurl;
        this.respuestaValida = false;
    }

    // Método para obtener todos los productos
    readAll() {
        return fetch(`${this.srvUrl}/product`)
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    // Método para obtener un producto por su ID
    readById(id = 0) {
        return fetch(`${this.srvUrl}/product/${id}`)
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    // Método para crear un producto
    create(product) {
        return fetch(`${this.srvUrl}/product`, {
            method: 'POST',
            body: JSON.stringify(product),
            headers: {
                'Content-type': 'application/json',
                'accept': 'application/json'
            }
        })
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    // Método para actualizar un producto
    save(product) {
        return fetch(`${this.srvUrl}/product/${product.id}`, {
            method: 'PUT',
            body: JSON.stringify(product),
            headers: {
                'Content-type': 'application/json',
                'accept': 'application/json'
            }
        })
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    // Método para eliminar un producto
    delete(id = 0) {
        return fetch(`${this.srvUrl}/product/${id}`, {
            method: 'DELETE'
        })
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    // Método que comprueba si la respuesta es válida
    comprobarRespuesta(response) {
        this.respuestaValida = response.ok;
        return response.json();
    }

    // Método que maneja la respuesta
    devolverRespuesta(json) {
        if (!this.respuestaValida) {
            return Promise.reject(json);
        }
        return json;
    }
}