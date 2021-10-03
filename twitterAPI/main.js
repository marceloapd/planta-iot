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
    console.log(`Tamanho da frase gerada: ${randomPhrase[0].dataValues.texto.length}`)
    if(randomPhrase[0].dataValues.texto.length>157){
        return getRandomPhrase()
    }else{
        return randomPhrase[0].dataValues.texto
    }
}

async function dangerAlerts(){
    checkSensor = setInterval(async function(){
        let sensor = await apiEsp.getSensorData()
        if(sensor<1 || sensor>90){
            tweetFunctions.sendTweet(`${config.twitterUser} ${recommendations.getAlerts(sensor)}`)
            duration = (60000*60)*14 // 6 horas (60000*60)*6
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
    const msg = await getRandomPhrase()
    let sensor = await recommendations.getRecommendations()
    tweetFunctions.sendTweet(`${msg}\n\n${config.twitterUser} ${sensor}\n\nBom dia.`)
}

cron.schedule('0 8 * * *', () => {
    sendMorningTweet()
});

dangerAlerts()