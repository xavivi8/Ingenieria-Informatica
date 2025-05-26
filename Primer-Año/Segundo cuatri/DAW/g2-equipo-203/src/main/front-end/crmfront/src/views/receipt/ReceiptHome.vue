<template>
  <div>
    <main>
      <div class="row">
        <nav class="col-md-2">
          <h2>Opciones</h2>
          <ul class="nav nav-pills flex-column">
            <li class="nav-item"><a class="nav-link" href="#">Inicio</a></li>
            <li class="nav-item"><a class="nav-link " href="#"
                                    @click.prevent="createFormReceipt()">Nueva Factura</a></li>
            <li v-if="receipt.id>0" class="nav-item">
              <a class="nav-link text-danger" href="#"
                 @click.prevent="deleteReceipt(receipt.id)">Borrar</a></li>
          </ul>
        </nav>

        <section class="col-md-10">
          <ErrorList :msgs="errorMsgs"/>
          <ReceiptList v-if="receipt.id === undefined"
                        :data="receiptList"
                        @select-receipt="readReceipt"/>
          <ReceiptForm v-if="receipt.id !== undefined"
                        :receipt="receipt" :users="userList" :clients="clientList"
                        @update-receipt="receiptUpdated"
                        @delete-receipt="deleteReceipt"/>
        </section>
      </div>
    </main>
  </div>
</template>

<script>
import ErrorList from "./../../components/commons/ErrorList.vue"
import {ReceiptDAOfetch, ReceiptDAOList} from "@/services/receipt.services.js";
import ReceiptForm from "@/components/receipt/ReceiptForm.vue";
import ReceiptList from "@/components/receipt/ReceiptList.vue";
import {UserDAOfetch} from "@/services/user.services.js";
import {ClientDAOfetch} from "@/services/client.services.js";
const receiptDAO = new ReceiptDAOfetch('http://localhost:8080/app/api/receipts');
const userDAO = new UserDAOfetch('http://localhost:8080/app/api/users');
const clientDAO = new ClientDAOfetch('http://localhost:8080/app/api/clients');


export default {

  components: {
    ReceiptList,
    ReceiptForm
    ,ErrorList
  },
  provide: {
    receiptDAO, userDAO, clientDAO
  },
  mounted() {
    this.uploadReceiptList()
    this.uploadUserList()
    this.uploadClientList()
  },
  data() {
    return {
      receiptList: [ ],
      receipt: {},
      user: {},
      userList: {},
      client: {},
      clientList: {},
      errorMsgs: {}
    }
  },
  methods: {
    uploadReceiptList() {
      //AJAX request: Promise version
      //TODO catch api access errors
      receiptDAO.readAll()
          .then(data => {
            this.receiptList = data
            this.receipt = { }
            this.errorMsgs={ }
          })
    },
    async deleteReceipt(receiptId) {
      if (receiptId > 0) {
        await receiptDAO.delete(receiptId);
        this.uploadReceiptList();
      }
    },
    async readReceipt(receiptId) {
      console.log(`visualizando receipt ${receiptId}`)
      this.receipt = await receiptDAO.readById(receiptId)
    },
    createFormReceipt() {
      this.errorMsgs={ }
      this.receipt = {id: 0, totalPrice: ''}
    },
    async receiptUpdated() {
      console.log("actualizado receipt en servidor")
      this.uploadReceiptList()
    },
    uploadUserList() {
      userDAO.readAll()
          .then(data => {
            this.userList = data
            this.user = { }
            this.errorMsgs={ }
          })
    },
    uploadClientList() {
      clientDAO.readAll()
          .then(data => {
            this.clientList = data
            this.client = { }
            this.errorMsgs={ }
          })
    },
  }
}
</script>