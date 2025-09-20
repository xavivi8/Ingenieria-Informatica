<template>
  <Menubar :model="navItems" class="p-shadow-2">
    <!-- Slot start: logo + título -->
    <template #start>
      <div class="flex items-center">
        <img :src="logo" alt="Logo" height="40" class="mr-2" loading="lazy" />
      </div>
    </template>

    <template #end>
      <Button icon="pi pi-user" class="p-button-rounded p-button-text" />
    </template>

  </Menubar>

    <!-- Registro -->
 <div class="registration-wrapper">
   <div class="registration-card">
   <Toast />
        <Form v-slot="$form" :initialValues :resolver :validateOnValueUpdate="false" :validateOnBlur="true" :validateOnMount="['firstName']" @submit="onFormSubmit" class="flex flex-col gap-4 w-full sm:w-56">
            <div class="flex flex-col gap-1">
                <InputText name="username" type="text" placeholder="Username" fluid />
                <Message v-if="$form.username?.invalid" severity="error" size="small" variant="simple">{{ $form.username.error.message }}</Message>
            </div>
            <div class="flex flex-col gap-1">
                <InputText name="email" type="text" placeholder="Email" fluid :formControl="{ validateOnValueUpdate: true }" />
                <Message v-if="$form.email?.invalid" severity="error" size="small" variant="simple">{{ $form.firstName.error.message }}</Message>
            </div>
            <div class="flex flex-col gap-1">
                <InputText name="password" type="text" placeholder="Password" fluid />
                <Message v-if="$form.password?.invalid" severity="error" size="small" variant="simple">{{ $form.lastName.error.message }}</Message>
            </div>
            <Button type="submit" severity="secondary" label="Submit" />
        </Form>
  </div>
  </div>

    <!-- Tarjetas de Películas -->
  <div class="p-container">
    <h2 class="text-2xl font-semibold mb-4">Películas Destacadas</h2>
        <div class="p-grid spaced-grid">
          <div class="p-col-12 p-md-4" v-for="movie in movies" :key="movie.id">
          <Card :title="movie.title" :subTitle="movie.year">
            <template #content>
            <div class="movie-content">
              <img :src="movie.poster" :alt="movie.title" class="movie-poster p-shadow-2 p-mb-3" loading="lazy" />
              <div class="movie-text">
              <p>{{ movie.description }}</p>
              </div>
            </div>
            </template>
            <template #footer>
              <Button label="Ver más" icon="pi pi-info-circle" class="p-button-text" />
            </template>
          </Card>
        </div>
      </div>
    </div>

    <!-- Footer -->
    <Footer class="p-mt-8 p-py-4 text-center">
      <div>© 2025 MovieDB. Todos los derechos reservados.</div>
    </Footer>
</template>

<script setup>
// PrimeVue components
import Menubar from 'primevue/menubar';
import InputText from 'primevue/inputtext';
import Button from 'primevue/button';
import Card from 'primevue/card';
import { Form } from '@primevue/forms';

import { ref } from 'vue';
import { useToast } from 'primevue/usetoast';

const toast = useToast();

const initialValues = ref({
    username: '',
    firstName: '',
    lastName: ''
});

const logo = ref('../../public/logo.jpg');

const resolver = ({ values }) => {
    const errors = {};

    if (!values.username) {
        errors.username = [{ message: 'Username is required.' }];
    }

    if (!values.name) {
        errors.firstName = [{ message: 'First name is required.' }];
    }

    if (!values.surname) {
        errors.lastName = [{ message: 'Last name is required.' }];
    }

    return {
        errors
    };
};

const onFormSubmit = ({ valid }) => {
    if (valid) {
        toast.add({ severity: 'success', summary: 'Form is submitted.', life: 3000 });
    }
}

// Navigation items
const navItems = [
  { label: 'Inicio', icon: 'pi pi-home', command: () => router.push('/') },
  { label: 'Películas', icon: 'pi pi-film', command: () => router.push('/movies') },
  { label: 'Contacto', icon: 'pi pi-envelope', command: () => router.push('/contact') }
];


// Movies data (could import from JSON or API in real use)
const movies = [
  { id: 1, title: 'Inception', year: 2010, poster: "../../public/inception.jpg", description: 'Experto en el arte del robo de información mediante la infiltración en sueños.' },
  { id: 2, title: 'Interstellar', year: 2014, poster: "../../public/interstellar.jpg", description: 'Viaje épico a través del espacio y el tiempo para salvar a la humanidad.' },
  { id: 3, title: 'The Matrix', year: 1999, poster: "../../public/matrix.jpg", description: 'Revelación de una realidad simulada y lucha por la libertad.' }
];

</script>

<style scoped>
.registration-wrapper {
  display: flex;
  justify-content: center;   
  padding: 3rem 0;  
  margin-top: 2rem;
  margin-bottom: 2rem;         
}

.registration-card {
  width: 100%;
  max-width: 24rem;          
  background: #1f1f1f;       
  padding: 1.5rem;           
  border-radius: 0.5rem;     
  box-shadow: 0 2px 8px rgba(0,0,0,0.1); 
}

.movie-poster {
  width: 120px;
  height: auto;
  object-fit: cover;
}

.spaced-grid {
  display: flex;          
  flex-wrap: wrap;
  gap: 1.5rem;            
}

.spaced-grid .p-col-12.p-md-4 {
  flex: 0 0 calc(33.333% - 1.5rem); 
}

.movie-content {
  display: flex;
  align-items: center;      
  gap: 1rem;               
}

.movie-poster {
  width: 120px;
  height: auto;
  object-fit: cover;
  flex-shrink: 0;           
}

.movie-text {
  display: flex;
  flex-direction: column;
  flex: 1;                  
}

.p-container { max-width: 1200px; margin: auto; }
.text-xl { font-size: 1.25rem; }
.text-2xl { font-size: 1.5rem; }
.font-bold { font-weight: bold; }
.font-semibold { font-weight: 600; }
.bg-gray-100 { background-color: #f7fafc; }
.p-menubar .p-menuitem-link {
  color: #f3f4f6; }
</style>