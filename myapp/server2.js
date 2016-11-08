var http = require('http').createServer(servidor);
var fs = require('fs');

function servidor(requisicao, resposta){
  var url = requisicao.url;
  if(url == '/'){
    resposta.writeHead(200);
    resposta.end(fs.readFileSync('view/index.html'));
  }else if(url == '/contatos'){
      resposta.writeHead(200);
      resposta.end(fs.readFileSync('ejemplo-SOFIA2_API_JS_2.8AWebsocket.html'));
  }else{
    resposta.writeHead(200);
    resposta.end("<h1>Error: 404, nada encontrado</h1>");
  }
};

http.listen(3000, function(){
  console.log("Servidor On-line");
});