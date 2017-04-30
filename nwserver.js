var http = require('http'),
    fs = require('fs'),
    indexsrv = require('serve-index'),
    servsrv = require('serve-static'),
    finalhandler = require('finalhandler');

var index = indexsrv('.', {'icons': true});
var serve = servsrv('.');

http.createServer(function (req, res) {

    console.log(req.url);

    if(req.url == "/logs/") {
        var done = finalhandler(req, res);
        index(req, res, done);
    }

    if(req.url.indexOf(".nmap") != -1) {
        fs.readFile(__dirname + req.url, function(err, data) {
            if(err) console.log(err);
            res.writeHead(200, {"Content-Type": "text/plain"});
            res.write(data);
            res.end();
        })
    }

    if(req.url.indexOf('.html') != -1 || req.url == "/"){ //req.url has the pathname, check if it conatins '.html'
        fs.readFile(__dirname + '/index.html', function (err, data) {
        if (err) console.log(err);
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        res.end();
      });

    }

    if(req.url.indexOf('.js') != -1){ //req.url has the pathname, check if it conatins '.js'

        fs.readFile(__dirname + '/static/js/script.js', function (err, data) {
        if (err) console.log(err);
        res.writeHead(200, {'Content-Type': 'text/javascript'});
        res.write(data);
        res.end();
      });

    }

    if(req.url.indexOf('.css') != -1){ //req.url has the pathname, check if it conatins '.css'

        fs.readFile(__dirname + '/static/css/style.css', function (err, data) {
        if (err) console.log(err);
        res.writeHead(200, {'Content-Type': 'text/css'});
        res.write(data);
        res.end();
      });
    }

}).listen(1337, '127.0.0.1');
console.log('Server running at http://127.0.0.1:1337/');
