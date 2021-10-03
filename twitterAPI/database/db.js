const {Sequelize} = require('sequelize');


const sequelize = new Sequelize({
    dialect: 'sqlite',
    storage: './database/database.sqlite',
    logging: false,
});

sequelize.authenticate().then(
    console.log('✔️ Banco de dados conectado')
)


module.exports = sequelize