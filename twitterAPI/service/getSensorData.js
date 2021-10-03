const axios = require("axios");
const readline = require('readline');
const tweetFunctions = require('../service/tweetFunctions')

var flag = true

async function getSensorData(){
    let sensor = await axios.get('http://192.168.1.13/sensors')
    sensor = parseInt(sensor.data.humidity)
    return sensor
}

function writeWaitingPercent(p) {
    readline.clearLine(process.stdout);
    readline.cursorTo(process.stdout, 0);
    process.stdout.write(`Umidade do solo: ${p}%`);
}


setInterval(async function(){
    sensor = await getSensorData()
    writeWaitingPercent(sensor)
    return sensor
},1000)


module.exports = {
    getSensorData
}

// tweetFunctions.sendTweet(`${config.twitterUser} estou com problemas de conexão erro: ${error.toJSON().code}`)
// console.log(`\n${config.twitterUser} estou com problemas de conexão erro: ${error.toJSON().code}`)