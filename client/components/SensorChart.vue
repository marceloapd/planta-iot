<template>
  <div class="shadow-lg rounded-lg overflow-hidden">
    <div class="py-3 px-5 bg-gray-50">
      Line chart
    </div>
    <canvas id="chartline" ref="chartLine" class="p-10" />
  </div>
</template>

<script>
export default {
  data () {
    return {}
  },
  head: {
    script: [
      {
        src: 'https://cdn.jsdelivr.net/npm/chart.js'
      }
    ]
  },
  mounted () {
    this.initChart()
  },
  methods: {
    initChart () {
      const data = {
        labels: ['January', 'February', 'March', 'April', 'May', 'June'],
        datasets: [
          {
            label: 'My First dataset',
            backgroundColor: 'hsl(252, 82.9%, 67.8%)',
            borderColor: 'hsl(252, 82.9%, 67.8%)',
            data: [0, 10, 5, 2, 20, 30, 45]
          }
        ]
      }
      const config = {
        type: 'line',
        data,
        options: {}
      }
      // eslint-disable-next-line no-undef
      const chart = new Chart(this.$refs.chartLine, config)
      chart.resize(250, 500)
    }
  }
}
</script>
