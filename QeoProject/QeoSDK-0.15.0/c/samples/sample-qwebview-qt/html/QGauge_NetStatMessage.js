/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/
if (typeof Qeo === "undefined") {Qeo = {registerType: function(td) {this.ttr.push(td);},ttr: []};}

Qeo.registerType({
"topic": "org::qeo::sample::gauge::NetStatMessage",
"behavior": "state",
"properties": {
"deviceId": {
"type": "object", "key": true,
"item": "org::qeo::system::DeviceId"
}, "ifName": {
"type": "string", "key": true
}, "bytesIn": {
"type": "int64"
}, "packetsIn": {
"type": "int64"
}, "bytesOut": {
"type": "int64"
}, "packetsOut": {
"type": "int64"
}, "timestamp": {
"type": "int64"
}
}
});

