<template>
  <SensorChart />
</template>

<script>
export default {
  mounted () {
    this.$store.dispatch('sensor/getSensorData')
  }
}
</script>
