//var http = require('http');
const http = require('http')
const os = require('os')

console.log("kubia server starting....")

//var handleRequest = function(request, response) {
var handler = function(request, response) {
    //console.log('Received request for URL: ' + request.url);
    console.log("Received request from " + request.connection.remoteAddress);
    response.writeHead(200);
    //response.end('Hello World!');
    response.end("You've hit " + os.hostname() + "\n");
};

var www = http.createServer(handler);
www.listen(8080);

