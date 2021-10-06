<template>
  <div class="container-fluid mt-5">
    <SensorChart />
  </div>
</template>

<script>
export default {
  mounted () {
    this.$store.dispatch('sensor/getSensorData')
  }
}
</script>
