<script>
    export let nombre;
  </script>
  
  <style>
    p {
      font-style: italic;
      color: rgb(21, 231, 231);
    }
  </style>
  
  {#if nombre}
    <p>Hola, {nombre} 👋</p>
  {:else}
    <p>Escribe tu nombre para saludarte</p>
  {/if}
  