<template>
  <main>
    <h1>Crear Producto</h1>

    <form @submit.prevent="onSubmit">
      <!-- Nombre -->
      <div>
        <label for="name">Nombre:</label>
        <input
          type="text"
          id="name"
          v-model="producto.name"
          @input="errors.name = null"
          :class="{ invalid: errors.name }"
        />
        <span class="error" v-if="errors.name">{{ errors.name }}</span>
      </div>

      <!-- Descripción -->
      <div>
        <label for="description">Descripción:</label>
        <input
          type="text"
          id="description"
          v-model="producto.description"
          @input="errors.description = null"
          :class="{ invalid: errors.description }"
        />
        <span class="error" v-if="errors.description">{{ errors.description }}</span>
      </div>

      <!-- Precio base -->
      <div>
        <label for="base_price">Precio Base:</label>
        <input
          type="number"
          id="base_price"
          v-model="producto.base_price"
          step="0.01"
          @input="errors.base_price = null"
          :class="{ invalid: errors.base_price }"
        />
        <span class="error" v-if="errors.base_price">{{ errors.base_price }}</span>
      </div>

      <!-- Stock -->
      <div>
        <label for="stock">Stock:</label>
        <input
          type="number"
          id="stock"
          v-model="producto.stock"
          @input="errors.stock = null"
          :class="{ invalid: errors.stock }"
        />
        <span class="error" v-if="errors.stock">{{ errors.stock }}</span>
      </div>

      <div>
        <button type="submit">Crear Producto</button>
      </div>
    </form>

    <p v-if="mensaje" :class="mensaje.tipo">{{ mensaje.texto }}</p>
  </main>
</template>

<script setup>
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { ProductDAOfetch } from '@/services/product.service'

// Router y servicio
const router = useRouter()
const productDAO = new ProductDAOfetch()

// Estado del formulario
const producto = ref({
  name: '',
  description: '',
  base_price: '',
  stock: ''
})

// Errores por campo
const errors = ref({
  name: null,
  description: null,
  base_price: null,
  stock: null
})

// Mensaje global
const mensaje = ref(null)

function validate () {
  let ok = true

  // Nombre
  if (!producto.value.name.trim()) {
    errors.value.name = 'El nombre es obligatorio'
    ok = false
  } else if (producto.value.name.length > 100) {
    errors.value.name = 'El nombre no debe exceder 100 caracteres'
    ok = false
  }

  // Descripción
  if (!producto.value.description.trim()) {
    errors.value.description = 'La descripción no puede estar vacía'
    ok = false
  }

  // Precio base
  const price = Number(producto.value.base_price)
  if (isNaN(price)) {
    errors.value.base_price = 'Debe ser un número'
    ok = false
  } else if (price < 0) {
    errors.value.base_price = 'El precio debe ser mayor o igual a 0'
    ok = false
  }

  // Stock
  const stockNum = Number(producto.value.stock)
  if (!Number.isInteger(stockNum)) {
    errors.value.stock = 'Debe ser un número entero'
    ok = false
  } else if (stockNum < 0) {
    errors.value.stock = 'El stock no puede ser negativo'
    ok = false
  }

  return ok
}

async function onSubmit () {
  // Limpia mensajes anteriores
  mensaje.value = null

  if (!validate()) return

  try {
    // Ajusta tipos antes de enviar
    const toSend = {
      name: producto.value.name.trim(),
      description: producto.value.description.trim(),
      base_price: Number(producto.value.base_price),
      stock: Number(producto.value.stock)
    }

    const response = await productDAO.create(toSend)

    mensaje.value = {
      texto: (typeof response === 'string') ? response : (response?.message || 'Producto creado con éxito'),
      tipo: 'success'
    }

    // Reinicia formulario
    producto.value = { name: '', description: '', base_price: '', stock: '' }
    errors.value = { name: null, description: null, base_price: null, stock: null }

    router.push({ name: 'ProductHome' })
  } catch (error) {
    mensaje.value = {
      texto: `Error al crear el producto: ${error?.message || 'desconocido'}`,
      tipo: 'error'
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

input {
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

.error {
  color: red;
  font-size: 0.875rem;
}

.invalid {
  border: 1px solid red;
}

.success {
  color: green;
}
</style>