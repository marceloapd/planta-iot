const { DataTypes } = require('sequelize')
const db = require('../database/db')

const Frase = db.define('Frase', {
    autor: {
        type: DataTypes.STRING(157)
    },
    texto: {
        type: DataTypes.STRING(157),
    }
},
    {
        freezeTableName: true
    }
)


// Frase.sync({alter: true}) // comente se o db estiver populado


module.exports = Frase