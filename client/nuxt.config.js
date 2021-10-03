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
      { rel: 'icon', type: 'image/x-icon', href: '/favicon.ico' }
    ]
  },

  server: {
    host: 'localhost',
    port: 3000
  },

  css: [
  ],

  plugins: [
  ],

  components: true,

  buildModules: [
    '@nuxtjs/eslint-module',
    '@nuxtjs/tailwindcss'
  ],

  modules: [
    '@nuxtjs/axios',
    '@nuxtjs/pwa'
  ],

  axios: {},

  pwa: {
    manifest: {
      lang: 'pt-br'
    }
  },

  build: {
  },

  loading: false
}
