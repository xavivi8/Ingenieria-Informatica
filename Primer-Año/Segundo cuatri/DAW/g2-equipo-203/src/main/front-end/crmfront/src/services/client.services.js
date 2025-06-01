export class ClientDAOfetch {

    constructor(apiurl) {
        this.srvUrl = apiurl;
        this.respuestaValida = false;
    }

    readAll() {
        return fetch(this.srvUrl)
            .then(response => this.comprobarRespuesta(response))
            .then(response => this.devolverRespuesta(response));
    }

    comprobarRespuesta(response) {
        this.respuestaValida = response.ok;
        return response.json();
    }

    devolverRespuesta(json) {
        if (!this.respuestaValida) {
            return Promise.reject(json);
        }
        return json;
    }
}
