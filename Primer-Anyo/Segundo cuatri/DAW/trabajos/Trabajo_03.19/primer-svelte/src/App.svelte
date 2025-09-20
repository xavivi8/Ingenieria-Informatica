<script>
  import Saludo from './Saludo.svelte';

  let count = 0;
  let nombre = '';
  let mostrarLista = true;
  let frutas = ['Manzana', 'Pera', 'Plátano'];

  let vista = 1; // 1: Reactividad, 2: Condicionales/Bucles, 3: Estilos

  function incrementar() {
    count += 1;
  }
</script>

<style>
  main {
    max-width: 600px;
    margin: auto;
    padding: 2rem;
    font-family: sans-serif;
  }

  h1 {
    color: #066501;
    margin-bottom: 1rem;
  }

  .contador {
    margin: 1em 0;
    font-size: 1.2em;
  }

  .frutas {
    color: green;
  }

  input {
    margin-bottom: 1em;
    padding: 0.5em;
    width: 100%;
  }

  nav {
    margin-bottom: 2rem;
    display: flex;
    justify-content: center;
    gap: 1rem;
  }

  button {
    padding: 0.5rem 1rem;
    background: #3498db;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
  }

  button:hover {
    background: #2980b9;
  }

  section {
    border: 1px solid #ddd;
    padding: 1.5rem;
    border-radius: 8px;
    margin-bottom: 2rem;
    box-shadow: 0 2px 6px rgba(0,0,0,0.05);
  }
</style>

<main>
  <h1>Mini App en Svelte</h1>

  <nav>
    <button on:click={() => (vista = 1)}>Reactividad</button>
    <button on:click={() => (vista = 2)}>Condicionales y Bucles</button>
    <button on:click={() => (vista = 3)}>Estilos con Ámbito</button>
  </nav>

  {#if vista === 1}
    <section>
      <h2>Reactividad Básica</h2>
      <button on:click={incrementar}>Incrementar</button>
      <p class="contador">Contador: {count}</p>

      <input bind:value={nombre} placeholder="Escribe tu nombre" />
      <Saludo nombre={nombre} />
    </section>
  {/if}

  {#if vista === 2}
    <section>
      <h2>Condicionales y Bucles</h2>

      <button on:click={() => (mostrarLista = !mostrarLista)}>
        {mostrarLista ? 'Ocultar' : 'Mostrar'} frutas
      </button>

      {#if mostrarLista}
        <ul>
          {#each frutas as fruta}
            <li class="frutas">{fruta}</li>
          {/each}
        </ul>
      {/if}
    </section>
  {/if}

  {#if vista === 3}
    <section>
      <h2>Estilos con Ámbito</h2>
      <p>Este texto y sus estilos están encapsulados dentro del componente.</p>
      <p style="color: purple; font-style: italic;">Ejemplo de estilo aplicado solo aquí.</p>
    </section>
  {/if}
</main>
