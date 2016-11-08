var express = require('express'), 
httpserver = require('http');
var http = require('http'),
    fs = require('fs');

var app = express();
var ws = httpserver.createServer(app);

ws.listen(9000);
console.log("Web Service escutando em http://localhost:9000");





  var id_antena;
  var id_veiculo;
  var id_cruzamento;
  var qtd_veiculo;

  var sessionKey;
  

 app.use('/api', express.static('api'));

 app.get('/', function(req, res) {

  id_antena = req.query.idantena;
  id_veiculo = req.query.idveiculo;
  id_cruzamento = req.query.idcruzamento;
  qtd_veiculo = req.query.qtdveiculo;
  
  //   localStorage.setItem("id_veiculo2", id_veiculo);
     
  //res.send({ user: id_veiculo });
  res.end(fs.readFileSync("view/WebSocket.html"));
  //res.send(id_antena + ' ' + id_veiculo + ' ' + id_cruzamento + ' ' + qtd_veiculo);
  console.log(id_antena + ' ' + id_veiculo + ' ' + id_cruzamento + ' ' + qtd_veiculo);

});


