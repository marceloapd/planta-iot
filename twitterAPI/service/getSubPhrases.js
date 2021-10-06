const umidadeValues = {
    alerts : {
        0: "Perdi o sinal do meu sensor, da uma olhada nele pra mim ? ",
        100: 'socorro alguem me deu muita agua!, com meu solo encharcado não consigo respirar\n\nTutorial para me salvar: Se eu estiver com uma aparencia "triste" me replante e apare todas as raízes pretas ou pastosas, se eu estiver aparentemente bem não me regue ate que eu te peça.'
    },
    1: "TO MORRENDO",
    10: "um valor extramente baixo, posso morrer se continuar assim",
    20: "um valor muito baixo, me irrigue da proxima vez que me ver",
    30: "um valor baixo, preciso de agua para continuar crescendo.",
    40: "um pouco abaixo do ideal, me molhe um pouco pela parte da manhã",
    50: "que é o ideal, obrigado por cuidar de mim",
    60: "um pouco acima do ideal, da proxima vez regue com menos agua",
    70: "acima do ideal, so me molhe se eu te pedir",
    90: "muito acima do ideal, não me molhe ate que eu te peça.",
    96: "extremamente acima do ideal, posso morrer !",
}

async function getRecommendations(sensor){

    const closest = Object.keys(umidadeValues).reduce((a, b) => {
        return Math.abs(b - sensor) < Math.abs(a - sensor) ? b : a;
    });
        return umidadeValues[closest]
}

function getAlerts(sensor){
    
    const closest = Object.keys(umidadeValues.alerts).reduce((a, b) => {
        return Math.abs(b - sensor) < Math.abs(a - sensor) ? b : a;
    });
    return umidadeValues.alerts[closest]
}


module.exports = {
    getRecommendations,
    getAlerts
}