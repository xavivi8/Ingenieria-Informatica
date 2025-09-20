<template>
  <h1>Editar Nómina</h1>

  <form @submit.prevent="guardarCambios">
    <div>
      <label for="date">Fecha</label>
      <input id="date" type="date" v-model="form.date" required />
    </div>

    <div>
      <label for="baseSalary">Salario Base</label>
      <input id="baseSalary" type="number" step="0.01" v-model.number="form.baseSalary" required />
    </div>

    <div>
      <label for="status">Estado</label>
      <select id="status" v-model="form.status" required>
        <option value="ACTIVE">ACTIVE</option>
        <option value="PENDING">PENDING</option>
        <option value="INACTIVE">INACTIVE</option>
      </select>
    </div>

    <button type="submit">Guardar</button>
    <RouterLink to="/payslip">Cancelar</RouterLink>

    <p v-if="mensaje" :class="mensaje.tipo">{{ mensaje.texto }}</p>
  </form>
</template>

<script>
import { ref, onMounted } from 'vue'
import { useRouter, RouterLink } from 'vue-router'
import { PayslipDAOfetch } from '@/services/payslip.service'

export default {
  name: 'PayslipEdit',
  components: { RouterLink },
  props: {
    id: { type: [String, Number], required: true }
  },
  setup(props) {
    // 🚫  Ya NO pasamos una URL porque la clase la monta con BASE_URL
    const payslipDAO = new PayslipDAOfetch()
    const router = useRouter()

    const form = ref({
      id: props.id,
      userID: null,
      date: '',
      baseSalary: 0,
      status: 'PENDIENTE'
    })

    const mensaje = ref(null)

    // Cargar datos existentes
    onMounted(async () => {
      try {
        form.value = await payslipDAO.readById(props.id)
      } catch (e) {
        console.error('Error al cargar la nómina:', e)
        mensaje.value = { texto: 'No se pudo cargar la nómina', tipo: 'error' }
      }
    })

    // Guardar cambios
    const guardarCambios = async () => {
      try {
        await payslipDAO.save(form.value)
        mensaje.value = { texto: 'Nómina guardada con éxito', tipo: 'success' }
        // Pequeño retraso opcional si quieres que se vea el mensaje
        setTimeout(() => router.push('/payslip'), 600)
      } catch (e) {
        console.error('Error al guardar la nómina:', e)
        mensaje.value = {
          texto: e?.message || 'Error al guardar',
          tipo: 'error'
        }
      }
    }

    return { form, mensaje, guardarCambios }
  }
}
</script>

<style scoped>
div {
  margin-bottom: 1rem;
}

label {
  display: block;
  font-weight: bold;
}

input,
select {
  width: 100%;
  padding: 0.5rem;
}

button {
  background-color: #4caf50;
  color: white;
  border: none;
  padding: 0.5rem 1rem;
  cursor: pointer;
}

button:hover {
  background-color: #45a049;
}

.success {
  color: green;
}

.error {
  color: red;
}
</style>