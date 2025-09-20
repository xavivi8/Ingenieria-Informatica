<template>
  <h2 v-if="receipt.id>0">Edición de factura</h2>
  <h2 v-if="receipt.id===0">Alta de factura</h2>

  <ErrorList :msgs="errorMsgs"/>

  <form novalidate name='formReceipt' class="well">

    <h3>ID: <span>{{ receipt.id }}</span></h3>

    <label>Empleado:</label>
    <select v-model="receipt.idUserCrm" required class="form-control" :class="{'is-invalid': errorMsgs.idUserCrm}">
      <option v-for="user in userList" :key="user.id" :value="user.id">{{ user.name }}</option>
    </select>
    <p id="erruserCrm" class="text-danger" v-if="errorMsgs.idUserCrm">
      Selecciona el empleado que está encargado de esta factura
    </p>

    <label>Cliente:</label>
    <select v-model="receipt.idClient" required class="form-control" :class="{'is-invalid': errorMsgs.idClient}">
      <option v-for="client in clientList" :key="client.id" :value="client.id">{{ client.name }}</option>
    </select>
    <p id="errclientCrm" class="text-danger" v-if="errorMsgs.idClient">
      Selecciona el cliente de la factura
    </p>

    <!-- Acciones -->
    <button class="btn btn-primary"
            @click.prevent="saveReceipt">Guardar
    </button>
    <button class="btn btn-danger"
            v-if='receipt.id>0'
            @click.prevent="$emit('deleteReceipt',receipt.id)">Borrar
    </button>
    <a @click.prevent="receipt.id=undefined" class="btn btn-default">Cancelar</a>
  </form>
</template>

<script>
import ErrorList from "@/components/commons/ErrorList.vue";


export default {
  props: [
    'receipt','userList', 'clientList'
  ],
  inject: ['receiptDAO','userDAO', 'clientDAO'],
  emits: [
    'updateReceipt',
    'deleteReceipt'
  ],
  data() {
    return {
      errorMsgs: {}
    }
  },
  components: {
    ErrorList,
  },
  computed: {
    isError() {
      return Object.keys(this.errorMsgs).length > 0;
    }
  },
  methods: {
    async saveReceipt() {
      if (this.validateReceipt()) {
        console.log("actualizando factura")
        try {
          if (this.receipt.id === 0) {
            await this.receiptDAO.create(this.receipt)
          } else {
            await this.receiptDAO.save(this.receipt)
          }
          this.$emit('updateReceipt')
        } catch (err) {
          console.log("Errores de validación en servidor")
          err.forEach(error => {
            this.errorMsgs[error.name] = error.message;
          })
        }
      }
    },
    validateReceipt() {
      return true; // TODO QUITAR
      console.log("Validación en factura")
      this.errorMsgs = {};
      let isValid = true;

      // if (this.receipt.nombre.length < 3)
      //   this.errorMsgs.nombre = "La longitud del nombre no es correcta (>=3)";
      // if (/^\d{7,8}-?[A-Z]$/i.test(this.receipt.dni) === false)
      //   this.errorMsgs.dni = "El DNI no es de la forma 12345678-A";

      if (Object.keys(this.errorMsgs).length > 0) {
        console.log("Errores de validación en factura")
        isValid = false;
      }
      return isValid;
    },
    fetchUsers() {
      this.userDAO.readAll()
          .then(response => {
            this.users = response;
          })
          .catch(error => {
            console.error('Error al obtener los usuarios:', error);
          });
    },
    fetchClients() {
      this.clientDAO.readAll()
          .then(response => {
            this.clientList = response;
          })
          .catch(error => {
            console.error('Error al obtener los clientes:', error);
          });
    }
  },
}
</script>