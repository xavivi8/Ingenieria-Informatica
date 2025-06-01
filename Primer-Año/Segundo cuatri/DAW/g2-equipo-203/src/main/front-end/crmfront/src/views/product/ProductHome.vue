<template>
    <h1>Lista de Productos</h1>
    <RouterLink to="/product/create">Crear Producto</RouterLink>
    <div class="product-tabla">
        <table v-if="productos.length > 0">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Nombre</th>
                    <th>Descripción</th>
                    <th>Precio Base</th>
                    <th>Stock</th>
                    <th>Acción</th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="producto in productos" :key="producto.id">
                    <td>{{ producto.id }}</td>
                    <td>{{ producto.name }}</td>
                    <td>{{ producto.description }}</td>
                    <td>{{ producto.base_price }}</td>
                    <td>{{ producto.stock }}</td>
                    <td>
                        <!-- Botón para editar -->
                        <RouterLink :to="`/product/${producto.id}/edit`">
                            <button class="edit">Editar</button>
                        </RouterLink>

                        <!-- Botón para eliminar -->
                        <button @click="eliminarProducto(producto.id)">Eliminar</button>
                    </td>
                </tr>
            </tbody>
        </table>
        <p v-else>No hay productos disponibles.</p>
        <p v-if="mensaje" :class="mensaje.tipo">{{ mensaje.texto }}</p> <!-- Mostrar el mensaje de éxito o error -->
    </div>
</template>

<script>
import { ref, onMounted } from 'vue'
import { RouterLink } from 'vue-router'
import { ProductDAOfetch } from '@/services/product.service'

export default {
  name: 'ProductHome',
  components: {
    RouterLink
  },
  setup() {
    // Crear una instancia del servicio
    const productDAO = new ProductDAOfetch()

    // Ref para almacenar los productos
    const productos = ref([])

    // Ref para mostrar mensajes de éxito o error
    const mensaje = ref(null)

    // Cargar los productos cuando el componente se monta
    onMounted(async () => {
      try {
        const data = await productDAO.readAll()
        productos.value = data
      } catch (error) {
        console.error('Error al cargar los productos:', error)
      }
    })

    // Función para eliminar un producto
    const eliminarProducto = async (id) => {
      try {
        // Llamar al servicio para eliminar el producto
        const response = await productDAO.delete(id)
        console.log('Respuesta del servidor:', response)

        // Mostrar el mensaje de éxito en la interfaz
        if (response && response.message) {
          mensaje.value = { texto: response.message, tipo: 'success' }
        }

        // Eliminar el producto de la lista
        productos.value = productos.value.filter((producto) => producto.id !== id)
      } catch (error) {
        console.error('Error al eliminar el producto:', error)
        if (error && error.message) {
          mensaje.value = { texto: `Error al eliminar el producto: ${error.message}`, tipo: 'error' }
        } else {
          mensaje.value = { texto: 'Error desconocido al eliminar el producto', tipo: 'error' }
        }
      }
    }

    return {
      productos,
      mensaje,
      eliminarProducto
    }
  }
}
</script>

<style scoped>
/* --- Estilos de la tabla y botones --- */

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