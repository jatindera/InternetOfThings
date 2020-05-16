var mqtt = require('mqtt')
var options = {
    username: '****************',
    password: '***********',
    port: 1883
}

var mqttHelper = function () { };

mqttHelper.prototype.carCommand = (command) => {
    return new Promise((resolve, reject) => {
        var client = mqtt.connect('mqtt://maqiatto.com', options)
        client.on('connect', function () {
            console.log("MQTT connection is created")
            console.log(command)
            if (command.toLowerCase() === 'forward' || command.toLowerCase() === 'back'|| command.toLowerCase() === 'left' || command.toLowerCase() === 'right' || command.toLowerCase() === 'stop') {
                client.publish('**************', command);
                client.end();
                return resolve({ 'success': command });
            }
            else {
                console.log('There is some error in MQTT...')
                client.end();
                return reject('Error while executing MQTT Helper')
            }
        })
    })

}

module.exports = new mqttHelper();