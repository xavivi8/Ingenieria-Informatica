<template>
  <h1>Editar Producto</h1>
  <form @submit.prevent="guardarCambios">
    <div>
      <label for="name">Nombre</label>
      <input id="name" v-model="form.name" required />
    </div>
    <div>
      <label for="description">Descripción</label>
      <input id="description" v-model="form.description" required />
    </div>
    <div>
      <label for="base_price">Precio Base</label>
      <input id="base_price" type="number" step="0.01" v-model.number="form.base_price" required />
    </div>
    <div>
      <label for="stock">Stock</label>
      <input id="stock" type="number" v-model.number="form.stock" required />
    </div>
    <button type="submit">Guardar</button>
    <RouterLink to="/product">Cancelar</RouterLink>

    <p v-if="mensaje" :class="mensaje.tipo">{{ mensaje.texto }}</p>
  </form>
</template>

<script>
import { ref, onMounted } from 'vue'
import { useRouter, RouterLink } from 'vue-router'
import { ProductDAOfetch } from '@/services/product.service'

export default {
  name: 'ProductEdit',
  components: {
    RouterLink
  },
  props: {
    id: {
      type: [String, Number],
      required: true
    }
  },
  setup(props) {
    const productDAO = new ProductDAOfetch()
    const router = useRouter()

    const form = ref({
      id: props.id,
      name: '',
      description: '',
      base_price: 0,
      stock: 0
    })

    const mensaje = ref(null)

    onMounted(async () => {
      try {
        const data = await productDAO.readById(props.id)
        form.value = { ...data }
      } catch (error) {
        console.error('Error al cargar el producto:', error)
        mensaje.value = { texto: 'No se pudo cargar el producto', tipo: 'error' }
      }
    })

    const guardarCambios = async () => {
      try {
        await productDAO.save(form.value)
        router.push('/product')
      } catch (error) {
        console.error('Error al guardar el producto:', error)
        mensaje.value = {
          texto: error.message || 'Error al guardar',
          tipo: 'error'
        }
      }
    }

    return {
      form,
      mensaje,
      guardarCambios
    }
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

input {
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