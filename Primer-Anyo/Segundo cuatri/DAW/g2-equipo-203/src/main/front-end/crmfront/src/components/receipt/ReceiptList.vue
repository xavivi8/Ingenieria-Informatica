<template>
  <h2>Listado de Facturas</h2>

  <table class="table table-striped table-hover">
    <thead>
      <tr title="Seleccionar encabezado para cambiar ordenación">
        <th v-on:click="orderBy('id')" scope="col">ID <span v-if="order==='id'">&darr;</span></th>
        <th @click="orderBy('idUserCrm')" scope="col">Empleado<span v-if="order==='idUserCrm'">&darr;</span></th>
        <th @click="orderBy('idClient')" scope="col">Cliente<span v-if="order==='idClient'">&darr;</span></th>
        <th @click="orderBy('totalPrice')" scope="col">Precio total<span v-if="order==='totalPrice'">&darr;</span></th>
      </tr>
    </thead>
    <tbody>
      <tr class="c-pointer" v-for="r in receiptListSorted" :key='r.id'
          @click="$emit('selectReceipt',r.id)">
        <td>{{ r.id }}</td>
        <td>{{ r.idUserCrm }}</td>
        <td>{{ r.idClient }}</td>
        <td>{{ r.totalPrice }}</td>
      </tr>
    </tbody>
  </table>
</template>

<script>
export default {
  props: [
    'data',
  ],
  emits: ['selectReceipt'],
  data() {
    return {
      order: 'id'
    }
  },
  computed: {
    receiptListSorted() {
      console.log("ordenando por " + this.order)
      return this.data.slice().sort((r1, r2) => {
        let result = 0;
        if (r1[this.order] > r2[this.order]) result = 1;
        if (r1[this.order] < r2[this.order]) result = -1;
        return result;
      });
    }
  },
  methods: {
    orderBy(newOrder) {
      this.order = newOrder;
    }
  },
}
</script>