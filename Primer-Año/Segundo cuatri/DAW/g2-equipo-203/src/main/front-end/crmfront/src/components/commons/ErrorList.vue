<template>
  <div v-if="Object.keys(msgs).length > 0">
    <ul>
      <li class="text-danger" v-for="(message,property, index) in msgs" :key="property">
        {{property}}: {{message}}
      </li>
    </ul>
  </div>
</template>

<script>
export default {
  props: [
    'msgs'
  ],
}
</script>