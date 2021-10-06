const Frase =  require('./models/Frase')
const {Sequelize} = require('sequelize');
const readline = require('readline');

const tweetFunctions = require('./service/tweetFunctions')
const config = require('./confg/confg.json')
const createPhrases = require('./service/createPhrases')
const recommendations = require('./service/getSubPhrases')
const apiEsp = require("./service/getSensorData");
var cron = require('node-cron');

let duration = 5000


createPhrases.getFrases(config.phraseType) // comente se o db estiver populado

async function getRandomPhrase(){
    let randomPhrase = await Frase.findAll({ order: Sequelize.literal('random()'), limit: 1 })
    if(randomPhrase[0].dataValues.texto.length>157){
        return getRandomPhrase()
    }else{
        return randomPhrase[0].dataValues.texto
    }
}

async function dangerAlerts(){
    checkSensor = setInterval(async function(){
        let sensor = await apiEsp.getSensorData()
        if(sensor.value<1 || sensor.value>90){
            tweetFunctions.sendTweet(`${config.twitterUser} ${recommendations.getAlerts(sensor.value)}`)
            duration = (60000*60)*14 // 14 horas 
            clearInterval(checkSensor)
            await readline.clearLine(process.stdout);
            await readline.cursorTo(process.stdout, 0);
            dangerAlerts()
        }else{
            duration = 5000
        }
    }, duration)
}

async function sendMorningTweet(){
    let sensor = await apiEsp.getSensorData()
    const msg = await getRandomPhrase()
    if(sensor.status === 200){
        readline.clearLine(process.stdout)
        readline.cursorTo(process.stdout, 0)
        let recommendation = await recommendations.getRecommendations(sensor.value)
        tweetFunctions.sendTweet(`${msg}\n\n${config.twitterUser} a umidade do meu solo hoje é de ${sensor.value}% ${recommendation}\n\nBom dia.`)
    }else{
        tweetFunctions.sendTweet(`${config.twitterUser} não estou conseguindo se comunicar com meu microcontrolador, pode olhar oque houve ?\n\nsem essa comunicação não consigo entender meus sensores.\n\nBom dia pra quem neh ?`)
    }
}

cron.schedule('0 8 * * *', () => {
    sendMorningTweet()
});

dangerAlerts()
