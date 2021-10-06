<template>
  <nav class="navbar navbar-expand-lg navbar-light bg-light">
    <div class="container-fluid">
      <h4>PlantIO</h4>
      <button
        class="navbar-toggler"
        type="button"
        data-bs-toggle="collapse"
        data-bs-target="#navbarNavAltMarkup"
        aria-controls="navbarNavAltMarkup"
        aria-expanded="false"
        aria-label="Toggle navigation"
      >
        <span class="navbar-toggler-icon" />
      </button>
      <div id="navbarNavAltMarkup" class="collapse navbar-collapse">
        <div class="navbar-nav">
          <nuxt-link class="nav-link active" to="/">
            Gráficos
          </nuxt-link>
          <nuxt-link class="nav-link disabled" to="#">
            Sensores
          </nuxt-link>
        </div>
      </div>
    </div>
  </nav>
</template>

<script>
export default {}
</script>

<style></style>
