const axios = require("axios");
const readline = require('readline');
const tweetFunctions = require('../service/tweetFunctions')
const config = require('../confg/confg.json')

let flag = true

async function getSensorData(){
    let sensor 
    try{
        sensor = await axios.get('http://186.209.191.126:5000/sensors', {timeout: 6000})
        if(sensor.status === 200){
        sensorValue = parseInt(sensor.data.humidity)
        flag = true
        return {value: sensorValue, status: sensor.status}
        }
    }catch(error){
        if(flag){
            tweetFunctions.sendTweet(`${config.twitterUser} estou com problemas de conexão\n\nERROR: ${error.toJSON().code}`)
            console.log(`\nproblema de conexão ERROR: ${error.toJSON().code}`)
            flag = false
        }
        return {value: 'off', status: 400}
    }
}

function writeLog(frase, cursor) {
    readline.clearLine(process.stdout)
    readline.cursorTo(process.stdout, cursor)
    process.stdout.write(frase);
}


setInterval(async function(){
    try{
        sensor = await getSensorData()
    }catch(error){
        console.log(error)
    }
    if(sensor.value){
        writeLog(`Umidade do solo: ${sensor.value}%`,0)
        return sensor
    }
    return
},10000)


module.exports = {
    getSensorData
}

// tweetFunctions.sendTweet(`${config.twitterUser} estou com problemas de conexão erro: ${error.toJSON().code}`)
// console.log(`\n${config.twitterUser} estou com problemas de conexão erro: ${error.toJSON().code}`)