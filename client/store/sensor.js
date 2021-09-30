export const state = () => ({
  sensors: {}
})

export const mutations = {
  set (state, [key, value]) {
    state[key] = value
  }
}

export const actions = {
  getSensorData ({ _ }) {
    console.log('WebSocket')
    const connection = new WebSocket('ws://192.168.1.10:81')
    connection.onmessage = (event) => {
      console.log(event.data)
    }
  }
}
