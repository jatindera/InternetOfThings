var mqtt = require('mqtt')
var options = {
    username: '*****',
    password: '*****',
    port: 1883
}

var mqttHelper = function () { };

mqttHelper.prototype.toggleCommand = (command) => {
    return new Promise((resolve, reject) => {
        var client = mqtt.connect('mqtt://maqiatto.com', options)
        client.on('connect', function () {
            console.log("MQTT connection is created")
            console.log(command)
            if (command.toLowerCase() === 'on' || command.toLowerCase() === 'off') {
                client.publish('*************Your topic name***************', command.toUpperCase());
                client.end();
                return resolve({ 'success': `light ${command}` });
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