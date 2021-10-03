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
  ArcElement,
  LineElement,
  BarElement,
  PointElement,
  BarController,
  BubbleController,
  DoughnutController,
  LineController,
  PieController,
  PolarAreaController,
  RadarController,
  ScatterController,
  CategoryScale,
  LinearScale,
  LogarithmicScale,
  RadialLinearScale,
  TimeScale,
  TimeSeriesScale,
  Decimation,
  Filler,
  Legend,
  Title,
  Tooltip,
  SubTitle
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
        ArcElement,
        LineElement,
        BarElement,
        PointElement,
        BarController,
        BubbleController,
        DoughnutController,
        LineController,
        PieController,
        PolarAreaController,
        RadarController,
        ScatterController,
        CategoryScale,
        LinearScale,
        LogarithmicScale,
        RadialLinearScale,
        TimeScale,
        TimeSeriesScale,
        Decimation,
        Filler,
        Legend,
        Title,
        Tooltip,
        SubTitle
      )
    },

    async initChart () {
      this.registerChartElements()
      const myChart = this.$refs.myChart.getContext('2d')
      await this.initChartData()
      this.chart = new Chart(myChart, {
        type: 'line',
        data: this.chartData
      })
    },

    async initChartData () {
      const datasets = await this.$store.dispatch('sensor/buildInitialDatasets')
      this.chartData = {
        labels: [this.getHours()],
        datasets
      }
    },

    addDataToChart (data) {
      let hasData = false
      this.chartData.datasets.forEach((dataset) => {
        const label = dataset.label
        if (data[label] !== undefined) {
          dataset.data.push(data[label])
          hasData = true
        }
      })
      if (hasData) {
        const hours = this.getHours()
        this.chartData.labels.push(hours)
        this.chart.update()
      }
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
