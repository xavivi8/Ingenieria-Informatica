<template>
  <div class="resenia-form p-4 border rounded bg-light">
    <h5>Reseñar: {{ pista.nombre }}</h5>

    <form @submit.prevent="handleSubmit">
      <!-- Puntuación -->
      <div class="mb-3">
        <label for="puntuacion" class="form-label">Puntuación (1–5)</label>
        <input
            id="puntuacion"
            type="number"
            v-model.number="formData.puntuacion"
            class="form-control"
            min="1"
            max="5"
        />
        <div v-if="errors.puntuacion" class="text-danger small">
          {{ errors.puntuacion }}
        </div>
      </div>

      <!-- Comentario -->
      <div class="mb-3">
        <label for="comentario" class="form-label">Comentario</label>
        <textarea
            id="comentario"
            v-model="formData.comentario"
            class="form-control"
            rows="3"
            maxlength="200"
        ></textarea>
        <div v-if="errors.comentario" class="text-danger small">
          {{ errors.comentario }}
        </div>
      </div>

      <!-- Botón Enviar -->
      <div class="d-grid">
        <button type="submit" class="btn btn-primary" :disabled="loading">
          <span v-if="loading" class="spinner-border spinner-border-sm me-2"></span>
          {{ loading ? "Enviando…" : "Enviar Reseña" }}
        </button>
      </div>

      <!-- Error genérico -->
      <div v-if="submitError" class="text-danger mt-2 small">
        {{ submitError }}
      </div>
    </form>
  </div>
</template>

<script setup lang="ts">
import { defineProps, defineEmits, reactive, ref, watch } from 'vue'
import { useRouter } from 'vue-router'
import axios from 'axios'
import type { Resenia } from '@/models/Resenia'
import {useAuth} from "@/composables/useAuth";

// 1) Recibimos la pista activa
const props = defineProps<{ pista: { id: number; nombre: string } }>()

// 2) Emitiremos 'created' al padre con la reseña recibida
const emit = defineEmits<{
  (e: 'created', newRes: Resenia): void
}>()
const router = useRouter()
const { user } = useAuth()
// 3) Estado del formulario y errores
const formData = reactive({
  pistaId: props.pista.id,
  puntuacion: 1,
  comentario: ''
})
watch(() => props.pista.id, id => (formData.pistaId = id))

const errors = reactive({
  puntuacion: '',
  comentario: ''
})
const submitError = ref<string|null>(null)
const loading = ref(false)

// 4) Validación local
function validate() {
  let ok = true
  errors.puntuacion = ''
  errors.comentario = ''

  if (formData.puntuacion < 1 || formData.puntuacion > 5) {
    errors.puntuacion = 'Debe estar entre 1 y 5'
    ok = false
  }
  if (!formData.comentario.trim()) {
    errors.comentario = 'El comentario es obligatorio'
    ok = false
  }
  return ok
}

// 5) Envío al servidor
async function handleSubmit() {
  if (!validate()) return

  submitError.value = null
  loading.value = true

  try {
    const payload = {
      pistaId: formData.pistaId,
      puntuacion: formData.puntuacion,
      comentario: formData.comentario
    }

    // Log para depurar, igual que en tu registro
    console.log('Enviando reseña:', payload)

    // POST a /resenias
    const response = await axios.post<Resenia>('/resenias', payload, {
      headers: { 'Content-Type': 'application/json' }
    })

    console.log('Reseña creada:', response.data)

    // Emitimos al padre la reseña creada
    emit('created', response.data)

    const destino = user.value?.tipo === 'ADMINISTRADOR'
                 ? 'ReseniaAdmin'
                 : 'ReseniaCliente'
           router.push({ name: destino })

    // Limpiar formulario
    formData.puntuacion = 1
    formData.comentario = ''
  } catch (error: any) {
    console.error('Error creando reseña:', error.response || error)
    // Igual manejo que usas en registro
    if (error.response?.data?.message) {
      submitError.value = error.response.data.message
    } else {
      submitError.value = 'Error al crear reseña: ' + (error.message || 'desconocido')
    }
  } finally {
    loading.value = false
  }
}
</script>

<style scoped>
.resenia-form {
  max-width: 500px;
  margin: 1rem auto;
}
</style>
