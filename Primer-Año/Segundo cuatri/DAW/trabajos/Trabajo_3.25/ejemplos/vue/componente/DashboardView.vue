<template>
  <div id="app-container">
    <Header
      :user-role="userRole"
      :current-component="currentComponent"
      @change-component="changeComponent"
      @logout="handleLogout"
    />
    <main class="main-content">
      <component
        :is="currentComponentInstance"
        :user-role="userRole"
      ></component>
    </main>
  </div>
</template>

<script setup lang="ts">
import { ref, shallowRef, onMounted } from "vue";
import { useRouter } from "vue-router";
import Header from "@/components/Header.vue";
import ReservaPista from "@/components/ReservaPista.vue";
import Resenias from "@/components/Resenias.vue";
import Admin from "@/components/Admin.vue";
import AdminPistas from "@/components/AdminPistas.vue";
import AdminUsers from "@/components/AdminUsers.vue";

const router = useRouter();
const userRole = ref<"DEPORTISTA" | "ADMINISTRADOR">("DEPORTISTA");
const currentComponent = ref("ReservaPista");
const currentComponentInstance = shallowRef(ReservaPista);

const components = {
  ReservaPista,
  Resenias,
  Admin,
  AdminPistas,
  AdminUsers
};

const changeComponent = (componentName: string) => {
  currentComponent.value = componentName;
  currentComponentInstance.value =
    components[componentName as keyof typeof components];
};

onMounted(() => {
  const userStr = localStorage.getItem("user");
  if (userStr) {
    const user = JSON.parse(userStr);
    userRole.value = user.tipo;
  }
});

const handleLogout = () => {
  localStorage.removeItem("token");
  localStorage.removeItem("user");
  router.push("/login");
};
</script>
