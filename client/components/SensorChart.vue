<template>
  <div class="row">
    <div class="col-12 col-md-8">
      <canvas
        id="myChart"
        ref="myChart"
        class="chart"
        style="position: relative; height:40vh; width:80vw"
      />
    </div>
    <div class="col-12 col-md-4">
      <div class="card text-center">
        <div class="card-header">
          Informações
        </div>
        <div class="card-body">
          <h5 class="card-title">
            Special title treatment
          </h5>
          <p class="card-text">
            Lorem ipsum dolor sit amet consectetur adipisicing elit. Voluptatum
            dolorem vel dicta debitis quidem numquam enim ea aperiam temporibus
            nobis mollitia, dignissimos illo? Maiores rerum dolor nemo quisquam
            delectus dolore.
          </p>
          <button class="btn btn-primary">
            Atualizar
          </button>
        </div>
        <div class="card-footer text-muted">
          2 days ago
        </div>
      </div>
    </div>
  </div>
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
    await this.automaticUpdateChart()
  },

  methods: {
    // Register chart.js elements
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

    // update chart automatically every 5 seconds
    automaticUpdateChart () {
      setInterval(async () => {
        await this.updateChart()
      }, 5000)
    },

    // update chart manually when a button is clicked
    async updateChart () {
      const data = await this.$store.dispatch('sensor/getSensorData')
      if (!data || !Object.keys(data).length) {
        return
      }
      this.addDataToChart(data)
    },

    // Initialize chart
    async initChart () {
      this.registerChartElements()
      const myChart = this.$refs.myChart.getContext('2d')
      await this.initChartData()
      this.chart = new Chart(myChart, {
        type: 'line',
        data: this.chartData
      })
    },

    // Initialize chart data
    async initChartData () {
      const datasets = await this.$store.dispatch('sensor/buildInitialDatasets')
      this.chartData = {
        labels: [this.getHours()],
        datasets
      }
    },

    // Add data to chart
    addDataToChart (data) {
      let hasData = false
      this.chartData.datasets.forEach((dataset) => {
        const label = dataset.label
        if (data[label] !== undefined) {
          dataset.data.push(data[label])
          dataset.data = this.truncDataset(dataset.data)
          hasData = true
        }
      })
      if (hasData) {
        const hours = this.getHours()
        this.chartData.labels.push(hours)
        this.chartData.labels = this.truncDataset(this.chartData.labels)
        this.chart.update()
      }
    },

    // Truncate datasets to max length
    truncDataset (data) {
      if (data.length >= 20) {
        data.shift()
      }
      return [...data]
    },

    // Get that sensor data as added to the chart
    getHours () {
      const today = new Date()
      return `${today.getHours()}:${today.getMinutes()}`
    }
  }
}
</script>

<style scoped></style>
