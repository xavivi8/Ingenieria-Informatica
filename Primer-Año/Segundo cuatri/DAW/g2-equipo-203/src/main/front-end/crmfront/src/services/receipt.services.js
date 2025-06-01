export class ReceiptDAOfetch {

    constructor(apiurl) {
        this.srvUrl = apiurl;
        this.respuestaValida=false;
    }
    readAll() {
        return fetch(this.srvUrl)
            .then (response => this.comprobarRespuesta(response) )
            .then (response => this.devolverRespuesta(response) );
    }
    readById(id = 0) {
        return fetch(this.srvUrl + "/" + id)
            .then (response => this.comprobarRespuesta(response) )
            .then (response => this.devolverRespuesta(response) );
    }
    create(receipt) {

        return fetch(this.srvUrl, {
            method: 'POST',
            body: JSON.stringify(receipt),
            headers: {
                'Content-type': 'application/json',
                'accept': 'application/json'
            }
        })
            .then (response => this.comprobarRespuesta(response) )
            .then (response => this.devolverRespuesta(response) );
    }
    save(receipt) {
        return fetch(`${this.srvUrl}/${receipt.id}`, {
            method: 'PUT',
            body: JSON.stringify(receipt),
            headers: {
                'Content-type': 'application/json',
                'accept': 'application/json'
            }
        })
            .then (response => this.comprobarRespuesta(response) )
            .then (response => this.devolverRespuesta(response) );
    }
    delete(id = 0) {
        return fetch(this.srvUrl + "/" + id,{
            method: 'DELETE'
        })
            .then (response => this.comprobarRespuesta(response) )
            .then (response => this.devolverRespuesta(response) );
    }

    /** Saves response status and returns object data*/
    comprobarRespuesta(response) {
        this.respuestaValida=response.ok;
        //TODO check network errors
        return response.json();
    }
    devolverRespuesta (json) {
        //Resolves or reject promise with response data
        if (!this.respuestaValida) {
            //send validation errors
            //Rejects promise, forces catch response in DAO
            return Promise.reject(json);
        }
        return json;
    }
} //End ReceiptDAOfetch

/** DAO implementation using in-memory sample data*/
export class ReceiptDAOList {

    constructor() {
        this.idReceipt = 1;
        this.receiptList = [
            {id: this.idReceipt++
                ,idUserCrm: 4
                ,idClient: 5
                ,totalPrice: '20'},
            {id: this.idReceipt++
                ,idUserCrm: 6
                ,idClient: 7
                ,totalPrice: '40'},
        ];
    }
    //Simulate an async operation which returns data with some delay
    asyncOp(data) {
        let promise=new Promise((resolve,reject) => {
            setTimeout(function () {
                resolve(data);
            }, 100);
        });
        return promise;
    }
    //public methods
    readAll() {
        return this.asyncOp(this.receiptList);
    }
    readById(id) {
        var receipt = {};
        if (id > 0) {
            this.receiptList.some(function (c, key) {

                if (c.id === id) {
                    receipt= {...c};
                    return true;
                }
                return false;
            });
        }
        return this.asyncOp(receipt);
    }
    delete(id) {
        if (id > 0) {
            this.receiptList.some(function (c, key, receiptList) {
                if (c.id === id) {
                    receiptList.splice(key, 1);
                    return true;
                }
                return false;
            });
        }
        return this.asyncOp({});
    }
    save(receipt) {
        if (receipt.id > 0) {
            this.receiptList.some(function (c, key) {
                if (c.id === receipt.id) {
                    c = {...receipt};
                    return true;
                }
                return false;
            });
        }
        return this.asyncOp({});
    }
    create(receipt) {
        receipt.id = this.idReceipt++;
        this.receiptList.push({...receipt});
        return this.asyncOp(receipt);
    }
}