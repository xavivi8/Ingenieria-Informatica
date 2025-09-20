<template>
  <TheHeader />

  <!-- Añadimos d-flex al <main> y eliminamos contenedores innecesarios -->
  <main class="d-flex flex-row h-100">
    <!-- Menú Vertical -->
    <nav id="sidebar" class="sidebar bg-light p-3">
      <h4>Menú</h4>
      <ul class="nav flex-column">
        <li class="nav-item">
          <RouterLink class="nav-link" to="/product">Producto</RouterLink>
        </li>
        <li class="nav-item">
          <RouterLink class="nav-link" to="/payslip">Nómina</RouterLink>
        </li>
        <li class="nav-item">
          <RouterLink class="nav-link" to="/receipt">Factura</RouterLink>
        </li>
      </ul>
    </nav>

    <!-- Contenido Principal -->
    <div id="contenido-principal" class="contenido-principal p-2">
      <RouterView />
    </div>
  </main>

  <TheFooter />
</template>

<script>
import { RouterLink, RouterView, useRouter } from 'vue-router'
import TheHeader from './components/TheHeader.vue'
import TheFooter from './components/TheFooter.vue'

export default {
  name: 'App',
  components: {
    TheHeader,
    TheFooter,
    RouterLink,
    RouterView
  },
  setup() {
    const router = useRouter()
    const goToProductHome = () => router.push({ name: 'ProductHome' })

    return {
      goToProductHome
    }
  }
}
</script>

<style scoped>
/* Mantén aquí estilos muy locales, si los necesitas */
</style>