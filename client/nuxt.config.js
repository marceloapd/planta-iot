export default {
  head: {
    title: 'Plant IOT',
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { hid: 'description', name: 'description', content: '' },
      { name: 'format-detection', content: 'telephone=no' }
    ],
    link: [
      { rel: 'icon', type: 'image/x-icon', href: '/favicon.ico' },
      {
        href:
          'https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/css/bootstrap.min.css',
        rel: 'stylesheet',
        crossorigin: 'anonymous',
        integrity:
          'sha384-F3w7mX95PdgyTmZZMECAngseQB83DfGTowi0iMjiWaeVhAn4FJkqJByhZMI3AhiU'
      }
    ],
    scripts: [
      {
        src:
          'https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/js/bootstrap.bundle.min.js',
        integrity:
          'sha384-/bQdsTh/da6pkI1MST/rWKFNjaCP5gBSY4sEBT38Q/9RBh9AH40zEOg7Hlq2THRZ',
        crossorigin: 'anonymous'
      }
    ]
  },

  server: {
    host: 'localhost',
    port: 3000
  },

  css: [],

  plugins: [],

  components: true,

  buildModules: ['@nuxtjs/eslint-module'],

  modules: ['@nuxtjs/axios', '@nuxtjs/pwa'],

  axios: {},

  pwa: {
    manifest: {
      lang: 'pt-br'
    }
  },

  build: {},

  loading: false
}
