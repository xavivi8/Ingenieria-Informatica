    <template>
  <main>
    <h1>Crear Nómina</h1>
    <form @submit.prevent="crearPayslip">
       <div>
        <label for="userID">ID Usuario:</label>
        <input type="number" id="userID" v-model="payslip.userID" required min="1" />
      </div>

      <div>
        <label for="date">Fecha:</label>
        <input type="date" id="date" v-model="payslip.date" required />
      </div>

        <div>
        <label for="baseSalary">Salario Base:</label>
        <input type="number" id="baseSalary" v-model="payslip.baseSalary" required min="0" />
      </div>

          <div>
        <label for="status">Estado:</label>
        <select id="status" v-model="payslip.status" required>
          <option value="ACTIVE">ACTIVE</option>
          <option value="PENDING">PENDING</option>
          <option value="INACTIVE">INACTIVE</option>
        </select>
      </div>
       
         <div>
        <button type="submit">Crear Nómina</button>
      </div>
</form>

</main>
    </template>
    
<script>
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { PayslipDAOfetch } from '@/services/payslip.service'

export default {
  name: 'PayslipCreate',
  setup() {
    const payslipDAO = new PayslipDAOfetch('http://localhost:8080/app/api/payslip')

    const payslip = ref({
      userID: '',
      date: '',
      baseSalary: 0,
      status: 'PENDIENTE'
    })

    const mensaje = ref(null)
    const router = useRouter()

    const crearPayslip = async () => {
      try {
        await payslipDAO.create(payslip.value)
        mensaje.value = { texto: 'Nómina creada con éxito', tipo: 'success' }

        payslip.value = {
          userID: '',
          date: '',
          baseSalary: 0,
          status: 'PENDIENTE'
        }

        router.push({ name: 'PayslipHome' })
      } catch (error) {
        console.error('Error al crear la nómina:', error)
        mensaje.value = {
          texto: `Error: ${error.message || 'Error desconocido al crear la nómina'}`,
          tipo: 'error'
        }
      }
    }

    return {
      payslip,
      mensaje,
      crearPayslip
    }
  }
}
</script>
<style scoped>
form {
  display: grid;
  gap: 1rem;
  max-width: 400px;
  margin: auto;
}

label {
  font-weight: bold;
}

input,
select {
  width: 100%;
  padding: 0.5rem;
  font-size: 1rem;
}

button {
  padding: 0.75rem;
  background-color: #4caf50;
  color: white;
  border: none;
  font-size: 1rem;
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