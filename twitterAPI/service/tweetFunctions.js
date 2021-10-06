var Twitter = require('twitter');
const config = require('../confg/confg.json')

var client = new Twitter({
    consumer_key: config.consumerKey,
    consumer_secret: config.consumerSecret,
    access_token_key: config.accessTokenKey,
    access_token_secret: config.accessTokenSecret
});

async function sendTweet(status){
    await client.post('statuses/update', {status: status }, function(error, tweet, response) {
        if (!error) {
            // console.log(tweet);
            console.log(`\nTweet enviado: ${status}\n`)
        }else{
            console.log(`\nFalha ao enviar o tweet: ${status}\n\nError: ${response.body}\n`)
        }
    });
}



module.exports = {
    sendTweet
}