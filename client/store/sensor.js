export const state = () => ({
  sensors: {}
})

export const mutations = {
  set (state, [key, value]) {
    state[key] = value
  }
}

export const actions = {
  async getSensorData ({ dispatch }) {
    try {
      const response = await this.$axios.get('http://192.168.1.11:80/sensors')
      const translatedData = dispatch('translateChartLabels', response.data)
      return translatedData || null
    } catch (error) {
      return null
    }
  },

  translateChartLabels ({ _ }, data) {
    const translations = {
      humidity: 'Umidade'
    }
    const translatedData = {}
    Object.keys(data).forEach((key) => {
      translatedData[translations[key]] = data[key]
    })
    return translatedData
  },

  async buildInitialDatasets ({ dispatch }) {
    const data = await dispatch('getSensorData')
    const colors = ['rgb(255, 0, 0)', 'rgb(0, 255, 0)']
    let datasets = []
    if (!data) {
      datasets = [{
        label: 'default',
        data: [1],
        borderColor: colors[0]
      }]
      return datasets
    }
    Object.entries(data).forEach(([key, value], index) => {
      const label = key
      const data = {
        label,
        data: [value],
        borderColor: colors[index]
      }
      datasets.push(data)
    })
    return datasets
  }
}
