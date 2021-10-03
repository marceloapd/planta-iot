export const state = () => ({
  sensors: {}
})

export const mutations = {
  set (state, [key, value]) {
    state[key] = value
  }
}

export const actions = {
  async getSensorData ({ _ }) {
    try {
      const response = await this.$axios.get('http://192.168.1.11:80/sensors')
      console.log(response.data)
      return response.data || null
    } catch (error) {
      console.log(error.message)
    }
  }
}
