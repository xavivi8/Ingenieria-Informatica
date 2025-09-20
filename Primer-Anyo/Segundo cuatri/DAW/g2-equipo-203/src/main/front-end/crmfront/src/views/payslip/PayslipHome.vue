<template>
  <h1>Lista de Nóminas</h1>

  <RouterLink to="/payslip/create">Crear Nómina</RouterLink>

  <div class="payslip-tabla">
    <table v-if="payslips.length">
      <thead>
        <tr>
          <th>ID</th>
          <th>ID Usuario</th>
          <th>Fecha</th>
          <th>Salario Base</th>
          <th>Estado</th>
          <th>Acción</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="p in payslips" :key="p.id">
          <td>{{ p.id }}</td>
          <td>{{ p.userID }}</td>
          <td>{{ p.date }}</td>
          <td>{{ p.baseSalary }}</td>
          <td>{{ p.status }}</td>
          <td>
            <RouterLink :to="`/payslip/${p.id}/edit`">
              <button class="edit">Editar</button>
            </RouterLink>
            <button @click="eliminarPayslip(p.id)">Eliminar</button>
          </td>
        </tr>
      </tbody>
    </table>

    <p v-else>No hay nóminas disponibles.</p>
    <p v-if="mensaje" :class="mensaje.tipo">{{ mensaje.texto }}</p>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import { RouterLink } from 'vue-router'
import { PayslipDAOfetch } from '@/services/payslip.service.js'

const payslipDAO = new PayslipDAOfetch()

const payslips = ref([])
const mensaje = ref(null)

const cargarPayslips = async () => {
  try {
    payslips.value = await payslipDAO.readAll()
  } catch (error) {
    mensaje.value = { texto: 'Error al cargar las nóminas', tipo: 'error' }
  }
}

onMounted(cargarPayslips)

const eliminarPayslip = async (id) => {
  try {
    await payslipDAO.delete(id)
    payslips.value = payslips.value.filter(p => p.id !== id)
    mensaje.value = { texto: 'Nómina eliminada correctamente', tipo: 'success' }
  } catch (error) {
    mensaje.value = { texto: 'Error al eliminar la nómina', tipo: 'error' }
  }
}
</script>

<style scoped>
table {
  width: 100%;
  border-collapse: collapse;
}

th,
td {
  padding: 8px 12px;
  text-align: left;
  border: 1px solid #ddd;
}

th {
  background-color: #f4f4f4;
}

button {
  background-color: red;
  color: white;
  border: none;
  padding: 6px 12px;
  cursor: pointer;
}

button.edit {
  background-color: #2196f3;
}

button.edit:hover {
  background-color: #1976d2;
}

button:hover {
  background-color: darkred;
}

.success {
  color: green;
}

.error {
  color: red;
}
</style>