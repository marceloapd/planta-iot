<template>
  <canvas
    id="myChart"
    ref="myChart"
    class="chart"
    style="position: relative; height:40vh; width:80vw"
  />
</template>

<script>
import {
  Chart,
  LinearScale,
  LineController,
  CategoryScale,
  LineElement,
  PointElement
} from 'chart.js'

export default {
  data () {
    return {
      chart: null,
      chartData: {}
    }
  },

  async mounted () {
    await this.initChart()
    await this.updateChart()
  },

  methods: {
    registerChartElements () {
      Chart.register(
        LinearScale,
        LineController,
        CategoryScale,
        LineElement,
        PointElement
      )
    },

    getChart () {
      return this.$refs.myChart.getContext('2d')
    },

    async initChart () {
      this.registerChartElements()
      const myChart = this.getChart()
      await this.initChartData()
      this.chart = new Chart(myChart, {
        type: 'line',
        data: this.chartData
      })
    },

    async initChartData () {
      const datasets = await this.buildDatasets()
      this.chartData = {
        labels: [this.getHours()],
        datasets
      }
    },

    async buildDatasets () {
      const data = await this.$store.dispatch('sensor/getSensorData')
      const colors = ['rgb(255, 0, 0)', 'rgb(0, 255, 0)']
      const datasets = []
      if (!data) {
        datasets.push({
          label: 'teste',
          data: [1],
          fill: false,
          borderColor: colors[0],
          tension: 0
        })
        return datasets
      }
      Object.entries(data).forEach(([key, value], index) => {
        const data = {
          label: key,
          data: [value],
          fill: false,
          borderColor: colors[index],
          tension: 0.1
        }
        datasets.push(data)
      })
      return datasets
    },

    addDataToChart (data) {
      const hours = this.getHours()
      this.chartData.labels.push(hours)
      this.chartData.datasets.forEach((dataset) => {
        dataset.data.push(data[dataset.label])
      })
      this.chart.update()
    },

    getHours () {
      const today = new Date()
      return `${today.getHours()}:${today.getMinutes()}`
    },

    updateChart () {
      setInterval(async () => {
        const data = await this.$store.dispatch('sensor/getSensorData')
        if (!data || !Object.keys(data).length) {
          return
        }
        this.addDataToChart(data)
      }, 5000)
    }
  }
}
</script>
