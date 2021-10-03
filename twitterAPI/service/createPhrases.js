fs = require('fs')
const axios = require("axios");
const { JSDOM } = require("jsdom");
const Frase =  require('../models/Frase')

const url = 'https://www.pensador.com';


function capitalizeFirstLetter(string) {
    return string.charAt(0).toUpperCase() + string.slice(1);
}



async function getFrases(term){
    console.log('⌛ Buscando Frases...')
    const { count, rows } = await Frase.findAndCountAll({})
    if (count< 1){
        let pensador = await axios.get(`${url}/${term}`);
        let pensadorFrases = new JSDOM(pensador.data);
        let totalDeFrases = pensadorFrases.window.document.querySelector('.total').textContent
        totalDeFrases = totalDeFrases.replace('Cerca de ',"")
        totalDeFrases = totalDeFrases.replace(` frases e pensamentos: ${capitalizeFirstLetter(term)}`,"")
        let result = await axios.get(`http://localhost:3333/?term=${term}&max=${totalDeFrases}`)
        await Frase.bulkCreate(result.data.frases)
        console.log('✔️ Frases salvas\n')
    }else{
        console.log('✔️ Ja existem frases salvas no banco de dados\n')
    }
    
}

module.exports = {
    getFrases
}